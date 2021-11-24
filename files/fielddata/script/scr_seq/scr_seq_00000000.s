	.text
	.include "asm/macros/script.inc"
#include "constants/sndseq.h"

_offsets:
	scrdef _scr000
	scrdef _scr001
	scrdef _scr002
	scrdef_end

_scr000:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_104
	scrcmd_045 0x00
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr001:
	scrcmd_609
	scrcmd_096
	scrcmd_045 0x09
	scrcmd_746
	scrcmd_748 0x800C
	scrcmd_747
	comparevartovalue 0x800C, 0x0000
	gotoif 0x01, _fun001
	comparevartovalue 0x800C, 0x0001
	gotoif 0x01, _fun002
	end

_scr002:
	scrcmd_609
	scrcmd_096
_fun001:
	scrcmd_151
	scrcmd_045 0x0C
	scrcmd_257 0x005E
	scrcmd_053
	scrcmd_587
	scrcmd_449 0x0061, 0x0002
_fun002:
	scrcmd_053
	scrcmd_097
	end

.short 0 ; nop, alignment workaround
.byte 0
