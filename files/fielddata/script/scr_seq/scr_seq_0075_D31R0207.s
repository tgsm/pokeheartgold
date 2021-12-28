#include "constants/scrcmd.h"
	.include "asm/macros/script.inc"

	.rodata

	scrdef scr_seq_0075_D31R0207_0177 ; 000
	scrdef scr_seq_0075_D31R0207_0246 ; 001
	scrdef scr_seq_0075_D31R0207_02D3 ; 002
	scrdef scr_seq_0075_D31R0207_033E ; 003
	scrdef scr_seq_0075_D31R0207_03A3 ; 004
	scrdef scr_seq_0075_D31R0207_0408 ; 005
	scrdef scr_seq_0075_D31R0207_002A ; 006
	scrdef scr_seq_0075_D31R0207_0126 ; 007
	scrdef scr_seq_0075_D31R0207_0156 ; 008
	scrdef scr_seq_0075_D31R0207_01D3 ; 009
	scrdef_end

scr_seq_0075_D31R0207_002A:
	comparevartovalue VAR_UNK_4151, 2
	gotoif ne, scr_seq_0075_D31R0207_004C
	scrcmd_412 55, 2, 16393
	comparevartovalue VAR_TEMP_x4009, 0
	gotoif eq, scr_seq_0075_D31R0207_00EA
scr_seq_0075_D31R0207_004C:
	clearflag FLAG_UNK_2AD
scr_seq_0075_D31R0207_0050:
	comparevartovalue VAR_UNK_4151, 2
	gotoif ne, scr_seq_0075_D31R0207_0072
	scrcmd_412 55, 2, 16393
	comparevartovalue VAR_TEMP_x4009, 1
	gotoif eq, scr_seq_0075_D31R0207_00F6
scr_seq_0075_D31R0207_0072:
	clearflag FLAG_UNK_2AE
scr_seq_0075_D31R0207_0076:
	comparevartovalue VAR_UNK_4151, 2
	gotoif ne, scr_seq_0075_D31R0207_0098
	scrcmd_412 55, 2, 16393
	comparevartovalue VAR_TEMP_x4009, 2
	gotoif eq, scr_seq_0075_D31R0207_0102
scr_seq_0075_D31R0207_0098:
	clearflag FLAG_UNK_2AF
scr_seq_0075_D31R0207_009C:
	comparevartovalue VAR_UNK_4151, 2
	gotoif ne, scr_seq_0075_D31R0207_00BE
	scrcmd_412 55, 2, 16393
	comparevartovalue VAR_TEMP_x4009, 3
	gotoif eq, scr_seq_0075_D31R0207_010E
scr_seq_0075_D31R0207_00BE:
	clearflag FLAG_UNK_2B0
scr_seq_0075_D31R0207_00C2:
	comparevartovalue VAR_UNK_4151, 2
	gotoif ne, scr_seq_0075_D31R0207_00E4
	scrcmd_412 55, 2, 16393
	comparevartovalue VAR_TEMP_x4009, 4
	gotoif eq, scr_seq_0075_D31R0207_011A
scr_seq_0075_D31R0207_00E4:
	clearflag FLAG_UNK_2B1
scr_seq_0075_D31R0207_00E8:
	end

scr_seq_0075_D31R0207_00EA:
	setflag FLAG_UNK_2AD
	goto scr_seq_0075_D31R0207_0050

scr_seq_0075_D31R0207_00F4:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_00F6:
	setflag FLAG_UNK_2AE
	goto scr_seq_0075_D31R0207_0076

scr_seq_0075_D31R0207_0100:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_0102:
	setflag FLAG_UNK_2AF
	goto scr_seq_0075_D31R0207_009C

scr_seq_0075_D31R0207_010C:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_010E:
	setflag FLAG_UNK_2B0
	goto scr_seq_0075_D31R0207_00C2

scr_seq_0075_D31R0207_0118:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_011A:
	setflag FLAG_UNK_2B1
	goto scr_seq_0075_D31R0207_00E8

scr_seq_0075_D31R0207_0124:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_0126:
	comparevartovalue VAR_UNK_4151, 1
	callif eq, scr_seq_0075_D31R0207_0142
	comparevartovalue VAR_UNK_4151, 2
	gotoif eq, scr_seq_0075_D31R0207_0148
	end

