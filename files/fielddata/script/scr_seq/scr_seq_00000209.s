	.text
	.include "asm/macros/script.inc"

_offsets:
	scrdef _scr000
	scrdef _scr001
	scrdef_end

_scr000:
	scrcmd_186 0x01
	end

_scr001:
	scrcmd_186 0x01
	end
