#include "sysconfig.h"
#include "sysdeps.h"
#include "options.h"
#include "memory.h"
#include "custom.h"
#include "events.h"
#include "newcpu.h"
#include "machdep/m68kops.h"
#include "cpu_prefetch.h"
#include "cputbl.h"
#define CPUFUNC(x) x##_ff
#define SET_CFLG_ALWAYS(flags, x) SET_CFLG(flags, x)
#define SET_NFLG_ALWAYS(flags, x) SET_NFLG(flags, x)
#ifdef NOFLAGS
#include "noflags.h"
#endif

#if !defined(PART_1) && !defined(PART_2) && !defined(PART_3) && !defined(PART_4) && !defined(PART_5) && !defined(PART_6) && !defined(PART_7) && !defined(PART_8)
#define PART_1 1
#define PART_2 1
#define PART_3 1
#define PART_4 1
#define PART_5 1
#define PART_6 1
#define PART_7 1
#define PART_8 1
#endif

#ifdef PART_1
/* OR.B #<data>.B,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0000_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* OR.B #<data>.B,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0010_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 20;
}
/* OR.B #<data>.B,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0018_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 20;
}
/* OR.B #<data>.B,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0020_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 22;
}
/* OR.B #<data>.B,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0028_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 24;
}
/* OR.B #<data>.B,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0030_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
{	uae_s8 dst = get_byte (dsta);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 26;
}
/* OR.B #<data>.B,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0038_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 24;
}
/* OR.B #<data>.B,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0039_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 8);
return CYCLE_UNIT / 2 * 28;
}
/* ORSR.B #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_003c_5)(uae_u32 opcode, struct regstruct *regs)
{
{	MakeSR (regs);
{	uae_s16 src = get_word_prefetch (regs, 4);
	src &= 0xFF;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	regs->sr |= src;
	MakeFromSR (regs);
}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* OR.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0040_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* OR.W #<data>.W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0050_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2152;
	}
{{	uae_s16 dst = get_word (dsta);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel2152: ;
return CYCLE_UNIT / 2 * 16;
}
/* OR.W #<data>.W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0058_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2153;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel2153: ;
return CYCLE_UNIT / 2 * 16;
}
/* OR.W #<data>.W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0060_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2154;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel2154: ;
return CYCLE_UNIT / 2 * 18;
}
/* OR.W #<data>.W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0068_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2155;
	}
{{	uae_s16 dst = get_word (dsta);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2155: ;
return CYCLE_UNIT / 2 * 20;
}
/* OR.W #<data>.W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0070_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2156;
	}
{{	uae_s16 dst = get_word (dsta);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2156: ;
return CYCLE_UNIT / 2 * 22;
}
/* OR.W #<data>.W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0078_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2157;
	}
{{	uae_s16 dst = get_word (dsta);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2157: ;
return CYCLE_UNIT / 2 * 20;
}
/* OR.W #<data>.W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0079_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2158;
	}
{{	uae_s16 dst = get_word (dsta);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 8);
endlabel2158: ;
return CYCLE_UNIT / 2 * 24;
}
/* ORSR.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_007c_5)(uae_u32 opcode, struct regstruct *regs)
{
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2159; }
{	MakeSR (regs);
{	uae_s16 src = get_word_prefetch (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	regs->sr |= src;
	MakeFromSR (regs);
}}}	m68k_incpc (regs, 4);
endlabel2159: ;
return CYCLE_UNIT / 2 * 8;
}
/* OR.L #<data>.L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0080_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 12;
}
/* OR.L #<data>.L,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0090_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2161;
	}
{{	uae_s32 dst = get_long (dsta);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2161: ;
return CYCLE_UNIT / 2 * 28;
}
/* OR.L #<data>.L,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0098_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2162;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2162: ;
return CYCLE_UNIT / 2 * 28;
}
/* OR.L #<data>.L,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_00a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2163;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2163: ;
return CYCLE_UNIT / 2 * 30;
}
/* OR.L #<data>.L,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_00a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2164;
	}
{{	uae_s32 dst = get_long (dsta);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 8);
endlabel2164: ;
return CYCLE_UNIT / 2 * 32;
}
/* OR.L #<data>.L,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_00b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 8));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2165;
	}
{{	uae_s32 dst = get_long (dsta);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 8);
endlabel2165: ;
return CYCLE_UNIT / 2 * 34;
}
/* OR.L #<data>.L,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_00b8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2166;
	}
{{	uae_s32 dst = get_long (dsta);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 8);
endlabel2166: ;
return CYCLE_UNIT / 2 * 32;
}
/* OR.L #<data>.L,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_00b9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2167;
	}
{{	uae_s32 dst = get_long (dsta);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 12);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 10);
endlabel2167: ;
return CYCLE_UNIT / 2 * 36;
}
/* BTST.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0100_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 31;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* MVPMR.W (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_0108_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr memp = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_u16 val = (get_byte (memp) << 8) + get_byte (memp + 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* BTST.B Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0110_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 8;
}
/* BTST.B Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0118_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 8;
}
/* BTST.B Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0120_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 10;
}
/* BTST.B Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0128_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* BTST.B Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0130_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 14;
}
/* BTST.B Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0138_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* BTST.B Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0139_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 16;
}
/* BTST.B Dn,(d16,PC) */
unsigned long REGPARAM2 CPUFUNC(op_013a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = 2;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_getpc (regs) + 2;
	dsta += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* BTST.B Dn,(d8,PC,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_013b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = 3;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr tmppc;
	uaecptr dsta;
	tmppc = m68k_getpc (regs) + 2;
	dsta = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 14;
}
/* BTST.B Dn,#<data>.B */
unsigned long REGPARAM2 CPUFUNC(op_013c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = (uae_u8)get_word_prefetch (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* BCHG.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0140_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 31;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	m68k_dreg (regs, dstreg) = (dst);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* MVPMR.L (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_0148_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr memp = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_u32 val = (get_byte (memp) << 24) + (get_byte (memp + 2) << 16)
              + (get_byte (memp + 4) << 8) + get_byte (memp + 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (val);
}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* BCHG.B Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0150_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* BCHG.B Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0158_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* BCHG.B Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0160_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* BCHG.B Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0168_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* BCHG.B Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0170_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* BCHG.B Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0178_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* BCHG.B Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0179_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* BCHG.B Dn,(d16,PC) */
unsigned long REGPARAM2 CPUFUNC(op_017a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = 2;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_getpc (regs) + 2;
	dsta += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* BCHG.B Dn,(d8,PC,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_017b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = 3;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr tmppc;
	uaecptr dsta;
	tmppc = m68k_getpc (regs) + 2;
	dsta = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* BCLR.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0180_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 31;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	m68k_dreg (regs, dstreg) = (dst);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* MVPRM.W Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0188_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
	uaecptr memp = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	put_byte (memp, src >> 8); put_byte (memp + 2, src);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* BCLR.B Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0190_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* BCLR.B Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0198_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* BCLR.B Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_01a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* BCLR.B Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_01a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* BCLR.B Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_01b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* BCLR.B Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_01b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* BCLR.B Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_01b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* BCLR.B Dn,(d16,PC) */
unsigned long REGPARAM2 CPUFUNC(op_01ba_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = 2;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_getpc (regs) + 2;
	dsta += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* BCLR.B Dn,(d8,PC,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_01bb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = 3;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr tmppc;
	uaecptr dsta;
	tmppc = m68k_getpc (regs) + 2;
	dsta = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* BSET.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_01c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 31;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	m68k_dreg (regs, dstreg) = (dst);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* MVPRM.L Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_01c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
	uaecptr memp = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	put_byte (memp, src >> 24); put_byte (memp + 2, src >> 16);
	put_byte (memp + 4, src >> 8); put_byte (memp + 6, src);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* BSET.B Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_01d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* BSET.B Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_01d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* BSET.B Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_01e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* BSET.B Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_01e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* BSET.B Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_01f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* BSET.B Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_01f8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* BSET.B Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_01f9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* BSET.B Dn,(d16,PC) */
unsigned long REGPARAM2 CPUFUNC(op_01fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = 2;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_getpc (regs) + 2;
	dsta += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* BSET.B Dn,(d8,PC,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_01fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = 3;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr tmppc;
	uaecptr dsta;
	tmppc = m68k_getpc (regs) + 2;
	dsta = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* AND.B #<data>.B,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0200_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* AND.B #<data>.B,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0210_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 20;
}
/* AND.B #<data>.B,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0218_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 20;
}
/* AND.B #<data>.B,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0220_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 22;
}
/* AND.B #<data>.B,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0228_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 24;
}
/* AND.B #<data>.B,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0230_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
{	uae_s8 dst = get_byte (dsta);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 26;
}
/* AND.B #<data>.B,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0238_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 24;
}
/* AND.B #<data>.B,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0239_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 8);
return CYCLE_UNIT / 2 * 28;
}
/* ANDSR.B #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_023c_5)(uae_u32 opcode, struct regstruct *regs)
{
{	MakeSR (regs);
{	uae_s16 src = get_word_prefetch (regs, 4);
	src |= 0xFF00;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	regs->sr &= src;
	MakeFromSR (regs);
}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* AND.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0240_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* AND.W #<data>.W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0250_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2223;
	}
{{	uae_s16 dst = get_word (dsta);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel2223: ;
return CYCLE_UNIT / 2 * 16;
}
/* AND.W #<data>.W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0258_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2224;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel2224: ;
return CYCLE_UNIT / 2 * 16;
}
/* AND.W #<data>.W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0260_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2225;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel2225: ;
return CYCLE_UNIT / 2 * 18;
}
/* AND.W #<data>.W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0268_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2226;
	}
{{	uae_s16 dst = get_word (dsta);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2226: ;
return CYCLE_UNIT / 2 * 20;
}
/* AND.W #<data>.W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0270_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2227;
	}
{{	uae_s16 dst = get_word (dsta);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2227: ;
return CYCLE_UNIT / 2 * 22;
}
/* AND.W #<data>.W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0278_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2228;
	}
{{	uae_s16 dst = get_word (dsta);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2228: ;
return CYCLE_UNIT / 2 * 20;
}
/* AND.W #<data>.W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0279_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2229;
	}
{{	uae_s16 dst = get_word (dsta);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 8);
endlabel2229: ;
return CYCLE_UNIT / 2 * 24;
}
/* ANDSR.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_027c_5)(uae_u32 opcode, struct regstruct *regs)
{
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2230; }
{	MakeSR (regs);
{	uae_s16 src = get_word_prefetch (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	regs->sr &= src;
	MakeFromSR (regs);
}}}	m68k_incpc (regs, 4);
endlabel2230: ;
return CYCLE_UNIT / 2 * 8;
}
/* AND.L #<data>.L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0280_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 12;
}
/* AND.L #<data>.L,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0290_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2232;
	}
{{	uae_s32 dst = get_long (dsta);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2232: ;
return CYCLE_UNIT / 2 * 28;
}
/* AND.L #<data>.L,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0298_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2233;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2233: ;
return CYCLE_UNIT / 2 * 28;
}
/* AND.L #<data>.L,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_02a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2234;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2234: ;
return CYCLE_UNIT / 2 * 30;
}
/* AND.L #<data>.L,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_02a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2235;
	}
{{	uae_s32 dst = get_long (dsta);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 8);
endlabel2235: ;
return CYCLE_UNIT / 2 * 32;
}
/* AND.L #<data>.L,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_02b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 8));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2236;
	}
{{	uae_s32 dst = get_long (dsta);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 8);
endlabel2236: ;
return CYCLE_UNIT / 2 * 34;
}
/* AND.L #<data>.L,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_02b8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2237;
	}
{{	uae_s32 dst = get_long (dsta);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 8);
endlabel2237: ;
return CYCLE_UNIT / 2 * 32;
}
/* AND.L #<data>.L,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_02b9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2238;
	}
{{	uae_s32 dst = get_long (dsta);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 12);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 10);
endlabel2238: ;
return CYCLE_UNIT / 2 * 36;
}
/* SUB.B #<data>.B,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0400_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* SUB.B #<data>.B,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0410_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 20;
}
/* SUB.B #<data>.B,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0418_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 20;
}
/* SUB.B #<data>.B,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0420_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 22;
}
/* SUB.B #<data>.B,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0428_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 24;
}
/* SUB.B #<data>.B,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0430_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 26;
}
/* SUB.B #<data>.B,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0438_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 24;
}
/* SUB.B #<data>.B,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0439_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 8);
return CYCLE_UNIT / 2 * 28;
}
/* SUB.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0440_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* SUB.W #<data>.W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0450_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2248;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel2248: ;
return CYCLE_UNIT / 2 * 16;
}
/* SUB.W #<data>.W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0458_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2249;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel2249: ;
return CYCLE_UNIT / 2 * 16;
}
/* SUB.W #<data>.W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0460_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2250;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel2250: ;
return CYCLE_UNIT / 2 * 18;
}
/* SUB.W #<data>.W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0468_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2251;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel2251: ;
return CYCLE_UNIT / 2 * 20;
}
/* SUB.W #<data>.W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0470_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2252;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel2252: ;
return CYCLE_UNIT / 2 * 22;
}
/* SUB.W #<data>.W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0478_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2253;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel2253: ;
return CYCLE_UNIT / 2 * 20;
}
/* SUB.W #<data>.W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0479_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2254;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 8);
endlabel2254: ;
return CYCLE_UNIT / 2 * 24;
}
/* SUB.L #<data>.L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0480_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 12;
}
/* SUB.L #<data>.L,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0490_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2256;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel2256: ;
return CYCLE_UNIT / 2 * 28;
}
/* SUB.L #<data>.L,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0498_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2257;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel2257: ;
return CYCLE_UNIT / 2 * 28;
}
/* SUB.L #<data>.L,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_04a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2258;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel2258: ;
return CYCLE_UNIT / 2 * 30;
}
/* SUB.L #<data>.L,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_04a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2259;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 8);
endlabel2259: ;
return CYCLE_UNIT / 2 * 32;
}
/* SUB.L #<data>.L,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_04b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 8));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2260;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 8);
endlabel2260: ;
return CYCLE_UNIT / 2 * 34;
}
/* SUB.L #<data>.L,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_04b8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2261;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 8);
endlabel2261: ;
return CYCLE_UNIT / 2 * 32;
}
/* SUB.L #<data>.L,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_04b9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2262;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 12);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 10);
endlabel2262: ;
return CYCLE_UNIT / 2 * 36;
}
/* ADD.B #<data>.B,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0600_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* ADD.B #<data>.B,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0610_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 20;
}
/* ADD.B #<data>.B,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0618_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 20;
}
/* ADD.B #<data>.B,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0620_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 22;
}
/* ADD.B #<data>.B,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0628_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 24;
}
/* ADD.B #<data>.B,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0630_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 26;
}
/* ADD.B #<data>.B,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0638_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 24;
}
/* ADD.B #<data>.B,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0639_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 8);
return CYCLE_UNIT / 2 * 28;
}
/* ADD.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0640_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* ADD.W #<data>.W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0650_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2272;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel2272: ;
return CYCLE_UNIT / 2 * 16;
}
/* ADD.W #<data>.W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0658_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2273;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel2273: ;
return CYCLE_UNIT / 2 * 16;
}
/* ADD.W #<data>.W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0660_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2274;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel2274: ;
return CYCLE_UNIT / 2 * 18;
}
/* ADD.W #<data>.W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0668_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2275;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel2275: ;
return CYCLE_UNIT / 2 * 20;
}
/* ADD.W #<data>.W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0670_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2276;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel2276: ;
return CYCLE_UNIT / 2 * 22;
}
/* ADD.W #<data>.W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0678_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2277;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel2277: ;
return CYCLE_UNIT / 2 * 20;
}
/* ADD.W #<data>.W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0679_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2278;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 8);
endlabel2278: ;
return CYCLE_UNIT / 2 * 24;
}
/* ADD.L #<data>.L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0680_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 12;
}
/* ADD.L #<data>.L,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0690_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2280;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel2280: ;
return CYCLE_UNIT / 2 * 28;
}
/* ADD.L #<data>.L,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0698_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2281;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel2281: ;
return CYCLE_UNIT / 2 * 28;
}
/* ADD.L #<data>.L,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_06a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2282;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel2282: ;
return CYCLE_UNIT / 2 * 30;
}
/* ADD.L #<data>.L,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_06a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2283;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 8);
endlabel2283: ;
return CYCLE_UNIT / 2 * 32;
}
/* ADD.L #<data>.L,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_06b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 8));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2284;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 8);
endlabel2284: ;
return CYCLE_UNIT / 2 * 34;
}
/* ADD.L #<data>.L,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_06b8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2285;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 8);
endlabel2285: ;
return CYCLE_UNIT / 2 * 32;
}
/* ADD.L #<data>.L,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_06b9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2286;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 12);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 10);
endlabel2286: ;
return CYCLE_UNIT / 2 * 36;
}
/* BTST.L #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0800_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 31;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* BTST.B #<data>.W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0810_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* BTST.B #<data>.W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0818_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* BTST.B #<data>.W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0820_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 14;
}
/* BTST.B #<data>.W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0828_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 16;
}
/* BTST.B #<data>.W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0830_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 18;
}
/* BTST.B #<data>.W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0838_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 16;
}
/* BTST.B #<data>.W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0839_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 8);
return CYCLE_UNIT / 2 * 20;
}
/* BTST.B #<data>.W,(d16,PC) */
unsigned long REGPARAM2 CPUFUNC(op_083a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = 2;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_getpc (regs) + 4;
	dsta += (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 16;
}
/* BTST.B #<data>.W,(d8,PC,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_083b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = 3;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr tmppc;
	uaecptr dsta;
	tmppc = m68k_getpc (regs) + 4;
	dsta = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 6));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 18;
}
/* BTST.B #<data>.W,#<data>.B */
unsigned long REGPARAM2 CPUFUNC(op_083c_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s8 dst = (uae_u8)get_word_prefetch (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 16;
}
/* BCHG.L #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0840_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 31;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	m68k_dreg (regs, dstreg) = (dst);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* BCHG.B #<data>.W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0850_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* BCHG.B #<data>.W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0858_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* BCHG.B #<data>.W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0860_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* BCHG.B #<data>.W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0868_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* BCHG.B #<data>.W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0870_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 22;
}
/* BCHG.B #<data>.W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0878_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* BCHG.B #<data>.W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0879_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 8);
return CYCLE_UNIT / 2 * 24;
}
/* BCHG.B #<data>.W,(d16,PC) */
unsigned long REGPARAM2 CPUFUNC(op_087a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = 2;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_getpc (regs) + 4;
	dsta += (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* BCHG.B #<data>.W,(d8,PC,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_087b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = 3;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr tmppc;
	uaecptr dsta;
	tmppc = m68k_getpc (regs) + 4;
	dsta = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 6));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	dst ^= (1 << src);
	SET_ZFLG (&regs->ccrflags, ((uae_u32)dst & (1 << src)) >> src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 22;
}
/* BCLR.L #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0880_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 31;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	m68k_dreg (regs, dstreg) = (dst);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* BCLR.B #<data>.W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0890_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* BCLR.B #<data>.W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0898_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* BCLR.B #<data>.W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_08a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* BCLR.B #<data>.W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_08a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* BCLR.B #<data>.W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_08b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 22;
}
/* BCLR.B #<data>.W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_08b8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* BCLR.B #<data>.W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_08b9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 8);
return CYCLE_UNIT / 2 * 24;
}
/* BCLR.B #<data>.W,(d16,PC) */
unsigned long REGPARAM2 CPUFUNC(op_08ba_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = 2;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_getpc (regs) + 4;
	dsta += (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* BCLR.B #<data>.W,(d8,PC,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_08bb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = 3;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr tmppc;
	uaecptr dsta;
	tmppc = m68k_getpc (regs) + 4;
	dsta = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 6));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst &= ~(1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 22;
}
/* BSET.L #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_08c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 31;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	m68k_dreg (regs, dstreg) = (dst);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* BSET.B #<data>.W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_08d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* BSET.B #<data>.W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_08d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* BSET.B #<data>.W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_08e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* BSET.B #<data>.W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_08e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* BSET.B #<data>.W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_08f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 22;
}
/* BSET.B #<data>.W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_08f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* BSET.B #<data>.W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_08f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 8);
return CYCLE_UNIT / 2 * 24;
}
/* BSET.B #<data>.W,(d16,PC) */
unsigned long REGPARAM2 CPUFUNC(op_08fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = 2;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_getpc (regs) + 4;
	dsta += (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* BSET.B #<data>.W,(d8,PC,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_08fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = 3;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr tmppc;
	uaecptr dsta;
	tmppc = m68k_getpc (regs) + 4;
	dsta = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 6));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src &= 7;
	SET_ZFLG (&regs->ccrflags, 1 ^ ((dst >> src) & 1));
	dst |= (1 << src);
	put_byte (dsta,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 22;
}
/* EOR.B #<data>.B,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0a00_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* EOR.B #<data>.B,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0a10_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 20;
}
/* EOR.B #<data>.B,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0a18_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 20;
}
/* EOR.B #<data>.B,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0a20_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 22;
}
/* EOR.B #<data>.B,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0a28_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 24;
}
/* EOR.B #<data>.B,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0a30_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
{	uae_s8 dst = get_byte (dsta);
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 26;
}
/* EOR.B #<data>.B,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0a38_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 24;
}
/* EOR.B #<data>.B,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0a39_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 8);
return CYCLE_UNIT / 2 * 28;
}
/* EORSR.B #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_0a3c_5)(uae_u32 opcode, struct regstruct *regs)
{
{	MakeSR (regs);
{	uae_s16 src = get_word_prefetch (regs, 4);
	src &= 0xFF;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	regs->sr ^= src;
	MakeFromSR (regs);
}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* EOR.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0a40_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* EOR.W #<data>.W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0a50_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2338;
	}
{{	uae_s16 dst = get_word (dsta);
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel2338: ;
return CYCLE_UNIT / 2 * 16;
}
/* EOR.W #<data>.W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0a58_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2339;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel2339: ;
return CYCLE_UNIT / 2 * 16;
}
/* EOR.W #<data>.W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0a60_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2340;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel2340: ;
return CYCLE_UNIT / 2 * 18;
}
/* EOR.W #<data>.W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0a68_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2341;
	}
{{	uae_s16 dst = get_word (dsta);
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2341: ;
return CYCLE_UNIT / 2 * 20;
}
/* EOR.W #<data>.W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0a70_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2342;
	}
{{	uae_s16 dst = get_word (dsta);
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2342: ;
return CYCLE_UNIT / 2 * 22;
}
/* EOR.W #<data>.W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0a78_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2343;
	}
{{	uae_s16 dst = get_word (dsta);
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2343: ;
return CYCLE_UNIT / 2 * 20;
}
/* EOR.W #<data>.W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0a79_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2344;
	}
{{	uae_s16 dst = get_word (dsta);
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 8);
endlabel2344: ;
return CYCLE_UNIT / 2 * 24;
}
#endif

#ifdef PART_2
/* EORSR.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_0a7c_5)(uae_u32 opcode, struct regstruct *regs)
{
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2345; }
{	MakeSR (regs);
{	uae_s16 src = get_word_prefetch (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	regs->sr ^= src;
	MakeFromSR (regs);
}}}	m68k_incpc (regs, 4);
endlabel2345: ;
return CYCLE_UNIT / 2 * 8;
}
/* EOR.L #<data>.L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0a80_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 12;
}
/* EOR.L #<data>.L,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0a90_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2347;
	}
{{	uae_s32 dst = get_long (dsta);
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2347: ;
return CYCLE_UNIT / 2 * 28;
}
/* EOR.L #<data>.L,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0a98_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2348;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2348: ;
return CYCLE_UNIT / 2 * 28;
}
/* EOR.L #<data>.L,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0aa0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2349;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel2349: ;
return CYCLE_UNIT / 2 * 30;
}
/* EOR.L #<data>.L,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0aa8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2350;
	}
{{	uae_s32 dst = get_long (dsta);
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 8);
endlabel2350: ;
return CYCLE_UNIT / 2 * 32;
}
/* EOR.L #<data>.L,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0ab0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 8));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2351;
	}
{{	uae_s32 dst = get_long (dsta);
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 8);
endlabel2351: ;
return CYCLE_UNIT / 2 * 34;
}
/* EOR.L #<data>.L,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0ab8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2352;
	}
{{	uae_s32 dst = get_long (dsta);
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 8);
endlabel2352: ;
return CYCLE_UNIT / 2 * 32;
}
/* EOR.L #<data>.L,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0ab9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2353;
	}
{{	uae_s32 dst = get_long (dsta);
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 12);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 10);
endlabel2353: ;
return CYCLE_UNIT / 2 * 36;
}
/* CMP.B #<data>.B,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0c00_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* CMP.B #<data>.B,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0c10_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* CMP.B #<data>.B,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0c18_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* CMP.B #<data>.B,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0c20_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* CMP.B #<data>.B,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0c28_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* CMP.B #<data>.B,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0c30_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 22;
}
/* CMP.B #<data>.B,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0c38_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* CMP.B #<data>.B,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0c39_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 8);
return CYCLE_UNIT / 2 * 24;
}
/* CMP.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0c40_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* CMP.W #<data>.W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0c50_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2363;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel2363: ;
return CYCLE_UNIT / 2 * 12;
}
/* CMP.W #<data>.W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0c58_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2364;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel2364: ;
return CYCLE_UNIT / 2 * 12;
}
/* CMP.W #<data>.W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0c60_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2365;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel2365: ;
return CYCLE_UNIT / 2 * 14;
}
/* CMP.W #<data>.W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0c68_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2366;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 6);
endlabel2366: ;
return CYCLE_UNIT / 2 * 16;
}
/* CMP.W #<data>.W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0c70_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2367;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 6);
endlabel2367: ;
return CYCLE_UNIT / 2 * 18;
}
/* CMP.W #<data>.W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0c78_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2368;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 6);
endlabel2368: ;
return CYCLE_UNIT / 2 * 16;
}
/* CMP.W #<data>.W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0c79_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2369;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 8);
endlabel2369: ;
return CYCLE_UNIT / 2 * 20;
}
/* CMP.L #<data>.L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_0c80_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 12;
}
/* CMP.L #<data>.L,(An) */
unsigned long REGPARAM2 CPUFUNC(op_0c90_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2371;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 6);
endlabel2371: ;
return CYCLE_UNIT / 2 * 20;
}
/* CMP.L #<data>.L,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_0c98_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2372;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 6);
endlabel2372: ;
return CYCLE_UNIT / 2 * 20;
}
/* CMP.L #<data>.L,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_0ca0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2373;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 6);
endlabel2373: ;
return CYCLE_UNIT / 2 * 22;
}
/* CMP.L #<data>.L,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_0ca8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2374;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 8);
endlabel2374: ;
return CYCLE_UNIT / 2 * 24;
}
/* CMP.L #<data>.L,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_0cb0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 8));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2375;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 8);
endlabel2375: ;
return CYCLE_UNIT / 2 * 26;
}
/* CMP.L #<data>.L,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_0cb8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2376;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 8);
endlabel2376: ;
return CYCLE_UNIT / 2 * 24;
}
/* CMP.L #<data>.L,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_0cb9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2377;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 12);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 10);
endlabel2377: ;
return CYCLE_UNIT / 2 * 28;
}
/* MOVE.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_1000_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 4;
}
/* MOVE.B (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_1010_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 8;
}
/* MOVE.B (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_1018_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 8;
}
/* MOVE.B -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_1020_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 10;
}
/* MOVE.B (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_1028_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 12;
}
/* MOVE.B (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_1030_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 14;
}
/* MOVE.B (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_1038_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 12;
}
/* MOVE.B (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_1039_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_103a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 12;
}
/* MOVE.B (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_103b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 14;
}
/* MOVE.B #<data>.B,Dn */
unsigned long REGPARAM2 CPUFUNC(op_103c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 12;
}
/* MOVE.B Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_1080_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 8;
}
/* MOVE.B (An),(An) */
unsigned long REGPARAM2 CPUFUNC(op_1090_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 12;
}
/* MOVE.B (An)+,(An) */
unsigned long REGPARAM2 CPUFUNC(op_1098_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta = m68k_areg (regs, dstreg);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 12;
}
/* MOVE.B -(An),(An) */
unsigned long REGPARAM2 CPUFUNC(op_10a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 14;
}
/* MOVE.B (d16,An),(An) */
unsigned long REGPARAM2 CPUFUNC(op_10a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B (d8,An,Xn),(An) */
unsigned long REGPARAM2 CPUFUNC(op_10b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 18;
}
/* MOVE.B (xxx).W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_10b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B (xxx).L,(An) */
unsigned long REGPARAM2 CPUFUNC(op_10b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 20;
}
/* MOVE.B (d16,PC),(An) */
unsigned long REGPARAM2 CPUFUNC(op_10ba_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B (d8,PC,Xn),(An) */
unsigned long REGPARAM2 CPUFUNC(op_10bb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 18;
}
/* MOVE.B #<data>.B,(An) */
unsigned long REGPARAM2 CPUFUNC(op_10bc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_10c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 8;
}
/* MOVE.B (An),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_10d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 12;
}
/* MOVE.B (An)+,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_10d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 12;
}
/* MOVE.B -(An),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_10e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 14;
}
/* MOVE.B (d16,An),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_10e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B (d8,An,Xn),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_10f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 18;
}
/* MOVE.B (xxx).W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_10f8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B (xxx).L,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_10f9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 20;
}
/* MOVE.B (d16,PC),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_10fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B (d8,PC,Xn),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_10fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 18;
}
/* MOVE.B #<data>.B,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_10fc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_1100_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
}}}return CYCLE_UNIT / 2 * 8;
}
/* MOVE.B (An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_1110_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
}}}}return CYCLE_UNIT / 2 * 12;
}
/* MOVE.B (An)+,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_1118_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
}}}}return CYCLE_UNIT / 2 * 12;
}
/* MOVE.B -(An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_1120_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 2);
}}}}return CYCLE_UNIT / 2 * 14;
}
/* MOVE.B (d16,An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_1128_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
}}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B (d8,An,Xn),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_1130_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
}}}}return CYCLE_UNIT / 2 * 18;
}
/* MOVE.B (xxx).W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_1138_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
}}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B (xxx).L,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_1139_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
}}}}return CYCLE_UNIT / 2 * 20;
}
/* MOVE.B (d16,PC),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_113a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
}}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B (d8,PC,Xn),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_113b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
}}}}return CYCLE_UNIT / 2 * 18;
}
/* MOVE.B #<data>.B,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_113c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_1140_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 12;
}
/* MOVE.B (An),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_1150_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B (An)+,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_1158_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B -(An),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_1160_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 18;
}
/* MOVE.B (d16,An),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_1168_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 20;
}
/* MOVE.B (d8,An,Xn),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_1170_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 22;
}
/* MOVE.B (xxx).W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_1178_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 20;
}
/* MOVE.B (xxx).L,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_1179_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 8);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 24;
}
/* MOVE.B (d16,PC),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_117a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 20;
}
/* MOVE.B (d8,PC,Xn),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_117b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 22;
}
/* MOVE.B #<data>.B,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_117c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 20;
}
/* MOVE.B Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_1180_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 14;
}
/* MOVE.B (An),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_1190_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 18;
}
/* MOVE.B (An)+,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_1198_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 18;
}
/* MOVE.B -(An),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_11a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 20;
}
/* MOVE.B (d16,An),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_11a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 22;
}
/* MOVE.B (d8,An,Xn),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_11b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 24;
}
/* MOVE.B (xxx).W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_11b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 22;
}
/* MOVE.B (xxx).L,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_11b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 8));
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 8);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 26;
}
/* MOVE.B (d16,PC),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_11ba_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 22;
}
/* MOVE.B (d8,PC,Xn),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_11bb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 24;
}
/* MOVE.B #<data>.B,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_11bc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 22;
}
/* MOVE.B Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_11c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 12;
}
/* MOVE.B (An),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_11d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B (An)+,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_11d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B -(An),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_11e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 18;
}
/* MOVE.B (d16,An),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_11e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 20;
}
/* MOVE.B (d8,An,Xn),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_11f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 22;
}
/* MOVE.B (xxx).W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_11f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 20;
}
/* MOVE.B (xxx).L,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_11f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 8);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 24;
}
/* MOVE.B (d16,PC),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_11fa_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 20;
}
/* MOVE.B (d8,PC,Xn),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_11fb_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 22;
}
/* MOVE.B #<data>.B,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_11fc_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 20;
}
/* MOVE.B Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_13c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 16;
}
/* MOVE.B (An),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_13d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 4) << 16;
	dsta |= regs->irc;
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 20;
}
/* MOVE.B (An)+,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_13d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 4) << 16;
	dsta |= regs->irc;
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 20;
}
/* MOVE.B -(An),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_13e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 4) << 16;
	dsta |= regs->irc;
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 6);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 22;
}
/* MOVE.B (d16,An),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_13e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 6) << 16;
	dsta |= regs->irc;
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 8);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 24;
}
/* MOVE.B (d8,An,Xn),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_13f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 6) << 16;
	dsta |= regs->irc;
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 8);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 26;
}
/* MOVE.B (xxx).W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_13f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 6) << 16;
	dsta |= regs->irc;
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 8);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 24;
}
/* MOVE.B (xxx).L,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_13f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 8) << 16;
	dsta |= regs->irc;
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 10);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 28;
}
/* MOVE.B (d16,PC),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_13fa_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 6) << 16;
	dsta |= regs->irc;
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 8);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 24;
}
/* MOVE.B (d8,PC,Xn),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_13fb_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 6) << 16;
	dsta |= regs->irc;
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 8);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}return CYCLE_UNIT / 2 * 26;
}
/* MOVE.B #<data>.B,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_13fc_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
	put_byte (dsta,src);
	optflag_testb (regs, (uae_s8)(src));
	m68k_incpc (regs, 8);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_2000_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	m68k_dreg (regs, dstreg) = (src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 4;
}
/* MOVE.L An,Dn */
unsigned long REGPARAM2 CPUFUNC(op_2008_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	m68k_dreg (regs, dstreg) = (src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 4;
}
/* MOVE.L (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_2010_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2468;
	}
{{	uae_s32 src = get_long (srca);
{	m68k_dreg (regs, dstreg) = (src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2468: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.L (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_2018_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2469;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	m68k_dreg (regs, dstreg) = (src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2469: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.L -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_2020_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2470;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	m68k_dreg (regs, dstreg) = (src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2470: ;
return CYCLE_UNIT / 2 * 14;
}
/* MOVE.L (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_2028_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2471;
	}
{{	uae_s32 src = get_long (srca);
{	m68k_dreg (regs, dstreg) = (src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2471: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.L (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_2030_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2472;
	}
{{	uae_s32 src = get_long (srca);
{	m68k_dreg (regs, dstreg) = (src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2472: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVE.L (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_2038_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2473;
	}
{{	uae_s32 src = get_long (srca);
{	m68k_dreg (regs, dstreg) = (src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2473: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.L (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_2039_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2474;
	}
{{	uae_s32 src = get_long (srca);
{	m68k_dreg (regs, dstreg) = (src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2474: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.L (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_203a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2475;
	}
{{	uae_s32 src = get_long (srca);
{	m68k_dreg (regs, dstreg) = (src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2475: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.L (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_203b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2476;
	}
{{	uae_s32 src = get_long (srca);
{	m68k_dreg (regs, dstreg) = (src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2476: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVE.L #<data>.L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_203c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	m68k_dreg (regs, dstreg) = (src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 12;
}
/* MOVEA.L Dn,An */
unsigned long REGPARAM2 CPUFUNC(op_2040_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 4;
}
/* MOVEA.L An,An */
unsigned long REGPARAM2 CPUFUNC(op_2048_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 4;
}
/* MOVEA.L (An),An */
unsigned long REGPARAM2 CPUFUNC(op_2050_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2480;
	}
{{	uae_s32 src = get_long (srca);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2480: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVEA.L (An)+,An */
unsigned long REGPARAM2 CPUFUNC(op_2058_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2481;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2481: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVEA.L -(An),An */
unsigned long REGPARAM2 CPUFUNC(op_2060_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2482;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2482: ;
return CYCLE_UNIT / 2 * 14;
}
/* MOVEA.L (d16,An),An */
unsigned long REGPARAM2 CPUFUNC(op_2068_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2483;
	}
{{	uae_s32 src = get_long (srca);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2483: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVEA.L (d8,An,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_2070_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2484;
	}
{{	uae_s32 src = get_long (srca);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2484: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVEA.L (xxx).W,An */
unsigned long REGPARAM2 CPUFUNC(op_2078_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2485;
	}
{{	uae_s32 src = get_long (srca);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2485: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVEA.L (xxx).L,An */
unsigned long REGPARAM2 CPUFUNC(op_2079_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2486;
	}
{{	uae_s32 src = get_long (srca);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2486: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVEA.L (d16,PC),An */
unsigned long REGPARAM2 CPUFUNC(op_207a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2487;
	}
{{	uae_s32 src = get_long (srca);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2487: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVEA.L (d8,PC,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_207b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2488;
	}
{{	uae_s32 src = get_long (srca);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2488: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVEA.L #<data>.L,An */
unsigned long REGPARAM2 CPUFUNC(op_207c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	m68k_areg (regs, dstreg) = (src);
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 12;
}
/* MOVE.L Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_2080_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2490;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2490: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.L An,(An) */
unsigned long REGPARAM2 CPUFUNC(op_2088_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2491;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2491: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.L (An),(An) */
unsigned long REGPARAM2 CPUFUNC(op_2090_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2492;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2492;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2492: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.L (An)+,(An) */
unsigned long REGPARAM2 CPUFUNC(op_2098_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2493;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2493;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2493: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.L -(An),(An) */
unsigned long REGPARAM2 CPUFUNC(op_20a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2494;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2494;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2494: ;
return CYCLE_UNIT / 2 * 22;
}
/* MOVE.L (d16,An),(An) */
unsigned long REGPARAM2 CPUFUNC(op_20a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2495;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2495;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2495: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L (d8,An,Xn),(An) */
unsigned long REGPARAM2 CPUFUNC(op_20b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2496;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2496;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2496: ;
return CYCLE_UNIT / 2 * 26;
}
/* MOVE.L (xxx).W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_20b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2497;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2497;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2497: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L (xxx).L,(An) */
unsigned long REGPARAM2 CPUFUNC(op_20b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2498;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2498;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2498: ;
return CYCLE_UNIT / 2 * 28;
}
/* MOVE.L (d16,PC),(An) */
unsigned long REGPARAM2 CPUFUNC(op_20ba_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2499;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2499;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2499: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L (d8,PC,Xn),(An) */
unsigned long REGPARAM2 CPUFUNC(op_20bb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2500;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2500;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2500: ;
return CYCLE_UNIT / 2 * 26;
}
/* MOVE.L #<data>.L,(An) */
unsigned long REGPARAM2 CPUFUNC(op_20bc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2501;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2501: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.L Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_20c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2502;
	}
{	m68k_areg (regs, dstreg) += 4;
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2502: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.L An,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_20c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2503;
	}
{	m68k_areg (regs, dstreg) += 4;
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2503: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.L (An),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_20d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2504;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2504;
	}
{	m68k_areg (regs, dstreg) += 4;
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2504: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.L (An)+,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_20d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2505;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2505;
	}
{	m68k_areg (regs, dstreg) += 4;
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2505: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.L -(An),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_20e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2506;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2506;
	}
{	m68k_areg (regs, dstreg) += 4;
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2506: ;
return CYCLE_UNIT / 2 * 22;
}
/* MOVE.L (d16,An),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_20e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2507;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2507;
	}
{	m68k_areg (regs, dstreg) += 4;
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2507: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L (d8,An,Xn),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_20f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2508;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2508;
	}
{	m68k_areg (regs, dstreg) += 4;
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2508: ;
return CYCLE_UNIT / 2 * 26;
}
/* MOVE.L (xxx).W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_20f8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2509;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2509;
	}
{	m68k_areg (regs, dstreg) += 4;
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2509: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L (xxx).L,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_20f9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2510;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2510;
	}
{	m68k_areg (regs, dstreg) += 4;
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2510: ;
return CYCLE_UNIT / 2 * 28;
}
/* MOVE.L (d16,PC),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_20fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2511;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2511;
	}
{	m68k_areg (regs, dstreg) += 4;
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2511: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L (d8,PC,Xn),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_20fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2512;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2512;
	}
{	m68k_areg (regs, dstreg) += 4;
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2512: ;
return CYCLE_UNIT / 2 * 26;
}
/* MOVE.L #<data>.L,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_20fc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2513;
	}
{	m68k_areg (regs, dstreg) += 4;
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2513: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.L Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_2100_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2514;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
}}}}endlabel2514: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.L An,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_2108_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2515;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
}}}}endlabel2515: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.L (An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_2110_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2516;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2516;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
}}}}}}endlabel2516: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.L (An)+,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_2118_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2517;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2517;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
}}}}}}endlabel2517: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.L -(An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_2120_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2518;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2518;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
}}}}}}endlabel2518: ;
return CYCLE_UNIT / 2 * 22;
}
/* MOVE.L (d16,An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_2128_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2519;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2519;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
}}}}}}endlabel2519: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L (d8,An,Xn),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_2130_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2520;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2520;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
}}}}}}endlabel2520: ;
return CYCLE_UNIT / 2 * 26;
}
/* MOVE.L (xxx).W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_2138_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2521;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2521;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
}}}}}}endlabel2521: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L (xxx).L,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_2139_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2522;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2522;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
}}}}}}endlabel2522: ;
return CYCLE_UNIT / 2 * 28;
}
/* MOVE.L (d16,PC),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_213a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2523;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2523;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
}}}}}}endlabel2523: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L (d8,PC,Xn),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_213b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2524;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2524;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
}}}}}}endlabel2524: ;
return CYCLE_UNIT / 2 * 26;
}
/* MOVE.L #<data>.L,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_213c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2525;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
}}}}endlabel2525: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.L Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_2140_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2526;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2526: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.L An,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_2148_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2527;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2527: ;
return CYCLE_UNIT / 2 * 16;
}
#endif

#ifdef PART_3
/* MOVE.L (An),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_2150_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2528;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2528;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2528: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L (An)+,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_2158_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2529;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2529;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2529: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L -(An),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_2160_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2530;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2530;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2530: ;
return CYCLE_UNIT / 2 * 26;
}
/* MOVE.L (d16,An),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_2168_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2531;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2531;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2531: ;
return CYCLE_UNIT / 2 * 28;
}
/* MOVE.L (d8,An,Xn),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_2170_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2532;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2532;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2532: ;
return CYCLE_UNIT / 2 * 30;
}
/* MOVE.L (xxx).W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_2178_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2533;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2533;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2533: ;
return CYCLE_UNIT / 2 * 28;
}
/* MOVE.L (xxx).L,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_2179_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2534;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2534;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 8);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2534: ;
return CYCLE_UNIT / 2 * 32;
}
/* MOVE.L (d16,PC),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_217a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2535;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2535;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2535: ;
return CYCLE_UNIT / 2 * 28;
}
/* MOVE.L (d8,PC,Xn),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_217b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2536;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2536;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2536: ;
return CYCLE_UNIT / 2 * 30;
}
/* MOVE.L #<data>.L,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_217c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2537;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 8);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2537: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_2180_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2538;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2538: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVE.L An,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_2188_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2539;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2539: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVE.L (An),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_2190_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2540;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2540;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2540: ;
return CYCLE_UNIT / 2 * 26;
}
/* MOVE.L (An)+,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_2198_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2541;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2541;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2541: ;
return CYCLE_UNIT / 2 * 26;
}
/* MOVE.L -(An),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_21a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2542;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2542;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2542: ;
return CYCLE_UNIT / 2 * 28;
}
/* MOVE.L (d16,An),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_21a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2543;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2543;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2543: ;
return CYCLE_UNIT / 2 * 30;
}
/* MOVE.L (d8,An,Xn),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_21b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2544;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2544;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2544: ;
return CYCLE_UNIT / 2 * 32;
}
/* MOVE.L (xxx).W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_21b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2545;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2545;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2545: ;
return CYCLE_UNIT / 2 * 30;
}
/* MOVE.L (xxx).L,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_21b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2546;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 8));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2546;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 8);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2546: ;
return CYCLE_UNIT / 2 * 34;
}
/* MOVE.L (d16,PC),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_21ba_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2547;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2547;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2547: ;
return CYCLE_UNIT / 2 * 30;
}
/* MOVE.L (d8,PC,Xn),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_21bb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2548;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2548;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2548: ;
return CYCLE_UNIT / 2 * 32;
}
/* MOVE.L #<data>.L,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_21bc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 8));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2549;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 8);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2549: ;
return CYCLE_UNIT / 2 * 26;
}
/* MOVE.L Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_21c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2550;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2550: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.L An,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_21c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2551;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2551: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.L (An),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_21d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2552;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2552;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2552: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L (An)+,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_21d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2553;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2553;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2553: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L -(An),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_21e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2554;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2554;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2554: ;
return CYCLE_UNIT / 2 * 26;
}
/* MOVE.L (d16,An),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_21e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2555;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2555;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2555: ;
return CYCLE_UNIT / 2 * 28;
}
/* MOVE.L (d8,An,Xn),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_21f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2556;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2556;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2556: ;
return CYCLE_UNIT / 2 * 30;
}
/* MOVE.L (xxx).W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_21f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2557;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2557;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2557: ;
return CYCLE_UNIT / 2 * 28;
}
/* MOVE.L (xxx).L,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_21f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2558;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2558;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 8);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2558: ;
return CYCLE_UNIT / 2 * 32;
}
/* MOVE.L (d16,PC),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_21fa_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2559;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2559;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2559: ;
return CYCLE_UNIT / 2 * 28;
}
/* MOVE.L (d8,PC,Xn),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_21fb_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2560;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2560;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2560: ;
return CYCLE_UNIT / 2 * 30;
}
/* MOVE.L #<data>.L,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_21fc_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2561;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 8);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2561: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.L Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_23c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2562;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2562: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.L An,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_23c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2563;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2563: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.L (An),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_23d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2564;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 4) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2564;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2564: ;
return CYCLE_UNIT / 2 * 28;
}
/* MOVE.L (An)+,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_23d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2565;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 4) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2565;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2565: ;
return CYCLE_UNIT / 2 * 28;
}
/* MOVE.L -(An),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_23e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2566;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 4) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2566;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 6);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2566: ;
return CYCLE_UNIT / 2 * 30;
}
/* MOVE.L (d16,An),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_23e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2567;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 6) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2567;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 8);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2567: ;
return CYCLE_UNIT / 2 * 32;
}
/* MOVE.L (d8,An,Xn),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_23f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2568;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 6) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2568;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 8);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2568: ;
return CYCLE_UNIT / 2 * 34;
}
/* MOVE.L (xxx).W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_23f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2569;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 6) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2569;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 8);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2569: ;
return CYCLE_UNIT / 2 * 32;
}
/* MOVE.L (xxx).L,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_23f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2570;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 8) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2570;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 10);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2570: ;
return CYCLE_UNIT / 2 * 36;
}
/* MOVE.L (d16,PC),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_23fa_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2571;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 6) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2571;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 8);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2571: ;
return CYCLE_UNIT / 2 * 32;
}
/* MOVE.L (d8,PC,Xn),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_23fb_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2572;
	}
{{	uae_s32 src = get_long (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 6) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2572;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 8);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2572: ;
return CYCLE_UNIT / 2 * 34;
}
/* MOVE.L #<data>.L,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_23fc_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2573;
	}
{	put_long (dsta,src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 10);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2573: ;
return CYCLE_UNIT / 2 * 28;
}
/* MOVE.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_3000_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 4;
}
/* MOVE.W An,Dn */
unsigned long REGPARAM2 CPUFUNC(op_3008_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 4;
}
/* MOVE.W (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_3010_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2576;
	}
{{	uae_s16 src = get_word (srca);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2576: ;
return CYCLE_UNIT / 2 * 8;
}
/* MOVE.W (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_3018_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2577;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2577: ;
return CYCLE_UNIT / 2 * 8;
}
/* MOVE.W -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_3020_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2578;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2578: ;
return CYCLE_UNIT / 2 * 10;
}
/* MOVE.W (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_3028_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2579;
	}
{{	uae_s16 src = get_word (srca);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2579: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_3030_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2580;
	}
{{	uae_s16 src = get_word (srca);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2580: ;
return CYCLE_UNIT / 2 * 14;
}
/* MOVE.W (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_3038_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2581;
	}
{{	uae_s16 src = get_word (srca);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2581: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_3039_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2582;
	}
{{	uae_s16 src = get_word (srca);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2582: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_303a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2583;
	}
{{	uae_s16 src = get_word (srca);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2583: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_303b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2584;
	}
{{	uae_s16 src = get_word (srca);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2584: ;
return CYCLE_UNIT / 2 * 14;
}
/* MOVE.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_303c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 8;
}
/* MOVEA.W Dn,An */
unsigned long REGPARAM2 CPUFUNC(op_3040_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 4;
}
/* MOVEA.W An,An */
unsigned long REGPARAM2 CPUFUNC(op_3048_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 4;
}
/* MOVEA.W (An),An */
unsigned long REGPARAM2 CPUFUNC(op_3050_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2588;
	}
{{	uae_s16 src = get_word (srca);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2588: ;
return CYCLE_UNIT / 2 * 8;
}
/* MOVEA.W (An)+,An */
unsigned long REGPARAM2 CPUFUNC(op_3058_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2589;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2589: ;
return CYCLE_UNIT / 2 * 8;
}
/* MOVEA.W -(An),An */
unsigned long REGPARAM2 CPUFUNC(op_3060_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2590;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2590: ;
return CYCLE_UNIT / 2 * 10;
}
/* MOVEA.W (d16,An),An */
unsigned long REGPARAM2 CPUFUNC(op_3068_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2591;
	}
{{	uae_s16 src = get_word (srca);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2591: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVEA.W (d8,An,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_3070_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2592;
	}
{{	uae_s16 src = get_word (srca);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2592: ;
return CYCLE_UNIT / 2 * 14;
}
/* MOVEA.W (xxx).W,An */
unsigned long REGPARAM2 CPUFUNC(op_3078_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2593;
	}
{{	uae_s16 src = get_word (srca);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2593: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVEA.W (xxx).L,An */
unsigned long REGPARAM2 CPUFUNC(op_3079_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2594;
	}
{{	uae_s16 src = get_word (srca);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2594: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVEA.W (d16,PC),An */
unsigned long REGPARAM2 CPUFUNC(op_307a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2595;
	}
{{	uae_s16 src = get_word (srca);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2595: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVEA.W (d8,PC,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_307b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2596;
	}
{{	uae_s16 src = get_word (srca);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2596: ;
return CYCLE_UNIT / 2 * 14;
}
/* MOVEA.W #<data>.W,An */
unsigned long REGPARAM2 CPUFUNC(op_307c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	src = (uae_s32)(uae_s16)src;
	m68k_areg (regs, dstreg) = (uae_s32)(uae_s16)(src);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 8;
}
/* MOVE.W Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_3080_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2598;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2598: ;
return CYCLE_UNIT / 2 * 8;
}
/* MOVE.W An,(An) */
unsigned long REGPARAM2 CPUFUNC(op_3088_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2599;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2599: ;
return CYCLE_UNIT / 2 * 8;
}
/* MOVE.W (An),(An) */
unsigned long REGPARAM2 CPUFUNC(op_3090_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2600;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2600;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2600: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W (An)+,(An) */
unsigned long REGPARAM2 CPUFUNC(op_3098_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2601;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2601;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2601: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W -(An),(An) */
unsigned long REGPARAM2 CPUFUNC(op_30a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2602;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2602;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2602: ;
return CYCLE_UNIT / 2 * 14;
}
/* MOVE.W (d16,An),(An) */
unsigned long REGPARAM2 CPUFUNC(op_30a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2603;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2603;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2603: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W (d8,An,Xn),(An) */
unsigned long REGPARAM2 CPUFUNC(op_30b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2604;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2604;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2604: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVE.W (xxx).W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_30b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2605;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2605;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2605: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W (xxx).L,(An) */
unsigned long REGPARAM2 CPUFUNC(op_30b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2606;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2606;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2606: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.W (d16,PC),(An) */
unsigned long REGPARAM2 CPUFUNC(op_30ba_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2607;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2607;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2607: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W (d8,PC,Xn),(An) */
unsigned long REGPARAM2 CPUFUNC(op_30bb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2608;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2608;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2608: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVE.W #<data>.W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_30bc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2609;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2609: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_30c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2610;
	}
{	m68k_areg (regs, dstreg) += 2;
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2610: ;
return CYCLE_UNIT / 2 * 8;
}
/* MOVE.W An,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_30c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2611;
	}
{	m68k_areg (regs, dstreg) += 2;
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2611: ;
return CYCLE_UNIT / 2 * 8;
}
/* MOVE.W (An),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_30d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2612;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2612;
	}
{	m68k_areg (regs, dstreg) += 2;
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2612: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W (An)+,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_30d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2613;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2613;
	}
{	m68k_areg (regs, dstreg) += 2;
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2613: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W -(An),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_30e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2614;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2614;
	}
{	m68k_areg (regs, dstreg) += 2;
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2614: ;
return CYCLE_UNIT / 2 * 14;
}
/* MOVE.W (d16,An),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_30e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2615;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2615;
	}
{	m68k_areg (regs, dstreg) += 2;
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2615: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W (d8,An,Xn),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_30f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2616;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2616;
	}
{	m68k_areg (regs, dstreg) += 2;
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2616: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVE.W (xxx).W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_30f8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2617;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2617;
	}
{	m68k_areg (regs, dstreg) += 2;
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2617: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W (xxx).L,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_30f9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2618;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2618;
	}
{	m68k_areg (regs, dstreg) += 2;
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2618: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.W (d16,PC),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_30fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2619;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2619;
	}
{	m68k_areg (regs, dstreg) += 2;
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2619: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W (d8,PC,Xn),(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_30fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2620;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2620;
	}
{	m68k_areg (regs, dstreg) += 2;
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2620: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVE.W #<data>.W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_30fc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2621;
	}
{	m68k_areg (regs, dstreg) += 2;
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2621: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_3100_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2622;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
}}}}endlabel2622: ;
return CYCLE_UNIT / 2 * 8;
}
/* MOVE.W An,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_3108_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2623;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
}}}}endlabel2623: ;
return CYCLE_UNIT / 2 * 8;
}
/* MOVE.W (An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_3110_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2624;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2624;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
}}}}}}endlabel2624: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W (An)+,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_3118_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2625;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2625;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
}}}}}}endlabel2625: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W -(An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_3120_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2626;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2626;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 2);
}}}}}}endlabel2626: ;
return CYCLE_UNIT / 2 * 14;
}
/* MOVE.W (d16,An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_3128_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2627;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2627;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
}}}}}}endlabel2627: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W (d8,An,Xn),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_3130_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2628;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2628;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
}}}}}}endlabel2628: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVE.W (xxx).W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_3138_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2629;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2629;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
}}}}}}endlabel2629: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W (xxx).L,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_3139_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2630;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2630;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
}}}}}}endlabel2630: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.W (d16,PC),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_313a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2631;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2631;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
}}}}}}endlabel2631: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W (d8,PC,Xn),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_313b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2632;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2632;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
}}}}}}endlabel2632: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVE.W #<data>.W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_313c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2633;
	}
{	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
}}}}endlabel2633: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_3140_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2634;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2634: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W An,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_3148_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2635;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2635: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W (An),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_3150_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2636;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2636;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2636: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W (An)+,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_3158_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2637;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2637;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2637: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W -(An),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_3160_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2638;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2638;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2638: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVE.W (d16,An),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_3168_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2639;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2639;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2639: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.W (d8,An,Xn),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_3170_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2640;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2640;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2640: ;
return CYCLE_UNIT / 2 * 22;
}
/* MOVE.W (xxx).W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_3178_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2641;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2641;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2641: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.W (xxx).L,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_3179_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2642;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2642;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 8);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2642: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.W (d16,PC),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_317a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2643;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2643;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2643: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.W (d8,PC,Xn),(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_317b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2644;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2644;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2644: ;
return CYCLE_UNIT / 2 * 22;
}
/* MOVE.W #<data>.W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_317c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2645;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2645: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_3180_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2646;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2646: ;
return CYCLE_UNIT / 2 * 14;
}
/* MOVE.W An,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_3188_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2647;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2647: ;
return CYCLE_UNIT / 2 * 14;
}
/* MOVE.W (An),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_3190_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2648;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2648;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2648: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVE.W (An)+,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_3198_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2649;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2649;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2649: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVE.W -(An),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_31a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2650;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2650;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2650: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.W (d16,An),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_31a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2651;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2651;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2651: ;
return CYCLE_UNIT / 2 * 22;
}
/* MOVE.W (d8,An,Xn),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_31b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2652;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2652;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2652: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.W (xxx).W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_31b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2653;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2653;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2653: ;
return CYCLE_UNIT / 2 * 22;
}
/* MOVE.W (xxx).L,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_31b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2654;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 8));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2654;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 8);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2654: ;
return CYCLE_UNIT / 2 * 26;
}
/* MOVE.W (d16,PC),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_31ba_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2655;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2655;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2655: ;
return CYCLE_UNIT / 2 * 22;
}
/* MOVE.W (d8,PC,Xn),(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_31bb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2656;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2656;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2656: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.W #<data>.W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_31bc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2657;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2657: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVE.W Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_31c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2658;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2658: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W An,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_31c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2659;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2659: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.W (An),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_31d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2660;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2660;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2660: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W (An)+,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_31d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2661;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2661;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2661: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W -(An),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_31e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2662;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2662;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2662: ;
return CYCLE_UNIT / 2 * 18;
}
/* MOVE.W (d16,An),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_31e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2663;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2663;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2663: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.W (d8,An,Xn),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_31f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2664;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2664;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2664: ;
return CYCLE_UNIT / 2 * 22;
}
/* MOVE.W (xxx).W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_31f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2665;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2665;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2665: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.W (xxx).L,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_31f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2666;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 8);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2666;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 8);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2666: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.W (d16,PC),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_31fa_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2667;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2667;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2667: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.W (d8,PC,Xn),(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_31fb_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2668;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2668;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2668: ;
return CYCLE_UNIT / 2 * 22;
}
/* MOVE.W #<data>.W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_31fc_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2669;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2669: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_33c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2670;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2670: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W An,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_33c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2671;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2671: ;
return CYCLE_UNIT / 2 * 16;
}
/* MOVE.W (An),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_33d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2672;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 4) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2672;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2672: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.W (An)+,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_33d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2673;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 4) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2673;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2673: ;
return CYCLE_UNIT / 2 * 20;
}
/* MOVE.W -(An),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_33e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2674;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 4) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2674;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 6);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2674: ;
return CYCLE_UNIT / 2 * 22;
}
/* MOVE.W (d16,An),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_33e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2675;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 6) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2675;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 8);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2675: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.W (d8,An,Xn),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_33f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2676;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 6) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2676;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 8);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2676: ;
return CYCLE_UNIT / 2 * 26;
}
/* MOVE.W (xxx).W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_33f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2677;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 6) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2677;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 8);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2677: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.W (xxx).L,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_33f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2678;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 8) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2678;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 10);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2678: ;
return CYCLE_UNIT / 2 * 28;
}
/* MOVE.W (d16,PC),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_33fa_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2679;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 6) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2679;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 8);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2679: ;
return CYCLE_UNIT / 2 * 24;
}
/* MOVE.W (d8,PC,Xn),(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_33fb_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2680;
	}
{{	uae_s16 src = get_word (srca);
{	uaecptr dsta;
	dsta  = get_word_prefetch (regs, 6) << 16;
	dsta |= regs->irc;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2680;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 8);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}endlabel2680: ;
return CYCLE_UNIT / 2 * 26;
}
/* MOVE.W #<data>.W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_33fc_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uaecptr dsta = get_long_prefetch (regs, 6);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2681;
	}
{	put_word (dsta,src);
	optflag_testw (regs, (uae_s16)(src));
	m68k_incpc (regs, 8);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2681: ;
return CYCLE_UNIT / 2 * 20;
}
/* NEGX.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_4000_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s8)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s8)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s8)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((newv) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* NEGX.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_4010_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s8)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s8)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s8)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (srca,newv);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* NEGX.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4018_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s8)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s8)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s8)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (srca,newv);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* NEGX.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_4020_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s8)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s8)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s8)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (srca,newv);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* NEGX.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4028_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s8)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s8)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s8)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (srca,newv);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* NEGX.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4030_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s8)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s8)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s8)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (srca,newv);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* NEGX.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4038_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s8)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s8)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s8)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (srca,newv);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* NEGX.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4039_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s8)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s8)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s8)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (srca,newv);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* NEGX.W Dn */
unsigned long REGPARAM2 CPUFUNC(op_4040_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s16)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s16)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s16)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s16)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s16)(newv)) < 0) ? 1 : 0);
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | ((newv) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* NEGX.W (An) */
unsigned long REGPARAM2 CPUFUNC(op_4050_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2691;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s16)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s16)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s16)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s16)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s16)(newv)) < 0) ? 1 : 0);
	put_word (srca,newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel2691: ;
return CYCLE_UNIT / 2 * 12;
}
/* NEGX.W (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4058_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2692;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s16)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s16)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s16)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s16)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s16)(newv)) < 0) ? 1 : 0);
	put_word (srca,newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel2692: ;
return CYCLE_UNIT / 2 * 12;
}
/* NEGX.W -(An) */
unsigned long REGPARAM2 CPUFUNC(op_4060_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2693;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s16)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s16)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s16)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s16)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s16)(newv)) < 0) ? 1 : 0);
	put_word (srca,newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel2693: ;
return CYCLE_UNIT / 2 * 14;
}
/* NEGX.W (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4068_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2694;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s16)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s16)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s16)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s16)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s16)(newv)) < 0) ? 1 : 0);
	put_word (srca,newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel2694: ;
return CYCLE_UNIT / 2 * 16;
}
/* NEGX.W (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4070_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2695;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s16)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s16)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s16)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s16)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s16)(newv)) < 0) ? 1 : 0);
	put_word (srca,newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel2695: ;
return CYCLE_UNIT / 2 * 18;
}
/* NEGX.W (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4078_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2696;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s16)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s16)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s16)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s16)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s16)(newv)) < 0) ? 1 : 0);
	put_word (srca,newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel2696: ;
return CYCLE_UNIT / 2 * 16;
}
/* NEGX.W (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4079_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2697;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s16)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s16)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s16)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s16)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s16)(newv)) < 0) ? 1 : 0);
	put_word (srca,newv);
}}}}}}	m68k_incpc (regs, 6);
endlabel2697: ;
return CYCLE_UNIT / 2 * 20;
}
/* NEGX.L Dn */
unsigned long REGPARAM2 CPUFUNC(op_4080_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s32)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s32)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s32)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s32)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s32)(newv)) < 0) ? 1 : 0);
	m68k_dreg (regs, srcreg) = (newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* NEGX.L (An) */
unsigned long REGPARAM2 CPUFUNC(op_4090_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2699;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s32)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s32)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s32)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s32)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s32)(newv)) < 0) ? 1 : 0);
	put_long (srca,newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel2699: ;
return CYCLE_UNIT / 2 * 20;
}
/* NEGX.L (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4098_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2700;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s32)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s32)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s32)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s32)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s32)(newv)) < 0) ? 1 : 0);
	put_long (srca,newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel2700: ;
return CYCLE_UNIT / 2 * 20;
}
/* NEGX.L -(An) */
unsigned long REGPARAM2 CPUFUNC(op_40a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2701;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s32)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s32)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s32)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s32)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s32)(newv)) < 0) ? 1 : 0);
	put_long (srca,newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel2701: ;
return CYCLE_UNIT / 2 * 22;
}
/* NEGX.L (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_40a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2702;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s32)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s32)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s32)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s32)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s32)(newv)) < 0) ? 1 : 0);
	put_long (srca,newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel2702: ;
return CYCLE_UNIT / 2 * 24;
}
/* NEGX.L (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_40b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2703;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s32)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s32)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s32)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s32)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s32)(newv)) < 0) ? 1 : 0);
	put_long (srca,newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel2703: ;
return CYCLE_UNIT / 2 * 26;
}
/* NEGX.L (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_40b8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2704;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s32)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s32)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s32)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s32)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s32)(newv)) < 0) ? 1 : 0);
	put_long (srca,newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel2704: ;
return CYCLE_UNIT / 2 * 24;
}
/* NEGX.L (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_40b9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2705;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 newv = 0 - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s32)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s32)(0)) < 0) ? 1 : 0;
	int flgn = (((uae_s32)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s32)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s32)(newv)) < 0) ? 1 : 0);
	put_long (srca,newv);
}}}}}}	m68k_incpc (regs, 6);
endlabel2705: ;
return CYCLE_UNIT / 2 * 28;
}
/* MVSR2.W Dn */
unsigned long REGPARAM2 CPUFUNC(op_40c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	MakeSR (regs);
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | ((regs->sr) & 0xffff);
}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* MVSR2.W (An) */
unsigned long REGPARAM2 CPUFUNC(op_40d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2707;
	}
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	MakeSR (regs);
	put_word (srca,regs->sr);
}}}	m68k_incpc (regs, 2);
endlabel2707: ;
return CYCLE_UNIT / 2 * 8;
}
/* MVSR2.W (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_40d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2708;
	}
{	m68k_areg (regs, srcreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	MakeSR (regs);
	put_word (srca,regs->sr);
}}}	m68k_incpc (regs, 2);
endlabel2708: ;
return CYCLE_UNIT / 2 * 8;
}
/* MVSR2.W -(An) */
unsigned long REGPARAM2 CPUFUNC(op_40e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2709;
	}
{	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	MakeSR (regs);
	put_word (srca,regs->sr);
}}}	m68k_incpc (regs, 2);
endlabel2709: ;
return CYCLE_UNIT / 2 * 10;
}
/* MVSR2.W (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_40e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2710;
	}
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	MakeSR (regs);
	put_word (srca,regs->sr);
}}}	m68k_incpc (regs, 4);
endlabel2710: ;
return CYCLE_UNIT / 2 * 12;
}
/* MVSR2.W (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_40f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2711;
	}
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	MakeSR (regs);
	put_word (srca,regs->sr);
}}}	m68k_incpc (regs, 4);
endlabel2711: ;
return CYCLE_UNIT / 2 * 14;
}
/* MVSR2.W (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_40f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2712;
	}
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	MakeSR (regs);
	put_word (srca,regs->sr);
}}}	m68k_incpc (regs, 4);
endlabel2712: ;
return CYCLE_UNIT / 2 * 12;
}
/* MVSR2.W (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_40f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2713;
	}
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	MakeSR (regs);
	put_word (srca,regs->sr);
}}}	m68k_incpc (regs, 6);
endlabel2713: ;
return CYCLE_UNIT / 2 * 16;
}
/* CHK.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_4100_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2714;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2714;
	}
}}}endlabel2714: ;
return CYCLE_UNIT / 2 * 4;
}
/* CHK.L (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_4110_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2715;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2715;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2715;
	}
}}}}}endlabel2715: ;
return CYCLE_UNIT / 2 * 12;
}
/* CHK.L (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_4118_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2716;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2716;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2716;
	}
}}}}}endlabel2716: ;
return CYCLE_UNIT / 2 * 12;
}
/* CHK.L -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_4120_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2717;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2717;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2717;
	}
}}}}}endlabel2717: ;
return CYCLE_UNIT / 2 * 14;
}
/* CHK.L (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_4128_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2718;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2718;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2718;
	}
}}}}}endlabel2718: ;
return CYCLE_UNIT / 2 * 16;
}
/* CHK.L (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_4130_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2719;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2719;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2719;
	}
}}}}}endlabel2719: ;
return CYCLE_UNIT / 2 * 18;
}
/* CHK.L (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_4138_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2720;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2720;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2720;
	}
}}}}}endlabel2720: ;
return CYCLE_UNIT / 2 * 16;
}
/* CHK.L (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_4139_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2721;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2721;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2721;
	}
}}}}}endlabel2721: ;
return CYCLE_UNIT / 2 * 20;
}
/* CHK.L (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_413a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2722;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2722;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2722;
	}
}}}}}endlabel2722: ;
return CYCLE_UNIT / 2 * 16;
}
/* CHK.L (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_413b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2723;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2723;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2723;
	}
}}}}}endlabel2723: ;
return CYCLE_UNIT / 2 * 18;
}
/* CHK.L #<data>.L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_413c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uae_s32 src = get_long_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2724;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2724;
	}
}}}endlabel2724: ;
return CYCLE_UNIT / 2 * 12;
}
/* CHK.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_4180_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2725;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2725;
	}
}}}endlabel2725: ;
return CYCLE_UNIT / 2 * 4;
}
/* CHK.W (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_4190_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2726;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2726;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2726;
	}
}}}}}endlabel2726: ;
return CYCLE_UNIT / 2 * 8;
}
/* CHK.W (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_4198_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2727;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2727;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2727;
	}
}}}}}endlabel2727: ;
return CYCLE_UNIT / 2 * 8;
}
/* CHK.W -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_41a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2728;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2728;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2728;
	}
}}}}}endlabel2728: ;
return CYCLE_UNIT / 2 * 10;
}
/* CHK.W (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_41a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2729;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2729;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2729;
	}
}}}}}endlabel2729: ;
return CYCLE_UNIT / 2 * 12;
}
/* CHK.W (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_41b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2730;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2730;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2730;
	}
}}}}}endlabel2730: ;
return CYCLE_UNIT / 2 * 14;
}
/* CHK.W (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_41b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2731;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2731;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2731;
	}
}}}}}endlabel2731: ;
return CYCLE_UNIT / 2 * 12;
}
/* CHK.W (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_41b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2732;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 6);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2732;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2732;
	}
}}}}}endlabel2732: ;
return CYCLE_UNIT / 2 * 16;
}
/* CHK.W (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_41ba_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2733;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2733;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2733;
	}
}}}}}endlabel2733: ;
return CYCLE_UNIT / 2 * 12;
}
/* CHK.W (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_41bb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2734;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2734;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2734;
	}
}}}}}endlabel2734: ;
return CYCLE_UNIT / 2 * 14;
}
/* CHK.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_41bc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	m68k_incpc (regs, 4);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	if ((uae_s32)dst < 0) {
		SET_NFLG (&regs->ccrflags, 1);
		Exception (6, regs, oldpc);
		goto endlabel2735;
	} else if (dst > src) {
		SET_NFLG (&regs->ccrflags, 0);
		Exception (6, regs, oldpc);
		goto endlabel2735;
	}
}}}endlabel2735: ;
return CYCLE_UNIT / 2 * 8;
}
/* LEA.L (An),An */
unsigned long REGPARAM2 CPUFUNC(op_41d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_areg (regs, dstreg) = (srca);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* LEA.L (d16,An),An */
unsigned long REGPARAM2 CPUFUNC(op_41e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_areg (regs, dstreg) = (srca);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* LEA.L (d8,An,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_41f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_areg (regs, dstreg) = (srca);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* LEA.L (xxx).W,An */
unsigned long REGPARAM2 CPUFUNC(op_41f8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_areg (regs, dstreg) = (srca);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* LEA.L (xxx).L,An */
unsigned long REGPARAM2 CPUFUNC(op_41f9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	m68k_areg (regs, dstreg) = (srca);
}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 12;
}
/* LEA.L (d16,PC),An */
unsigned long REGPARAM2 CPUFUNC(op_41fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_areg (regs, dstreg) = (srca);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* LEA.L (d8,PC,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_41fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_areg (regs, dstreg) = (srca);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* CLR.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_4200_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((0) & 0xff);
}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* CLR.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_4210_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_byte (srca,0);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* CLR.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4218_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_byte (srca,0);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* CLR.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_4220_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_byte (srca,0);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* CLR.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4228_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_byte (srca,0);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* CLR.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4230_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_byte (srca,0);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* CLR.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4238_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_byte (srca,0);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* CLR.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4239_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_byte (srca,0);
}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* CLR.W Dn */
unsigned long REGPARAM2 CPUFUNC(op_4240_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | ((0) & 0xffff);
}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* CLR.W (An) */
unsigned long REGPARAM2 CPUFUNC(op_4250_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2752;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_word (srca,0);
}}}}	m68k_incpc (regs, 2);
endlabel2752: ;
return CYCLE_UNIT / 2 * 12;
}
/* CLR.W (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4258_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2753;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_word (srca,0);
}}}}	m68k_incpc (regs, 2);
endlabel2753: ;
return CYCLE_UNIT / 2 * 12;
}
/* CLR.W -(An) */
unsigned long REGPARAM2 CPUFUNC(op_4260_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2754;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_word (srca,0);
}}}}	m68k_incpc (regs, 2);
endlabel2754: ;
return CYCLE_UNIT / 2 * 14;
}
/* CLR.W (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4268_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2755;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_word (srca,0);
}}}}	m68k_incpc (regs, 4);
endlabel2755: ;
return CYCLE_UNIT / 2 * 16;
}
/* CLR.W (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4270_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2756;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_word (srca,0);
}}}}	m68k_incpc (regs, 4);
endlabel2756: ;
return CYCLE_UNIT / 2 * 18;
}
/* CLR.W (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4278_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2757;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_word (srca,0);
}}}}	m68k_incpc (regs, 4);
endlabel2757: ;
return CYCLE_UNIT / 2 * 16;
}
/* CLR.W (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4279_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2758;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_word (srca,0);
}}}}	m68k_incpc (regs, 6);
endlabel2758: ;
return CYCLE_UNIT / 2 * 20;
}
/* CLR.L Dn */
unsigned long REGPARAM2 CPUFUNC(op_4280_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	m68k_dreg (regs, srcreg) = (0);
}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* CLR.L (An) */
unsigned long REGPARAM2 CPUFUNC(op_4290_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2760;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_long (srca,0);
}}}}	m68k_incpc (regs, 2);
endlabel2760: ;
return CYCLE_UNIT / 2 * 20;
}
#endif