scr_seq_0075_D31R0207_0142:
	scrcmd_375 255
	return

scr_seq_0075_D31R0207_0148:
	move_person 0, 8, 0, 3, 1
	end

scr_seq_0075_D31R0207_0156:
	scrcmd_609
	lockall
	setvar VAR_UNK_4151, 0
	call scr_seq_0075_D31R0207_048B
	npc_msg 0
	closemsg
	scrcmd_412 56, 0, 0
	releaseall
	end

scr_seq_0075_D31R0207_0177:
	play_se SEQ_SE_DP_SELECT
	lockall
	faceplayer
	buffer_players_name 0
	npc_msg 1
	touchscreen_menu_hide
	getmenuchoice VAR_SPECIAL_x800C
	touchscreen_menu_show
	comparevartovalue VAR_SPECIAL_x800C, 0
	gotoif eq, scr_seq_0075_D31R0207_01A3
	npc_msg 0
	closemsg
	releaseall
	end

scr_seq_0075_D31R0207_01A3:
	closemsg
	releaseall
	setvar VAR_UNK_414B, 3
	fade_screen 6, 1, 0, 0
	wait_fade
	scrcmd_176 265, 0, 11, 6, 0
	fade_screen 6, 1, 1, 0
	wait_fade
	end

scr_seq_0075_D31R0207_01D3:
	scrcmd_609
	lockall
	setvar VAR_UNK_4151, 0
	npc_msg 2
	closemsg
	call scr_seq_0075_D31R0207_04C5
	setvar VAR_UNK_414D, 2
	fade_screen 6, 1, 0, 0
	wait_fade
	scrcmd_176 266, 0, 3, 6, 0
	fade_screen 6, 1, 1, 0
	wait_fade
	releaseall
	end

scr_seq_0075_D31R0207_0216:
	scrcmd_413 16393, 0, 32772, 32773
	buffer_species_name_custom 0, VAR_SPECIAL_x8004, 0, 0
	scrcmd_197 1, 32773
	scrcmd_413 16393, 1, 32772, 32773
	buffer_species_name_custom 2, VAR_SPECIAL_x8004, 0, 0
	scrcmd_197 3, 32773
	return

scr_seq_0075_D31R0207_0246:
	play_se SEQ_SE_DP_SELECT
	lockall
	faceplayer
	comparevartovalue VAR_UNK_4151, 2
	gotoif eq, scr_seq_0075_D31R0207_02A7
	setvar VAR_TEMP_x4009, 0
	scrcmd_413 16393, 0, 32772, 32773
	scrcmd_846 0, VAR_SPECIAL_x8004, 0, 0
	scrcmd_197 1, 32773
	scrcmd_413 16393, 1, 32772, 32773
	scrcmd_846 2, VAR_SPECIAL_x8004, 0, 0
	scrcmd_197 3, 32773
	npc_msg 6
	touchscreen_menu_hide
	getmenuchoice VAR_SPECIAL_x800C
	touchscreen_menu_show
	comparevartovalue VAR_SPECIAL_x800C, 0
	gotoif eq, scr_seq_0075_D31R0207_02B2
scr_seq_0075_D31R0207_02A7:
	npc_msg 7
	waitbutton
	closemsg
	releaseall
	end

scr_seq_0075_D31R0207_02B2:
	scrcmd_412 50, 16393, 0
	setvar VAR_UNK_4151, 2
	npc_msg 8
	closemsg
	releaseall
	scrcmd_098 1
	goto scr_seq_0075_D31R0207_0541

scr_seq_0075_D31R0207_02D1:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_02D3:
	play_se SEQ_SE_DP_SELECT
	lockall
	faceplayer
	comparevartovalue VAR_UNK_4151, 2
	gotoif eq, scr_seq_0075_D31R0207_030F
	setvar VAR_TEMP_x4009, 1
	call scr_seq_0075_D31R0207_0216
	buffer_players_name 4
	npc_msg 15
	touchscreen_menu_hide
	getmenuchoice VAR_SPECIAL_x800C
	touchscreen_menu_show
	comparevartovalue VAR_SPECIAL_x800C, 0
	gotoif eq, scr_seq_0075_D31R0207_031A
