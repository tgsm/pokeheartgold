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
	scrdef_end

_scr000:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_045 0x00
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr001:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_045 0x01
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr002:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_045 0x02
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr003:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_045 0x03
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr004:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_045 0x04
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr005:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_045 0x05
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr006:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_045 0x06
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr007:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_045 0x07
	scrcmd_050
	scrcmd_053
	scrcmd_097
	end

_scr008:
	scrcmd_073 SEQ_SE_DP_SELECT
	scrcmd_096
	scrcmd_174 0x0006, 0x0001, 0x0000, 0x0000
	scrcmd_175
	scrcmd_157
	scrcmd_150
	scrcmd_174 0x0006, 0x0001, 0x0001, 0x0000
	scrcmd_175
	scrcmd_097
	end
