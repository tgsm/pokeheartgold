	.text
	.include "asm/macros/script.inc"

_offsets:
	scrdef _scr000
	scrdef _scr001
	scrdef_end

_scr000:
	checkflag 0x0149
	gotoif 0x01, _fun000
	end

_fun000:
	scrcmd_186 0x01
	end

_scr001:
	scrcmd_055 0x00, 0x01, 0x0001, 0x800C
	scrcmd_057 0x03
	scrcmd_058
	scrcmd_060 0x800C
	runscriptwait 0x07D0
	end

.byte 0 ; nop, alignment workaround
