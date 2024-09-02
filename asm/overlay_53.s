#include "constants/sndseq.h"
#include "constants/species.h"
#include "msgdata/msg/msg_0219.h"
	.include "asm/macros.inc"
	.include "overlay_53.inc"
	.include "global.inc"

	.text

	.extern ov53_021E64C4
	.extern ov53_021E67C4
	.extern ov53_021E6824
	.extern ov53_021E7D70
	.extern ov53_021E7DDC
	.extern ov53_021E8510
	.extern ov53_021E7E08
	.extern ov53_021E7E94
	.extern ov53_021E7EAC

	thumb_func_start ov53_021E80F4
ov53_021E80F4: ; 0x021E80F4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	str r3, [sp]
	cmp r5, #0
	bne _021E8108
	bl GF_AssertFail
_021E8108:
	ldr r0, [sp, #0x24]
	mov r1, #0x3c
	str r0, [sp, #4]
	bl AllocFromHeap
	mov r1, #0
	mov r2, #0x3c
	add r4, r0, #0
	bl MI_CpuFill8
	ldr r0, [sp, #0x24]
	str r0, [r4]
	str r5, [r4, #0xc]
	str r6, [r4, #0x10]
	ldr r0, [sp]
	strb r7, [r4, #0x19]
	strb r0, [r4, #0x1a]
	ldr r0, [sp, #0x20]
	strb r0, [r4, #0x18]
	ldr r0, [sp, #4]
	bl MessageFormat_New
	str r0, [r4, #0x14]
	add r0, r6, #0
	mov r1, #1
	bl Set2dSpriteAnimActiveFlag
	add r0, r4, #0
	bl ov53_021E82BC
	add r0, r4, #0
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.balign 4, 0
	thumb_func_end ov53_021E80F4

	thumb_func_start ov53_021E814C
ov53_021E814C: ; 0x021E814C
	push {r4, lr}
	add r4, r0, #0
	bne _021E8156
	bl GF_AssertFail
_021E8156:
	add r0, r4, #0
	bl ov53_021E8310
	ldr r0, [r4, #0x14]
	bl MessageFormat_Delete
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4, 0
	thumb_func_end ov53_021E814C

	thumb_func_start ov53_021E816C
ov53_021E816C: ; 0x021E816C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r4, [r5]
	ldrb r6, [r5, #0x19]
	add r7, r1, #0
	mov r0, #0xef
	add r1, r4, #0
	bl NARC_New
	mov r1, #0x20
	str r1, [sp]
	mov r1, #0
	mov r2, #4
	lsl r3, r7, #5
	str r0, [sp, #0x10]
	str r4, [sp, #4]
	bl GfGfxLoader_GXLoadPalFromOpenNarc
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r4, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0xc]
	mov r1, #1
	add r3, r6, #0
	bl GfGfxLoader_LoadCharDataFromOpenNarc
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	str r4, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [r5, #0xc]
	mov r1, #0xa
	add r3, r6, #0
	bl GfGfxLoader_LoadScrnDataFromOpenNarc
	mov r0, #0x20
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	lsl r0, r7, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #8]
	mov r2, #0
	ldr r0, [r5, #0xc]
	add r1, r6, #0
	add r3, r2, #0
	bl BgTilemapRectChangePalette
	ldr r0, [r5, #0xc]
	add r1, r6, #0
	bl BgCommitTilemapBufferToVram
	add r0, r6, #0
	mov r1, #0
	bl ToggleBgLayer
	ldr r0, [sp, #0x10]
	bl NARC_Delete
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
	thumb_func_end ov53_021E816C

	thumb_func_start ov53_021E81F4
ov53_021E81F4: ; 0x021E81F4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r1, r5, #0
	add r6, r3, #0
	add r1, #0x1c
	add r3, r4, #0
	bl ov53_021E8330
	add r1, r5, #0
	add r0, r5, #0
	add r1, #0x2c
	add r2, r6, #0
	add r3, r4, #0
	bl ov53_021E8330
	ldrb r1, [r5, #0x1b]
	mov r0, #0xf
	bic r1, r0
	strb r1, [r5, #0x1b]
	ldrb r1, [r5, #0x1b]
	mov r0, #0xf0
	bic r1, r0
	mov r0, #0x10
	orr r0, r1
	strb r0, [r5, #0x1b]
	add r0, r5, #0
	bl ov53_021E8390
	ldrb r0, [r5, #0x19]
	mov r1, #1
	bl ToggleBgLayer
	ldrb r0, [r5, #0x1a]
	mov r1, #1
	bl ToggleBgLayer
	ldr r0, [r5, #0x10]
	mov r1, #1
	bl Set2dSpriteVisibleFlag
	pop {r4, r5, r6, pc}
	thumb_func_end ov53_021E81F4

	thumb_func_start ov53_021E8248
ov53_021E8248: ; 0x021E8248
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #0x1b]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	beq _021E825A
	cmp r1, #1
	beq _021E827E
	b _021E82B2
_021E825A:
	bl ov53_021E83D4
	cmp r0, #0
	beq _021E82B6
	ldrb r2, [r4, #0x1b]
	mov r1, #0xf
	add r0, r2, #0
	bic r0, r1
	lsl r1, r2, #0x1c
	lsr r1, r1, #0x1c
	add r1, r1, #1
	lsl r1, r1, #0x18
	lsr r2, r1, #0x18
	mov r1, #0xf
	and r1, r2
	orr r0, r1
	strb r0, [r4, #0x1b]
	b _021E82B6
_021E827E:
	bl ov53_021E84D4
	cmp r0, #0
	beq _021E82B6
	ldrb r0, [r4, #0x1b]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	bne _021E8292
	bl GF_AssertFail
_021E8292:
	ldrb r0, [r4, #0x19]
	mov r1, #0
	bl ToggleBgLayer
	ldrb r0, [r4, #0x1a]
	mov r1, #0
	bl ToggleBgLayer
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl Set2dSpriteVisibleFlag
	ldrb r0, [r4, #0x1b]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	pop {r4, pc}
_021E82B2:
	bl GF_AssertFail
_021E82B6:
	mov r0, #0
	pop {r4, pc}
	.balign 4, 0
	thumb_func_end ov53_021E8248

	thumb_func_start ov53_021E82BC
ov53_021E82BC: ; 0x021E82BC
	push {r3, r4, lr}
	sub sp, #0x14
	add r4, r0, #0
	bne _021E82C8
	bl GF_AssertFail
_021E82C8:
	mov r0, #8
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	ldrb r0, [r4, #0x18]
	add r1, r4, #0
	add r1, #0x1c
	str r0, [sp, #0xc]
	mov r0, #0x50
	str r0, [sp, #0x10]
	ldrb r2, [r4, #0x1a]
	ldr r0, [r4, #0xc]
	mov r3, #4
	bl AddWindowParameterized
	mov r0, #0xe
	str r0, [sp]
	mov r0, #0x18
	str r0, [sp, #4]
	mov r0, #2
	str r0, [sp, #8]
	ldrb r0, [r4, #0x18]
	add r1, r4, #0
	add r1, #0x2c
	str r0, [sp, #0xc]
	mov r0, #0x80
	str r0, [sp, #0x10]
	ldrb r2, [r4, #0x1a]
	ldr r0, [r4, #0xc]
	mov r3, #4
	bl AddWindowParameterized
	add sp, #0x14
	pop {r3, r4, pc}
	thumb_func_end ov53_021E82BC

	thumb_func_start ov53_021E8310
ov53_021E8310: ; 0x021E8310
	push {r3, r4, r5, lr}
	add r5, r0, #0
	bne _021E831A
	bl GF_AssertFail
_021E831A:
	mov r4, #0
	add r5, #0x1c
_021E831E:
	add r0, r5, #0
	bl RemoveWindow
	add r4, r4, #1
	add r5, #0x10
	cmp r4, #2
	blt _021E831E
	pop {r3, r4, r5, pc}
	.balign 4, 0
	thumb_func_end ov53_021E8310

	thumb_func_start ov53_021E8330
ov53_021E8330: ; 0x021E8330
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r6, r2, #0
	add r2, r3, #0
	add r4, r1, #0
	ldr r3, [r5]
	mov r0, #0
	mov r1, #0x1b
	bl NewMsgDataFromNarc
	add r7, r0, #0
	ldr r0, [r5, #0x14]
	ldr r3, [r5]
	add r1, r7, #0
	add r2, r6, #0
	bl ReadMsgData_ExpandPlaceholders
	add r5, r0, #0
	add r0, r4, #0
	mov r1, #0
	bl FillWindowPixelBuffer
	mov r3, #0
	str r3, [sp]
	ldr r0, _021E838C ; =0x000F0100
	str r3, [sp, #4]
	str r0, [sp, #8]
	add r0, r4, #0
	mov r1, #4
	add r2, r5, #0
	str r3, [sp, #0xc]
	bl AddTextPrinterParameterizedWithColor
	add r0, r4, #0
	bl CopyWindowToVram
	add r0, r7, #0
	bl DestroyMsgData
	add r0, r5, #0
	bl String_Delete
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_021E838C: .word 0x000F0100
	thumb_func_end ov53_021E8330

	thumb_func_start ov53_021E8390
ov53_021E8390: ; 0x021E8390
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x10]
	cmp r0, #0
	bne _021E839E
	bl GF_AssertFail
_021E839E:
	ldrb r0, [r5, #0x1b]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	cmp r0, #1
	beq _021E83AE
	cmp r0, #2
	beq _021E83B2
	b _021E83B6
_021E83AE:
	mov r4, #0
	b _021E83BA
_021E83B2:
	mov r4, #1
	b _021E83BA
_021E83B6:
	bl GF_AssertFail
_021E83BA:
	ldr r1, _021E83CC ; =ov53_021E8874
	lsl r3, r4, #2
	ldr r2, _021E83D0 ; =ov53_021E8874 + 2
	ldrsh r1, [r1, r3]
	ldrsh r2, [r2, r3]
	ldr r0, [r5, #0x10]
	bl Sprite_SetPositionXY
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021E83CC: .word ov53_021E8874
_021E83D0: .word ov53_021E8874 + 2
	thumb_func_end ov53_021E8390

	thumb_func_start ov53_021E83D4
ov53_021E83D4: ; 0x021E83D4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, _021E84C8 ; =ov53_021E887C
	mov r4, #0
	bl TouchscreenHitbox_FindRectAtTouchNew
	add r6, r0, #0
	sub r0, r4, #1
	cmp r6, r0
	beq _021E841E
	ldr r0, _021E84CC ; =SEQ_SE_DP_SELECT
	bl PlaySE
	cmp r6, #0
	beq _021E83F8
	cmp r6, #1
	beq _021E8408
	b _021E8418
_021E83F8:
	ldrb r1, [r5, #0x1b]
	mov r0, #0xf0
	mov r4, #1
	bic r1, r0
	mov r0, #0x10
	orr r0, r1
	strb r0, [r5, #0x1b]
	b _021E84AA
_021E8408:
	ldrb r1, [r5, #0x1b]
	mov r0, #0xf0
	mov r4, #1
	bic r1, r0
	mov r0, #0x20
	orr r0, r1
	strb r0, [r5, #0x1b]
	b _021E84AA
_021E8418:
	bl GF_AssertFail
	b _021E84AA
_021E841E:
	ldr r0, _021E84D0 ; =gSystem
	mov r1, #0x40
	ldr r0, [r0, #0x48]
	tst r1, r0
	beq _021E844A
	ldrb r1, [r5, #0x1b]
	lsl r0, r1, #0x18
	lsr r0, r0, #0x1c
	cmp r0, #1
	beq _021E84AA
	mov r0, #0xf0
	bic r1, r0
	mov r0, #0x10
	orr r0, r1
	strb r0, [r5, #0x1b]
	add r0, r5, #0
	bl ov53_021E8390
	ldr r0, _021E84CC ; =SEQ_SE_DP_SELECT
	bl PlaySE
	b _021E84AA
_021E844A:
	mov r1, #0x80
	tst r1, r0
	beq _021E8472
	ldrb r1, [r5, #0x1b]
	lsl r0, r1, #0x18
	lsr r0, r0, #0x1c
	cmp r0, #2
	beq _021E84AA
	mov r0, #0xf0
	bic r1, r0
	mov r0, #0x20
	orr r0, r1
	strb r0, [r5, #0x1b]
	add r0, r5, #0
	bl ov53_021E8390
	ldr r0, _021E84CC ; =SEQ_SE_DP_SELECT
	bl PlaySE
	b _021E84AA
_021E8472:
	mov r2, #1
	add r1, r0, #0
	tst r1, r2
	beq _021E8496
	ldrb r0, [r5, #0x1b]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x1c
	bne _021E8492
	bl GF_AssertFail
	ldrb r1, [r5, #0x1b]
	mov r0, #0xf0
	bic r1, r0
	mov r0, #0x20
	orr r0, r1
	strb r0, [r5, #0x1b]
_021E8492:
	mov r4, #1
	b _021E84AA
_021E8496:
	mov r1, #2
	tst r0, r1
	beq _021E84AA
	ldrb r1, [r5, #0x1b]
	mov r0, #0xf0
	add r4, r2, #0
	bic r1, r0
	mov r0, #0x20
	orr r0, r1
	strb r0, [r5, #0x1b]
_021E84AA:
	cmp r4, #0
	beq _021E84C2
	add r0, r5, #0
	bl ov53_021E8390
	ldr r0, [r5, #0x10]
	mov r1, #3
	bl Set2dSpriteAnimSeqNo
	ldr r0, _021E84CC ; =SEQ_SE_DP_SELECT
	bl PlaySE
_021E84C2:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
	nop
_021E84C8: .word ov53_021E887C
_021E84CC: .word SEQ_SE_DP_SELECT
_021E84D0: .word gSystem
	thumb_func_end ov53_021E83D4

	thumb_func_start ov53_021E84D4
ov53_021E84D4: ; 0x021E84D4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x10]
	bl Get2dSpriteCurrentAnimSeqNo
	cmp r0, #3
	beq _021E84E6
	bl GF_AssertFail
_021E84E6:
	ldr r0, [r4, #0x10]
	bl Sprite_IsCellAnimationRunning
	cmp r0, #0
	bne _021E84F4
	mov r0, #1
	pop {r4, pc}
_021E84F4:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end ov53_021E84D4

	.rodata

	; file boundary

	.global ov53_021E8874
ov53_021E8874: ; 0x021E8874
	.short 0x0080, 0x0048
	.short 0x0080, 0x0078
	.size ov53_021E8874,.-ov53_021E8874

	.global ov53_021E887C
ov53_021E887C: ; 0x021E887C
	.byte 0x32, 0x5C, 0x03, 0xFB
	.byte 0x63, 0x8C, 0x03, 0xFB
	.byte 0xFF, 0x00, 0x00, 0x00
	.size ov53_021E887C,.-ov53_021E887C
	; 0x021E8888
