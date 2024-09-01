#include "oak_speech/oak_speech.h"
#include "constants/sndseq.h"
#include "gf_gfx_loader.h"
#include "system.h"
#include "text.h"
#include "touchscreen.h"
#include "unk_02005D10.h"

extern void ov53_021E82BC(UnkStruct_ov53_021E80F4*);

UnkStruct_ov53_021E80F4 *ov53_021E80F4(BgConfig *bgConfig, Sprite *sprite, u8 bgId1, u8 bgId2, u8 paletteNum, HeapID heapId);
#ifdef NONMATCHING
UnkStruct_ov53_021E80F4 *ov53_021E80F4(BgConfig *bgConfig, Sprite *sprite, u8 bgId1, u8 bgId2, u8 paletteNum, HeapID heapId) {
    GF_ASSERT(bgConfig != NULL);

    UnkStruct_ov53_021E80F4 *ret = AllocFromHeap(heapId, sizeof(UnkStruct_ov53_021E80F4));
    MI_CpuFill8(ret, 0, sizeof(UnkStruct_ov53_021E80F4));

    ret->heapId = heapId;
    ret->bgConfig = bgConfig;
    ret->sprite = sprite;
    ret->bgId1 = bgId1;
    ret->bgId2 = bgId2;
    ret->paletteNum = paletteNum;
    ret->messageFormat = MessageFormat_New(heapId);

    Set2dSpriteAnimActiveFlag(sprite, TRUE);

    ov53_021E82BC(ret);

    return ret;
}
#else
asm UnkStruct_ov53_021E80F4 *ov53_021E80F4(BgConfig *bgConfig, Sprite *sprite, u8 a2, u8 layer, u8 paletteNum, HeapID heapId) {
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
}
#endif

extern void ov53_021E8310(UnkStruct_ov53_021E80F4*);

void ov53_021E814C(UnkStruct_ov53_021E80F4 *a0);
void ov53_021E814C(UnkStruct_ov53_021E80F4 *a0) {
    GF_ASSERT(a0 != NULL);

    ov53_021E8310(a0);
    MessageFormat_Delete(a0->messageFormat);
    FreeToHeap(a0);
}

void ov53_021E816C(UnkStruct_ov53_021E80F4 *a0, int palette);
void ov53_021E816C(UnkStruct_ov53_021E80F4 *a0, int palette) {
    HeapID heapId = a0->heapId;
    GFBgLayer layer = (GFBgLayer)a0->bgId1;

    NARC *narc = NARC_New(NARC_a_2_3_7, a0->heapId);
    // FIXME: Use NAIX constants once a/2/3/7 has been dumped.
    GfGfxLoader_GXLoadPalFromOpenNarc(narc, 0, GF_PAL_LOCATION_SUB_BG, (enum GFPalSlotOffset)(palette * 32), 32, heapId);
    GfGfxLoader_LoadCharDataFromOpenNarc(narc, 1, a0->bgConfig, layer, 0, 0, FALSE, heapId);
    GfGfxLoader_LoadScrnDataFromOpenNarc(narc, 10, a0->bgConfig, layer, 0, 0, FALSE, heapId);
    BgTilemapRectChangePalette(a0->bgConfig, layer, 0, 0, 32, 24, palette);
    BgCommitTilemapBufferToVram(a0->bgConfig, layer);
    ToggleBgLayer(layer, GF_PLANE_TOGGLE_OFF);
    NARC_Delete(narc);
}

void ov53_021E8330(UnkStruct_ov53_021E80F4 *a0, Window *window, u32 msgNum, u32 gmmNum);
void ov53_021E8390(UnkStruct_ov53_021E80F4 *a0);

void ov53_021E81F4(UnkStruct_ov53_021E80F4 *a0, u32 gmmNum, u32 msgNum1, u32 msgNum2);
void ov53_021E81F4(UnkStruct_ov53_021E80F4 *a0, u32 gmmNum, u32 msgNum1, u32 msgNum2) {
    ov53_021E8330(a0, &a0->windows[0], msgNum1, gmmNum);
    ov53_021E8330(a0, &a0->windows[1], msgNum2, gmmNum);
    a0->unk1B_0 = 0;
    a0->unk1B_4 = 1;
    ov53_021E8390(a0);
    ToggleBgLayer(a0->bgId1, GF_PLANE_TOGGLE_ON);
    ToggleBgLayer(a0->bgId2, GF_PLANE_TOGGLE_ON);
    Set2dSpriteVisibleFlag(a0->sprite, TRUE);
}

extern BOOL ov53_021E83D4(UnkStruct_ov53_021E80F4*);
extern BOOL ov53_021E84D4(UnkStruct_ov53_021E80F4*);

