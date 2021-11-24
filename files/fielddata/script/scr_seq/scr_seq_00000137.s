	.text
	.include "asm/macros/script.inc"

_offsets:
	scrdef _scr000
	scrdef_end

_scr000:
	scrcmd_284
	end

.short 0 ; nop, alignment workaround