scr_seq_0075_D31R0207_030F:
	npc_msg 16
	waitbutton
	closemsg
	releaseall
	end

scr_seq_0075_D31R0207_031A:
	scrcmd_412 50, 16393, 0
	setvar VAR_UNK_4151, 2
	buffer_players_name 0
	npc_msg 17
	closemsg
	releaseall
	scrcmd_098 2
	goto scr_seq_0075_D31R0207_0586

scr_seq_0075_D31R0207_033C:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_033E:
	play_se SEQ_SE_DP_SELECT
	lockall
	faceplayer
	comparevartovalue VAR_UNK_4151, 2
	gotoif eq, scr_seq_0075_D31R0207_0377
	setvar VAR_TEMP_x4009, 2
	call scr_seq_0075_D31R0207_0216
	npc_msg 3
	touchscreen_menu_hide
	getmenuchoice VAR_SPECIAL_x800C
	touchscreen_menu_show
	comparevartovalue VAR_SPECIAL_x800C, 0
	gotoif eq, scr_seq_0075_D31R0207_0382
scr_seq_0075_D31R0207_0377:
	npc_msg 4
	waitbutton
	closemsg
	releaseall
	end

scr_seq_0075_D31R0207_0382:
	scrcmd_412 50, 16393, 0
	setvar VAR_UNK_4151, 2
	npc_msg 5
	closemsg
	releaseall
	scrcmd_098 3
	goto scr_seq_0075_D31R0207_05CB

scr_seq_0075_D31R0207_03A1:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_03A3:
	play_se SEQ_SE_DP_SELECT
	lockall
	faceplayer
	comparevartovalue VAR_UNK_4151, 2
	gotoif eq, scr_seq_0075_D31R0207_03DC
	setvar VAR_TEMP_x4009, 3
	call scr_seq_0075_D31R0207_0216
	npc_msg 12
	touchscreen_menu_hide
	getmenuchoice VAR_SPECIAL_x800C
	touchscreen_menu_show
	comparevartovalue VAR_SPECIAL_x800C, 0
	gotoif eq, scr_seq_0075_D31R0207_03E7
scr_seq_0075_D31R0207_03DC:
	npc_msg 13
	waitbutton
	closemsg
	releaseall
	end

scr_seq_0075_D31R0207_03E7:
	scrcmd_412 50, 16393, 0
	setvar VAR_UNK_4151, 2
	npc_msg 14
	closemsg
	releaseall
	scrcmd_098 4
	goto scr_seq_0075_D31R0207_0610

scr_seq_0075_D31R0207_0406:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_0408:
	play_se SEQ_SE_DP_SELECT
	lockall
	faceplayer
	comparevartovalue VAR_UNK_4151, 2
	gotoif eq, scr_seq_0075_D31R0207_0441
	setvar VAR_TEMP_x4009, 4
	call scr_seq_0075_D31R0207_0216
	npc_msg 9
	touchscreen_menu_hide
	getmenuchoice VAR_SPECIAL_x800C
	touchscreen_menu_show
	comparevartovalue VAR_SPECIAL_x800C, 0
	gotoif eq, scr_seq_0075_D31R0207_044C
scr_seq_0075_D31R0207_0441:
	npc_msg 10
	waitbutton
	closemsg
	releaseall
	end

scr_seq_0075_D31R0207_044C:
	scrcmd_412 50, 16393, 0
	setvar VAR_UNK_4151, 2
	npc_msg 11
	closemsg
	releaseall
	scrcmd_098 5
	goto scr_seq_0075_D31R0207_0655

scr_seq_0075_D31R0207_046B:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_046D:
	scrcmd_307 0, 0, 8, 2, 77
	scrcmd_310 77
	scrcmd_308 77
	return

scr_seq_0075_D31R0207_0480:
	scrcmd_311 77
	scrcmd_308 77
	scrcmd_309 77
	return

