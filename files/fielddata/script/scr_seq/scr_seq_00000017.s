	.text
	.include "asm/macros/script.inc"
#include "constants/sndseq.h"

_offsets:
	scrdef _scr000
	scrdef _scr001
	scrdef _scr002
	scrdef_end

_scr000:
	end

_scr001:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_104
	scrcmd_045 0x00
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr002:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_104
	scrcmd_045 0x01
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

.short 0 ; nop, alignment workaround