#ifdef PART_4
/* CLR.L (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4298_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2761;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_long (srca,0);
}}}}	m68k_incpc (regs, 2);
endlabel2761: ;
return CYCLE_UNIT / 2 * 20;
}
/* CLR.L -(An) */
unsigned long REGPARAM2 CPUFUNC(op_42a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2762;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_long (srca,0);
}}}}	m68k_incpc (regs, 2);
endlabel2762: ;
return CYCLE_UNIT / 2 * 22;
}
/* CLR.L (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_42a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2763;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_long (srca,0);
}}}}	m68k_incpc (regs, 4);
endlabel2763: ;
return CYCLE_UNIT / 2 * 24;
}
/* CLR.L (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_42b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2764;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_long (srca,0);
}}}}	m68k_incpc (regs, 4);
endlabel2764: ;
return CYCLE_UNIT / 2 * 26;
}
/* CLR.L (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_42b8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2765;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_long (srca,0);
}}}}	m68k_incpc (regs, 4);
endlabel2765: ;
return CYCLE_UNIT / 2 * 24;
}
/* CLR.L (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_42b9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2766;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	SET_CZNV (&regs->ccrflags, FLAGVAL_Z);
	put_long (srca,0);
}}}}	m68k_incpc (regs, 6);
endlabel2766: ;
return CYCLE_UNIT / 2 * 28;
}
/* NEG.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_4400_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 dst;
	optflag_subb (regs, dst, (uae_s8)(src), (uae_s8)(0));
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((dst) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* NEG.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_4410_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 dst;
	optflag_subb (regs, dst, (uae_s8)(src), (uae_s8)(0));
	put_byte (srca,dst);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* NEG.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4418_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 dst;
	optflag_subb (regs, dst, (uae_s8)(src), (uae_s8)(0));
	put_byte (srca,dst);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* NEG.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_4420_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 dst;
	optflag_subb (regs, dst, (uae_s8)(src), (uae_s8)(0));
	put_byte (srca,dst);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* NEG.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4428_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 dst;
	optflag_subb (regs, dst, (uae_s8)(src), (uae_s8)(0));
	put_byte (srca,dst);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* NEG.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4430_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 dst;
	optflag_subb (regs, dst, (uae_s8)(src), (uae_s8)(0));
	put_byte (srca,dst);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* NEG.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4438_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 dst;
	optflag_subb (regs, dst, (uae_s8)(src), (uae_s8)(0));
	put_byte (srca,dst);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* NEG.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4439_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 dst;
	optflag_subb (regs, dst, (uae_s8)(src), (uae_s8)(0));
	put_byte (srca,dst);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* NEG.W Dn */
