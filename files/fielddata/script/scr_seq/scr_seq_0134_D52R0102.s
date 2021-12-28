#include "constants/scrcmd.h"
	.include "asm/macros/script.inc"

	.rodata

	scrdef scr_seq_0134_D52R0102_0099 ; 000
	scrdef scr_seq_0134_D52R0102_000E ; 001
	scrdef scr_seq_0134_D52R0102_007E ; 002
	scrdef_end

scr_seq_0134_D52R0102_000E:
	comparevartovalue VAR_UNK_40F9, 4
	gotoif ge, scr_seq_0134_D52R0102_007C
	scrcmd_495 VAR_TEMP_x4000
	comparevartovalue VAR_TEMP_x4000, 7
	gotoif ne, scr_seq_0134_D52R0102_0038
	goto scr_seq_0134_D52R0102_004A

scr_seq_0134_D52R0102_0032:
	.byte 0x16, 0x00, 0x06, 0x00, 0x00, 0x00
scr_seq_0134_D52R0102_0038:
	goto scr_seq_0134_D52R0102_0040

scr_seq_0134_D52R0102_003E:
	.byte 0x02, 0x00
scr_seq_0134_D52R0102_0040:
	setflag FLAG_UNK_2D1
	setflag FLAG_UNK_2D4
	end

scr_seq_0134_D52R0102_004A:
	checkflag FLAG_UNK_18B
	gotoif TRUE, scr_seq_0134_D52R0102_007C
	hasitem ITEM_BLUE_ORB, 1, VAR_TEMP_x4000
	comparevartovalue VAR_TEMP_x4000, 1
	gotoif ge, scr_seq_0134_D52R0102_0072
	goto scr_seq_0134_D52R0102_0040

scr_seq_0134_D52R0102_0070:
	.byte 0x02, 0x00
scr_seq_0134_D52R0102_0072:
	setflag FLAG_UNK_2D4
	clearflag FLAG_UNK_2D1
	end

scr_seq_0134_D52R0102_007C:
	end

scr_seq_0134_D52R0102_007E:
	checkflag FLAG_UNK_0A4
	gotoif TRUE, scr_seq_0134_D52R0102_008B
	end

scr_seq_0134_D52R0102_008B:
	setflag FLAG_UNK_2D1
	hide_person 0
	clearflag FLAG_UNK_0A4
	end

scr_seq_0134_D52R0102_0099:
	play_se SEQ_SE_DP_SELECT
	lockall
	faceplayer
	scrcmd_076 382, 0
	npc_msg 0
	scrcmd_077
	closemsg
	setflag FLAG_UNK_0A4
	scrcmd_589 382, 50, 0
	clearflag FLAG_UNK_0A4
	check_battle_won VAR_SPECIAL_x800C
	comparevartovalue VAR_SPECIAL_x800C, 0
	gotoif eq, scr_seq_0134_D52R0102_019D
	scrcmd_683 16386
	comparevartovalue VAR_TEMP_x4002, 3
	gotoif eq, scr_seq_0134_D52R0102_00EC
	comparevartovalue VAR_TEMP_x4002, 4
	gotoif eq, scr_seq_0134_D52R0102_00FB
scr_seq_0134_D52R0102_00EC:
	npc_msg 1
	waitbutton
	closemsg
	setflag FLAG_UNK_18B
	releaseall
	end

scr_seq_0134_D52R0102_00FB:
	setvar VAR_UNK_40F9, 4
	setflag FLAG_UNK_17A
	clearflag FLAG_UNK_2D4
	show_person 1
	scrcmd_602 0
	scrcmd_603
	scrcmd_604 55
	scrcmd_386 VAR_TEMP_x4001
	comparevartovalue VAR_TEMP_x4001, 0
	gotoif ne, scr_seq_0134_D52R0102_0142
	apply_movement 1, scr_seq_0134_D52R0102_01A4
	wait_movement
	apply_movement 255, scr_seq_0134_D52R0102_01B0
	wait_movement
	goto scr_seq_0134_D52R0102_0156

scr_seq_0134_D52R0102_0142:
	apply_movement 1, scr_seq_0134_D52R0102_01BC
	wait_movement
	apply_movement 255, scr_seq_0134_D52R0102_01C8
	wait_movement
scr_seq_0134_D52R0102_0156:
	scrcmd_603
	scrcmd_602 1
	scrcmd_604 48
	npc_msg 2
	closemsg
	apply_movement 1, scr_seq_0134_D52R0102_01D0
	wait_movement
	npc_msg 3
	closemsg
	apply_movement 1, scr_seq_0134_D52R0102_01E0
	wait_movement
	npc_msg 4
	closemsg
	apply_movement 1, scr_seq_0134_D52R0102_01EC
	wait_movement
	hide_person 1
	setflag FLAG_UNK_2D4
	setflag FLAG_UNK_2CF
	releaseall
	end

scr_seq_0134_D52R0102_019D:
	white_out
	releaseall
	end

scr_seq_0134_D52R0102_01A3:
	.byte 0x00

scr_seq_0134_D52R0102_01A4:
	.short 12, 8
	.short 32, 1
	.short 254, 0

scr_seq_0134_D52R0102_01B0:
	.short 33, 1
	.short 13, 1
	.short 254, 0

scr_seq_0134_D52R0102_01BC:
	.short 12, 10
	.short 32, 1
	.short 254, 0

scr_seq_0134_D52R0102_01C8:
	.short 33, 1
	.short 254, 0

scr_seq_0134_D52R0102_01D0:
	.short 33, 1
	.short 9, 2
	.short 32, 1
	.short 254, 0

scr_seq_0134_D52R0102_01E0:
	.short 12, 2
	.short 32, 1
	.short 254, 0

scr_seq_0134_D52R0102_01EC:
	.short 13, 8
	.short 254, 0
	.balign 4, 0