u32 ov53_021E8248(UnkStruct_ov53_021E80F4 *a0);
u32 ov53_021E8248(UnkStruct_ov53_021E80F4 *a0) {
    switch (a0->unk1B_0) {
        case 0:
            if (ov53_021E83D4(a0)) {
                a0->unk1B_0++;
            }
            break;
        case 1:
            if (ov53_021E84D4(a0)) {
                GF_ASSERT(a0->unk1B_4 != 0);
                ToggleBgLayer(a0->bgId1, GF_PLANE_TOGGLE_OFF);
                ToggleBgLayer(a0->bgId2, GF_PLANE_TOGGLE_OFF);
                Set2dSpriteVisibleFlag(a0->sprite, FALSE);
                return a0->unk1B_4;
            }
            break;
        default:
            GF_ASSERT(FALSE);
            break;
    }

    return 0;
}

void ov53_021E82BC(UnkStruct_ov53_021E80F4 *a0) {
    GF_ASSERT(a0 != NULL);
    AddWindowParameterized(a0->bgConfig, &a0->windows[0], a0->bgId2, 4, 8, 24, 2, a0->paletteNum, 0x50);
    AddWindowParameterized(a0->bgConfig, &a0->windows[1], a0->bgId2, 4, 14, 24, 2, a0->paletteNum, 0x80);
}

void ov53_021E8310(UnkStruct_ov53_021E80F4 *a0) {
    GF_ASSERT(a0 != NULL);
    for (int i = 0; i < 2; i++) {
        RemoveWindow(&a0->windows[i]);
    }
}

void ov53_021E8330(UnkStruct_ov53_021E80F4 *a0, Window *window, u32 msgNum, u32 gmmNum) {
    MsgData *msgData = NewMsgDataFromNarc(MSGDATA_LOAD_DIRECT, NARC_msgdata_msg, gmmNum, a0->heapId);
    String *temp = ReadMsgData_ExpandPlaceholders(a0->messageFormat, msgData, msgNum, a0->heapId);

    FillWindowPixelBuffer(window, 0x0);
    AddTextPrinterParameterizedWithColor(window, 4, temp, 0, 0, TEXT_SPEED_INSTANT, MAKE_TEXT_COLOR(15, 1, 0), NULL);
    CopyWindowToVram(window);

    DestroyMsgData(msgData);
    String_Delete(temp);
}

void ov53_021E8390(UnkStruct_ov53_021E80F4 *a0) {
    GF_ASSERT(a0->sprite != NULL);

    u32 index;
    switch (a0->unk1B_4) {
        case 1:
            index = 0;
            break;
        case 2:
            index = 1;
            break;
        default:
            GF_ASSERT(FALSE);
            break;
    }

    static const s16 coords[2][2] = { { 128, 72 }, { 128, 120 } };
    Sprite_SetPositionXY(a0->sprite, coords[index][0], coords[index][1]);
}

BOOL ov53_021E83D4(UnkStruct_ov53_021E80F4 *a0) {
    BOOL ret = FALSE;

    static const TouchscreenHitbox hitboxes[3] = {
        { .rect = { .top = 50, .bottom = 92, .left = 3, .right = 251 } },
        { .rect = { .top = 99, .bottom = 140, .left = 3, .right = 251 } },
        { 0xFF },
    };

    int rect = TouchscreenHitbox_FindRectAtTouchNew(hitboxes);
    if (rect != -1) {
        PlaySE(SEQ_SE_DP_SELECT);
        switch (rect) {
            case 0:
                ret = TRUE;
                a0->unk1B_4 = 1;
                break;
            case 1:
                ret = TRUE;
                a0->unk1B_4 = 2;
                break;
            default:
                GF_ASSERT(FALSE);
                break;
        }
    } else {
        if (gSystem.newKeys & PAD_KEY_UP) {
            if (a0->unk1B_4 != 1) {
                a0->unk1B_4 = 1;
                ov53_021E8390(a0);
                PlaySE(SEQ_SE_DP_SELECT);
            }
        } else if (gSystem.newKeys & PAD_KEY_DOWN) {
            if (a0->unk1B_4 != 2) {
                a0->unk1B_4 = 2;
                ov53_021E8390(a0);
                PlaySE(SEQ_SE_DP_SELECT);
            }
        } else if (gSystem.newKeys & PAD_BUTTON_A) {
            if (a0->unk1B_4 == 0) {
                GF_ASSERT(FALSE);
                a0->unk1B_4 = 2;
            }
            ret = TRUE;
        } else if (gSystem.newKeys & PAD_BUTTON_B) {
            ret = TRUE;
            a0->unk1B_4 = 2;
        }
    }

    if (ret != FALSE) {
        ov53_021E8390(a0);
        Set2dSpriteAnimSeqNo(a0->sprite, 3);
        PlaySE(SEQ_SE_DP_SELECT);
    }

    return ret;
}

BOOL ov53_021E84D4(UnkStruct_ov53_021E80F4 *a0) {
    GF_ASSERT(Get2dSpriteCurrentAnimSeqNo(a0->sprite) == 3);
    return Sprite_IsCellAnimationRunning(a0->sprite) == FALSE;
}