unsigned long REGPARAM2 CPUFUNC(op_4440_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 dst;
	optflag_subw (regs, dst, (uae_s16)(src), (uae_s16)(0));
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | ((dst) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* NEG.W (An) */
unsigned long REGPARAM2 CPUFUNC(op_4450_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2776;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 dst;
	optflag_subw (regs, dst, (uae_s16)(src), (uae_s16)(0));
	put_word (srca,dst);
}}}}}}	m68k_incpc (regs, 2);
endlabel2776: ;
return CYCLE_UNIT / 2 * 12;
}
/* NEG.W (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4458_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2777;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 dst;
	optflag_subw (regs, dst, (uae_s16)(src), (uae_s16)(0));
	put_word (srca,dst);
}}}}}}	m68k_incpc (regs, 2);
endlabel2777: ;
return CYCLE_UNIT / 2 * 12;
}
/* NEG.W -(An) */
unsigned long REGPARAM2 CPUFUNC(op_4460_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2778;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 dst;
	optflag_subw (regs, dst, (uae_s16)(src), (uae_s16)(0));
	put_word (srca,dst);
}}}}}}	m68k_incpc (regs, 2);
endlabel2778: ;
return CYCLE_UNIT / 2 * 14;
}
/* NEG.W (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4468_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2779;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 dst;
	optflag_subw (regs, dst, (uae_s16)(src), (uae_s16)(0));
	put_word (srca,dst);
}}}}}}	m68k_incpc (regs, 4);
endlabel2779: ;
return CYCLE_UNIT / 2 * 16;
}
/* NEG.W (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4470_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2780;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 dst;
	optflag_subw (regs, dst, (uae_s16)(src), (uae_s16)(0));
	put_word (srca,dst);
}}}}}}	m68k_incpc (regs, 4);
endlabel2780: ;
return CYCLE_UNIT / 2 * 18;
}
/* NEG.W (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4478_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2781;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 dst;
	optflag_subw (regs, dst, (uae_s16)(src), (uae_s16)(0));
	put_word (srca,dst);
}}}}}}	m68k_incpc (regs, 4);
endlabel2781: ;
return CYCLE_UNIT / 2 * 16;
}
/* NEG.W (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4479_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2782;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 dst;
	optflag_subw (regs, dst, (uae_s16)(src), (uae_s16)(0));
	put_word (srca,dst);
}}}}}}	m68k_incpc (regs, 6);
endlabel2782: ;
return CYCLE_UNIT / 2 * 20;
}
/* NEG.L Dn */
unsigned long REGPARAM2 CPUFUNC(op_4480_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 dst;
	optflag_subl (regs, dst, (uae_s32)(src), (uae_s32)(0));
	m68k_dreg (regs, srcreg) = (dst);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* NEG.L (An) */
unsigned long REGPARAM2 CPUFUNC(op_4490_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2784;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 dst;
	optflag_subl (regs, dst, (uae_s32)(src), (uae_s32)(0));
	put_long (srca,dst);
}}}}}}	m68k_incpc (regs, 2);
endlabel2784: ;
return CYCLE_UNIT / 2 * 20;
}
/* NEG.L (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4498_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2785;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 dst;
	optflag_subl (regs, dst, (uae_s32)(src), (uae_s32)(0));
	put_long (srca,dst);
}}}}}}	m68k_incpc (regs, 2);
endlabel2785: ;
return CYCLE_UNIT / 2 * 20;
}
/* NEG.L -(An) */
unsigned long REGPARAM2 CPUFUNC(op_44a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2786;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 dst;
	optflag_subl (regs, dst, (uae_s32)(src), (uae_s32)(0));
	put_long (srca,dst);
}}}}}}	m68k_incpc (regs, 2);
endlabel2786: ;
return CYCLE_UNIT / 2 * 22;
}
/* NEG.L (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_44a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2787;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 dst;
	optflag_subl (regs, dst, (uae_s32)(src), (uae_s32)(0));
	put_long (srca,dst);
}}}}}}	m68k_incpc (regs, 4);
endlabel2787: ;
return CYCLE_UNIT / 2 * 24;
}
/* NEG.L (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_44b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2788;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 dst;
	optflag_subl (regs, dst, (uae_s32)(src), (uae_s32)(0));
	put_long (srca,dst);
}}}}}}	m68k_incpc (regs, 4);
endlabel2788: ;
return CYCLE_UNIT / 2 * 26;
}
/* NEG.L (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_44b8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2789;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 dst;
	optflag_subl (regs, dst, (uae_s32)(src), (uae_s32)(0));
	put_long (srca,dst);
}}}}}}	m68k_incpc (regs, 4);
endlabel2789: ;
return CYCLE_UNIT / 2 * 24;
}
/* NEG.L (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_44b9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2790;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 dst;
	optflag_subl (regs, dst, (uae_s32)(src), (uae_s32)(0));
	put_long (srca,dst);
}}}}}}	m68k_incpc (regs, 6);
endlabel2790: ;
return CYCLE_UNIT / 2 * 28;
}
/* MV2SR.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_44c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
	MakeSR (regs);
	regs->sr &= 0xFF00;
	regs->sr |= src & 0xFF;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	MakeFromSR (regs);
}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* MV2SR.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_44d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2792;
	}
{{	uae_s16 src = get_word (srca);
	MakeSR (regs);
	regs->sr &= 0xFF00;
	regs->sr |= src & 0xFF;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	MakeFromSR (regs);
}}}}	m68k_incpc (regs, 2);
endlabel2792: ;
return CYCLE_UNIT / 2 * 8;
}
/* MV2SR.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_44d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2793;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
	MakeSR (regs);
	regs->sr &= 0xFF00;
	regs->sr |= src & 0xFF;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	MakeFromSR (regs);
}}}}	m68k_incpc (regs, 2);
endlabel2793: ;
return CYCLE_UNIT / 2 * 8;
}
/* MV2SR.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_44e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2794;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
	MakeSR (regs);
	regs->sr &= 0xFF00;
	regs->sr |= src & 0xFF;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	MakeFromSR (regs);
}}}}	m68k_incpc (regs, 2);
endlabel2794: ;
return CYCLE_UNIT / 2 * 10;
}
/* MV2SR.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_44e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2795;
	}
{{	uae_s16 src = get_word (srca);
	MakeSR (regs);
	regs->sr &= 0xFF00;
	regs->sr |= src & 0xFF;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	MakeFromSR (regs);
}}}}	m68k_incpc (regs, 4);
endlabel2795: ;
return CYCLE_UNIT / 2 * 12;
}
/* MV2SR.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_44f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2796;
	}
{{	uae_s16 src = get_word (srca);
	MakeSR (regs);
	regs->sr &= 0xFF00;
	regs->sr |= src & 0xFF;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	MakeFromSR (regs);
}}}}	m68k_incpc (regs, 4);
endlabel2796: ;
return CYCLE_UNIT / 2 * 14;
}
/* MV2SR.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_44f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2797;
	}
{{	uae_s16 src = get_word (srca);
	MakeSR (regs);
	regs->sr &= 0xFF00;
	regs->sr |= src & 0xFF;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	MakeFromSR (regs);
}}}}	m68k_incpc (regs, 4);
endlabel2797: ;
return CYCLE_UNIT / 2 * 12;
}
/* MV2SR.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_44f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2798;
	}
{{	uae_s16 src = get_word (srca);
	MakeSR (regs);
	regs->sr &= 0xFF00;
	regs->sr |= src & 0xFF;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	MakeFromSR (regs);
}}}}	m68k_incpc (regs, 6);
endlabel2798: ;
return CYCLE_UNIT / 2 * 16;
}
/* MV2SR.B (d16,PC) */
unsigned long REGPARAM2 CPUFUNC(op_44fa_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2799;
	}
{{	uae_s16 src = get_word (srca);
	MakeSR (regs);
	regs->sr &= 0xFF00;
	regs->sr |= src & 0xFF;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	MakeFromSR (regs);
}}}}	m68k_incpc (regs, 4);
endlabel2799: ;
return CYCLE_UNIT / 2 * 12;
}
/* MV2SR.B (d8,PC,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_44fb_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2800;
	}
{{	uae_s16 src = get_word (srca);
	MakeSR (regs);
	regs->sr &= 0xFF00;
	regs->sr |= src & 0xFF;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	MakeFromSR (regs);
}}}}	m68k_incpc (regs, 4);
endlabel2800: ;
return CYCLE_UNIT / 2 * 14;
}
/* MV2SR.B #<data>.B */
unsigned long REGPARAM2 CPUFUNC(op_44fc_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = get_word_prefetch (regs, 4);
	MakeSR (regs);
	regs->sr &= 0xFF00;
	regs->sr |= src & 0xFF;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	MakeFromSR (regs);
}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* NOT.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_4600_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 dst = ~src;
	optflag_testb (regs, (uae_s8)(dst));
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((dst) & 0xff);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* NOT.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_4610_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 dst = ~src;
	optflag_testb (regs, (uae_s8)(dst));
	put_byte (srca,dst);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* NOT.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4618_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 dst = ~src;
	optflag_testb (regs, (uae_s8)(dst));
	put_byte (srca,dst);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* NOT.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_4620_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 dst = ~src;
	optflag_testb (regs, (uae_s8)(dst));
	put_byte (srca,dst);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* NOT.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4628_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 dst = ~src;
	optflag_testb (regs, (uae_s8)(dst));
	put_byte (srca,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* NOT.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4630_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 dst = ~src;
	optflag_testb (regs, (uae_s8)(dst));
	put_byte (srca,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* NOT.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4638_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 dst = ~src;
	optflag_testb (regs, (uae_s8)(dst));
	put_byte (srca,dst);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* NOT.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4639_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 dst = ~src;
	optflag_testb (regs, (uae_s8)(dst));
	put_byte (srca,dst);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* NOT.W Dn */
unsigned long REGPARAM2 CPUFUNC(op_4640_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 dst = ~src;
	optflag_testw (regs, (uae_s16)(dst));
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | ((dst) & 0xffff);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* NOT.W (An) */
unsigned long REGPARAM2 CPUFUNC(op_4650_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2811;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 dst = ~src;
	optflag_testw (regs, (uae_s16)(dst));
	put_word (srca,dst);
}}}}}	m68k_incpc (regs, 2);
endlabel2811: ;
return CYCLE_UNIT / 2 * 12;
}
/* NOT.W (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4658_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2812;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 dst = ~src;
	optflag_testw (regs, (uae_s16)(dst));
	put_word (srca,dst);
}}}}}	m68k_incpc (regs, 2);
endlabel2812: ;
return CYCLE_UNIT / 2 * 12;
}
/* NOT.W -(An) */
unsigned long REGPARAM2 CPUFUNC(op_4660_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2813;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 dst = ~src;
	optflag_testw (regs, (uae_s16)(dst));
	put_word (srca,dst);
}}}}}	m68k_incpc (regs, 2);
endlabel2813: ;
return CYCLE_UNIT / 2 * 14;
}
/* NOT.W (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4668_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2814;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 dst = ~src;
	optflag_testw (regs, (uae_s16)(dst));
	put_word (srca,dst);
}}}}}	m68k_incpc (regs, 4);
endlabel2814: ;
return CYCLE_UNIT / 2 * 16;
}
/* NOT.W (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4670_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2815;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 dst = ~src;
	optflag_testw (regs, (uae_s16)(dst));
	put_word (srca,dst);
}}}}}	m68k_incpc (regs, 4);
endlabel2815: ;
return CYCLE_UNIT / 2 * 18;
}
/* NOT.W (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4678_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2816;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 dst = ~src;
	optflag_testw (regs, (uae_s16)(dst));
	put_word (srca,dst);
}}}}}	m68k_incpc (regs, 4);
endlabel2816: ;
return CYCLE_UNIT / 2 * 16;
}
/* NOT.W (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4679_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2817;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 dst = ~src;
	optflag_testw (regs, (uae_s16)(dst));
	put_word (srca,dst);
}}}}}	m68k_incpc (regs, 6);
endlabel2817: ;
return CYCLE_UNIT / 2 * 20;
}
/* NOT.L Dn */
unsigned long REGPARAM2 CPUFUNC(op_4680_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 dst = ~src;
	optflag_testl (regs, (uae_s32)(dst));
	m68k_dreg (regs, srcreg) = (dst);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* NOT.L (An) */
unsigned long REGPARAM2 CPUFUNC(op_4690_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2819;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 dst = ~src;
	optflag_testl (regs, (uae_s32)(dst));
	put_long (srca,dst);
}}}}}	m68k_incpc (regs, 2);
endlabel2819: ;
return CYCLE_UNIT / 2 * 20;
}
/* NOT.L (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4698_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2820;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 dst = ~src;
	optflag_testl (regs, (uae_s32)(dst));
	put_long (srca,dst);
}}}}}	m68k_incpc (regs, 2);
endlabel2820: ;
return CYCLE_UNIT / 2 * 20;
}
/* NOT.L -(An) */
unsigned long REGPARAM2 CPUFUNC(op_46a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2821;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 dst = ~src;
	optflag_testl (regs, (uae_s32)(dst));
	put_long (srca,dst);
}}}}}	m68k_incpc (regs, 2);
endlabel2821: ;
return CYCLE_UNIT / 2 * 22;
}
/* NOT.L (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_46a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2822;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 dst = ~src;
	optflag_testl (regs, (uae_s32)(dst));
	put_long (srca,dst);
}}}}}	m68k_incpc (regs, 4);
endlabel2822: ;
return CYCLE_UNIT / 2 * 24;
}
/* NOT.L (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_46b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2823;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 dst = ~src;
	optflag_testl (regs, (uae_s32)(dst));
	put_long (srca,dst);
}}}}}	m68k_incpc (regs, 4);
endlabel2823: ;
return CYCLE_UNIT / 2 * 26;
}
/* NOT.L (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_46b8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2824;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 dst = ~src;
	optflag_testl (regs, (uae_s32)(dst));
	put_long (srca,dst);
}}}}}	m68k_incpc (regs, 4);
endlabel2824: ;
return CYCLE_UNIT / 2 * 24;
}
/* NOT.L (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_46b9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2825;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 dst = ~src;
	optflag_testl (regs, (uae_s32)(dst));
	put_long (srca,dst);
}}}}}	m68k_incpc (regs, 6);
endlabel2825: ;
return CYCLE_UNIT / 2 * 28;
}
/* MV2SR.W Dn */
unsigned long REGPARAM2 CPUFUNC(op_46c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2826; }
{{	uae_s16 src = m68k_dreg (regs, srcreg);
	regs->sr = src;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	MakeFromSR (regs);
}}}	m68k_incpc (regs, 2);
endlabel2826: ;
return CYCLE_UNIT / 2 * 4;
}
/* MV2SR.W (An) */
unsigned long REGPARAM2 CPUFUNC(op_46d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2827; }
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2827;
	}
{{	uae_s16 src = get_word (srca);
	regs->sr = src;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	MakeFromSR (regs);
}}}}}	m68k_incpc (regs, 2);
endlabel2827: ;
return CYCLE_UNIT / 2 * 8;
}
/* MV2SR.W (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_46d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2828; }
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2828;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
	regs->sr = src;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	MakeFromSR (regs);
}}}}}	m68k_incpc (regs, 2);
endlabel2828: ;
return CYCLE_UNIT / 2 * 8;
}
/* MV2SR.W -(An) */
unsigned long REGPARAM2 CPUFUNC(op_46e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2829; }
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2829;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->sr = src;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	MakeFromSR (regs);
}}}}}	m68k_incpc (regs, 2);
endlabel2829: ;
return CYCLE_UNIT / 2 * 10;
}
/* MV2SR.W (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_46e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2830; }
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2830;
	}
{{	uae_s16 src = get_word (srca);
	regs->sr = src;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	MakeFromSR (regs);
}}}}}	m68k_incpc (regs, 4);
endlabel2830: ;
return CYCLE_UNIT / 2 * 12;
}
/* MV2SR.W (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_46f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2831; }
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2831;
	}
{{	uae_s16 src = get_word (srca);
	regs->sr = src;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	MakeFromSR (regs);
}}}}}	m68k_incpc (regs, 4);
endlabel2831: ;
return CYCLE_UNIT / 2 * 14;
}
/* MV2SR.W (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_46f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2832; }
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2832;
	}
{{	uae_s16 src = get_word (srca);
	regs->sr = src;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	MakeFromSR (regs);
}}}}}	m68k_incpc (regs, 4);
endlabel2832: ;
return CYCLE_UNIT / 2 * 12;
}
/* MV2SR.W (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_46f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2833; }
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2833;
	}
{{	uae_s16 src = get_word (srca);
	regs->sr = src;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	MakeFromSR (regs);
}}}}}	m68k_incpc (regs, 6);
endlabel2833: ;
return CYCLE_UNIT / 2 * 16;
}
/* MV2SR.W (d16,PC) */
unsigned long REGPARAM2 CPUFUNC(op_46fa_5)(uae_u32 opcode, struct regstruct *regs)
{
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2834; }
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2834;
	}
{{	uae_s16 src = get_word (srca);
	regs->sr = src;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	MakeFromSR (regs);
}}}}}	m68k_incpc (regs, 4);
endlabel2834: ;
return CYCLE_UNIT / 2 * 12;
}
/* MV2SR.W (d8,PC,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_46fb_5)(uae_u32 opcode, struct regstruct *regs)
{
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2835; }
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2835;
	}
{{	uae_s16 src = get_word (srca);
	regs->sr = src;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	MakeFromSR (regs);
}}}}}	m68k_incpc (regs, 4);
endlabel2835: ;
return CYCLE_UNIT / 2 * 14;
}
/* MV2SR.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_46fc_5)(uae_u32 opcode, struct regstruct *regs)
{
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2836; }
{{	uae_s16 src = get_word_prefetch (regs, 4);
	regs->sr = src;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	MakeFromSR (regs);
}}}	m68k_incpc (regs, 4);
endlabel2836: ;
return CYCLE_UNIT / 2 * 8;
}
/* NBCD.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_4800_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 newv_lo = - (src & 0xF) - GET_XFLG (&regs->ccrflags);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (&regs->ccrflags, cflg ? 1 : 0);
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((newv) & 0xff);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* NBCD.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_4810_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 newv_lo = - (src & 0xF) - GET_XFLG (&regs->ccrflags);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (&regs->ccrflags, cflg ? 1 : 0);
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (srca,newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* NBCD.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4818_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 newv_lo = - (src & 0xF) - GET_XFLG (&regs->ccrflags);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (&regs->ccrflags, cflg ? 1 : 0);
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (srca,newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* NBCD.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_4820_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 newv_lo = - (src & 0xF) - GET_XFLG (&regs->ccrflags);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (&regs->ccrflags, cflg ? 1 : 0);
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (srca,newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* NBCD.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4828_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 newv_lo = - (src & 0xF) - GET_XFLG (&regs->ccrflags);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (&regs->ccrflags, cflg ? 1 : 0);
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (srca,newv);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* NBCD.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4830_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 newv_lo = - (src & 0xF) - GET_XFLG (&regs->ccrflags);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (&regs->ccrflags, cflg ? 1 : 0);
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (srca,newv);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* NBCD.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4838_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 newv_lo = - (src & 0xF) - GET_XFLG (&regs->ccrflags);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (&regs->ccrflags, cflg ? 1 : 0);
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (srca,newv);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* NBCD.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4839_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u16 newv_lo = - (src & 0xF) - GET_XFLG (&regs->ccrflags);
	uae_u16 newv_hi = - (src & 0xF0);
	uae_u16 newv;
	int cflg;
	if (newv_lo > 9) { newv_lo -= 6; }
	newv = newv_hi + newv_lo;	cflg = (newv & 0x1F0) > 0x90;
	if (cflg) newv -= 0x60;
	SET_CFLG (&regs->ccrflags, cflg ? 1 : 0);
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (srca,newv);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* SWAP.W Dn */
unsigned long REGPARAM2 CPUFUNC(op_4840_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 dst = ((src >> 16)&0xFFFF) | ((src&0xFFFF)<<16);
	optflag_testl (regs, (uae_s32)(dst));
	m68k_dreg (regs, srcreg) = (dst);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* PEA.L (An) */
unsigned long REGPARAM2 CPUFUNC(op_4850_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, 7) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2846;
	}
{	m68k_areg (regs, 7) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_long (dsta,srca);
}}}}	m68k_incpc (regs, 2);
endlabel2846: ;
return CYCLE_UNIT / 2 * 12;
}
/* PEA.L (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4868_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, 7) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2847;
	}
{	m68k_areg (regs, 7) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,srca);
}}}}	m68k_incpc (regs, 4);
endlabel2847: ;
return CYCLE_UNIT / 2 * 16;
}
/* PEA.L (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4870_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uaecptr dsta;
	dsta = m68k_areg (regs, 7) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2848;
	}
{	m68k_areg (regs, 7) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,srca);
}}}}	m68k_incpc (regs, 4);
endlabel2848: ;
return CYCLE_UNIT / 2 * 16;
}
/* PEA.L (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4878_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, 7) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2849;
	}
{	m68k_areg (regs, 7) = dsta;
	put_long (dsta,srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
}}}}	m68k_incpc (regs, 4);
endlabel2849: ;
return CYCLE_UNIT / 2 * 16;
}
/* PEA.L (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4879_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, 7) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 6, dsta);
		goto endlabel2850;
	}
{	m68k_areg (regs, 7) = dsta;
	put_long (dsta,srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
}}}}	m68k_incpc (regs, 6);
endlabel2850: ;
return CYCLE_UNIT / 2 * 20;
}
/* PEA.L (d16,PC) */
unsigned long REGPARAM2 CPUFUNC(op_487a_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uaecptr dsta;
	dsta = m68k_areg (regs, 7) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2851;
	}
{	m68k_areg (regs, 7) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,srca);
}}}}	m68k_incpc (regs, 4);
endlabel2851: ;
return CYCLE_UNIT / 2 * 16;
}
/* PEA.L (d8,PC,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_487b_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uaecptr dsta;
	dsta = m68k_areg (regs, 7) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, dsta);
		goto endlabel2852;
	}
{	m68k_areg (regs, 7) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,srca);
}}}}	m68k_incpc (regs, 4);
endlabel2852: ;
return CYCLE_UNIT / 2 * 16;
}
/* EXT.W Dn */
unsigned long REGPARAM2 CPUFUNC(op_4880_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 dst = (uae_s16)(uae_s8)src;
	optflag_testw (regs, (uae_s16)(dst));
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | ((dst) & 0xffff);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* MVMLE.W #<data>.W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_4890_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
{	uaecptr srca = m68k_areg (regs, dstreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2854;
	}
{	m68k_incpc (regs, 4);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { put_word(srca, m68k_dreg (regs, movem_index1[dmask])); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { put_word(srca, m68k_areg (regs, movem_index1[amask])); srca += 2; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2854: ;
return CYCLE_UNIT / 2 * 8;
}
/* MVMLE.W #<data>.W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_48a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
{	uaecptr srca;
	srca = m68k_areg (regs, dstreg) - 0;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2855;
	}
{	m68k_incpc (regs, 4);
{	uae_u16 amask = mask & 0xff, dmask = (mask >> 8) & 0xff;
	while (amask) { srca -= 2; put_word(srca, m68k_areg (regs, movem_index2[amask])); amask = movem_next[amask]; }
	while (dmask) { srca -= 2; put_word(srca, m68k_dreg (regs, movem_index2[dmask])); dmask = movem_next[dmask]; }
	m68k_areg (regs, dstreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2855: ;
return CYCLE_UNIT / 2 * 10;
}
/* MVMLE.W #<data>.W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_48a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
{	uaecptr srca = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2856;
	}
{	m68k_incpc (regs, 6);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { put_word(srca, m68k_dreg (regs, movem_index1[dmask])); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { put_word(srca, m68k_areg (regs, movem_index1[amask])); srca += 2; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2856: ;
return CYCLE_UNIT / 2 * 12;
}
/* MVMLE.W #<data>.W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_48b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2857;
	}
{	m68k_incpc (regs, 6);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { put_word(srca, m68k_dreg (regs, movem_index1[dmask])); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { put_word(srca, m68k_areg (regs, movem_index1[amask])); srca += 2; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2857: ;
return CYCLE_UNIT / 2 * 14;
}
/* MVMLE.W #<data>.W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_48b8_5)(uae_u32 opcode, struct regstruct *regs)
{
{	uae_u16 mask = get_word_prefetch (regs, 4);
{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2858;
	}
{	m68k_incpc (regs, 6);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { put_word(srca, m68k_dreg (regs, movem_index1[dmask])); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { put_word(srca, m68k_areg (regs, movem_index1[amask])); srca += 2; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2858: ;
return CYCLE_UNIT / 2 * 12;
}
/* MVMLE.W #<data>.W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_48b9_5)(uae_u32 opcode, struct regstruct *regs)
{
{	uae_u16 mask = get_word_prefetch (regs, 4);
{	uaecptr srca = get_long_prefetch (regs, 6);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2859;
	}
{	m68k_incpc (regs, 8);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { put_word(srca, m68k_dreg (regs, movem_index1[dmask])); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { put_word(srca, m68k_areg (regs, movem_index1[amask])); srca += 2; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2859: ;
return CYCLE_UNIT / 2 * 16;
}
/* EXT.L Dn */
unsigned long REGPARAM2 CPUFUNC(op_48c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 dst = (uae_s32)(uae_s16)src;
	optflag_testl (regs, (uae_s32)(dst));
	m68k_dreg (regs, srcreg) = (dst);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* MVMLE.L #<data>.W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_48d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
{	uaecptr srca = m68k_areg (regs, dstreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2861;
	}
{	m68k_incpc (regs, 4);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { put_long(srca, m68k_dreg (regs, movem_index1[dmask])); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { put_long(srca, m68k_areg (regs, movem_index1[amask])); srca += 4; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2861: ;
return CYCLE_UNIT / 2 * 8;
}
/* MVMLE.L #<data>.W,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_48e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
{	uaecptr srca;
	srca = m68k_areg (regs, dstreg) - 0;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2862;
	}
{	m68k_incpc (regs, 4);
{	uae_u16 amask = mask & 0xff, dmask = (mask >> 8) & 0xff;
	while (amask) { srca -= 4; put_long(srca, m68k_areg (regs, movem_index2[amask])); amask = movem_next[amask]; }
	while (dmask) { srca -= 4; put_long(srca, m68k_dreg (regs, movem_index2[dmask])); dmask = movem_next[dmask]; }
	m68k_areg (regs, dstreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2862: ;
return CYCLE_UNIT / 2 * 10;
}
/* MVMLE.L #<data>.W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_48e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
{	uaecptr srca = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2863;
	}
{	m68k_incpc (regs, 6);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { put_long(srca, m68k_dreg (regs, movem_index1[dmask])); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { put_long(srca, m68k_areg (regs, movem_index1[amask])); srca += 4; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2863: ;
return CYCLE_UNIT / 2 * 12;
}
/* MVMLE.L #<data>.W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_48f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2864;
	}
{	m68k_incpc (regs, 6);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { put_long(srca, m68k_dreg (regs, movem_index1[dmask])); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { put_long(srca, m68k_areg (regs, movem_index1[amask])); srca += 4; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2864: ;
return CYCLE_UNIT / 2 * 14;
}
/* MVMLE.L #<data>.W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_48f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{	uae_u16 mask = get_word_prefetch (regs, 4);
{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2865;
	}
{	m68k_incpc (regs, 6);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { put_long(srca, m68k_dreg (regs, movem_index1[dmask])); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { put_long(srca, m68k_areg (regs, movem_index1[amask])); srca += 4; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2865: ;
return CYCLE_UNIT / 2 * 12;
}
/* MVMLE.L #<data>.W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_48f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{	uae_u16 mask = get_word_prefetch (regs, 4);
{	uaecptr srca = get_long_prefetch (regs, 6);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2866;
	}
{	m68k_incpc (regs, 8);
{	uae_u16 dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
	while (dmask) { put_long(srca, m68k_dreg (regs, movem_index1[dmask])); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { put_long(srca, m68k_areg (regs, movem_index1[amask])); srca += 4; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}endlabel2866: ;
return CYCLE_UNIT / 2 * 16;
}
/* EXT.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_49c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 dst = (uae_s32)(uae_s8)src;
	optflag_testl (regs, (uae_s32)(dst));
	m68k_dreg (regs, srcreg) = (dst);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* TST.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_4a00_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	optflag_testb (regs, (uae_s8)(src));
}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* TST.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_4a10_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	optflag_testb (regs, (uae_s8)(src));
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 8;
}
/* TST.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4a18_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	optflag_testb (regs, (uae_s8)(src));
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 8;
}
/* TST.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_4a20_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	optflag_testb (regs, (uae_s8)(src));
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 10;
}
/* TST.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4a28_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	optflag_testb (regs, (uae_s8)(src));
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* TST.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4a30_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	optflag_testb (regs, (uae_s8)(src));
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 14;
}
/* TST.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4a38_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	optflag_testb (regs, (uae_s8)(src));
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* TST.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4a39_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	optflag_testb (regs, (uae_s8)(src));
}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 16;
}
/* TST.W Dn */
unsigned long REGPARAM2 CPUFUNC(op_4a40_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	optflag_testw (regs, (uae_s16)(src));
}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* TST.W (An) */
unsigned long REGPARAM2 CPUFUNC(op_4a50_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2877;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	optflag_testw (regs, (uae_s16)(src));
}}}}	m68k_incpc (regs, 2);
endlabel2877: ;
return CYCLE_UNIT / 2 * 8;
}
/* TST.W (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4a58_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2878;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	optflag_testw (regs, (uae_s16)(src));
}}}}	m68k_incpc (regs, 2);
endlabel2878: ;
return CYCLE_UNIT / 2 * 8;
}
/* TST.W -(An) */
unsigned long REGPARAM2 CPUFUNC(op_4a60_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2879;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	optflag_testw (regs, (uae_s16)(src));
}}}}	m68k_incpc (regs, 2);
endlabel2879: ;
return CYCLE_UNIT / 2 * 10;
}
/* TST.W (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4a68_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2880;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	optflag_testw (regs, (uae_s16)(src));
}}}}	m68k_incpc (regs, 4);
endlabel2880: ;
return CYCLE_UNIT / 2 * 12;
}
/* TST.W (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4a70_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2881;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	optflag_testw (regs, (uae_s16)(src));
}}}}	m68k_incpc (regs, 4);
endlabel2881: ;
return CYCLE_UNIT / 2 * 14;
}
/* TST.W (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4a78_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2882;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	optflag_testw (regs, (uae_s16)(src));
}}}}	m68k_incpc (regs, 4);
endlabel2882: ;
return CYCLE_UNIT / 2 * 12;
}
/* TST.W (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4a79_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2883;
	}
{{	uae_s16 src = get_word (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	optflag_testw (regs, (uae_s16)(src));
}}}}	m68k_incpc (regs, 6);
endlabel2883: ;
return CYCLE_UNIT / 2 * 16;
}
/* TST.L Dn */
unsigned long REGPARAM2 CPUFUNC(op_4a80_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	optflag_testl (regs, (uae_s32)(src));
}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* TST.L (An) */
unsigned long REGPARAM2 CPUFUNC(op_4a90_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2885;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	optflag_testl (regs, (uae_s32)(src));
}}}}	m68k_incpc (regs, 2);
endlabel2885: ;
return CYCLE_UNIT / 2 * 12;
}
/* TST.L (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4a98_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2886;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	optflag_testl (regs, (uae_s32)(src));
}}}}	m68k_incpc (regs, 2);
endlabel2886: ;
return CYCLE_UNIT / 2 * 12;
}
/* TST.L -(An) */
unsigned long REGPARAM2 CPUFUNC(op_4aa0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2887;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	optflag_testl (regs, (uae_s32)(src));
}}}}	m68k_incpc (regs, 2);
endlabel2887: ;
return CYCLE_UNIT / 2 * 14;
}
/* TST.L (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4aa8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2888;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	optflag_testl (regs, (uae_s32)(src));
}}}}	m68k_incpc (regs, 4);
endlabel2888: ;
return CYCLE_UNIT / 2 * 16;
}
/* TST.L (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4ab0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2889;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	optflag_testl (regs, (uae_s32)(src));
}}}}	m68k_incpc (regs, 4);
endlabel2889: ;
return CYCLE_UNIT / 2 * 18;
}
/* TST.L (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4ab8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2890;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	optflag_testl (regs, (uae_s32)(src));
}}}}	m68k_incpc (regs, 4);
endlabel2890: ;
return CYCLE_UNIT / 2 * 16;
}
/* TST.L (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4ab9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel2891;
	}
{{	uae_s32 src = get_long (srca);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	optflag_testl (regs, (uae_s32)(src));
}}}}	m68k_incpc (regs, 6);
endlabel2891: ;
return CYCLE_UNIT / 2 * 20;
}
/* TAS.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_4ac0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src |= 0x80;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((src) & 0xff);
}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* TAS.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_4ad0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src |= 0x80;
	put_byte (srca,src);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* TAS.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4ad8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src |= 0x80;
	put_byte (srca,src);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* TAS.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_4ae0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	src |= 0x80;
	put_byte (srca,src);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* TAS.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4ae8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src |= 0x80;
	put_byte (srca,src);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* TAS.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4af0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src |= 0x80;
	put_byte (srca,src);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* TAS.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4af8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	src |= 0x80;
	put_byte (srca,src);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* TAS.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4af9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	src |= 0x80;
	put_byte (srca,src);
}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* MVMEL.W #<data>.W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_4c90_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca = m68k_areg (regs, dstreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2900;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
}}}}	m68k_incpc (regs, 4);
endlabel2900: ;
return CYCLE_UNIT / 2 * 8;
}
/* MVMEL.W #<data>.W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4c98_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca = m68k_areg (regs, dstreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2901;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; amask = movem_next[amask]; }
	m68k_areg (regs, dstreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
}}}}	m68k_incpc (regs, 4);
endlabel2901: ;
return CYCLE_UNIT / 2 * 8;
}
/* MVMEL.W #<data>.W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4ca8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2902;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
}}}}	m68k_incpc (regs, 6);
endlabel2902: ;
return CYCLE_UNIT / 2 * 12;
}
/* MVMEL.W #<data>.W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4cb0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2903;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
}}}}	m68k_incpc (regs, 6);
endlabel2903: ;
return CYCLE_UNIT / 2 * 14;
}
/* MVMEL.W #<data>.W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4cb8_5)(uae_u32 opcode, struct regstruct *regs)
{
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2904;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
}}}}	m68k_incpc (regs, 6);
endlabel2904: ;
return CYCLE_UNIT / 2 * 12;
}
/* MVMEL.W #<data>.W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4cb9_5)(uae_u32 opcode, struct regstruct *regs)
{
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca = get_long_prefetch (regs, 6);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2905;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
}}}}	m68k_incpc (regs, 8);
endlabel2905: ;
return CYCLE_UNIT / 2 * 16;
}
/* MVMEL.W #<data>.W,(d16,PC) */
unsigned long REGPARAM2 CPUFUNC(op_4cba_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = 2;
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca = m68k_getpc (regs) + 4;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2906;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
}}}}	m68k_incpc (regs, 6);
endlabel2906: ;
return CYCLE_UNIT / 2 * 12;
}
/* MVMEL.W #<data>.W,(d8,PC,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4cbb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = 3;
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 4;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 6));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2907;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = (uae_s32)(uae_s16)get_word(srca); srca += 2; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
}}}}	m68k_incpc (regs, 6);
endlabel2907: ;
return CYCLE_UNIT / 2 * 14;
}
/* MVMEL.L #<data>.W,(An) */
unsigned long REGPARAM2 CPUFUNC(op_4cd0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca = m68k_areg (regs, dstreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2908;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = get_long(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = get_long(srca); srca += 4; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
}}}}	m68k_incpc (regs, 4);
endlabel2908: ;
return CYCLE_UNIT / 2 * 8;
}
/* MVMEL.L #<data>.W,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_4cd8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca = m68k_areg (regs, dstreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2909;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = get_long(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = get_long(srca); srca += 4; amask = movem_next[amask]; }
	m68k_areg (regs, dstreg) = srca;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
}}}}	m68k_incpc (regs, 4);
endlabel2909: ;
return CYCLE_UNIT / 2 * 8;
}
/* MVMEL.L #<data>.W,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4ce8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2910;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = get_long(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = get_long(srca); srca += 4; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
}}}}	m68k_incpc (regs, 6);
endlabel2910: ;
return CYCLE_UNIT / 2 * 12;
}
/* MVMEL.L #<data>.W,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4cf0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = opcode & 7;
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 6));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2911;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = get_long(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = get_long(srca); srca += 4; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
}}}}	m68k_incpc (regs, 6);
endlabel2911: ;
return CYCLE_UNIT / 2 * 14;
}
/* MVMEL.L #<data>.W,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4cf8_5)(uae_u32 opcode, struct regstruct *regs)
{
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2912;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = get_long(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = get_long(srca); srca += 4; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
}}}}	m68k_incpc (regs, 6);
endlabel2912: ;
return CYCLE_UNIT / 2 * 12;
}
/* MVMEL.L #<data>.W,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4cf9_5)(uae_u32 opcode, struct regstruct *regs)
{
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca = get_long_prefetch (regs, 6);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2913;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = get_long(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = get_long(srca); srca += 4; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 10);
}}}}	m68k_incpc (regs, 8);
endlabel2913: ;
return CYCLE_UNIT / 2 * 16;
}
/* MVMEL.L #<data>.W,(d16,PC) */
unsigned long REGPARAM2 CPUFUNC(op_4cfa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = 2;
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr srca = m68k_getpc (regs) + 4;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 6);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2914;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = get_long(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = get_long(srca); srca += 4; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
}}}}	m68k_incpc (regs, 6);
endlabel2914: ;
return CYCLE_UNIT / 2 * 12;
}
/* MVMEL.L #<data>.W,(d8,PC,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4cfb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = 3;
{	uae_u16 mask = get_word_prefetch (regs, 4);
	unsigned int dmask = mask & 0xff, amask = (mask >> 8) & 0xff;
{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 4;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 6));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 4, srca);
		goto endlabel2915;
	}
{{	while (dmask) { m68k_dreg (regs, movem_index1[dmask]) = get_long(srca); srca += 4; dmask = movem_next[dmask]; }
	while (amask) { m68k_areg (regs, movem_index1[amask]) = get_long(srca); srca += 4; amask = movem_next[amask]; }
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
}}}}	m68k_incpc (regs, 6);
endlabel2915: ;
return CYCLE_UNIT / 2 * 14;
}
/* TRAP.L #<data> */
unsigned long REGPARAM2 CPUFUNC(op_4e40_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 15);
{{	uae_u32 src = srcreg;
	m68k_incpc (regs, 2);
	Exception (src + 32, regs, 0);
}}return CYCLE_UNIT / 2 * 0;
}
/* LINK.W An,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_4e50_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr olda;
	olda = m68k_areg (regs, 7) - 4;
	if (olda & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, olda);
		goto endlabel2917;
	}
{	m68k_areg (regs, 7) = olda;
{	uae_s32 src = m68k_areg (regs, srcreg);
	put_long (olda,src);
	m68k_areg (regs, srcreg) = (m68k_areg (regs, 7));
{	uae_s16 offs = get_word_prefetch (regs, 4);
	m68k_areg (regs, 7) += offs;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
}}}}}	m68k_incpc (regs, 4);
endlabel2917: ;
return CYCLE_UNIT / 2 * 16;
}
/* UNLK.L An */
unsigned long REGPARAM2 CPUFUNC(op_4e58_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s32 src = m68k_areg (regs, srcreg);
	m68k_areg (regs, 7) = src;
{	uaecptr olda = m68k_areg (regs, 7);
	if (olda & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, olda);
		goto endlabel2918;
	}
{{	uae_s32 old = get_long (olda);
	m68k_areg (regs, 7) += 4;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_areg (regs, srcreg) = (old);
}}}}}	m68k_incpc (regs, 2);
endlabel2918: ;
return CYCLE_UNIT / 2 * 12;
}
/* MVR2USP.L An */
unsigned long REGPARAM2 CPUFUNC(op_4e60_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2919; }
{{	uae_s32 src = m68k_areg (regs, srcreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	regs->usp = src;
}}}	m68k_incpc (regs, 2);
endlabel2919: ;
return CYCLE_UNIT / 2 * 4;
}
/* MVUSP2R.L An */
unsigned long REGPARAM2 CPUFUNC(op_4e68_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2920; }
{{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_areg (regs, srcreg) = (regs->usp);
}}}	m68k_incpc (regs, 2);
endlabel2920: ;
return CYCLE_UNIT / 2 * 4;
}
/* RESET.L  */
unsigned long REGPARAM2 CPUFUNC(op_4e70_5)(uae_u32 opcode, struct regstruct *regs)
{
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2921; }
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	cpureset();
	regs->irc = get_iword (regs, 4);
}}	m68k_incpc (regs, 2);
endlabel2921: ;
return CYCLE_UNIT / 2 * 4;
}
/* NOP.L  */
unsigned long REGPARAM2 CPUFUNC(op_4e71_5)(uae_u32 opcode, struct regstruct *regs)
{
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* STOP.L #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_4e72_5)(uae_u32 opcode, struct regstruct *regs)
{
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2923; }
{{	uae_s16 src = get_word_prefetch (regs, 4);
	regs->sr = src;
	MakeFromSR (regs);
	m68k_setstopped (regs, 1);
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel2923: ;
return CYCLE_UNIT / 2 * 12;
}
/* RTE.L  */
unsigned long REGPARAM2 CPUFUNC(op_4e73_5)(uae_u32 opcode, struct regstruct *regs)
{
{if (!regs->s) { Exception (8, regs, 0); goto endlabel2924; }
{{	uaecptr sra = m68k_areg (regs, 7);
	if (sra & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, sra);
		goto endlabel2924;
	}
{{	uae_s16 sr = get_word (sra);
	m68k_areg (regs, 7) += 2;
{	uaecptr pca = m68k_areg (regs, 7);
	if (pca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, pca);
		goto endlabel2924;
	}
{{	uae_s32 pc = get_long (pca);
	m68k_areg (regs, 7) += 4;
	regs->sr = sr; m68k_setpc (regs, pc);
	MakeFromSR (regs);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}}}endlabel2924: ;
return CYCLE_UNIT / 2 * 20;
}
/* RTD.L #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_4e74_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr pca = m68k_areg (regs, 7);
	if (pca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, pca);
		goto endlabel2925;
	}
{{	uae_s32 pc = get_long (pca);
	m68k_areg (regs, 7) += 4;
{	uae_s16 offs = get_word_prefetch (regs, 4);
	m68k_areg (regs, 7) += offs;
	if (pc & 1)
		exception3 (0x4e74, m68k_getpc (regs), pc);
	else
		m68k_setpc (regs, pc);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}endlabel2925: ;
return CYCLE_UNIT / 2 * 20;
}
/* RTS.L  */
unsigned long REGPARAM2 CPUFUNC(op_4e75_5)(uae_u32 opcode, struct regstruct *regs)
{
{	m68k_do_rts (regs);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}return CYCLE_UNIT / 2 * 8;
}
/* TRAPV.L  */
unsigned long REGPARAM2 CPUFUNC(op_4e76_5)(uae_u32 opcode, struct regstruct *regs)
{
{	m68k_incpc (regs, 2);
	if (GET_VFLG (&regs->ccrflags)) {
		Exception (7, regs, m68k_getpc (regs));
		goto endlabel2927;
	}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}endlabel2927: ;
return CYCLE_UNIT / 2 * 4;
}
/* RTR.L  */
unsigned long REGPARAM2 CPUFUNC(op_4e77_5)(uae_u32 opcode, struct regstruct *regs)
{
{	MakeSR (regs);
{	uaecptr sra = m68k_areg (regs, 7);
	if (sra & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, sra);
		goto endlabel2928;
	}
{{	uae_s16 sr = get_word (sra);
	m68k_areg (regs, 7) += 2;
{	uaecptr pca = m68k_areg (regs, 7);
	if (pca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, pca);
		goto endlabel2928;
	}
{{	uae_s32 pc = get_long (pca);
	m68k_areg (regs, 7) += 4;
	regs->sr &= 0xFF00; sr &= 0xFF;
	regs->sr |= sr; m68k_setpc (regs, pc);
	MakeFromSR (regs);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}}}}}endlabel2928: ;
return CYCLE_UNIT / 2 * 20;
}
/* JSR.L (An) */
unsigned long REGPARAM2 CPUFUNC(op_4e90_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uaecptr oldpc = m68k_getpc (regs) + 2;
	if (srca & 1) {
		exception3i (opcode, oldpc, srca);
		goto endlabel2929;
	}
	m68k_setpc (regs, srca);
	get_word_prefetch (regs, 0);
	m68k_areg (regs, 7) -= 4;
	put_long (m68k_areg (regs, 7), oldpc);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel2929: ;
return CYCLE_UNIT / 2 * 8;
}
/* JSR.L (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4ea8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)regs->irc;
{	uaecptr oldpc = m68k_getpc (regs) + 4;
	if (srca & 1) {
		exception3i (opcode, oldpc, srca);
		goto endlabel2930;
	}
	m68k_setpc (regs, srca);
	get_word_prefetch (regs, 0);
	m68k_areg (regs, 7) -= 4;
	put_long (m68k_areg (regs, 7), oldpc);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel2930: ;
return CYCLE_UNIT / 2 * 8;
}
/* JSR.L (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4eb0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), regs->irc);
{	uaecptr oldpc = m68k_getpc (regs) + 4;
	if (srca & 1) {
		exception3i (opcode, oldpc, srca);
		goto endlabel2931;
	}
	m68k_setpc (regs, srca);
	get_word_prefetch (regs, 0);
	m68k_areg (regs, 7) -= 4;
	put_long (m68k_areg (regs, 7), oldpc);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel2931: ;
return CYCLE_UNIT / 2 * 8;
}
/* JSR.L (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4eb8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)regs->irc;
{	uaecptr oldpc = m68k_getpc (regs) + 4;
	if (srca & 1) {
		exception3i (opcode, oldpc, srca);
		goto endlabel2932;
	}
	m68k_setpc (regs, srca);
	get_word_prefetch (regs, 0);
	m68k_areg (regs, 7) -= 4;
	put_long (m68k_areg (regs, 7), oldpc);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel2932: ;
return CYCLE_UNIT / 2 * 8;
}
/* JSR.L (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4eb9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca;
	srca  = get_word_prefetch (regs, 4) << 16;
	srca |= regs->irc;
{	uaecptr oldpc = m68k_getpc (regs) + 6;
	if (srca & 1) {
		exception3i (opcode, oldpc, srca);
		goto endlabel2933;
	}
	m68k_setpc (regs, srca);
	get_word_prefetch (regs, 0);
	m68k_areg (regs, 7) -= 4;
	put_long (m68k_areg (regs, 7), oldpc);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel2933: ;
return CYCLE_UNIT / 2 * 12;
}
/* JSR.L (d16,PC) */
unsigned long REGPARAM2 CPUFUNC(op_4eba_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)regs->irc;
{	uaecptr oldpc = m68k_getpc (regs) + 4;
	if (srca & 1) {
		exception3i (opcode, oldpc, srca);
		goto endlabel2934;
	}
	m68k_setpc (regs, srca);
	get_word_prefetch (regs, 0);
	m68k_areg (regs, 7) -= 4;
	put_long (m68k_areg (regs, 7), oldpc);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel2934: ;
return CYCLE_UNIT / 2 * 8;
}
/* JSR.L (d8,PC,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4ebb_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, regs->irc);
{	uaecptr oldpc = m68k_getpc (regs) + 4;
	if (srca & 1) {
		exception3i (opcode, oldpc, srca);
		goto endlabel2935;
	}
	m68k_setpc (regs, srca);
	get_word_prefetch (regs, 0);
	m68k_areg (regs, 7) -= 4;
	put_long (m68k_areg (regs, 7), oldpc);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel2935: ;
return CYCLE_UNIT / 2 * 8;
}
/* JMP.L (An) */
unsigned long REGPARAM2 CPUFUNC(op_4ed0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3i (opcode, m68k_getpc (regs) + 6, srca);
		goto endlabel2936;
	}
	m68k_setpc (regs, srca);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel2936: ;
return CYCLE_UNIT / 2 * 8;
}
/* JMP.L (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_4ee8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)regs->irc;
	if (srca & 1) {
		exception3i (opcode, m68k_getpc (regs) + 6, srca);
		goto endlabel2937;
	}
	m68k_setpc (regs, srca);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel2937: ;
return CYCLE_UNIT / 2 * 8;
}
/* JMP.L (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4ef0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), regs->irc);
	if (srca & 1) {
		exception3i (opcode, m68k_getpc (regs) + 6, srca);
		goto endlabel2938;
	}
	m68k_setpc (regs, srca);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel2938: ;
return CYCLE_UNIT / 2 * 8;
}
/* JMP.L (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_4ef8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)regs->irc;
	if (srca & 1) {
		exception3i (opcode, m68k_getpc (regs) + 6, srca);
		goto endlabel2939;
	}
	m68k_setpc (regs, srca);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel2939: ;
return CYCLE_UNIT / 2 * 8;
}
/* JMP.L (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_4ef9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca;
	srca  = get_word_prefetch (regs, 4) << 16;
	srca |= regs->irc;
	if (srca & 1) {
		exception3i (opcode, m68k_getpc (regs) + 6, srca);
		goto endlabel2940;
	}
	m68k_setpc (regs, srca);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel2940: ;
return CYCLE_UNIT / 2 * 12;
}
/* JMP.L (d16,PC) */
unsigned long REGPARAM2 CPUFUNC(op_4efa_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)regs->irc;
	if (srca & 1) {
		exception3i (opcode, m68k_getpc (regs) + 6, srca);
		goto endlabel2941;
	}
	m68k_setpc (regs, srca);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel2941: ;
return CYCLE_UNIT / 2 * 8;
}
/* JMP.L (d8,PC,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_4efb_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, regs->irc);
	if (srca & 1) {
		exception3i (opcode, m68k_getpc (regs) + 6, srca);
		goto endlabel2942;
	}
	m68k_setpc (regs, srca);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel2942: ;
return CYCLE_UNIT / 2 * 8;
}
/* ADD.B #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_5000_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADD.B #<data>,(An) */
unsigned long REGPARAM2 CPUFUNC(op_5010_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* ADD.B #<data>,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_5018_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* ADD.B #<data>,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_5020_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* ADD.B #<data>,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_5028_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* ADD.B #<data>,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_5030_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* ADD.B #<data>,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_5038_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
{{	uae_u32 src = srcreg;
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
#endif

#ifdef PART_5
/* ADD.B #<data>,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_5039_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
{{	uae_u32 src = srcreg;
{	uaecptr dsta = get_long_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* ADD.W #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_5040_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADDA.W #<data>,An */
unsigned long REGPARAM2 CPUFUNC(op_5048_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADD.W #<data>,(An) */
unsigned long REGPARAM2 CPUFUNC(op_5050_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2953;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel2953: ;
return CYCLE_UNIT / 2 * 12;
}
/* ADD.W #<data>,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_5058_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2954;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel2954: ;
return CYCLE_UNIT / 2 * 12;
}
/* ADD.W #<data>,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_5060_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2955;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel2955: ;
return CYCLE_UNIT / 2 * 14;
}
/* ADD.W #<data>,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_5068_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2956;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel2956: ;
return CYCLE_UNIT / 2 * 16;
}
/* ADD.W #<data>,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_5070_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2957;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel2957: ;
return CYCLE_UNIT / 2 * 18;
}
/* ADD.W #<data>,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_5078_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
{{	uae_u32 src = srcreg;
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2958;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel2958: ;
return CYCLE_UNIT / 2 * 16;
}
/* ADD.W #<data>,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_5079_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
{{	uae_u32 src = srcreg;
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2959;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel2959: ;
return CYCLE_UNIT / 2 * 20;
}
/* ADD.L #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_5080_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADDA.L #<data>,An */
unsigned long REGPARAM2 CPUFUNC(op_5088_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADD.L #<data>,(An) */
unsigned long REGPARAM2 CPUFUNC(op_5090_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2962;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel2962: ;
return CYCLE_UNIT / 2 * 20;
}
/* ADD.L #<data>,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_5098_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2963;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel2963: ;
return CYCLE_UNIT / 2 * 20;
}
/* ADD.L #<data>,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_50a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2964;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel2964: ;
return CYCLE_UNIT / 2 * 22;
}
/* ADD.L #<data>,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_50a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2965;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel2965: ;
return CYCLE_UNIT / 2 * 24;
}
/* ADD.L #<data>,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_50b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2966;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel2966: ;
return CYCLE_UNIT / 2 * 26;
}
/* ADD.L #<data>,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_50b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
{{	uae_u32 src = srcreg;
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2967;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel2967: ;
return CYCLE_UNIT / 2 * 24;
}
/* ADD.L #<data>,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_50b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
{{	uae_u32 src = srcreg;
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2968;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel2968: ;
return CYCLE_UNIT / 2 * 28;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_50c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 0) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_50c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 0)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel2970;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel2970: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_50d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 0) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_50d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 0) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_50e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 0) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_50e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 0) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_50f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 0) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_50f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 0) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_50f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 0) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* SUB.B #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_5100_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUB.B #<data>,(An) */
unsigned long REGPARAM2 CPUFUNC(op_5110_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* SUB.B #<data>,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_5118_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* SUB.B #<data>,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_5120_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* SUB.B #<data>,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_5128_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* SUB.B #<data>,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_5130_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* SUB.B #<data>,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_5138_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
{{	uae_u32 src = srcreg;
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* SUB.B #<data>,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_5139_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
{{	uae_u32 src = srcreg;
{	uaecptr dsta = get_long_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* SUB.W #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_5140_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUBA.W #<data>,An */
unsigned long REGPARAM2 CPUFUNC(op_5148_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUB.W #<data>,(An) */
unsigned long REGPARAM2 CPUFUNC(op_5150_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2988;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel2988: ;
return CYCLE_UNIT / 2 * 12;
}
/* SUB.W #<data>,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_5158_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2989;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel2989: ;
return CYCLE_UNIT / 2 * 12;
}
/* SUB.W #<data>,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_5160_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2990;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel2990: ;
return CYCLE_UNIT / 2 * 14;
}
/* SUB.W #<data>,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_5168_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2991;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel2991: ;
return CYCLE_UNIT / 2 * 16;
}
/* SUB.W #<data>,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_5170_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2992;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel2992: ;
return CYCLE_UNIT / 2 * 18;
}
/* SUB.W #<data>,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_5178_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
{{	uae_u32 src = srcreg;
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2993;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel2993: ;
return CYCLE_UNIT / 2 * 16;
}
/* SUB.W #<data>,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_5179_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
{{	uae_u32 src = srcreg;
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2994;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel2994: ;
return CYCLE_UNIT / 2 * 20;
}
/* SUB.L #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_5180_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUBA.L #<data>,An */
unsigned long REGPARAM2 CPUFUNC(op_5188_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUB.L #<data>,(An) */
unsigned long REGPARAM2 CPUFUNC(op_5190_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2997;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel2997: ;
return CYCLE_UNIT / 2 * 20;
}
/* SUB.L #<data>,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_5198_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2998;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel2998: ;
return CYCLE_UNIT / 2 * 20;
}
/* SUB.L #<data>,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_51a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel2999;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel2999: ;
return CYCLE_UNIT / 2 * 22;
}
/* SUB.L #<data>,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_51a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3000;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3000: ;
return CYCLE_UNIT / 2 * 24;
}
/* SUB.L #<data>,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_51b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 src = srcreg;
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3001;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3001: ;
return CYCLE_UNIT / 2 * 26;
}
/* SUB.L #<data>,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_51b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
{{	uae_u32 src = srcreg;
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3002;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3002: ;
return CYCLE_UNIT / 2 * 24;
}
/* SUB.L #<data>,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_51b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
{{	uae_u32 src = srcreg;
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3003;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel3003: ;
return CYCLE_UNIT / 2 * 28;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_51c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 1) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_51c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 1)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel3005;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel3005: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_51d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 1) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_51d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 1) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_51e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 1) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_51e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 1) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_51f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 1) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_51f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 1) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_51f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 1) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_52c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 2) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_52c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 2)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel3014;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel3014: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_52d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 2) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_52d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 2) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_52e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 2) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_52e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 2) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_52f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 2) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_52f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 2) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_52f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 2) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_53c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 3) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_53c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 3)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel3023;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel3023: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_53d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 3) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_53d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 3) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_53e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 3) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_53e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 3) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_53f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 3) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_53f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 3) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_53f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 3) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_54c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 4) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_54c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 4)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel3032;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel3032: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_54d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 4) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_54d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 4) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_54e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 4) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_54e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 4) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_54f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 4) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_54f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 4) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_54f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 4) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_55c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 5) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_55c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 5)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel3041;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel3041: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_55d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 5) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_55d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 5) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_55e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 5) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_55e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 5) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_55f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 5) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_55f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 5) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_55f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 5) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_56c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 6) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_56c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 6)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel3050;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel3050: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_56d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 6) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_56d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 6) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_56e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 6) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_56e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 6) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_56f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 6) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_56f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 6) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_56f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 6) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_57c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 7) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_57c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 7)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel3059;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel3059: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_57d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 7) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_57d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 7) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_57e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 7) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_57e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 7) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_57f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 7) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_57f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 7) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_57f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 7) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_58c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 8) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_58c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 8)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel3068;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel3068: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_58d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 8) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_58d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 8) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_58e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 8) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_58e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 8) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_58f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 8) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_58f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 8) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_58f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 8) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_59c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 9) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_59c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 9)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel3077;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel3077: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_59d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 9) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_59d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 9) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_59e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 9) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_59e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 9) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_59f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 9) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_59f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 9) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_59f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 9) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_5ac0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 10) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_5ac8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 10)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel3086;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel3086: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_5ad0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 10) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_5ad8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 10) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_5ae0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 10) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_5ae8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 10) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_5af0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 10) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_5af8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 10) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_5af9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 10) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_5bc0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 11) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_5bc8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 11)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel3095;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel3095: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_5bd0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 11) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_5bd8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 11) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_5be0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 11) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_5be8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 11) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_5bf0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 11) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_5bf8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 11) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_5bf9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 11) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_5cc0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 12) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_5cc8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 12)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel3104;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel3104: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_5cd0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 12) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_5cd8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 12) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_5ce0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 12) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_5ce8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 12) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_5cf0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 12) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_5cf8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 12) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_5cf9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 12) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_5dc0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 13) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_5dc8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 13)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel3113;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel3113: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_5dd0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 13) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_5dd8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 13) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_5de0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 13) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_5de8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 13) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_5df0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 13) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_5df8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 13) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_5df9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 13) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_5ec0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 14) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_5ec8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 14)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel3122;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel3122: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_5ed0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 14) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_5ed8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 14) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_5ee0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 14) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_5ee8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 14) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_5ef0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 14) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_5ef8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 14) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_5ef9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 14) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* Scc.B Dn */
unsigned long REGPARAM2 CPUFUNC(op_5fc0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 15) ? 0xff : 0;
	m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* DBcc.W Dn,#<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_5fc8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 offs = regs->irc;
	uaecptr oldpc = m68k_getpc (regs);
	if (!cctrue (&regs->ccrflags, 15)) {
		m68k_incpc (regs, (uae_s32)offs + 2);
		get_word_prefetch (regs, 0);
		m68k_dreg (regs, srcreg) = (m68k_dreg (regs, srcreg) & ~0xffff) | (((src-1)) & 0xffff);
		if (src) {
			if (offs & 1) {
				exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)offs + 2);
				goto endlabel3131;
			}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
			return CYCLE_UNIT / 2 * 12;
		}
	} else {
	}
	m68k_setpc (regs, oldpc + 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}endlabel3131: ;
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An) */
unsigned long REGPARAM2 CPUFUNC(op_5fd0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 15) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_5fd8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 15) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* Scc.B -(An) */
unsigned long REGPARAM2 CPUFUNC(op_5fe0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	int val = cctrue (&regs->ccrflags, 15) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* Scc.B (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_5fe8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 15) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* Scc.B (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_5ff0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 15) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* Scc.B (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_5ff8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	int val = cctrue (&regs->ccrflags, 15) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
#endif

#ifdef PART_6
/* Scc.B (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_5ff9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	int val = cctrue (&regs->ccrflags, 15) ? 0xff : 0;
	put_byte (srca,val);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* Bcc.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6000_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = regs->irc;
	if (!cctrue (&regs->ccrflags, 0)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3139;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3139: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6001_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{{	uae_u32 src = srcreg;
	if (!cctrue (&regs->ccrflags, 0)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3140;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3140: ;
return CYCLE_UNIT / 2 * 8;
}
/* Bcc.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_60ff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	if (cctrue (&regs->ccrflags, 0)) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 1);
		goto endlabel3141;
	}
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	goto endlabel3141;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 2) << 16;
	src |= regs->irc;
	if (!cctrue (&regs->ccrflags, 0)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3141;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3141: ;
return CYCLE_UNIT / 2 * 12;
}
/* BSR.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6100_5)(uae_u32 opcode, struct regstruct *regs)
{
{	uae_s32 s;
{	uae_s16 src = regs->irc;
	s = (uae_s32)src + 2;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + s);
		goto endlabel3142;
	}
	m68k_do_bsr (regs, m68k_getpc (regs) + 4, s);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3142: ;
return CYCLE_UNIT / 2 * 8;
}
/* BSR.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6101_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{	uae_s32 s;
{	uae_u32 src = srcreg;
	s = (uae_s32)src + 2;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + s);
		goto endlabel3143;
	}
	m68k_do_bsr (regs, m68k_getpc (regs) + 2, s);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3143: ;
return CYCLE_UNIT / 2 * 8;
}
/* BSR.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_61ff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	uae_s32 s;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 4) << 16;
	src |= regs->irc;
	s = (uae_s32)src + 2;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + s);
		goto endlabel3144;
	}
	m68k_do_bsr (regs, m68k_getpc (regs) + 6, s);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3144: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6200_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = regs->irc;
	if (!cctrue (&regs->ccrflags, 2)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3145;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3145: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6201_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{{	uae_u32 src = srcreg;
	if (!cctrue (&regs->ccrflags, 2)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3146;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3146: ;
return CYCLE_UNIT / 2 * 8;
}
/* Bcc.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_62ff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	if (cctrue (&regs->ccrflags, 2)) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 1);
		goto endlabel3147;
	}
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	goto endlabel3147;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 2) << 16;
	src |= regs->irc;
	if (!cctrue (&regs->ccrflags, 2)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3147;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3147: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6300_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = regs->irc;
	if (!cctrue (&regs->ccrflags, 3)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3148;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3148: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6301_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{{	uae_u32 src = srcreg;
	if (!cctrue (&regs->ccrflags, 3)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3149;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3149: ;
return CYCLE_UNIT / 2 * 8;
}
/* Bcc.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_63ff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	if (cctrue (&regs->ccrflags, 3)) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 1);
		goto endlabel3150;
	}
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	goto endlabel3150;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 2) << 16;
	src |= regs->irc;
	if (!cctrue (&regs->ccrflags, 3)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3150;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3150: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6400_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = regs->irc;
	if (!cctrue (&regs->ccrflags, 4)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3151;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3151: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6401_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{{	uae_u32 src = srcreg;
	if (!cctrue (&regs->ccrflags, 4)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3152;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3152: ;
return CYCLE_UNIT / 2 * 8;
}
/* Bcc.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_64ff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	if (cctrue (&regs->ccrflags, 4)) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 1);
		goto endlabel3153;
	}
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	goto endlabel3153;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 2) << 16;
	src |= regs->irc;
	if (!cctrue (&regs->ccrflags, 4)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3153;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3153: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6500_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = regs->irc;
	if (!cctrue (&regs->ccrflags, 5)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3154;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3154: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6501_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{{	uae_u32 src = srcreg;
	if (!cctrue (&regs->ccrflags, 5)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3155;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3155: ;
return CYCLE_UNIT / 2 * 8;
}
/* Bcc.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_65ff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	if (cctrue (&regs->ccrflags, 5)) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 1);
		goto endlabel3156;
	}
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	goto endlabel3156;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 2) << 16;
	src |= regs->irc;
	if (!cctrue (&regs->ccrflags, 5)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3156;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3156: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6600_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = regs->irc;
	if (!cctrue (&regs->ccrflags, 6)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3157;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3157: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6601_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{{	uae_u32 src = srcreg;
	if (!cctrue (&regs->ccrflags, 6)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3158;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3158: ;
return CYCLE_UNIT / 2 * 8;
}
/* Bcc.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_66ff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	if (cctrue (&regs->ccrflags, 6)) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 1);
		goto endlabel3159;
	}
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	goto endlabel3159;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 2) << 16;
	src |= regs->irc;
	if (!cctrue (&regs->ccrflags, 6)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3159;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3159: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6700_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = regs->irc;
	if (!cctrue (&regs->ccrflags, 7)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3160;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3160: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6701_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{{	uae_u32 src = srcreg;
	if (!cctrue (&regs->ccrflags, 7)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3161;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3161: ;
return CYCLE_UNIT / 2 * 8;
}
/* Bcc.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_67ff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	if (cctrue (&regs->ccrflags, 7)) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 1);
		goto endlabel3162;
	}
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	goto endlabel3162;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 2) << 16;
	src |= regs->irc;
	if (!cctrue (&regs->ccrflags, 7)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3162;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3162: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6800_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = regs->irc;
	if (!cctrue (&regs->ccrflags, 8)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3163;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3163: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6801_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{{	uae_u32 src = srcreg;
	if (!cctrue (&regs->ccrflags, 8)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3164;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3164: ;
return CYCLE_UNIT / 2 * 8;
}
/* Bcc.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_68ff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	if (cctrue (&regs->ccrflags, 8)) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 1);
		goto endlabel3165;
	}
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	goto endlabel3165;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 2) << 16;
	src |= regs->irc;
	if (!cctrue (&regs->ccrflags, 8)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3165;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3165: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6900_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = regs->irc;
	if (!cctrue (&regs->ccrflags, 9)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3166;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3166: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6901_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{{	uae_u32 src = srcreg;
	if (!cctrue (&regs->ccrflags, 9)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3167;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3167: ;
return CYCLE_UNIT / 2 * 8;
}
/* Bcc.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_69ff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	if (cctrue (&regs->ccrflags, 9)) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 1);
		goto endlabel3168;
	}
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	goto endlabel3168;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 2) << 16;
	src |= regs->irc;
	if (!cctrue (&regs->ccrflags, 9)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3168;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3168: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6a00_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = regs->irc;
	if (!cctrue (&regs->ccrflags, 10)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3169;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3169: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6a01_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{{	uae_u32 src = srcreg;
	if (!cctrue (&regs->ccrflags, 10)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3170;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3170: ;
return CYCLE_UNIT / 2 * 8;
}
/* Bcc.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_6aff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	if (cctrue (&regs->ccrflags, 10)) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 1);
		goto endlabel3171;
	}
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	goto endlabel3171;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 2) << 16;
	src |= regs->irc;
	if (!cctrue (&regs->ccrflags, 10)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3171;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3171: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6b00_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = regs->irc;
	if (!cctrue (&regs->ccrflags, 11)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3172;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3172: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6b01_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{{	uae_u32 src = srcreg;
	if (!cctrue (&regs->ccrflags, 11)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3173;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3173: ;
return CYCLE_UNIT / 2 * 8;
}
/* Bcc.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_6bff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	if (cctrue (&regs->ccrflags, 11)) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 1);
		goto endlabel3174;
	}
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	goto endlabel3174;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 2) << 16;
	src |= regs->irc;
	if (!cctrue (&regs->ccrflags, 11)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3174;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3174: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6c00_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = regs->irc;
	if (!cctrue (&regs->ccrflags, 12)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3175;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3175: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6c01_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{{	uae_u32 src = srcreg;
	if (!cctrue (&regs->ccrflags, 12)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3176;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3176: ;
return CYCLE_UNIT / 2 * 8;
}
/* Bcc.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_6cff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	if (cctrue (&regs->ccrflags, 12)) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 1);
		goto endlabel3177;
	}
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	goto endlabel3177;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 2) << 16;
	src |= regs->irc;
	if (!cctrue (&regs->ccrflags, 12)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3177;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3177: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6d00_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = regs->irc;
	if (!cctrue (&regs->ccrflags, 13)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3178;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3178: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6d01_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{{	uae_u32 src = srcreg;
	if (!cctrue (&regs->ccrflags, 13)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3179;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3179: ;
return CYCLE_UNIT / 2 * 8;
}
/* Bcc.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_6dff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	if (cctrue (&regs->ccrflags, 13)) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 1);
		goto endlabel3180;
	}
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	goto endlabel3180;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 2) << 16;
	src |= regs->irc;
	if (!cctrue (&regs->ccrflags, 13)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3180;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3180: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6e00_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = regs->irc;
	if (!cctrue (&regs->ccrflags, 14)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3181;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3181: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6e01_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{{	uae_u32 src = srcreg;
	if (!cctrue (&regs->ccrflags, 14)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3182;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3182: ;
return CYCLE_UNIT / 2 * 8;
}
/* Bcc.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_6eff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	if (cctrue (&regs->ccrflags, 14)) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 1);
		goto endlabel3183;
	}
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	goto endlabel3183;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 2) << 16;
	src |= regs->irc;
	if (!cctrue (&regs->ccrflags, 14)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3183;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3183: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.W #<data>.W */
unsigned long REGPARAM2 CPUFUNC(op_6f00_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uae_s16 src = regs->irc;
	if (!cctrue (&regs->ccrflags, 15)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3184;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3184: ;
return CYCLE_UNIT / 2 * 12;
}
/* Bcc.B #<data> */
unsigned long REGPARAM2 CPUFUNC(op_6f01_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
{{	uae_u32 src = srcreg;
	if (!cctrue (&regs->ccrflags, 15)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3185;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3185: ;
return CYCLE_UNIT / 2 * 8;
}
/* Bcc.L #<data>.L */
unsigned long REGPARAM2 CPUFUNC(op_6fff_5)(uae_u32 opcode, struct regstruct *regs)
{
{	if (cctrue (&regs->ccrflags, 15)) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 1);
		goto endlabel3186;
	}
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	goto endlabel3186;
{	uae_s32 src;
	src  = get_word_prefetch (regs, 2) << 16;
	src |= regs->irc;
	if (!cctrue (&regs->ccrflags, 15)) goto didnt_jump;
	if (src & 1) {
		exception3i (opcode, m68k_getpc (regs) + 2, m68k_getpc (regs) + 2 + (uae_s32)src);
		goto endlabel3186;
	}
	m68k_incpc (regs, (uae_s32)src + 2);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
	return 10 * CYCLE_UNIT / 2;
didnt_jump:;
	m68k_incpc (regs, 4);
	get_word_prefetch (regs, 0);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}endlabel3186: ;
return CYCLE_UNIT / 2 * 12;
}
/* MOVE.L #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_7000_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (uae_s32)(uae_s8)(opcode & 255);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_u32 src = srcreg;
{	m68k_dreg (regs, dstreg) = (src);
	optflag_testl (regs, (uae_s32)(src));
	m68k_incpc (regs, 2);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 2);
}}}return CYCLE_UNIT / 2 * 4;
}
/* OR.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_8000_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* OR.B (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_8010_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 8;
}
/* OR.B (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_8018_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 8;
}
/* OR.B -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_8020_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 10;
}
/* OR.B (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_8028_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* OR.B (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_8030_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 14;
}
/* OR.B (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_8038_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* OR.B (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_8039_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 16;
}
/* OR.B (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_803a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* OR.B (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_803b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 14;
}
/* OR.B #<data>.B,Dn */
unsigned long REGPARAM2 CPUFUNC(op_803c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* OR.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_8040_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* OR.W (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_8050_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3200;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 2);
endlabel3200: ;
return CYCLE_UNIT / 2 * 8;
}
/* OR.W (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_8058_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3201;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 2);
endlabel3201: ;
return CYCLE_UNIT / 2 * 8;
}
/* OR.W -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_8060_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3202;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 2);
endlabel3202: ;
return CYCLE_UNIT / 2 * 10;
}
/* OR.W (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_8068_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3203;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 4);
endlabel3203: ;
return CYCLE_UNIT / 2 * 12;
}
/* OR.W (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_8070_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3204;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 4);
endlabel3204: ;
return CYCLE_UNIT / 2 * 14;
}
/* OR.W (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_8078_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3205;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 4);
endlabel3205: ;
return CYCLE_UNIT / 2 * 12;
}
/* OR.W (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_8079_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3206;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 6);
endlabel3206: ;
return CYCLE_UNIT / 2 * 16;
}
/* OR.W (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_807a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3207;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 4);
endlabel3207: ;
return CYCLE_UNIT / 2 * 12;
}
/* OR.W (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_807b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3208;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 4);
endlabel3208: ;
return CYCLE_UNIT / 2 * 14;
}
/* OR.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_807c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* OR.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_8080_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* OR.L (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_8090_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3211;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 2);
endlabel3211: ;
return CYCLE_UNIT / 2 * 12;
}
/* OR.L (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_8098_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3212;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 2);
endlabel3212: ;
return CYCLE_UNIT / 2 * 12;
}
/* OR.L -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_80a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3213;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 2);
endlabel3213: ;
return CYCLE_UNIT / 2 * 14;
}
/* OR.L (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_80a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3214;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 4);
endlabel3214: ;
return CYCLE_UNIT / 2 * 16;
}
/* OR.L (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_80b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3215;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 4);
endlabel3215: ;
return CYCLE_UNIT / 2 * 18;
}
/* OR.L (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_80b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3216;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 4);
endlabel3216: ;
return CYCLE_UNIT / 2 * 16;
}
/* OR.L (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_80b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3217;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 6);
endlabel3217: ;
return CYCLE_UNIT / 2 * 20;
}
/* OR.L (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_80ba_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3218;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 4);
endlabel3218: ;
return CYCLE_UNIT / 2 * 16;
}
/* OR.L (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_80bb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3219;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 4);
endlabel3219: ;
return CYCLE_UNIT / 2 * 18;
}
/* OR.L #<data>.L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_80bc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 12;
}
/* DIVU.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_80c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 2);
		Exception (5, regs, oldpc);
		goto endlabel3221;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_incpc (regs, 2);
	}
}}}endlabel3221: ;
return CYCLE_UNIT / 2 * 110;
}
/* DIVU.W (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_80d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3222;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 2);
		Exception (5, regs, oldpc);
		goto endlabel3222;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_incpc (regs, 2);
	}
}}}}}endlabel3222: ;
return CYCLE_UNIT / 2 * 114;
}
/* DIVU.W (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_80d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3223;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 2);
		Exception (5, regs, oldpc);
		goto endlabel3223;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_incpc (regs, 2);
	}
}}}}}endlabel3223: ;
return CYCLE_UNIT / 2 * 114;
}
/* DIVU.W -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_80e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3224;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 2);
		Exception (5, regs, oldpc);
		goto endlabel3224;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_incpc (regs, 2);
	}
}}}}}endlabel3224: ;
return CYCLE_UNIT / 2 * 116;
}
/* DIVU.W (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_80e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3225;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 4);
		Exception (5, regs, oldpc);
		goto endlabel3225;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_incpc (regs, 4);
	}
}}}}}endlabel3225: ;
return CYCLE_UNIT / 2 * 118;
}
/* DIVU.W (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_80f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3226;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 4);
		Exception (5, regs, oldpc);
		goto endlabel3226;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_incpc (regs, 4);
	}
}}}}}endlabel3226: ;
return CYCLE_UNIT / 2 * 120;
}
/* DIVU.W (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_80f8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3227;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 4);
		Exception (5, regs, oldpc);
		goto endlabel3227;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_incpc (regs, 4);
	}
}}}}}endlabel3227: ;
return CYCLE_UNIT / 2 * 118;
}
/* DIVU.W (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_80f9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3228;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 6);
		Exception (5, regs, oldpc);
		goto endlabel3228;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	m68k_incpc (regs, 6);
	}
}}}}}endlabel3228: ;
return CYCLE_UNIT / 2 * 122;
}
/* DIVU.W (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_80fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3229;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 4);
		Exception (5, regs, oldpc);
		goto endlabel3229;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_incpc (regs, 4);
	}
}}}}}endlabel3229: ;
return CYCLE_UNIT / 2 * 118;
}
/* DIVU.W (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_80fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3230;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 4);
		Exception (5, regs, oldpc);
		goto endlabel3230;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_incpc (regs, 4);
	}
}}}}}endlabel3230: ;
return CYCLE_UNIT / 2 * 120;
}
/* DIVU.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_80fc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 4);
		Exception (5, regs, oldpc);
		goto endlabel3231;
	} else {
		uae_u32 newv = (uae_u32)dst / (uae_u32)(uae_u16)src;
		uae_u32 rem = (uae_u32)dst % (uae_u32)(uae_u16)src;
		if (newv > 0xffff) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_incpc (regs, 4);
	}
}}}endlabel3231: ;
return CYCLE_UNIT / 2 * 114;
}
/* SBCD.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_8100_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 newv_lo = (dst & 0xF) - (src & 0xF) - GET_XFLG (&regs->ccrflags);
	uae_u16 newv_hi = (dst & 0xF0) - (src & 0xF0);
	uae_u16 newv, tmp_newv;
	int bcd = 0;
	newv = tmp_newv = newv_hi + newv_lo;
	if (newv_lo & 0xF0) { newv -= 6; bcd = 6; };
	if ((((dst & 0xFF) - (src & 0xFF) - GET_XFLG (&regs->ccrflags)) & 0x100) > 0xFF) { newv -= 0x60; }
	SET_CFLG (&regs->ccrflags, ((((dst & 0xFF) - (src & 0xFF) - bcd - GET_XFLG (&regs->ccrflags)) & 0x300) > 0xFF) ? 1 : 0);
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	SET_VFLG (&regs->ccrflags, ((tmp_newv & 0x80) != 0 && (newv & 0x80) == 0) ? 1 : 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SBCD.B -(An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_8108_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 newv_lo = (dst & 0xF) - (src & 0xF) - GET_XFLG (&regs->ccrflags);
	uae_u16 newv_hi = (dst & 0xF0) - (src & 0xF0);
	uae_u16 newv, tmp_newv;
	int bcd = 0;
	newv = tmp_newv = newv_hi + newv_lo;
	if (newv_lo & 0xF0) { newv -= 6; bcd = 6; };
	if ((((dst & 0xFF) - (src & 0xFF) - GET_XFLG (&regs->ccrflags)) & 0x100) > 0xFF) { newv -= 0x60; }
	SET_CFLG (&regs->ccrflags, ((((dst & 0xFF) - (src & 0xFF) - bcd - GET_XFLG (&regs->ccrflags)) & 0x300) > 0xFF) ? 1 : 0);
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	SET_VFLG (&regs->ccrflags, ((tmp_newv & 0x80) != 0 && (newv & 0x80) == 0) ? 1 : 0);
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 16;
}
/* OR.B Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_8110_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* OR.B Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_8118_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* OR.B Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_8120_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* OR.B Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_8128_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* OR.B Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_8130_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
{	uae_s8 dst = get_byte (dsta);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* OR.B Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_8138_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* OR.B Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_8139_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	src |= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* OR.W Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_8150_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3241;
	}
{{	uae_s16 dst = get_word (dsta);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3241: ;
return CYCLE_UNIT / 2 * 12;
}
/* OR.W Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_8158_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3242;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3242: ;
return CYCLE_UNIT / 2 * 12;
}
/* OR.W Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_8160_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3243;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3243: ;
return CYCLE_UNIT / 2 * 14;
}
/* OR.W Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_8168_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3244;
	}
{{	uae_s16 dst = get_word (dsta);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3244: ;
return CYCLE_UNIT / 2 * 16;
}
/* OR.W Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_8170_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3245;
	}
{{	uae_s16 dst = get_word (dsta);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3245: ;
return CYCLE_UNIT / 2 * 18;
}
/* OR.W Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_8178_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3246;
	}
{{	uae_s16 dst = get_word (dsta);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3246: ;
return CYCLE_UNIT / 2 * 16;
}
/* OR.W Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_8179_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3247;
	}
{{	uae_s16 dst = get_word (dsta);
	src |= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel3247: ;
return CYCLE_UNIT / 2 * 20;
}
/* OR.L Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_8190_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3248;
	}
{{	uae_s32 dst = get_long (dsta);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3248: ;
return CYCLE_UNIT / 2 * 20;
}
/* OR.L Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_8198_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3249;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3249: ;
return CYCLE_UNIT / 2 * 20;
}
/* OR.L Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_81a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3250;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3250: ;
return CYCLE_UNIT / 2 * 22;
}
/* OR.L Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_81a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3251;
	}
{{	uae_s32 dst = get_long (dsta);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3251: ;
return CYCLE_UNIT / 2 * 24;
}
/* OR.L Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_81b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3252;
	}
{{	uae_s32 dst = get_long (dsta);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3252: ;
return CYCLE_UNIT / 2 * 26;
}
/* OR.L Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_81b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3253;
	}
{{	uae_s32 dst = get_long (dsta);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3253: ;
return CYCLE_UNIT / 2 * 24;
}
/* OR.L Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_81b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3254;
	}
{{	uae_s32 dst = get_long (dsta);
	src |= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel3254: ;
return CYCLE_UNIT / 2 * 28;
}
/* DIVS.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_81c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 2);
		Exception (5, regs, oldpc);
		goto endlabel3255;
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_incpc (regs, 2);
	}
}}}endlabel3255: ;
return CYCLE_UNIT / 2 * 142;
}
/* DIVS.W (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_81d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3256;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 2);
		Exception (5, regs, oldpc);
		goto endlabel3256;
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_incpc (regs, 2);
	}
}}}}}endlabel3256: ;
return CYCLE_UNIT / 2 * 146;
}
/* DIVS.W (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_81d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3257;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 2);
		Exception (5, regs, oldpc);
		goto endlabel3257;
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_incpc (regs, 2);
	}
}}}}}endlabel3257: ;
return CYCLE_UNIT / 2 * 146;
}
/* DIVS.W -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_81e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3258;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 2);
		Exception (5, regs, oldpc);
		goto endlabel3258;
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_incpc (regs, 2);
	}
}}}}}endlabel3258: ;
return CYCLE_UNIT / 2 * 148;
}
/* DIVS.W (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_81e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3259;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 4);
		Exception (5, regs, oldpc);
		goto endlabel3259;
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_incpc (regs, 4);
	}
}}}}}endlabel3259: ;
return CYCLE_UNIT / 2 * 150;
}
/* DIVS.W (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_81f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3260;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 4);
		Exception (5, regs, oldpc);
		goto endlabel3260;
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_incpc (regs, 4);
	}
}}}}}endlabel3260: ;
return CYCLE_UNIT / 2 * 152;
}
/* DIVS.W (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_81f8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3261;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 4);
		Exception (5, regs, oldpc);
		goto endlabel3261;
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_incpc (regs, 4);
	}
}}}}}endlabel3261: ;
return CYCLE_UNIT / 2 * 150;
}
/* DIVS.W (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_81f9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3262;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 6);
		Exception (5, regs, oldpc);
		goto endlabel3262;
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	m68k_incpc (regs, 6);
	}
}}}}}endlabel3262: ;
return CYCLE_UNIT / 2 * 154;
}
/* DIVS.W (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_81fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3263;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 4);
		Exception (5, regs, oldpc);
		goto endlabel3263;
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_incpc (regs, 4);
	}
}}}}}endlabel3263: ;
return CYCLE_UNIT / 2 * 150;
}
/* DIVS.W (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_81fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3264;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 4);
		Exception (5, regs, oldpc);
		goto endlabel3264;
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_incpc (regs, 4);
	}
}}}}}endlabel3264: ;
return CYCLE_UNIT / 2 * 152;
}
/* DIVS.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_81fc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{	uaecptr oldpc = m68k_getpc (regs);
{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	CLEAR_CZNV (&regs->ccrflags);
	if (src == 0) {
		m68k_incpc (regs, 4);
		Exception (5, regs, oldpc);
		goto endlabel3265;
	} else {
		uae_s32 newv = (uae_s32)dst / (uae_s32)(uae_s16)src;
		uae_u16 rem = (uae_s32)dst % (uae_s32)(uae_s16)src;
		if ((newv & 0xffff8000) != 0 && (newv & 0xffff8000) != 0xffff8000) {
			SET_VFLG (&regs->ccrflags, 1);
			SET_NFLG (&regs->ccrflags, 1);
		} else {
			if (((uae_s16)rem < 0) != ((uae_s32)dst < 0)) rem = -rem;
	optflag_testw (regs, (uae_s16)(newv));
			newv = (newv & 0xffff) | ((uae_u32)rem << 16);
			m68k_dreg (regs, dstreg) = (newv);
		}
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_incpc (regs, 4);
	}
}}}endlabel3265: ;
return CYCLE_UNIT / 2 * 146;
}
/* SUB.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_9000_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUB.B (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_9010_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 8;
}
/* SUB.B (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_9018_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 8;
}
/* SUB.B -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_9020_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 10;
}
/* SUB.B (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_9028_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* SUB.B (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_9030_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 14;
}
/* SUB.B (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_9038_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* SUB.B (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_9039_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 16;
}
/* SUB.B (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_903a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* SUB.B (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_903b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 14;
}
/* SUB.B #<data>.B,Dn */
unsigned long REGPARAM2 CPUFUNC(op_903c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* SUB.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_9040_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUB.W An,Dn */
unsigned long REGPARAM2 CPUFUNC(op_9048_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUB.W (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_9050_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3279;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3279: ;
return CYCLE_UNIT / 2 * 8;
}
/* SUB.W (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_9058_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3280;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3280: ;
return CYCLE_UNIT / 2 * 8;
}
/* SUB.W -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_9060_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3281;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3281: ;
return CYCLE_UNIT / 2 * 10;
}
/* SUB.W (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_9068_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3282;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3282: ;
return CYCLE_UNIT / 2 * 12;
}
/* SUB.W (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_9070_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3283;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3283: ;
return CYCLE_UNIT / 2 * 14;
}
/* SUB.W (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_9078_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3284;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3284: ;
return CYCLE_UNIT / 2 * 12;
}
/* SUB.W (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_9079_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3285;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 6);
endlabel3285: ;
return CYCLE_UNIT / 2 * 16;
}
/* SUB.W (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_907a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3286;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3286: ;
return CYCLE_UNIT / 2 * 12;
}
/* SUB.W (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_907b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3287;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3287: ;
return CYCLE_UNIT / 2 * 14;
}
/* SUB.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_907c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* SUB.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_9080_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUB.L An,Dn */
unsigned long REGPARAM2 CPUFUNC(op_9088_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUB.L (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_9090_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3291;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3291: ;
return CYCLE_UNIT / 2 * 12;
}
/* SUB.L (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_9098_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3292;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3292: ;
return CYCLE_UNIT / 2 * 12;
}
/* SUB.L -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_90a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3293;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3293: ;
return CYCLE_UNIT / 2 * 14;
}
/* SUB.L (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_90a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3294;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3294: ;
return CYCLE_UNIT / 2 * 16;
}
/* SUB.L (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_90b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3295;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3295: ;
return CYCLE_UNIT / 2 * 18;
}
/* SUB.L (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_90b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3296;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3296: ;
return CYCLE_UNIT / 2 * 16;
}
/* SUB.L (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_90b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3297;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel3297: ;
return CYCLE_UNIT / 2 * 20;
}
/* SUB.L (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_90ba_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3298;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3298: ;
return CYCLE_UNIT / 2 * 16;
}
/* SUB.L (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_90bb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3299;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3299: ;
return CYCLE_UNIT / 2 * 18;
}
/* SUB.L #<data>.L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_90bc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 12;
}
/* SUBA.W Dn,An */
unsigned long REGPARAM2 CPUFUNC(op_90c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUBA.W An,An */
unsigned long REGPARAM2 CPUFUNC(op_90c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUBA.W (An),An */
unsigned long REGPARAM2 CPUFUNC(op_90d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3303;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel3303: ;
return CYCLE_UNIT / 2 * 8;
}
/* SUBA.W (An)+,An */
unsigned long REGPARAM2 CPUFUNC(op_90d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3304;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel3304: ;
return CYCLE_UNIT / 2 * 8;
}
/* SUBA.W -(An),An */
unsigned long REGPARAM2 CPUFUNC(op_90e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3305;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel3305: ;
return CYCLE_UNIT / 2 * 10;
}
/* SUBA.W (d16,An),An */
unsigned long REGPARAM2 CPUFUNC(op_90e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3306;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3306: ;
return CYCLE_UNIT / 2 * 12;
}
/* SUBA.W (d8,An,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_90f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3307;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3307: ;
return CYCLE_UNIT / 2 * 14;
}
/* SUBA.W (xxx).W,An */
unsigned long REGPARAM2 CPUFUNC(op_90f8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3308;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3308: ;
return CYCLE_UNIT / 2 * 12;
}
/* SUBA.W (xxx).L,An */
unsigned long REGPARAM2 CPUFUNC(op_90f9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3309;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 6);
endlabel3309: ;
return CYCLE_UNIT / 2 * 16;
}
/* SUBA.W (d16,PC),An */
unsigned long REGPARAM2 CPUFUNC(op_90fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3310;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3310: ;
return CYCLE_UNIT / 2 * 12;
}
/* SUBA.W (d8,PC,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_90fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3311;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3311: ;
return CYCLE_UNIT / 2 * 14;
}
/* SUBA.W #<data>.W,An */
unsigned long REGPARAM2 CPUFUNC(op_90fc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* SUBX.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_9100_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s8)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s8)(dst)) < 0) ? 1 : 0;
	int flgn = (((uae_s8)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUBX.B -(An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_9108_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s8)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s8)(dst)) < 0) ? 1 : 0;
	int flgn = (((uae_s8)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 16;
}
/* SUB.B Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_9110_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* SUB.B Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_9118_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* SUB.B Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_9120_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* SUB.B Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_9128_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* SUB.B Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_9130_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* SUB.B Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_9138_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* SUB.B Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_9139_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* SUBX.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_9140_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s16)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s16)(dst)) < 0) ? 1 : 0;
	int flgn = (((uae_s16)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s16)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s16)(newv)) < 0) ? 1 : 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUBX.W -(An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_9148_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3323;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3323;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s16)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s16)(dst)) < 0) ? 1 : 0;
	int flgn = (((uae_s16)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s16)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s16)(newv)) < 0) ? 1 : 0);
	put_word (dsta,newv);
}}}}}}}}}	m68k_incpc (regs, 2);
endlabel3323: ;
return CYCLE_UNIT / 2 * 16;
}
/* SUB.W Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_9150_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3324;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3324: ;
return CYCLE_UNIT / 2 * 12;
}
/* SUB.W Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_9158_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3325;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3325: ;
return CYCLE_UNIT / 2 * 12;
}
/* SUB.W Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_9160_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3326;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3326: ;
return CYCLE_UNIT / 2 * 14;
}
/* SUB.W Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_9168_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3327;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3327: ;
return CYCLE_UNIT / 2 * 16;
}
/* SUB.W Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_9170_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3328;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3328: ;
return CYCLE_UNIT / 2 * 18;
}
/* SUB.W Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_9178_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3329;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3329: ;
return CYCLE_UNIT / 2 * 16;
}
/* SUB.W Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_9179_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3330;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel3330: ;
return CYCLE_UNIT / 2 * 20;
}
/* SUBX.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_9180_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s32)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s32)(dst)) < 0) ? 1 : 0;
	int flgn = (((uae_s32)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s32)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s32)(newv)) < 0) ? 1 : 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUBX.L -(An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_9188_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3332;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3332;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src - GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s32)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s32)(dst)) < 0) ? 1 : 0;
	int flgn = (((uae_s32)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgo) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgn) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s32)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s32)(newv)) < 0) ? 1 : 0);
	put_long (dsta,newv);
}}}}}}}}}	m68k_incpc (regs, 2);
endlabel3332: ;
return CYCLE_UNIT / 2 * 28;
}
/* SUB.L Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_9190_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3333;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3333: ;
return CYCLE_UNIT / 2 * 20;
}
/* SUB.L Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_9198_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3334;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3334: ;
return CYCLE_UNIT / 2 * 20;
}
/* SUB.L Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_91a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3335;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3335: ;
return CYCLE_UNIT / 2 * 22;
}
/* SUB.L Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_91a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3336;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3336: ;
return CYCLE_UNIT / 2 * 24;
}
/* SUB.L Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_91b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3337;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3337: ;
return CYCLE_UNIT / 2 * 26;
}
/* SUB.L Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_91b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3338;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3338: ;
return CYCLE_UNIT / 2 * 24;
}
/* SUB.L Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_91b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3339;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_subl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel3339: ;
return CYCLE_UNIT / 2 * 28;
}
/* SUBA.L Dn,An */
unsigned long REGPARAM2 CPUFUNC(op_91c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUBA.L An,An */
unsigned long REGPARAM2 CPUFUNC(op_91c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* SUBA.L (An),An */
unsigned long REGPARAM2 CPUFUNC(op_91d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3342;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel3342: ;
return CYCLE_UNIT / 2 * 12;
}
/* SUBA.L (An)+,An */
unsigned long REGPARAM2 CPUFUNC(op_91d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3343;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel3343: ;
return CYCLE_UNIT / 2 * 12;
}
/* SUBA.L -(An),An */
unsigned long REGPARAM2 CPUFUNC(op_91e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3344;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel3344: ;
return CYCLE_UNIT / 2 * 14;
}
/* SUBA.L (d16,An),An */
unsigned long REGPARAM2 CPUFUNC(op_91e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3345;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3345: ;
return CYCLE_UNIT / 2 * 16;
}
/* SUBA.L (d8,An,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_91f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3346;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3346: ;
return CYCLE_UNIT / 2 * 18;
}
/* SUBA.L (xxx).W,An */
unsigned long REGPARAM2 CPUFUNC(op_91f8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3347;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3347: ;
return CYCLE_UNIT / 2 * 16;
}
/* SUBA.L (xxx).L,An */
unsigned long REGPARAM2 CPUFUNC(op_91f9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3348;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 6);
endlabel3348: ;
return CYCLE_UNIT / 2 * 20;
}
/* SUBA.L (d16,PC),An */
unsigned long REGPARAM2 CPUFUNC(op_91fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3349;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3349: ;
return CYCLE_UNIT / 2 * 16;
}
/* SUBA.L (d8,PC,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_91fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3350;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3350: ;
return CYCLE_UNIT / 2 * 18;
}
/* SUBA.L #<data>.L,An */
unsigned long REGPARAM2 CPUFUNC(op_91fc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 newv = dst - src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 12;
}
/* CMP.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b000_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* CMP.B (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b010_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 8;
}
/* CMP.B (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b018_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 8;
}
/* CMP.B -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b020_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 10;
}
/* CMP.B (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b028_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* CMP.B (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b030_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 14;
}
/* CMP.B (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b038_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* CMP.B (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b039_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 16;
}
/* CMP.B (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b03a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* CMP.B (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b03b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 14;
}
/* CMP.B #<data>.B,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b03c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* CMP.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b040_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
#endif

#ifdef PART_7
/* CMP.W An,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b048_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* CMP.W (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b050_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3365;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 2);
endlabel3365: ;
return CYCLE_UNIT / 2 * 8;
}
/* CMP.W (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b058_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3366;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 2);
endlabel3366: ;
return CYCLE_UNIT / 2 * 8;
}
/* CMP.W -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b060_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3367;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 2);
endlabel3367: ;
return CYCLE_UNIT / 2 * 10;
}
/* CMP.W (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b068_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3368;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3368: ;
return CYCLE_UNIT / 2 * 12;
}
/* CMP.W (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b070_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3369;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3369: ;
return CYCLE_UNIT / 2 * 14;
}
/* CMP.W (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b078_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3370;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3370: ;
return CYCLE_UNIT / 2 * 12;
}
/* CMP.W (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b079_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3371;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 6);
endlabel3371: ;
return CYCLE_UNIT / 2 * 16;
}
/* CMP.W (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b07a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3372;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3372: ;
return CYCLE_UNIT / 2 * 12;
}
/* CMP.W (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b07b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3373;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3373: ;
return CYCLE_UNIT / 2 * 14;
}
/* CMP.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b07c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* CMP.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b080_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* CMP.L An,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b088_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* CMP.L (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b090_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3377;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 2);
endlabel3377: ;
return CYCLE_UNIT / 2 * 12;
}
/* CMP.L (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b098_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3378;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 2);
endlabel3378: ;
return CYCLE_UNIT / 2 * 12;
}
/* CMP.L -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b0a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3379;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 2);
endlabel3379: ;
return CYCLE_UNIT / 2 * 14;
}
/* CMP.L (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b0a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3380;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3380: ;
return CYCLE_UNIT / 2 * 16;
}
/* CMP.L (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b0b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3381;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3381: ;
return CYCLE_UNIT / 2 * 18;
}
/* CMP.L (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b0b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3382;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3382: ;
return CYCLE_UNIT / 2 * 16;
}
/* CMP.L (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b0b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3383;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 6);
endlabel3383: ;
return CYCLE_UNIT / 2 * 20;
}
/* CMP.L (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b0ba_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3384;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3384: ;
return CYCLE_UNIT / 2 * 16;
}
/* CMP.L (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_b0bb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3385;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3385: ;
return CYCLE_UNIT / 2 * 18;
}
/* CMP.L #<data>.L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b0bc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 12;
}
/* CMPA.W Dn,An */
unsigned long REGPARAM2 CPUFUNC(op_b0c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* CMPA.W An,An */
unsigned long REGPARAM2 CPUFUNC(op_b0c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* CMPA.W (An),An */
unsigned long REGPARAM2 CPUFUNC(op_b0d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3389;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 2);
endlabel3389: ;
return CYCLE_UNIT / 2 * 8;
}
/* CMPA.W (An)+,An */
unsigned long REGPARAM2 CPUFUNC(op_b0d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3390;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 2);
endlabel3390: ;
return CYCLE_UNIT / 2 * 8;
}
/* CMPA.W -(An),An */
unsigned long REGPARAM2 CPUFUNC(op_b0e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3391;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 2);
endlabel3391: ;
return CYCLE_UNIT / 2 * 10;
}
/* CMPA.W (d16,An),An */
unsigned long REGPARAM2 CPUFUNC(op_b0e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3392;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3392: ;
return CYCLE_UNIT / 2 * 12;
}
/* CMPA.W (d8,An,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_b0f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3393;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3393: ;
return CYCLE_UNIT / 2 * 14;
}
/* CMPA.W (xxx).W,An */
unsigned long REGPARAM2 CPUFUNC(op_b0f8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3394;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3394: ;
return CYCLE_UNIT / 2 * 12;
}
/* CMPA.W (xxx).L,An */
unsigned long REGPARAM2 CPUFUNC(op_b0f9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3395;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 6);
endlabel3395: ;
return CYCLE_UNIT / 2 * 16;
}
/* CMPA.W (d16,PC),An */
unsigned long REGPARAM2 CPUFUNC(op_b0fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3396;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3396: ;
return CYCLE_UNIT / 2 * 12;
}
/* CMPA.W (d8,PC,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_b0fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3397;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3397: ;
return CYCLE_UNIT / 2 * 14;
}
/* CMPA.W #<data>.W,An */
unsigned long REGPARAM2 CPUFUNC(op_b0fc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* EOR.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b100_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* CMPM.B (An)+,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_b108_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpb (regs, (uae_s8)(src), (uae_s8)(dst));
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* EOR.B Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_b110_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* EOR.B Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_b118_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* EOR.B Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_b120_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* EOR.B Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_b128_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* EOR.B Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_b130_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
{	uae_s8 dst = get_byte (dsta);
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* EOR.B Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_b138_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* EOR.B Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_b139_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	src ^= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* EOR.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b140_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* CMPM.W (An)+,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_b148_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3409;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3409;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpw (regs, (uae_s16)(src), (uae_s16)(dst));
}}}}}}}}	m68k_incpc (regs, 2);
endlabel3409: ;
return CYCLE_UNIT / 2 * 12;
}
/* EOR.W Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_b150_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3410;
	}
{{	uae_s16 dst = get_word (dsta);
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3410: ;
return CYCLE_UNIT / 2 * 12;
}
/* EOR.W Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_b158_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3411;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3411: ;
return CYCLE_UNIT / 2 * 12;
}
/* EOR.W Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_b160_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3412;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3412: ;
return CYCLE_UNIT / 2 * 14;
}
/* EOR.W Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_b168_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3413;
	}
{{	uae_s16 dst = get_word (dsta);
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3413: ;
return CYCLE_UNIT / 2 * 16;
}
/* EOR.W Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_b170_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3414;
	}
{{	uae_s16 dst = get_word (dsta);
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3414: ;
return CYCLE_UNIT / 2 * 18;
}
/* EOR.W Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_b178_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3415;
	}
{{	uae_s16 dst = get_word (dsta);
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3415: ;
return CYCLE_UNIT / 2 * 16;
}
/* EOR.W Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_b179_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3416;
	}
{{	uae_s16 dst = get_word (dsta);
	src ^= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel3416: ;
return CYCLE_UNIT / 2 * 20;
}
/* EOR.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_b180_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* CMPM.L (An)+,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_b188_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3418;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3418;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}}}	m68k_incpc (regs, 2);
endlabel3418: ;
return CYCLE_UNIT / 2 * 20;
}
/* EOR.L Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_b190_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3419;
	}
{{	uae_s32 dst = get_long (dsta);
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3419: ;
return CYCLE_UNIT / 2 * 20;
}
/* EOR.L Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_b198_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3420;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3420: ;
return CYCLE_UNIT / 2 * 20;
}
/* EOR.L Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_b1a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3421;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3421: ;
return CYCLE_UNIT / 2 * 22;
}
/* EOR.L Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_b1a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3422;
	}
{{	uae_s32 dst = get_long (dsta);
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3422: ;
return CYCLE_UNIT / 2 * 24;
}
/* EOR.L Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_b1b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3423;
	}
{{	uae_s32 dst = get_long (dsta);
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3423: ;
return CYCLE_UNIT / 2 * 26;
}
/* EOR.L Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_b1b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3424;
	}
{{	uae_s32 dst = get_long (dsta);
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3424: ;
return CYCLE_UNIT / 2 * 24;
}
/* EOR.L Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_b1b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3425;
	}
{{	uae_s32 dst = get_long (dsta);
	src ^= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel3425: ;
return CYCLE_UNIT / 2 * 28;
}
/* CMPA.L Dn,An */
unsigned long REGPARAM2 CPUFUNC(op_b1c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* CMPA.L An,An */
unsigned long REGPARAM2 CPUFUNC(op_b1c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* CMPA.L (An),An */
unsigned long REGPARAM2 CPUFUNC(op_b1d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3428;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 2);
endlabel3428: ;
return CYCLE_UNIT / 2 * 12;
}
/* CMPA.L (An)+,An */
unsigned long REGPARAM2 CPUFUNC(op_b1d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3429;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 2);
endlabel3429: ;
return CYCLE_UNIT / 2 * 12;
}
/* CMPA.L -(An),An */
unsigned long REGPARAM2 CPUFUNC(op_b1e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3430;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 2);
endlabel3430: ;
return CYCLE_UNIT / 2 * 14;
}
/* CMPA.L (d16,An),An */
unsigned long REGPARAM2 CPUFUNC(op_b1e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3431;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3431: ;
return CYCLE_UNIT / 2 * 16;
}
/* CMPA.L (d8,An,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_b1f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3432;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3432: ;
return CYCLE_UNIT / 2 * 18;
}
/* CMPA.L (xxx).W,An */
unsigned long REGPARAM2 CPUFUNC(op_b1f8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3433;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3433: ;
return CYCLE_UNIT / 2 * 16;
}
/* CMPA.L (xxx).L,An */
unsigned long REGPARAM2 CPUFUNC(op_b1f9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3434;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 6);
endlabel3434: ;
return CYCLE_UNIT / 2 * 20;
}
/* CMPA.L (d16,PC),An */
unsigned long REGPARAM2 CPUFUNC(op_b1fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3435;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3435: ;
return CYCLE_UNIT / 2 * 16;
}
/* CMPA.L (d8,PC,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_b1fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3436;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}}}	m68k_incpc (regs, 4);
endlabel3436: ;
return CYCLE_UNIT / 2 * 18;
}
/* CMPA.L #<data>.L,An */
unsigned long REGPARAM2 CPUFUNC(op_b1fc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	optflag_cmpl (regs, (uae_s32)(src), (uae_s32)(dst));
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 12;
}
/* AND.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c000_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* AND.B (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c010_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 8;
}
/* AND.B (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c018_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 8;
}
/* AND.B -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c020_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 10;
}
/* AND.B (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c028_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* AND.B (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c030_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 14;
}
/* AND.B (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c038_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* AND.B (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c039_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 16;
}
/* AND.B (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c03a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* AND.B (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c03b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 14;
}
/* AND.B #<data>.B,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c03c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((src) & 0xff);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* AND.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c040_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* AND.W (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c050_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3450;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 2);
endlabel3450: ;
return CYCLE_UNIT / 2 * 8;
}
/* AND.W (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c058_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3451;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 2);
endlabel3451: ;
return CYCLE_UNIT / 2 * 8;
}
/* AND.W -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c060_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3452;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 2);
endlabel3452: ;
return CYCLE_UNIT / 2 * 10;
}
/* AND.W (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c068_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3453;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 4);
endlabel3453: ;
return CYCLE_UNIT / 2 * 12;
}
/* AND.W (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c070_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3454;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 4);
endlabel3454: ;
return CYCLE_UNIT / 2 * 14;
}
/* AND.W (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c078_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3455;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 4);
endlabel3455: ;
return CYCLE_UNIT / 2 * 12;
}
/* AND.W (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c079_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3456;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 6);
endlabel3456: ;
return CYCLE_UNIT / 2 * 16;
}
/* AND.W (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c07a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3457;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 4);
endlabel3457: ;
return CYCLE_UNIT / 2 * 12;
}
/* AND.W (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c07b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3458;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}}}	m68k_incpc (regs, 4);
endlabel3458: ;
return CYCLE_UNIT / 2 * 14;
}
/* AND.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c07c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((src) & 0xffff);
}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* AND.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c080_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* AND.L (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c090_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3461;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 2);
endlabel3461: ;
return CYCLE_UNIT / 2 * 12;
}
/* AND.L (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c098_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3462;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 2);
endlabel3462: ;
return CYCLE_UNIT / 2 * 12;
}
/* AND.L -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3463;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 2);
endlabel3463: ;
return CYCLE_UNIT / 2 * 14;
}
/* AND.L (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3464;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 4);
endlabel3464: ;
return CYCLE_UNIT / 2 * 16;
}
/* AND.L (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3465;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 4);
endlabel3465: ;
return CYCLE_UNIT / 2 * 18;
}
/* AND.L (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3466;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 4);
endlabel3466: ;
return CYCLE_UNIT / 2 * 16;
}
/* AND.L (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3467;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 6);
endlabel3467: ;
return CYCLE_UNIT / 2 * 20;
}
/* AND.L (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0ba_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3468;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 4);
endlabel3468: ;
return CYCLE_UNIT / 2 * 16;
}
/* AND.L (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0bb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3469;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	m68k_dreg (regs, dstreg) = (src);
}}}}}	m68k_incpc (regs, 4);
endlabel3469: ;
return CYCLE_UNIT / 2 * 18;
}
/* AND.L #<data>.L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0bc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 12;
}
/* MULU.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpc (regs, 2);
}}}}return CYCLE_UNIT / 2 * 58;
}
/* MULU.W (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3472;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpc (regs, 2);
}}}}}}endlabel3472: ;
return CYCLE_UNIT / 2 * 62;
}
/* MULU.W (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3473;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpc (regs, 2);
}}}}}}endlabel3473: ;
return CYCLE_UNIT / 2 * 62;
}
/* MULU.W -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3474;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpc (regs, 2);
}}}}}}endlabel3474: ;
return CYCLE_UNIT / 2 * 64;
}
/* MULU.W (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3475;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpc (regs, 4);
}}}}}}endlabel3475: ;
return CYCLE_UNIT / 2 * 66;
}
/* MULU.W (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3476;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpc (regs, 4);
}}}}}}endlabel3476: ;
return CYCLE_UNIT / 2 * 68;
}
/* MULU.W (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0f8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3477;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpc (regs, 4);
}}}}}}endlabel3477: ;
return CYCLE_UNIT / 2 * 66;
}
/* MULU.W (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0f9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3478;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpc (regs, 6);
}}}}}}endlabel3478: ;
return CYCLE_UNIT / 2 * 70;
}
/* MULU.W (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3479;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpc (regs, 4);
}}}}}}endlabel3479: ;
return CYCLE_UNIT / 2 * 66;
}
/* MULU.W (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3480;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpc (regs, 4);
}}}}}}endlabel3480: ;
return CYCLE_UNIT / 2 * 68;
}
/* MULU.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c0fc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = (uae_u32)(uae_u16)dst * (uae_u32)(uae_u16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
	m68k_incpc (regs, 4);
}}}}return CYCLE_UNIT / 2 * 62;
}
/* ABCD.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c100_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 newv_lo = (src & 0xF) + (dst & 0xF) + GET_XFLG (&regs->ccrflags);
	uae_u16 newv_hi = (src & 0xF0) + (dst & 0xF0);
	uae_u16 newv, tmp_newv;
	int cflg;
	newv = tmp_newv = newv_hi + newv_lo;	if (newv_lo > 9) { newv += 6; }
	cflg = (newv & 0x3F0) > 0x90;
	if (cflg) newv += 0x60;
	SET_CFLG (&regs->ccrflags, cflg ? 1 : 0);
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	SET_VFLG (&regs->ccrflags, ((tmp_newv & 0x80) == 0 && (newv & 0x80) != 0) ? 1 : 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ABCD.B -(An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_c108_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 newv_lo = (src & 0xF) + (dst & 0xF) + GET_XFLG (&regs->ccrflags);
	uae_u16 newv_hi = (src & 0xF0) + (dst & 0xF0);
	uae_u16 newv, tmp_newv;
	int cflg;
	newv = tmp_newv = newv_hi + newv_lo;	if (newv_lo > 9) { newv += 6; }
	cflg = (newv & 0x3F0) > 0x90;
	if (cflg) newv += 0x60;
	SET_CFLG (&regs->ccrflags, cflg ? 1 : 0);
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	SET_VFLG (&regs->ccrflags, ((tmp_newv & 0x80) == 0 && (newv & 0x80) != 0) ? 1 : 0);
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 16;
}
/* AND.B Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_c110_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* AND.B Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_c118_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* AND.B Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_c120_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* AND.B Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_c128_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* AND.B Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_c130_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
{	uae_s8 dst = get_byte (dsta);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* AND.B Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_c138_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* AND.B Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_c139_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	src &= dst;
	optflag_testb (regs, (uae_s8)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_byte (dsta,src);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* EXG.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c140_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, srcreg) = (dst);
	m68k_dreg (regs, dstreg) = (src);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* EXG.L An,An */
unsigned long REGPARAM2 CPUFUNC(op_c148_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_areg (regs, srcreg) = (dst);
	m68k_areg (regs, dstreg) = (src);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* AND.W Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_c150_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3493;
	}
{{	uae_s16 dst = get_word (dsta);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3493: ;
return CYCLE_UNIT / 2 * 12;
}
/* AND.W Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_c158_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3494;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3494: ;
return CYCLE_UNIT / 2 * 12;
}
/* AND.W Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_c160_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3495;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3495: ;
return CYCLE_UNIT / 2 * 14;
}
/* AND.W Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_c168_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3496;
	}
{{	uae_s16 dst = get_word (dsta);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3496: ;
return CYCLE_UNIT / 2 * 16;
}
/* AND.W Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_c170_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3497;
	}
{{	uae_s16 dst = get_word (dsta);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3497: ;
return CYCLE_UNIT / 2 * 18;
}
/* AND.W Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_c178_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3498;
	}
{{	uae_s16 dst = get_word (dsta);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3498: ;
return CYCLE_UNIT / 2 * 16;
}
/* AND.W Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_c179_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3499;
	}
{{	uae_s16 dst = get_word (dsta);
	src &= dst;
	optflag_testw (regs, (uae_s16)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_word (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel3499: ;
return CYCLE_UNIT / 2 * 20;
}
/* EXG.L Dn,An */
unsigned long REGPARAM2 CPUFUNC(op_c188_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	m68k_dreg (regs, srcreg) = (dst);
	m68k_areg (regs, dstreg) = (src);
}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* AND.L Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_c190_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3501;
	}
{{	uae_s32 dst = get_long (dsta);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3501: ;
return CYCLE_UNIT / 2 * 20;
}
/* AND.L Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_c198_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3502;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3502: ;
return CYCLE_UNIT / 2 * 20;
}
/* AND.L Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_c1a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3503;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 2);
endlabel3503: ;
return CYCLE_UNIT / 2 * 22;
}
/* AND.L Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_c1a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3504;
	}
{{	uae_s32 dst = get_long (dsta);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3504: ;
return CYCLE_UNIT / 2 * 24;
}
/* AND.L Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_c1b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3505;
	}
{{	uae_s32 dst = get_long (dsta);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3505: ;
return CYCLE_UNIT / 2 * 26;
}
/* AND.L Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_c1b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3506;
	}
{{	uae_s32 dst = get_long (dsta);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 4);
endlabel3506: ;
return CYCLE_UNIT / 2 * 24;
}
/* AND.L Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_c1b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3507;
	}
{{	uae_s32 dst = get_long (dsta);
	src &= dst;
	optflag_testl (regs, (uae_s32)(src));
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
	put_long (dsta,src);
}}}}}	m68k_incpc (regs, 6);
endlabel3507: ;
return CYCLE_UNIT / 2 * 28;
}
/* MULS.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c1c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 58;
}
/* MULS.W (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c1d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3509;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel3509: ;
return CYCLE_UNIT / 2 * 62;
}
/* MULS.W (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c1d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3510;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel3510: ;
return CYCLE_UNIT / 2 * 62;
}
/* MULS.W -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c1e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3511;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel3511: ;
return CYCLE_UNIT / 2 * 64;
}
/* MULS.W (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c1e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3512;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3512: ;
return CYCLE_UNIT / 2 * 66;
}
/* MULS.W (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c1f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3513;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3513: ;
return CYCLE_UNIT / 2 * 68;
}
/* MULS.W (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c1f8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3514;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3514: ;
return CYCLE_UNIT / 2 * 66;
}
/* MULS.W (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c1f9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3515;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 6);
endlabel3515: ;
return CYCLE_UNIT / 2 * 70;
}
/* MULS.W (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c1fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3516;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3516: ;
return CYCLE_UNIT / 2 * 66;
}
/* MULS.W (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_c1fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3517;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3517: ;
return CYCLE_UNIT / 2 * 68;
}
/* MULS.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_c1fc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = (uae_s32)(uae_s16)dst * (uae_s32)(uae_s16)src;
	optflag_testl (regs, (uae_s32)(newv));
	m68k_dreg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 62;
}
/* ADD.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d000_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADD.B (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d010_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 8;
}
/* ADD.B (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d018_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) += areg_byteinc[srcreg];
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 8;
}
/* ADD.B -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d020_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 10;
}
/* ADD.B (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d028_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* ADD.B (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d030_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 14;
}
/* ADD.B (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d038_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* ADD.B (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d039_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 16;
}
/* ADD.B (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d03a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* ADD.B (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d03b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
{	uae_s8 src = get_byte (srca);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 14;
}
/* ADD.B #<data>.B,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d03c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = (uae_u8)get_word_prefetch (regs, 4);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 12;
}
/* ADD.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d040_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADD.W An,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d048_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADD.W (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d050_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3532;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3532: ;
return CYCLE_UNIT / 2 * 8;
}
/* ADD.W (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d058_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3533;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3533: ;
return CYCLE_UNIT / 2 * 8;
}
/* ADD.W -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d060_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3534;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3534: ;
return CYCLE_UNIT / 2 * 10;
}
/* ADD.W (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d068_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3535;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3535: ;
return CYCLE_UNIT / 2 * 12;
}
/* ADD.W (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d070_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3536;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3536: ;
return CYCLE_UNIT / 2 * 14;
}
/* ADD.W (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d078_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3537;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3537: ;
return CYCLE_UNIT / 2 * 12;
}
/* ADD.W (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d079_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3538;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 6);
endlabel3538: ;
return CYCLE_UNIT / 2 * 16;
}
/* ADD.W (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d07a_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3539;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3539: ;
return CYCLE_UNIT / 2 * 12;
}
/* ADD.W (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d07b_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3540;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3540: ;
return CYCLE_UNIT / 2 * 14;
}
/* ADD.W #<data>.W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d07c_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* ADD.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d080_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADD.L An,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d088_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADD.L (An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d090_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3544;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3544: ;
return CYCLE_UNIT / 2 * 12;
}
/* ADD.L (An)+,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d098_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3545;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3545: ;
return CYCLE_UNIT / 2 * 12;
}
/* ADD.L -(An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d0a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3546;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3546: ;
return CYCLE_UNIT / 2 * 14;
}
/* ADD.L (d16,An),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d0a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3547;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3547: ;
return CYCLE_UNIT / 2 * 16;
}
/* ADD.L (d8,An,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d0b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3548;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3548: ;
return CYCLE_UNIT / 2 * 18;
}
/* ADD.L (xxx).W,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d0b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3549;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3549: ;
return CYCLE_UNIT / 2 * 16;
}
/* ADD.L (xxx).L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d0b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3550;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel3550: ;
return CYCLE_UNIT / 2 * 20;
}
/* ADD.L (d16,PC),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d0ba_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3551;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3551: ;
return CYCLE_UNIT / 2 * 16;
}
/* ADD.L (d8,PC,Xn),Dn */
unsigned long REGPARAM2 CPUFUNC(op_d0bb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3552;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3552: ;
return CYCLE_UNIT / 2 * 18;
}
/* ADD.L #<data>.L,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d0bc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 12;
}
/* ADDA.W Dn,An */
unsigned long REGPARAM2 CPUFUNC(op_d0c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADDA.W An,An */
unsigned long REGPARAM2 CPUFUNC(op_d0c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADDA.W (An),An */
unsigned long REGPARAM2 CPUFUNC(op_d0d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3556;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel3556: ;
return CYCLE_UNIT / 2 * 8;
}
/* ADDA.W (An)+,An */
unsigned long REGPARAM2 CPUFUNC(op_d0d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3557;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) += 2;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel3557: ;
return CYCLE_UNIT / 2 * 8;
}
/* ADDA.W -(An),An */
unsigned long REGPARAM2 CPUFUNC(op_d0e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3558;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel3558: ;
return CYCLE_UNIT / 2 * 10;
}
/* ADDA.W (d16,An),An */
unsigned long REGPARAM2 CPUFUNC(op_d0e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3559;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3559: ;
return CYCLE_UNIT / 2 * 12;
}
/* ADDA.W (d8,An,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_d0f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3560;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3560: ;
return CYCLE_UNIT / 2 * 14;
}
/* ADDA.W (xxx).W,An */
unsigned long REGPARAM2 CPUFUNC(op_d0f8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3561;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3561: ;
return CYCLE_UNIT / 2 * 12;
}
/* ADDA.W (xxx).L,An */
unsigned long REGPARAM2 CPUFUNC(op_d0f9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3562;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 6);
endlabel3562: ;
return CYCLE_UNIT / 2 * 16;
}
/* ADDA.W (d16,PC),An */
unsigned long REGPARAM2 CPUFUNC(op_d0fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3563;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3563: ;
return CYCLE_UNIT / 2 * 12;
}
/* ADDA.W (d8,PC,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_d0fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3564;
	}
{{	uae_s16 src = get_word (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3564: ;
return CYCLE_UNIT / 2 * 14;
}
/* ADDA.W #<data>.W,An */
unsigned long REGPARAM2 CPUFUNC(op_d0fc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = get_word_prefetch (regs, 4);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 8;
}
/* ADDX.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d100_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uae_s8 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src + GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s8)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s8)(dst)) < 0) ? 1 : 0;
	int flgn = (((uae_s8)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((newv) & 0xff);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADDX.B -(An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_d108_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - areg_byteinc[srcreg];
{	uae_s8 src = get_byte (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src + GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s8)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s8)(dst)) < 0) ? 1 : 0;
	int flgn = (((uae_s8)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s8)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s8)(newv)) < 0) ? 1 : 0);
	put_byte (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 16;
}
/* ADD.B Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_d110_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* ADD.B Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_d118_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) += areg_byteinc[dstreg];
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 12;
}
/* ADD.B Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_d120_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - areg_byteinc[dstreg];
{	uae_s8 dst = get_byte (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 14;
}
/* ADD.B Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_d128_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* ADD.B Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_d130_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 18;
}
/* ADD.B Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_d138_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 4);
return CYCLE_UNIT / 2 * 16;
}
/* ADD.B Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_d139_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s8 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
{	uae_s8 dst = get_byte (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addb (regs, newv, (uae_s8)(src), (uae_s8)(dst));
	put_byte (dsta,newv);
}}}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 20;
}
/* ADDX.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d140_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uae_s16 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src + GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s16)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s16)(dst)) < 0) ? 1 : 0;
	int flgn = (((uae_s16)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s16)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s16)(newv)) < 0) ? 1 : 0);
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((newv) & 0xffff);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADDX.W -(An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_d148_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 2;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3576;
	}
{{	uae_s16 src = get_word (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3576;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src + GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s16)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s16)(dst)) < 0) ? 1 : 0;
	int flgn = (((uae_s16)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s16)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s16)(newv)) < 0) ? 1 : 0);
	put_word (dsta,newv);
}}}}}}}}}	m68k_incpc (regs, 2);
endlabel3576: ;
return CYCLE_UNIT / 2 * 16;
}
/* ADD.W Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_d150_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3577;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3577: ;
return CYCLE_UNIT / 2 * 12;
}
/* ADD.W Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_d158_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3578;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3578: ;
return CYCLE_UNIT / 2 * 12;
}
/* ADD.W Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_d160_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 2;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3579;
	}
{{	uae_s16 dst = get_word (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3579: ;
return CYCLE_UNIT / 2 * 14;
}
/* ADD.W Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_d168_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3580;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3580: ;
return CYCLE_UNIT / 2 * 16;
}
/* ADD.W Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_d170_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3581;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3581: ;
return CYCLE_UNIT / 2 * 18;
}
/* ADD.W Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_d178_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3582;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3582: ;
return CYCLE_UNIT / 2 * 16;
}
/* ADD.W Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_d179_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s16 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3583;
	}
{{	uae_s16 dst = get_word (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addw (regs, newv, (uae_s16)(src), (uae_s16)(dst));
	put_word (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel3583: ;
return CYCLE_UNIT / 2 * 20;
}
/* ADDX.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_d180_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src + GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s32)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s32)(dst)) < 0) ? 1 : 0;
	int flgn = (((uae_s32)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s32)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s32)(newv)) < 0) ? 1 : 0);
	m68k_dreg (regs, dstreg) = (newv);
}}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADDX.L -(An),-(An) */
unsigned long REGPARAM2 CPUFUNC(op_d188_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3585;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3585;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src + GET_XFLG (&regs->ccrflags);
{	int flgs = (((uae_s32)(src)) < 0) ? 1 : 0;
	int flgo = (((uae_s32)(dst)) < 0) ? 1 : 0;
	int flgn = (((uae_s32)(newv)) < 0) ? 1 : 0;
	SET_VFLG (&regs->ccrflags, (flgs ^ flgn) & (flgo ^ flgn));
	SET_CFLG (&regs->ccrflags, flgs ^ ((flgs ^ flgo) & (flgo ^ flgn)));
	COPY_CARRY (&regs->ccrflags);
	SET_ZFLG (&regs->ccrflags, GET_ZFLG (&regs->ccrflags) & ((((uae_s32)(newv)) == 0) ? 1 : 0));
	SET_NFLG (&regs->ccrflags, (((uae_s32)(newv)) < 0) ? 1 : 0);
	put_long (dsta,newv);
}}}}}}}}}	m68k_incpc (regs, 2);
endlabel3585: ;
return CYCLE_UNIT / 2 * 28;
}
/* ADD.L Dn,(An) */
unsigned long REGPARAM2 CPUFUNC(op_d190_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3586;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3586: ;
return CYCLE_UNIT / 2 * 20;
}
/* ADD.L Dn,(An)+ */
unsigned long REGPARAM2 CPUFUNC(op_d198_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3587;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) += 4;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3587: ;
return CYCLE_UNIT / 2 * 20;
}
/* ADD.L Dn,-(An) */
unsigned long REGPARAM2 CPUFUNC(op_d1a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = m68k_areg (regs, dstreg) - 4;
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3588;
	}
{{	uae_s32 dst = get_long (dsta);
	m68k_areg (regs, dstreg) = dsta;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 2);
endlabel3588: ;
return CYCLE_UNIT / 2 * 22;
}
/* ADD.L Dn,(d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_d1a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = m68k_areg (regs, dstreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3589;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3589: ;
return CYCLE_UNIT / 2 * 24;
}
/* ADD.L Dn,(d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_d1b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta;
	dsta = get_disp_ea_000 (regs, m68k_areg (regs, dstreg), get_word_prefetch (regs, 4));
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3590;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3590: ;
return CYCLE_UNIT / 2 * 26;
}
/* ADD.L Dn,(xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_d1b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3591;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 4);
endlabel3591: ;
return CYCLE_UNIT / 2 * 24;
}
/* ADD.L Dn,(xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_d1b9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uaecptr dsta = get_long_prefetch (regs, 4);
	if (dsta & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dsta);
		goto endlabel3592;
	}
{{	uae_s32 dst = get_long (dsta);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{{	uae_u32 newv;
	optflag_addl (regs, newv, (uae_s32)(src), (uae_s32)(dst));
	put_long (dsta,newv);
}}}}}}}	m68k_incpc (regs, 6);
endlabel3592: ;
return CYCLE_UNIT / 2 * 28;
}
/* ADDA.L Dn,An */
unsigned long REGPARAM2 CPUFUNC(op_d1c0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_dreg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADDA.L An,An */
unsigned long REGPARAM2 CPUFUNC(op_d1c8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = m68k_areg (regs, srcreg);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ADDA.L (An),An */
unsigned long REGPARAM2 CPUFUNC(op_d1d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3595;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel3595: ;
return CYCLE_UNIT / 2 * 12;
}
/* ADDA.L (An)+,An */
unsigned long REGPARAM2 CPUFUNC(op_d1d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3596;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) += 4;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel3596: ;
return CYCLE_UNIT / 2 * 12;
}
#endif

#ifdef PART_8
/* ADDA.L -(An),An */
unsigned long REGPARAM2 CPUFUNC(op_d1e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = m68k_areg (regs, srcreg) - 4;
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3597;
	}
{{	uae_s32 src = get_long (srca);
	m68k_areg (regs, srcreg) = srca;
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 2);
endlabel3597: ;
return CYCLE_UNIT / 2 * 14;
}
/* ADDA.L (d16,An),An */
unsigned long REGPARAM2 CPUFUNC(op_d1e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3598;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3598: ;
return CYCLE_UNIT / 2 * 16;
}
/* ADDA.L (d8,An,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_d1f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca;
	srca = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3599;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3599: ;
return CYCLE_UNIT / 2 * 18;
}
/* ADDA.L (xxx).W,An */
unsigned long REGPARAM2 CPUFUNC(op_d1f8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3600;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3600: ;
return CYCLE_UNIT / 2 * 16;
}
/* ADDA.L (xxx).L,An */
unsigned long REGPARAM2 CPUFUNC(op_d1f9_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = get_long_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3601;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 6);
endlabel3601: ;
return CYCLE_UNIT / 2 * 20;
}
/* ADDA.L (d16,PC),An */
unsigned long REGPARAM2 CPUFUNC(op_d1fa_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr srca = m68k_getpc (regs) + 2;
	srca += (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3602;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3602: ;
return CYCLE_UNIT / 2 * 16;
}
/* ADDA.L (d8,PC,Xn),An */
unsigned long REGPARAM2 CPUFUNC(op_d1fb_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uaecptr tmppc;
	uaecptr srca;
	tmppc = m68k_getpc (regs) + 2;
	srca = get_disp_ea_000 (regs, tmppc, get_word_prefetch (regs, 4));
	if (srca & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, srca);
		goto endlabel3603;
	}
{{	uae_s32 src = get_long (srca);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}}}	m68k_incpc (regs, 4);
endlabel3603: ;
return CYCLE_UNIT / 2 * 18;
}
/* ADDA.L #<data>.L,An */
unsigned long REGPARAM2 CPUFUNC(op_d1fc_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 dstreg = (opcode >> 9) & 7;
{{	uae_s32 src = get_long_prefetch (regs, 4);
{	uae_s32 dst = m68k_areg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 newv = dst + src;
	m68k_areg (regs, dstreg) = (newv);
}}}}	m68k_incpc (regs, 6);
return CYCLE_UNIT / 2 * 12;
}
/* ASR.B #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e000_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	uae_u32 sign = (0x80 & val) >> 7;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 8) {
		val = 0xff & (uae_u32)-sign;
		SET_CFLG (&regs->ccrflags, sign);
		COPY_CARRY (&regs->ccrflags);
	} else {
		val >>= cnt - 1;
		SET_CFLG (&regs->ccrflags, val & 1);
		COPY_CARRY (&regs->ccrflags);
		val >>= 1;
		val |= (0xff << (8 - cnt)) & (uae_u32)-sign;
		val &= 0xff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* LSR.B #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e008_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 8) {
		SET_CFLG (&regs->ccrflags, ((cnt == 8) ? 1 : 0) & (val >> 7));
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else {
		val >>= cnt - 1;
		SET_CFLG (&regs->ccrflags, val & 1);
		COPY_CARRY (&regs->ccrflags);
		val >>= 1;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROXR.B #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e010_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
{	cnt--;
	{
	uae_u32 carry;
	uae_u32 hival = (val << 1) | GET_XFLG (&regs->ccrflags);
	hival <<= (7 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (&regs->ccrflags, carry);
	val &= 0xff;
	} }
	SET_CFLG (&regs->ccrflags, GET_XFLG (&regs->ccrflags));
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROR.B #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e018_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
{	uae_u32 hival;
	cnt &= 7;
	hival = val << (8 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xff;
	SET_CFLG (&regs->ccrflags, (val & 0x80) >> 7);
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ASR.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e020_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	uae_u32 sign = (0x80 & val) >> 7;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 8) {
		val = 0xff & (uae_u32)-sign;
		SET_CFLG (&regs->ccrflags, sign);
		COPY_CARRY (&regs->ccrflags);
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (&regs->ccrflags, val & 1);
		COPY_CARRY (&regs->ccrflags);
		val >>= 1;
		val |= (0xff << (8 - cnt)) & (uae_u32)-sign;
		val &= 0xff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* LSR.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e028_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 8) {
		SET_CFLG (&regs->ccrflags, ((cnt == 8) ? 1 : 0) & (val >> 7));
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (&regs->ccrflags, val & 1);
		COPY_CARRY (&regs->ccrflags);
		val >>= 1;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROXR.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e030_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 36) cnt -= 36;
	if (cnt >= 18) cnt -= 18;
	if (cnt >= 9) cnt -= 9;
	if (cnt > 0) {
	cnt--;
	{
	uae_u32 carry;
	uae_u32 hival = (val << 1) | GET_XFLG (&regs->ccrflags);
	hival <<= (7 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (&regs->ccrflags, carry);
	val &= 0xff;
	} }
	SET_CFLG (&regs->ccrflags, GET_XFLG (&regs->ccrflags));
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROR.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e038_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt > 0) {	uae_u32 hival;
	cnt &= 7;
	hival = val << (8 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xff;
	SET_CFLG (&regs->ccrflags, (val & 0x80) >> 7);
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ASR.W #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e040_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = (0x8000 & val) >> 15;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 16) {
		val = 0xffff & (uae_u32)-sign;
		SET_CFLG (&regs->ccrflags, sign);
		COPY_CARRY (&regs->ccrflags);
	} else {
		val >>= cnt - 1;
		SET_CFLG (&regs->ccrflags, val & 1);
		COPY_CARRY (&regs->ccrflags);
		val >>= 1;
		val |= (0xffff << (16 - cnt)) & (uae_u32)-sign;
		val &= 0xffff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* LSR.W #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e048_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 16) {
		SET_CFLG (&regs->ccrflags, ((cnt == 16) ? 1 : 0) & (val >> 15));
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else {
		val >>= cnt - 1;
		SET_CFLG (&regs->ccrflags, val & 1);
		COPY_CARRY (&regs->ccrflags);
		val >>= 1;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROXR.W #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e050_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
{	cnt--;
	{
	uae_u32 carry;
	uae_u32 hival = (val << 1) | GET_XFLG (&regs->ccrflags);
	hival <<= (15 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (&regs->ccrflags, carry);
	val &= 0xffff;
	} }
	SET_CFLG (&regs->ccrflags, GET_XFLG (&regs->ccrflags));
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROR.W #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e058_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
{	uae_u32 hival;
	cnt &= 15;
	hival = val << (16 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xffff;
	SET_CFLG (&regs->ccrflags, (val & 0x8000) >> 15);
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ASR.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e060_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = (0x8000 & val) >> 15;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 16) {
		val = 0xffff & (uae_u32)-sign;
		SET_CFLG (&regs->ccrflags, sign);
		COPY_CARRY (&regs->ccrflags);
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (&regs->ccrflags, val & 1);
		COPY_CARRY (&regs->ccrflags);
		val >>= 1;
		val |= (0xffff << (16 - cnt)) & (uae_u32)-sign;
		val &= 0xffff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* LSR.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e068_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 16) {
		SET_CFLG (&regs->ccrflags, ((cnt == 16) ? 1 : 0) & (val >> 15));
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (&regs->ccrflags, val & 1);
		COPY_CARRY (&regs->ccrflags);
		val >>= 1;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROXR.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e070_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 34) cnt -= 34;
	if (cnt >= 17) cnt -= 17;
	if (cnt > 0) {
	cnt--;
	{
	uae_u32 carry;
	uae_u32 hival = (val << 1) | GET_XFLG (&regs->ccrflags);
	hival <<= (15 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (&regs->ccrflags, carry);
	val &= 0xffff;
	} }
	SET_CFLG (&regs->ccrflags, GET_XFLG (&regs->ccrflags));
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROR.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e078_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt > 0) {	uae_u32 hival;
	cnt &= 15;
	hival = val << (16 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xffff;
	SET_CFLG (&regs->ccrflags, (val & 0x8000) >> 15);
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ASR.L #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e080_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	uae_u32 sign = (0x80000000 & val) >> 31;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 32) {
		val = 0xffffffff & (uae_u32)-sign;
		SET_CFLG (&regs->ccrflags, sign);
		COPY_CARRY (&regs->ccrflags);
	} else {
		val >>= cnt - 1;
		SET_CFLG (&regs->ccrflags, val & 1);
		COPY_CARRY (&regs->ccrflags);
		val >>= 1;
		val |= (0xffffffff << (32 - cnt)) & (uae_u32)-sign;
		val &= 0xffffffff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* LSR.L #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e088_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 32) {
		SET_CFLG (&regs->ccrflags, ((cnt == 32) ? 1 : 0) & (val >> 31));
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else {
		val >>= cnt - 1;
		SET_CFLG (&regs->ccrflags, val & 1);
		COPY_CARRY (&regs->ccrflags);
		val >>= 1;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROXR.L #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e090_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
{	cnt--;
	{
	uae_u32 carry;
	uae_u32 hival = (val << 1) | GET_XFLG (&regs->ccrflags);
	hival <<= (31 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (&regs->ccrflags, carry);
	val &= 0xffffffff;
	} }
	SET_CFLG (&regs->ccrflags, GET_XFLG (&regs->ccrflags));
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROR.L #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e098_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
{	uae_u32 hival;
	cnt &= 31;
	hival = val << (32 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xffffffff;
	SET_CFLG (&regs->ccrflags, (val & 0x80000000) >> 31);
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ASR.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e0a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	uae_u32 sign = (0x80000000 & val) >> 31;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 32) {
		val = 0xffffffff & (uae_u32)-sign;
		SET_CFLG (&regs->ccrflags, sign);
		COPY_CARRY (&regs->ccrflags);
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (&regs->ccrflags, val & 1);
		COPY_CARRY (&regs->ccrflags);
		val >>= 1;
		val |= (0xffffffff << (32 - cnt)) & (uae_u32)-sign;
		val &= 0xffffffff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* LSR.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e0a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 32) {
		SET_CFLG (&regs->ccrflags, ((cnt == 32) ? 1 : 0) & (val >> 31));
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else if (cnt > 0) {
		val >>= cnt - 1;
		SET_CFLG (&regs->ccrflags, val & 1);
		COPY_CARRY (&regs->ccrflags);
		val >>= 1;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROXR.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e0b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 33) cnt -= 33;
	if (cnt > 0) {
	cnt--;
	{
	uae_u32 carry;
	uae_u32 hival = (val << 1) | GET_XFLG (&regs->ccrflags);
	hival <<= (31 - cnt);
	val >>= cnt;
	carry = val & 1;
	val >>= 1;
	val |= hival;
	SET_XFLG (&regs->ccrflags, carry);
	val &= 0xffffffff;
	} }
	SET_CFLG (&regs->ccrflags, GET_XFLG (&regs->ccrflags));
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROR.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e0b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt > 0) {	uae_u32 hival;
	cnt &= 31;
	hival = val << (32 - cnt);
	val >>= cnt;
	val |= hival;
	val &= 0xffffffff;
	SET_CFLG (&regs->ccrflags, (val & 0x80000000) >> 31);
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ASRW.W (An) */
unsigned long REGPARAM2 CPUFUNC(op_e0d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3629;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 cflg = val & 1;
	val = (val >> 1) | sign;
	optflag_testw (regs, (uae_s16)(val));
	SET_CFLG (&regs->ccrflags, cflg);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3629: ;
return CYCLE_UNIT / 2 * 12;
}
/* ASRW.W (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_e0d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3630;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 cflg = val & 1;
	val = (val >> 1) | sign;
	optflag_testw (regs, (uae_s16)(val));
	SET_CFLG (&regs->ccrflags, cflg);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3630: ;
return CYCLE_UNIT / 2 * 12;
}
/* ASRW.W -(An) */
unsigned long REGPARAM2 CPUFUNC(op_e0e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3631;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 cflg = val & 1;
	val = (val >> 1) | sign;
	optflag_testw (regs, (uae_s16)(val));
	SET_CFLG (&regs->ccrflags, cflg);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3631: ;
return CYCLE_UNIT / 2 * 14;
}
/* ASRW.W (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_e0e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3632;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 cflg = val & 1;
	val = (val >> 1) | sign;
	optflag_testw (regs, (uae_s16)(val));
	SET_CFLG (&regs->ccrflags, cflg);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3632: ;
return CYCLE_UNIT / 2 * 16;
}
/* ASRW.W (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_e0f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3633;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 cflg = val & 1;
	val = (val >> 1) | sign;
	optflag_testw (regs, (uae_s16)(val));
	SET_CFLG (&regs->ccrflags, cflg);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3633: ;
return CYCLE_UNIT / 2 * 18;
}
/* ASRW.W (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_e0f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3634;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 cflg = val & 1;
	val = (val >> 1) | sign;
	optflag_testw (regs, (uae_s16)(val));
	SET_CFLG (&regs->ccrflags, cflg);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3634: ;
return CYCLE_UNIT / 2 * 16;
}
/* ASRW.W (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_e0f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = get_long_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3635;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 cflg = val & 1;
	val = (val >> 1) | sign;
	optflag_testw (regs, (uae_s16)(val));
	SET_CFLG (&regs->ccrflags, cflg);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 6);
endlabel3635: ;
return CYCLE_UNIT / 2 * 20;
}
/* ASL.B #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e100_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 8) {
		SET_VFLG (&regs->ccrflags, (val != 0) ? 1 : 0);
		SET_CFLG (&regs->ccrflags, cnt == 8 ? val & 1 : 0);
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else {
		uae_u32 mask = (0xff << (7 - cnt)) & 0xff;
		SET_VFLG (&regs->ccrflags, ((val & mask) != mask && (val & mask) != 0) ? 1 : 0);
		val <<= cnt - 1;
		SET_CFLG (&regs->ccrflags, (val & 0x80) >> 7);
		COPY_CARRY (&regs->ccrflags);
		val <<= 1;
		val &= 0xff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* LSL.B #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e108_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 8) {
		SET_CFLG (&regs->ccrflags, cnt == 8 ? val & 1 : 0);
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else {
		val <<= (cnt - 1);
		SET_CFLG (&regs->ccrflags, (val & 0x80) >> 7);
		COPY_CARRY (&regs->ccrflags);
		val <<= 1;
	val &= 0xff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROXL.B #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e110_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
{	cnt--;
	{
	uae_u32 carry;
	uae_u32 loval = val >> (7 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG (&regs->ccrflags)) << cnt) | (loval >> 1);
	SET_XFLG (&regs->ccrflags, carry);
	val &= 0xff;
	} }
	SET_CFLG (&regs->ccrflags, GET_XFLG (&regs->ccrflags));
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROL.B #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e118_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
{	uae_u32 loval;
	cnt &= 7;
	loval = val >> (8 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xff;
	SET_CFLG (&regs->ccrflags, val & 1);
}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ASL.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e120_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 8) {
		SET_VFLG (&regs->ccrflags, (val != 0) ? 1 : 0);
		SET_CFLG (&regs->ccrflags, cnt == 8 ? val & 1 : 0);
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else if (cnt > 0) {
		uae_u32 mask = (0xff << (7 - cnt)) & 0xff;
		SET_VFLG (&regs->ccrflags, ((val & mask) != mask && (val & mask) != 0) ? 1 : 0);
		val <<= cnt - 1;
		SET_CFLG (&regs->ccrflags, (val & 0x80) >> 7);
		COPY_CARRY (&regs->ccrflags);
		val <<= 1;
		val &= 0xff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* LSL.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e128_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 8) {
		SET_CFLG (&regs->ccrflags, cnt == 8 ? val & 1 : 0);
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else if (cnt > 0) {
		val <<= (cnt - 1);
		SET_CFLG (&regs->ccrflags, (val & 0x80) >> 7);
		COPY_CARRY (&regs->ccrflags);
		val <<= 1;
	val &= 0xff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROXL.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e130_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 36) cnt -= 36;
	if (cnt >= 18) cnt -= 18;
	if (cnt >= 9) cnt -= 9;
	if (cnt > 0) {
	cnt--;
	{
	uae_u32 carry;
	uae_u32 loval = val >> (7 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG (&regs->ccrflags)) << cnt) | (loval >> 1);
	SET_XFLG (&regs->ccrflags, carry);
	val &= 0xff;
	} }
	SET_CFLG (&regs->ccrflags, GET_XFLG (&regs->ccrflags));
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROL.B Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e138_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s8 cnt = m68k_dreg (regs, srcreg);
{	uae_s8 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u8)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt > 0) {
	uae_u32 loval;
	cnt &= 7;
	loval = val >> (8 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xff;
	SET_CFLG (&regs->ccrflags, val & 1);
}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testb (regs, (uae_s8)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xff) | ((val) & 0xff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ASL.W #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e140_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 16) {
		SET_VFLG (&regs->ccrflags, (val != 0) ? 1 : 0);
		SET_CFLG (&regs->ccrflags, cnt == 16 ? val & 1 : 0);
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else {
		uae_u32 mask = (0xffff << (15 - cnt)) & 0xffff;
		SET_VFLG (&regs->ccrflags, ((val & mask) != mask && (val & mask) != 0) ? 1 : 0);
		val <<= cnt - 1;
		SET_CFLG (&regs->ccrflags, (val & 0x8000) >> 15);
		COPY_CARRY (&regs->ccrflags);
		val <<= 1;
		val &= 0xffff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* LSL.W #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e148_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 16) {
		SET_CFLG (&regs->ccrflags, cnt == 16 ? val & 1 : 0);
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else {
		val <<= (cnt - 1);
		SET_CFLG (&regs->ccrflags, (val & 0x8000) >> 15);
		COPY_CARRY (&regs->ccrflags);
		val <<= 1;
	val &= 0xffff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROXL.W #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e150_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
{	cnt--;
	{
	uae_u32 carry;
	uae_u32 loval = val >> (15 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG (&regs->ccrflags)) << cnt) | (loval >> 1);
	SET_XFLG (&regs->ccrflags, carry);
	val &= 0xffff;
	} }
	SET_CFLG (&regs->ccrflags, GET_XFLG (&regs->ccrflags));
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROL.W #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e158_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
{	uae_u32 loval;
	cnt &= 15;
	loval = val >> (16 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xffff;
	SET_CFLG (&regs->ccrflags, val & 1);
}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ASL.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e160_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 16) {
		SET_VFLG (&regs->ccrflags, (val != 0) ? 1 : 0);
		SET_CFLG (&regs->ccrflags, cnt == 16 ? val & 1 : 0);
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else if (cnt > 0) {
		uae_u32 mask = (0xffff << (15 - cnt)) & 0xffff;
		SET_VFLG (&regs->ccrflags, ((val & mask) != mask && (val & mask) != 0) ? 1 : 0);
		val <<= cnt - 1;
		SET_CFLG (&regs->ccrflags, (val & 0x8000) >> 15);
		COPY_CARRY (&regs->ccrflags);
		val <<= 1;
		val &= 0xffff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* LSL.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e168_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 16) {
		SET_CFLG (&regs->ccrflags, cnt == 16 ? val & 1 : 0);
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else if (cnt > 0) {
		val <<= (cnt - 1);
		SET_CFLG (&regs->ccrflags, (val & 0x8000) >> 15);
		COPY_CARRY (&regs->ccrflags);
		val <<= 1;
	val &= 0xffff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROXL.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e170_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 34) cnt -= 34;
	if (cnt >= 17) cnt -= 17;
	if (cnt > 0) {
	cnt--;
	{
	uae_u32 carry;
	uae_u32 loval = val >> (15 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG (&regs->ccrflags)) << cnt) | (loval >> 1);
	SET_XFLG (&regs->ccrflags, carry);
	val &= 0xffff;
	} }
	SET_CFLG (&regs->ccrflags, GET_XFLG (&regs->ccrflags));
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROL.W Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e178_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s16 cnt = m68k_dreg (regs, srcreg);
{	uae_s16 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt > 0) {
	uae_u32 loval;
	cnt &= 15;
	loval = val >> (16 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xffff;
	SET_CFLG (&regs->ccrflags, val & 1);
}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testw (regs, (uae_s16)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (m68k_dreg (regs, dstreg) & ~0xffff) | ((val) & 0xffff);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ASL.L #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e180_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 32) {
		SET_VFLG (&regs->ccrflags, (val != 0) ? 1 : 0);
		SET_CFLG (&regs->ccrflags, cnt == 32 ? val & 1 : 0);
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else {
		uae_u32 mask = (0xffffffff << (31 - cnt)) & 0xffffffff;
		SET_VFLG (&regs->ccrflags, ((val & mask) != mask && (val & mask) != 0) ? 1 : 0);
		val <<= cnt - 1;
		SET_CFLG (&regs->ccrflags, (val & 0x80000000) >> 31);
		COPY_CARRY (&regs->ccrflags);
		val <<= 1;
		val &= 0xffffffff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* LSL.L #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e188_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 32) {
		SET_CFLG (&regs->ccrflags, cnt == 32 ? val & 1 : 0);
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else {
		val <<= (cnt - 1);
		SET_CFLG (&regs->ccrflags, (val & 0x80000000) >> 31);
		COPY_CARRY (&regs->ccrflags);
		val <<= 1;
	val &= 0xffffffff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROXL.L #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e190_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
{	cnt--;
	{
	uae_u32 carry;
	uae_u32 loval = val >> (31 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG (&regs->ccrflags)) << cnt) | (loval >> 1);
	SET_XFLG (&regs->ccrflags, carry);
	val &= 0xffffffff;
	} }
	SET_CFLG (&regs->ccrflags, GET_XFLG (&regs->ccrflags));
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROL.L #<data>,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e198_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = imm8_table[((opcode >> 9) & 7)];
	uae_u32 dstreg = opcode & 7;
{{	uae_u32 cnt = srcreg;
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
{	uae_u32 loval;
	cnt &= 31;
	loval = val >> (32 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xffffffff;
	SET_CFLG (&regs->ccrflags, val & 1);
}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ASL.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e1a0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 32) {
		SET_VFLG (&regs->ccrflags, (val != 0) ? 1 : 0);
		SET_CFLG (&regs->ccrflags, cnt == 32 ? val & 1 : 0);
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else if (cnt > 0) {
		uae_u32 mask = (0xffffffff << (31 - cnt)) & 0xffffffff;
		SET_VFLG (&regs->ccrflags, ((val & mask) != mask && (val & mask) != 0) ? 1 : 0);
		val <<= cnt - 1;
		SET_CFLG (&regs->ccrflags, (val & 0x80000000) >> 31);
		COPY_CARRY (&regs->ccrflags);
		val <<= 1;
		val &= 0xffffffff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* LSL.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e1a8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 32) {
		SET_CFLG (&regs->ccrflags, cnt == 32 ? val & 1 : 0);
		COPY_CARRY (&regs->ccrflags);
		val = 0;
	} else if (cnt > 0) {
		val <<= (cnt - 1);
		SET_CFLG (&regs->ccrflags, (val & 0x80000000) >> 31);
		COPY_CARRY (&regs->ccrflags);
		val <<= 1;
	val &= 0xffffffff;
	}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROXL.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e1b0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt >= 33) cnt -= 33;
	if (cnt > 0) {
	cnt--;
	{
	uae_u32 carry;
	uae_u32 loval = val >> (31 - cnt);
	carry = loval & 1;
	val = (((val << 1) | GET_XFLG (&regs->ccrflags)) << cnt) | (loval >> 1);
	SET_XFLG (&regs->ccrflags, carry);
	val &= 0xffffffff;
	} }
	SET_CFLG (&regs->ccrflags, GET_XFLG (&regs->ccrflags));
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ROL.L Dn,Dn */
unsigned long REGPARAM2 CPUFUNC(op_e1b8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = ((opcode >> 9) & 7);
	uae_u32 dstreg = opcode & 7;
{{	uae_s32 cnt = m68k_dreg (regs, srcreg);
{	uae_s32 data = m68k_dreg (regs, dstreg);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = data;
	int ccnt = cnt & 63;
	cnt &= 63;
	CLEAR_CZNV (&regs->ccrflags);
	if (cnt > 0) {
	uae_u32 loval;
	cnt &= 31;
	loval = val >> (32 - cnt);
	val <<= cnt;
	val |= loval;
	val &= 0xffffffff;
	SET_CFLG (&regs->ccrflags, val & 1);
}
	{uae_u32 oldcznv = GET_CZNV (&regs->ccrflags) & ~(FLAGVAL_Z | FLAGVAL_N);
	optflag_testl (regs, (uae_s32)(val));
	IOR_CZNV (&regs->ccrflags, oldcznv);
	}
	m68k_dreg (regs, dstreg) = (val);
}}}}	m68k_incpc (regs, 2);
return CYCLE_UNIT / 2 * 4;
}
/* ASLW.W (An) */
unsigned long REGPARAM2 CPUFUNC(op_e1d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3660;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 sign2;
	val <<= 1;
	optflag_testw (regs, (uae_s16)(val));
	sign2 = 0x8000 & val;
	SET_CFLG (&regs->ccrflags, sign != 0);
	COPY_CARRY (&regs->ccrflags);
	SET_VFLG (&regs->ccrflags, (GET_VFLG (&regs->ccrflags) | (sign2 != sign)) ? 1 : 0);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3660: ;
return CYCLE_UNIT / 2 * 12;
}
/* ASLW.W (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_e1d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3661;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 sign2;
	val <<= 1;
	optflag_testw (regs, (uae_s16)(val));
	sign2 = 0x8000 & val;
	SET_CFLG (&regs->ccrflags, sign != 0);
	COPY_CARRY (&regs->ccrflags);
	SET_VFLG (&regs->ccrflags, (GET_VFLG (&regs->ccrflags) | (sign2 != sign)) ? 1 : 0);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3661: ;
return CYCLE_UNIT / 2 * 12;
}
/* ASLW.W -(An) */
unsigned long REGPARAM2 CPUFUNC(op_e1e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3662;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 sign2;
	val <<= 1;
	optflag_testw (regs, (uae_s16)(val));
	sign2 = 0x8000 & val;
	SET_CFLG (&regs->ccrflags, sign != 0);
	COPY_CARRY (&regs->ccrflags);
	SET_VFLG (&regs->ccrflags, (GET_VFLG (&regs->ccrflags) | (sign2 != sign)) ? 1 : 0);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3662: ;
return CYCLE_UNIT / 2 * 14;
}
/* ASLW.W (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_e1e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3663;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 sign2;
	val <<= 1;
	optflag_testw (regs, (uae_s16)(val));
	sign2 = 0x8000 & val;
	SET_CFLG (&regs->ccrflags, sign != 0);
	COPY_CARRY (&regs->ccrflags);
	SET_VFLG (&regs->ccrflags, (GET_VFLG (&regs->ccrflags) | (sign2 != sign)) ? 1 : 0);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3663: ;
return CYCLE_UNIT / 2 * 16;
}
/* ASLW.W (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_e1f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3664;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 sign2;
	val <<= 1;
	optflag_testw (regs, (uae_s16)(val));
	sign2 = 0x8000 & val;
	SET_CFLG (&regs->ccrflags, sign != 0);
	COPY_CARRY (&regs->ccrflags);
	SET_VFLG (&regs->ccrflags, (GET_VFLG (&regs->ccrflags) | (sign2 != sign)) ? 1 : 0);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3664: ;
return CYCLE_UNIT / 2 * 18;
}
/* ASLW.W (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_e1f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3665;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 sign2;
	val <<= 1;
	optflag_testw (regs, (uae_s16)(val));
	sign2 = 0x8000 & val;
	SET_CFLG (&regs->ccrflags, sign != 0);
	COPY_CARRY (&regs->ccrflags);
	SET_VFLG (&regs->ccrflags, (GET_VFLG (&regs->ccrflags) | (sign2 != sign)) ? 1 : 0);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3665: ;
return CYCLE_UNIT / 2 * 16;
}
/* ASLW.W (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_e1f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = get_long_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3666;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 val = (uae_u16)data;
	uae_u32 sign = 0x8000 & val;
	uae_u32 sign2;
	val <<= 1;
	optflag_testw (regs, (uae_s16)(val));
	sign2 = 0x8000 & val;
	SET_CFLG (&regs->ccrflags, sign != 0);
	COPY_CARRY (&regs->ccrflags);
	SET_VFLG (&regs->ccrflags, (GET_VFLG (&regs->ccrflags) | (sign2 != sign)) ? 1 : 0);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 6);
endlabel3666: ;
return CYCLE_UNIT / 2 * 20;
}
/* LSRW.W (An) */
unsigned long REGPARAM2 CPUFUNC(op_e2d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3667;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	uae_u32 carry = val & 1;
	val >>= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3667: ;
return CYCLE_UNIT / 2 * 12;
}
/* LSRW.W (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_e2d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3668;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	uae_u32 carry = val & 1;
	val >>= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3668: ;
return CYCLE_UNIT / 2 * 12;
}
/* LSRW.W -(An) */
unsigned long REGPARAM2 CPUFUNC(op_e2e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3669;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u32 val = (uae_u16)data;
	uae_u32 carry = val & 1;
	val >>= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3669: ;
return CYCLE_UNIT / 2 * 14;
}
/* LSRW.W (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_e2e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3670;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 val = (uae_u16)data;
	uae_u32 carry = val & 1;
	val >>= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3670: ;
return CYCLE_UNIT / 2 * 16;
}
/* LSRW.W (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_e2f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3671;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 val = (uae_u16)data;
	uae_u32 carry = val & 1;
	val >>= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3671: ;
return CYCLE_UNIT / 2 * 18;
}
/* LSRW.W (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_e2f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3672;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u32 val = (uae_u16)data;
	uae_u32 carry = val & 1;
	val >>= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3672: ;
return CYCLE_UNIT / 2 * 16;
}
/* LSRW.W (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_e2f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = get_long_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3673;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u32 val = (uae_u16)data;
	uae_u32 carry = val & 1;
	val >>= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 6);
endlabel3673: ;
return CYCLE_UNIT / 2 * 20;
}
/* LSLW.W (An) */
unsigned long REGPARAM2 CPUFUNC(op_e3d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3674;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3674: ;
return CYCLE_UNIT / 2 * 12;
}
/* LSLW.W (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_e3d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3675;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3675: ;
return CYCLE_UNIT / 2 * 12;
}
/* LSLW.W -(An) */
unsigned long REGPARAM2 CPUFUNC(op_e3e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3676;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3676: ;
return CYCLE_UNIT / 2 * 14;
}
/* LSLW.W (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_e3e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3677;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3677: ;
return CYCLE_UNIT / 2 * 16;
}
/* LSLW.W (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_e3f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3678;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3678: ;
return CYCLE_UNIT / 2 * 18;
}
/* LSLW.W (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_e3f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3679;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3679: ;
return CYCLE_UNIT / 2 * 16;
}
/* LSLW.W (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_e3f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = get_long_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3680;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 6);
endlabel3680: ;
return CYCLE_UNIT / 2 * 20;
}
/* ROXRW.W (An) */
unsigned long REGPARAM2 CPUFUNC(op_e4d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3681;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG (&regs->ccrflags)) val |= 0x8000;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3681: ;
return CYCLE_UNIT / 2 * 12;
}
/* ROXRW.W (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_e4d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3682;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG (&regs->ccrflags)) val |= 0x8000;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3682: ;
return CYCLE_UNIT / 2 * 12;
}
/* ROXRW.W -(An) */
unsigned long REGPARAM2 CPUFUNC(op_e4e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3683;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG (&regs->ccrflags)) val |= 0x8000;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3683: ;
return CYCLE_UNIT / 2 * 14;
}
/* ROXRW.W (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_e4e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3684;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG (&regs->ccrflags)) val |= 0x8000;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3684: ;
return CYCLE_UNIT / 2 * 16;
}
/* ROXRW.W (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_e4f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3685;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG (&regs->ccrflags)) val |= 0x8000;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3685: ;
return CYCLE_UNIT / 2 * 18;
}
/* ROXRW.W (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_e4f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3686;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG (&regs->ccrflags)) val |= 0x8000;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3686: ;
return CYCLE_UNIT / 2 * 16;
}
/* ROXRW.W (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_e4f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = get_long_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3687;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (GET_XFLG (&regs->ccrflags)) val |= 0x8000;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 6);
endlabel3687: ;
return CYCLE_UNIT / 2 * 20;
}
/* ROXLW.W (An) */
unsigned long REGPARAM2 CPUFUNC(op_e5d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3688;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG (&regs->ccrflags)) val |= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3688: ;
return CYCLE_UNIT / 2 * 12;
}
/* ROXLW.W (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_e5d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3689;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG (&regs->ccrflags)) val |= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3689: ;
return CYCLE_UNIT / 2 * 12;
}
/* ROXLW.W -(An) */
unsigned long REGPARAM2 CPUFUNC(op_e5e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3690;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG (&regs->ccrflags)) val |= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3690: ;
return CYCLE_UNIT / 2 * 14;
}
/* ROXLW.W (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_e5e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3691;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG (&regs->ccrflags)) val |= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3691: ;
return CYCLE_UNIT / 2 * 16;
}
/* ROXLW.W (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_e5f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3692;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG (&regs->ccrflags)) val |= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3692: ;
return CYCLE_UNIT / 2 * 18;
}
/* ROXLW.W (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_e5f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3693;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG (&regs->ccrflags)) val |= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3693: ;
return CYCLE_UNIT / 2 * 16;
}
/* ROXLW.W (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_e5f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = get_long_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3694;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (GET_XFLG (&regs->ccrflags)) val |= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	COPY_CARRY (&regs->ccrflags);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 6);
endlabel3694: ;
return CYCLE_UNIT / 2 * 20;
}
/* RORW.W (An) */
unsigned long REGPARAM2 CPUFUNC(op_e6d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3695;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3695: ;
return CYCLE_UNIT / 2 * 12;
}
/* RORW.W (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_e6d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3696;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3696: ;
return CYCLE_UNIT / 2 * 12;
}
/* RORW.W -(An) */
unsigned long REGPARAM2 CPUFUNC(op_e6e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3697;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3697: ;
return CYCLE_UNIT / 2 * 14;
}
/* RORW.W (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_e6e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3698;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3698: ;
return CYCLE_UNIT / 2 * 16;
}
/* RORW.W (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_e6f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3699;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3699: ;
return CYCLE_UNIT / 2 * 18;
}
/* RORW.W (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_e6f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3700;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3700: ;
return CYCLE_UNIT / 2 * 16;
}
/* RORW.W (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_e6f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = get_long_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3701;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u16 val = data;
	uae_u32 carry = val & 1;
	val >>= 1;
	if (carry) val |= 0x8000;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 6);
endlabel3701: ;
return CYCLE_UNIT / 2 * 20;
}
/* ROLW.W (An) */
unsigned long REGPARAM2 CPUFUNC(op_e7d0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3702;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3702: ;
return CYCLE_UNIT / 2 * 12;
}
/* ROLW.W (An)+ */
unsigned long REGPARAM2 CPUFUNC(op_e7d8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3703;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) += 2;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3703: ;
return CYCLE_UNIT / 2 * 12;
}
/* ROLW.W -(An) */
unsigned long REGPARAM2 CPUFUNC(op_e7e0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = m68k_areg (regs, srcreg) - 2;
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3704;
	}
{{	uae_s16 data = get_word (dataa);
	m68k_areg (regs, srcreg) = dataa;
	regs->ir = regs->irc;
	get_word_prefetch (regs, 4);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 2);
endlabel3704: ;
return CYCLE_UNIT / 2 * 14;
}
/* ROLW.W (d16,An) */
unsigned long REGPARAM2 CPUFUNC(op_e7e8_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa = m68k_areg (regs, srcreg) + (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3705;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3705: ;
return CYCLE_UNIT / 2 * 16;
}
/* ROLW.W (d8,An,Xn) */
unsigned long REGPARAM2 CPUFUNC(op_e7f0_5)(uae_u32 opcode, struct regstruct *regs)
{
	uae_u32 srcreg = (opcode & 7);
{{	uaecptr dataa;
	dataa = get_disp_ea_000 (regs, m68k_areg (regs, srcreg), get_word_prefetch (regs, 4));
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3706;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3706: ;
return CYCLE_UNIT / 2 * 18;
}
/* ROLW.W (xxx).W */
unsigned long REGPARAM2 CPUFUNC(op_e7f8_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = (uae_s32)(uae_s16)get_word_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3707;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 6);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 4);
endlabel3707: ;
return CYCLE_UNIT / 2 * 16;
}
/* ROLW.W (xxx).L */
unsigned long REGPARAM2 CPUFUNC(op_e7f9_5)(uae_u32 opcode, struct regstruct *regs)
{
{{	uaecptr dataa = get_long_prefetch (regs, 4);
	if (dataa & 1) {
		exception3 (opcode, m68k_getpc(regs) + 2, dataa);
		goto endlabel3708;
	}
{{	uae_s16 data = get_word (dataa);
	regs->ir = regs->irc;
	get_word_prefetch (regs, 8);
{	uae_u16 val = data;
	uae_u32 carry = val & 0x8000;
	val <<= 1;
	if (carry)  val |= 1;
	optflag_testw (regs, (uae_s16)(val));
SET_CFLG (&regs->ccrflags, carry >> 15);
	put_word (dataa,val);
}}}}}	m68k_incpc (regs, 6);
endlabel3708: ;
return CYCLE_UNIT / 2 * 20;
}
#endif

