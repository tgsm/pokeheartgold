	.text
	.include "asm/macros/script.inc"
#include "constants/sndseq.h"

_offsets:
	scrdef _scr000
	scrdef _scr001
	scrdef _scr002
	scrdef _scr003
	scrdef _scr004
	scrdef _scr005
	scrdef _scr006
	scrdef _scr007
	scrdef _scr008
	scrdef _scr009
	scrdef _scr010
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
	scrcmd_045 0x03
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr003:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_104
	scrcmd_045 0x06
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr004:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_104
	scrcmd_045 0x0C
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr005:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_104
	scrcmd_045 0x09
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr006:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_104
	scrcmd_045 0x0F
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr007:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_104
	scrcmd_045 0x12
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr008:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_104
	scrcmd_045 0x15
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr009:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_104
	scrcmd_045 0x18
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr010:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_104
	scrcmd_045 0x1B
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

.short 0 ; nop, alignment workaround
