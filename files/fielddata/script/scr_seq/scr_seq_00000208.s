	.text
	.include "asm/macros/script.inc"

_offsets:
	scrdef _scr000
	scrdef_end

_scr000:
	clearflag 0x0149
	end

_fun001:
	end

.short 0 ; nop, alignment workaround