scr_seq_0075_D31R0207_048B:
	call scr_seq_0075_D31R0207_046D
	apply_movement 0, scr_seq_0075_D31R0207_06AC
	wait_movement
	scrcmd_374 255
	apply_movement 255, scr_seq_0075_D31R0207_069C
	wait_movement
	call scr_seq_0075_D31R0207_0480
	apply_movement 0, scr_seq_0075_D31R0207_06BC
	wait_movement
	apply_movement 255, scr_seq_0075_D31R0207_06A4
	wait_movement
	return

scr_seq_0075_D31R0207_04C5:
	call scr_seq_0075_D31R0207_046D
	apply_movement 0, scr_seq_0075_D31R0207_06F0
	apply_movement 255, scr_seq_0075_D31R0207_06E4
	wait_movement
	call scr_seq_0075_D31R0207_0480
	return

scr_seq_0075_D31R0207_04E5:
	apply_movement VAR_TEMP_x4000, scr_seq_0075_D31R0207_06FC
	wait_movement
	apply_movement 0, scr_seq_0075_D31R0207_06C8
	wait_movement
	call scr_seq_0075_D31R0207_046D
	apply_movement VAR_TEMP_x4000, scr_seq_0075_D31R0207_0704
	wait_movement
	call scr_seq_0075_D31R0207_0480
	apply_movement 0, scr_seq_0075_D31R0207_06D8
	wait_movement
	fade_screen 6, 1, 0, 0
	wait_fade
	scrcmd_176 271, 0, 8, 4, 0
	fade_screen 6, 1, 1, 0
	wait_fade
	releaseall
	end

scr_seq_0075_D31R0207_0541:
	setvar VAR_TEMP_x4000, 1
	get_player_coords VAR_SPECIAL_x8000, VAR_SPECIAL_x8001
	comparevartovalue VAR_SPECIAL_x8000, 12
	gotoif eq, scr_seq_0075_D31R0207_0562
	goto scr_seq_0075_D31R0207_0574

scr_seq_0075_D31R0207_0560:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_0562:
	apply_movement 1, scr_seq_0075_D31R0207_0710
	wait_movement
	goto scr_seq_0075_D31R0207_04E5

scr_seq_0075_D31R0207_0572:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_0574:
	apply_movement 1, scr_seq_0075_D31R0207_0724
	wait_movement
	goto scr_seq_0075_D31R0207_04E5

scr_seq_0075_D31R0207_0584:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_0586:
	setvar VAR_TEMP_x4000, 2
	get_player_coords VAR_SPECIAL_x8000, VAR_SPECIAL_x8001
	comparevartovalue VAR_SPECIAL_x8000, 4
	gotoif eq, scr_seq_0075_D31R0207_05A7
	goto scr_seq_0075_D31R0207_05B9

scr_seq_0075_D31R0207_05A5:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_05A7:
	apply_movement 2, scr_seq_0075_D31R0207_073C
	wait_movement
	goto scr_seq_0075_D31R0207_04E5

scr_seq_0075_D31R0207_05B7:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_05B9:
	apply_movement 2, scr_seq_0075_D31R0207_074C
	wait_movement
	goto scr_seq_0075_D31R0207_04E5

scr_seq_0075_D31R0207_05C9:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_05CB:
	setvar VAR_TEMP_x4000, 3
	get_player_coords VAR_SPECIAL_x8000, VAR_SPECIAL_x8001
	comparevartovalue VAR_SPECIAL_x8001, 7
	gotoif eq, scr_seq_0075_D31R0207_05EC
	goto scr_seq_0075_D31R0207_05FE

scr_seq_0075_D31R0207_05EA:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_05EC:
	apply_movement 3, scr_seq_0075_D31R0207_0758
	wait_movement
	goto scr_seq_0075_D31R0207_04E5

scr_seq_0075_D31R0207_05FC:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_05FE:
	apply_movement 3, scr_seq_0075_D31R0207_0768
	wait_movement
	goto scr_seq_0075_D31R0207_04E5

scr_seq_0075_D31R0207_060E:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_0610:
	setvar VAR_TEMP_x4000, 4
	get_player_coords VAR_SPECIAL_x8000, VAR_SPECIAL_x8001
	comparevartovalue VAR_SPECIAL_x8001, 9
	gotoif eq, scr_seq_0075_D31R0207_0631
	goto scr_seq_0075_D31R0207_0643

scr_seq_0075_D31R0207_062F:
	.byte 0x02
	.byte 0x00
scr_seq_0075_D31R0207_0631:
	apply_movement 4, scr_seq_0075_D31R0207_0774
	wait_movement
	goto scr_seq_0075_D31R0207_04E5

scr_seq_0075_D31R0207_0641:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_0643:
	apply_movement 4, scr_seq_0075_D31R0207_0788
	wait_movement
	goto scr_seq_0075_D31R0207_04E5

scr_seq_0075_D31R0207_0653:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_0655:
	setvar VAR_TEMP_x4000, 5
	get_player_coords VAR_SPECIAL_x8000, VAR_SPECIAL_x8001
	comparevartovalue VAR_SPECIAL_x8000, 8
	gotoif eq, scr_seq_0075_D31R0207_0676
	goto scr_seq_0075_D31R0207_0688

scr_seq_0075_D31R0207_0674:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_0676:
	apply_movement 5, scr_seq_0075_D31R0207_079C
	wait_movement
	goto scr_seq_0075_D31R0207_04E5

scr_seq_0075_D31R0207_0686:
	.byte 0x02, 0x00
scr_seq_0075_D31R0207_0688:
	apply_movement 5, scr_seq_0075_D31R0207_07AC
	wait_movement
	goto scr_seq_0075_D31R0207_04E5

scr_seq_0075_D31R0207_0698:
	.byte 0x02, 0x00, 0x00, 0x00

scr_seq_0075_D31R0207_069C:
	.short 13, 2
	.short 254, 0

scr_seq_0075_D31R0207_06A4:
	.short 0, 1
	.short 254, 0

scr_seq_0075_D31R0207_06AC:
	.short 13, 2
	.short 14, 1
	.short 3, 1
	.short 254, 0

scr_seq_0075_D31R0207_06BC:
	.short 15, 1
	.short 1, 1
	.short 254, 0

scr_seq_0075_D31R0207_06C8:
	.short 1, 1
	.short 18, 1
	.short 3, 1
	.short 254, 0

scr_seq_0075_D31R0207_06D8:
	.short 19, 1
	.short 1, 1
	.short 254, 0

scr_seq_0075_D31R0207_06E4:
	.short 12, 2
	.short 69, 1
	.short 254, 0

scr_seq_0075_D31R0207_06F0:
	.short 12, 1
	.short 69, 1
	.short 254, 0

scr_seq_0075_D31R0207_06FC:
	.short 0, 1
	.short 254, 0

scr_seq_0075_D31R0207_0704:
	.short 16, 2
	.short 69, 1
	.short 254, 0

scr_seq_0075_D31R0207_0710:
	.short 17, 1
	.short 18, 3
	.short 16, 7
	.short 18, 2
	.short 254, 0

scr_seq_0075_D31R0207_0724:
	.short 18, 1
	.short 16, 1
	.short 18, 2
	.short 16, 5
	.short 18, 2
	.short 254, 0

scr_seq_0075_D31R0207_073C:
	.short 19, 1
	.short 16, 2
	.short 19, 3
	.short 254, 0

scr_seq_0075_D31R0207_074C:
	.short 16, 2
	.short 19, 4
	.short 254, 0

scr_seq_0075_D31R0207_0758:
	.short 18, 1
	.short 16, 4
	.short 18, 2
	.short 254, 0

scr_seq_0075_D31R0207_0768:
	.short 16, 4
	.short 18, 3
	.short 254, 0

scr_seq_0075_D31R0207_0774:
	.short 17, 1
	.short 19, 4
	.short 16, 7
	.short 19, 2
	.short 254, 0

scr_seq_0075_D31R0207_0788:
	.short 16, 1
	.short 19, 4
	.short 16, 5
	.short 19, 2
	.short 254, 0

scr_seq_0075_D31R0207_079C:
	.short 18, 1
	.short 16, 5
	.short 19, 2
	.short 254, 0

scr_seq_0075_D31R0207_07AC:
	.short 19, 3
	.short 16, 5
	.short 18, 2
	.short 254, 0
	.balign 4, 0
