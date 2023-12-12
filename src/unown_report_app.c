#include "global.h"
#include "bg_window.h"
#include "font.h"
#include "gf_gfx_loader.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "msgdata/msg/msg_0001.h"
#include "pokedex.h"
#include "pokemon_icon_idx.h"
#include "render_window.h"
#include "sound_02004A44.h"
#include "sys_vars.h"
#include "system.h"
#include "text.h"
#include "touchscreen.h"
#include "unk_02005D10.h"
#include "unk_0200B150.h"
#include "unk_0200CF18.h"
#include "unk_0200FA24.h"
#include "unk_020183F0.h"
#include "unk_020210A0.h"
#include "unown_report_app.h"
#include "vram_transfer_manager.h"
#include "yes_no_prompt.h"

typedef struct UnownReportApp_Args {
    u32 *unk0;
    SaveData *savedata;
} UnownReportApp_Args;

typedef struct UnownReportApp_UnkSubstruct {
    void *screenData;
    NNSG2dScreenData *g2dScreenData;
    u32 *data;
    u8 width;
    u8 height;
} UnownReportApp_UnkSubstruct;

typedef struct UnownReportApp_Data {
    HeapID heapId;
    UnownReportApp_Args *args;
    u8 unk8[4];
    Pokedex *pokedex;
    u16 unk10;
    u32 unk14;
    u8 textFrameDelay;
    u8 frame;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 numSeenUnowns;
    u8 unk20[28];
    u8 unownReportLevel;
    BgConfig *bgConfig;
    MsgData *msgData;
    MessageFormat *messageFormat;
    String *unk4C;
    String *tempString;
    String *cancelButtonString;
    String *pageNumberString;
    String *playerNameString;
    u8 unk60[8];
    Window windows[4];
    YesNoPrompt *unkA8;
    SpriteRenderer *spriteRenderer;
    SpriteGfxHandler *spriteGfxHandler1;
    SpriteGfxHandler *spriteGfxHandler2;
    Sprite *sprites[3];
    UnkImageStruct *unkC4[14];
    NARC *narc;
    UnownReportApp_UnkSubstruct unk100;
    UnownReportApp_UnkSubstruct unk110;
    UnownReportApp_UnkSubstruct unk120;
    UnownReportApp_UnkSubstruct unk130;
    UnownReportApp_UnkSubstruct unk140;
    UnownReportApp_UnkSubstruct unk150;
} UnownReportApp_Data;

extern void ov113_021E59F8(void);
u32 ov113_021E5A48(Pokedex *pokedex, u8 *a1);
extern void ov113_021E5A7C(UnownReportApp_Data *data);
extern void ov113_021E5B60(UnownReportApp_Data *data);
extern BOOL ov113_021E5B70(UnownReportApp_Data *data);
extern BOOL ov113_021E5BB0(UnownReportApp_Data *data);
extern u32 ov113_021E5BC4(UnownReportApp_Data *data);
extern u32 ov113_021E5C0C(UnownReportApp_Data *data);
extern u32 ov113_021E5C60(UnownReportApp_Data *data);
extern u32 ov113_021E5C68(UnownReportApp_Data *data);
extern void ov113_021E5CF8(UnownReportApp_Data *data);
extern void ov113_021E5D28(UnownReportApp_Data *data);
extern void ov113_021E5D4C(UnownReportApp_Data *data);
extern u32 ov113_021E5D60(UnownReportApp_Data *data);
extern u8 ov113_021E5D80(UnownReportApp_Data *data);
extern void ov113_021E5DA4(UnownReportApp_Data *data, u8 a1);
extern void ov113_021E5E64(UnownReportApp_Data *data, u32 a1);
extern u32 ov113_021E5EC4(UnownReportApp_Data *data);
extern u32 ov113_021E5ED0(UnownReportApp_Data *data, u32 a1);
extern u32 ov113_021E5F48(UnownReportApp_Data *data);
extern u32 ov113_021E5F94(UnownReportApp_Data *data, u32 *a1);
extern void ov113_021E5FC0(UnownReportApp_Data *data);
extern void ov113_021E6084(UnownReportApp_Data *data, u8 a1);
extern void ov113_021E613C(UnownReportApp_Data *data, u8 a1);
extern void ov113_021E6238(UnownReportApp_Data *data, UnownReportApp_UnkSubstruct *a1, u32 bgId);
extern void UnownReportApp_PrintTextWithFont(Window *window, String *string, FontID fontId, u16 x, u16 y);
extern void UnownReportApp_PrintText(Window *window, String *string, u16 x, u16 y);
void ov113_021E62E0(void);
extern void ov113_021E6300(UnownReportApp_Data *data);
extern void ov113_021E6490(UnownReportApp_Data *data);
void ov113_021E64DC(UnownReportApp_UnkSubstruct *a0, NARC *narc, u32 memberNum, HeapID heapId);
extern void ov113_021E650C(UnownReportApp_Data *data);
extern void ov113_021E663C(UnownReportApp_Data *data);
void ov113_021E677C(UnownReportApp_Data *data);
void ov113_021E6930(UnownReportApp_Data *data);
extern void ov113_021E6988(UnownReportApp_Data *data);
extern void ov113_021E69A8(UnownReportApp_Data *data);
void ov113_021E69CC(UnownReportApp_Data *data);
extern void ov113_021E6AB0(UnownReportApp_Data *data);
extern void ov113_021E6AE8(UnownReportApp_Data *data, u32 a1, u8 form);
extern void ov113_021E6B1C(UnownReportApp_Data *data);
extern void UnownReportApp_SetupText(UnownReportApp_Data *data);
extern void UnownReportApp_FreeText(UnownReportApp_Data *data);
extern void UnownReportApp_SetupWindows(UnownReportApp_Data *data);
extern void UnownReportApp_FreeWindows(UnownReportApp_Data *data);
extern void UnownReportApp_OnVBlank(UnownReportApp_Data *data);

BOOL UnownReportApp_Init(OVY_MANAGER *manager, int *state) {
    switch (*state) {
        case 0: {
            ov113_021E59F8();

            CreateHeap(HEAP_ID_3, HEAP_ID_UNOWN_REPORT, 0x20000);

            UnownReportApp_Data *data = OverlayManager_CreateAndGetData(manager, sizeof(UnownReportApp_Data), HEAP_ID_UNOWN_REPORT);
            MI_CpuFill8(data, 0, sizeof(UnownReportApp_Data));
            data->heapId = HEAP_ID_UNOWN_REPORT;
            data->args = OverlayManager_GetArgs(manager);
            ov113_021E5A7C(data);

            (*state)++;
            break;
        }
        case 1: {
            UnownReportApp_Data *data = OverlayManager_GetData(manager);
            if (ov113_021E5B70(data)) {
                return TRUE;
            }

            break;
        }
    }

    return FALSE;
}

BOOL UnownReportApp_Run(OVY_MANAGER *manager, int *state) {
    UnownReportApp_Data *data = OverlayManager_GetData(manager);

    switch (*state) {
        case 0:
            *state = ov113_021E5BC4(data);
            break;
        case 1:
            *state = ov113_021E5C0C(data);
            break;
        case 2:
            *state = ov113_021E5C60(data);
            break;
        case 3:
            *state = ov113_021E5C68(data);
            break;
        case 4:
            return TRUE;
    }

    sub_0200D020(data->spriteGfxHandler1);
    sub_0200D020(data->spriteGfxHandler2);

    return FALSE;
}

BOOL UnownReportApp_Exit(OVY_MANAGER *manager, int *state) {
    UnownReportApp_Data *data = OverlayManager_GetData(manager);

    if (!ov113_021E5BB0(data)) {
        return FALSE;
    }

    ov113_021E59F8();
    ov113_021E5B60(data);

    OverlayManager_FreeData(manager);

    DestroyHeap(HEAP_ID_UNOWN_REPORT);

    return TRUE;
}

void ov113_021E59F8(void) {
    Main_SetVBlankIntrCB(NULL, NULL);
    HBlankInterruptDisable();

    GfGfx_DisableEngineAPlanes();
    GfGfx_DisableEngineBPlanes();
    GX_SetVisiblePlane(GX_PLANEMASK_NONE);
    GXS_SetVisiblePlane(GX_PLANEMASK_NONE);

    sub_0200FBF4(0, 0);
    sub_0200FBF4(1, 0);
    sub_0200FBDC(0);
    sub_0200FBDC(1);
}

u32 ov113_021E5A48(Pokedex *pokedex, u8 *a1) {
    u32 forms = 0;
    for (int i = 0; i < UNOWN_FORM_MAX; i++) {
        u8 unk = Pokedex_GetSeenFormByIdx_Unown(pokedex, i, TRUE);
        if ((u8)(unk + (0x100 - UNOWN_EXCLAMATION_MARK)) <= 1) {
            a1[forms++] = unk;
        }
    }
    return forms;
}

void ov113_021E5A7C(UnownReportApp_Data *data) {
    data->unk14 = sub_020183F0(data->args->unk0);
    Options *options = Save_PlayerData_GetOptionsAddr(data->args->savedata);
    data->textFrameDelay = Options_GetTextFrameDelay(options);
    data->frame = Options_GetFrame(options);
    data->pokedex = Save_Pokedex_Get(data->args->savedata);
    data->unownReportLevel = Save_VarsFlags_GetUnownReportLevel(Save_VarsFlags_Get(data->args->savedata));
    data->unk1D = ov113_021E5D80(data);
    data->numSeenUnowns = Pokedex_GetSeenFormNum_Unown(data->pokedex, TRUE);

    int i;
    if (data->unownReportLevel >= 4) {
        for (i = UNOWN_A; i <= UNOWN_Z; i++) {
            data->unk20[i] = i;
        }

        u8 unkBuffer[4];
        u8 unk = ov113_021E5A48(data->pokedex, (u8*)&unkBuffer);

        for (i = 0; i < unk; i++) {
            data->unk20[i + 26] = unkBuffer[i];
        }
    } else {
        for (i = 0; i < data->numSeenUnowns; i++) {
            data->unk20[i] = Pokedex_GetSeenFormByIdx_Unown(data->pokedex, i, TRUE);
        }
    }

    data->unk1C = data->numSeenUnowns / 14;
    if (data->numSeenUnowns != 0 && data->numSeenUnowns % 14 != 0) {
        data->unk1C++;
    }

    data->unk1B = data->unk1C + data->unk1D + 1;
}

void ov113_021E5B60(UnownReportApp_Data *data) {
    sub_02018410(data->args->unk0, data->unk14);
}

BOOL ov113_021E5B70(UnownReportApp_Data *data) {
    switch (data->unk10) {
        case 0:
            ov113_021E5CF8(data);
            data->unk10++;
            break;
        case 1:
            ov113_021E5D4C(data);
            sub_020210BC();
            sub_02021148(1);
            sub_02004EC4(69, 0, 0);
            data->unk10 = 0;
            return TRUE;
    }

    return FALSE;
}

BOOL ov113_021E5BB0(UnownReportApp_Data *data) {
    sub_02021238();
    ov113_021E5D28(data);
    return TRUE;
}

u32 ov113_021E5BC4(UnownReportApp_Data *data) {
    switch (data->unk10) {
        case 0:
            BeginNormalPaletteFade(0, 1, 1, RGB_BLACK, 6, 1, data->heapId);
            data->unk10++;
            break;
        case 1:
            if (!IsPaletteFadeFinished()) {
                break;
            }

            data->unk10 = 0;
            return 2;
    }

    return 0;
}

u32 ov113_021E5C0C(UnownReportApp_Data *data) {
    switch (data->unk10) {
        case 0:
            if (ov113_021E5EC4(data) == 0) {
                BeginNormalPaletteFade(0, 0, 0, RGB_BLACK, 6, 1, data->heapId);
                data->unk10++;
            }
            break;
        case 1:
            if (!IsPaletteFadeFinished()) {
                break;
            }

            data->unk10 = 0;
            return 4;
    }

    return 1;
}

u32 ov113_021E5C60(UnownReportApp_Data *data) {
    return ov113_021E5D60(data);
}

u32 ov113_021E5C68(UnownReportApp_Data *data) {
    switch (data->unk10) {
        case 0:
            BeginNormalPaletteFade(0, 4, 2, RGB_BLACK, 6, 1, data->heapId);
            data->unk10++;
            break;
        case 1:
            if (!IsPaletteFadeFinished()) {
                break;
            }

            ov113_021E5DA4(data, data->unk1A);
            data->unk10++;
            break;
        case 2:
            BeginNormalPaletteFade(0, 3, 5, RGB_BLACK, 6, 1, data->heapId);
            data->unk10++;
            break;
        case 3:
            if (!IsPaletteFadeFinished()) {
                break;
            }

            data->unk10 = 0;
            return 2;
    }

    return 3;
}

void ov113_021E5CF8(UnownReportApp_Data *data) {
    ov113_021E6300(data);
    ov113_021E650C(data);
    UnownReportApp_SetupText(data);
    UnownReportApp_SetupWindows(data);
    ov113_021E6988(data);
    Main_SetVBlankIntrCB((GFIntrCB)UnownReportApp_OnVBlank, data);
}

void ov113_021E5D28(UnownReportApp_Data *data) {
    ov113_021E69A8(data);
    UnownReportApp_FreeWindows(data);
    UnownReportApp_FreeText(data);
    ov113_021E663C(data);
    ov113_021E6490(data);
}

void ov113_021E5D4C(UnownReportApp_Data *data) {
    ov113_021E5E64(data, 0);
    ov113_021E5DA4(data, data->unk1A);
}

u32 ov113_021E5D60(UnownReportApp_Data *data) {
    u32 unk = 0;
    u32 ret = ov113_021E5F94(data, &unk);
    if (unk == 0) {
        ret = ov113_021E5F48(data);
    }
    return ret;
}

struct UnkStruct_ov113_021E6BD0 {
    u16 unk0_0:6;
    u16 unk0_6:2;
    u16 unk0_8:8;
    u16 unk2_0:6;
    u16 unk2_6:2;
    u16 unk2_8:8;
};

extern const struct UnkStruct_ov113_021E6BD0 ov113_021E6BD0[6];

u8 ov113_021E5D80(UnownReportApp_Data *data) {
    int i;
    for (i = 0; i < 6; i++) {
        if (ov113_021E6BD0[i].unk0_8 > data->unownReportLevel) {
            break;
        }
    }
    return i;
}

void ov113_021E5DA4(UnownReportApp_Data *data, u8 a1) {
    FillWindowPixelBuffer(&data->windows[1], 0x00);
    FillWindowPixelBuffer(&data->windows[2], 0x00);
    FillWindowPixelBuffer(&data->windows[3], 0x00);

    u32 unk = data->unk1A;
    if (unk == 0) {
        ov113_021E5FC0(data);
    } else if ((int)unk - 1 < data->unk1C) {
        ov113_021E6084(data, unk - 1);
    } else {
        ov113_021E613C(data, unk - (data->unk1C + 1));
    }

    BufferIntegerAsString(data->messageFormat, 0, data->unk1A + 1, 1, PRINTING_MODE_LEFT_ALIGN, 1);
    BufferIntegerAsString(data->messageFormat, 1, data->unk1B, 1, PRINTING_MODE_LEFT_ALIGN, 1);
    StringExpandPlaceholders(data->messageFormat, data->tempString, data->pageNumberString);
    AddTextPrinterParameterizedWithColor(&data->windows[3], 0, data->tempString, 0, 0, TEXT_SPEED_NOTRANSFER, MAKE_TEXT_COLOR(15, 2, 0), NULL);

    ScheduleWindowCopyToVram(&data->windows[1]);
    ScheduleWindowCopyToVram(&data->windows[2]);
    ScheduleWindowCopyToVram(&data->windows[3]);

    ov113_021E6B1C(data);
}

void ov113_021E5E64(UnownReportApp_Data *data, u32 seqNo) {
    Set2dSpriteAnimSeqNo(data->sprites[0], seqNo);
    Sprite_ResetAnimCtrlState(data->sprites[0]);
    FillWindowPixelBuffer(&data->windows[0], 0x00);

    u32 stringWidth = FontID_String_GetWidth(4, data->cancelButtonString, 0);
    AddTextPrinterParameterizedWithColor(&data->windows[0], 4, data->cancelButtonString, (48 - stringWidth) / 2, 0, TEXT_SPEED_NOTRANSFER, MAKE_TEXT_COLOR(7, 15, 0), NULL);
    ScheduleWindowCopyToVram(&data->windows[0]);
}

u32 ov113_021E5EC4(UnownReportApp_Data *data) {
    return Sprite_IsCellAnimationFinished(data->sprites[0]);
}

u32 ov113_021E5ED0(UnownReportApp_Data *data, u32 a1) {
    switch (a1) {
        case 0:
            PlaySE(SEQ_SE_DP_DECIDE);
            ov113_021E5E64(data, 1);
            return 1;
        case 1:
            if (data->unk1A == 0) {
                return 2;
            }

            data->unk1A--;
            Set2dSpriteAnimSeqNo(data->sprites[1], 3);
            PlaySE(SEQ_SE_DP_SELECT);
            return 3;
        case 2:
            if (data->unk1A >= data->unk1B - 1) {
                return 2;
            }

            data->unk1A++;
            Set2dSpriteAnimSeqNo(data->sprites[2], 6);
            PlaySE(SEQ_SE_DP_SELECT);
            return 3;
        default:
            return 2;
    }
}

u32 ov113_021E5F48(UnownReportApp_Data *data) {
    if (gSystem.newKeys & (PAD_BUTTON_A | PAD_BUTTON_B | PAD_BUTTON_X | PAD_BUTTON_Y | PAD_KEY_UP | PAD_KEY_DOWN | PAD_KEY_LEFT | PAD_KEY_RIGHT)) {
        data->unk14 = 0;
    }

    if (gSystem.newKeys & PAD_BUTTON_B) {
        return ov113_021E5ED0(data, 0);
    }

    if (gSystem.newKeys & PAD_KEY_UP) {
        return ov113_021E5ED0(data, 1);
    }

    if (gSystem.newKeys & PAD_KEY_DOWN) {
        return ov113_021E5ED0(data, 2);
    }

    return 2;
}

extern const TouchscreenHitbox ov113_021E6B82;

u32 ov113_021E5F94(UnownReportApp_Data *data, u32 *a1) {
    int unk = TouchscreenHitbox_FindHitboxAtTouchNew(&ov113_021E6B82);
    if (unk == -1) {
        return 2;
    }

    *a1 = TRUE;

    data->unk14 = 1;
    return ov113_021E5ED0(data, unk);
}

void ov113_021E5FC0(UnownReportApp_Data *data) {
    ov113_021E6238(data, &data->unk130, 6);
    ov113_021E6238(data, &data->unk100, 2);

    for (int i = 0; i < 14; i++) {
        UnkImageStruct_SetSpriteVisibleFlag(data->unkC4[i], FALSE);
    }

    ReadMsgDataIntoString(data->msgData, msg_0001_00001, data->tempString);
    UnownReportApp_PrintText(&data->windows[1], data->tempString, 0, 56);
    UnownReportApp_PrintText(&data->windows[1], data->playerNameString, 176 - FontID_String_GetWidth(0, data->playerNameString, 0), 72);

    ReadMsgDataIntoString(data->msgData, msg_0001_00003, data->tempString);
    UnownReportApp_PrintText(&data->windows[2], data->tempString, 4, 60);

    ReadMsgDataIntoString(data->msgData, msg_0001_00004, data->unk4C);
    BufferIntegerAsString(data->messageFormat, 0, data->numSeenUnowns, 2, PRINTING_MODE_RIGHT_ALIGN, 1);
    StringExpandPlaceholders(data->messageFormat, data->tempString, data->unk4C);
    UnownReportApp_PrintText(&data->windows[2], data->tempString, 4, 76);
}

// https://decomp.me/scratch/YnV7X
// Functionally identical.
#ifdef NONMATCHING
void ov113_021E6084(UnownReportApp_Data *data, u8 a1) {
    ov113_021E6238(data, &data->unk140, 6);
    ov113_021E6238(data, &data->unk110, 2);

    int offset = a1 * 14;
    for (int i = 0, y = 0; i < 14; i++, y += 24) {
        int index = offset + i;
        if (index >= data->numSeenUnowns) {
            UnkImageStruct_SetSpriteVisibleFlag(data->unkC4[i], FALSE);
            continue;
        }

        UnkImageStruct_SetSpriteVisibleFlag(data->unkC4[i], TRUE);
        ov113_021E6AE8(data, i, data->unk20[index]);
        ReadMsgDataIntoString(data->msgData, msg_0001_00020 + data->unk20[index], data->tempString);

        if (i < 7) {
            UnownReportApp_PrintText(&data->windows[1], data->tempString, 48, y);
        } else {
            UnownReportApp_PrintText(&data->windows[2], data->tempString, 48, y - 168);
        }
    }
}
#else
asm void ov113_021E6084(UnownReportApp_Data *data, u8 a1) {
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r4, r1, #0
	mov r1, #5
	add r5, r0, #0
	lsl r1, r1, #6
	add r1, r5, r1
	mov r2, #6
	bl ov113_021E6238
	mov r1, #0x11
	lsl r1, r1, #4
	add r0, r5, #0
	add r1, r5, r1
	mov r2, #2
	bl ov113_021E6238
	mov r0, #0xe
	mul r0, r4
	str r0, [sp, #4]
	add r0, r5, #0
	str r0, [sp, #0xc]
	add r0, #0x88
	str r0, [sp, #0xc]
	add r0, r5, #0
	mov r4, #0
	str r0, [sp, #8]
	add r0, #0x78
	str r5, [sp]
	add r6, r4, #0
	str r0, [sp, #8]
_021E60C2:
	ldr r0, [sp, #4]
	add r7, r0, r4
	ldrb r0, [r5, #0x1f]
	cmp r7, r0
	blt _021E60DA
	ldr r0, [sp]
	mov r1, #0
	add r0, #0xc4
	ldr r0, [r0, #0]
	bl UnkImageStruct_SetSpriteVisibleFlag
	b _021E612A
_021E60DA:
	ldr r0, [sp]
	mov r1, #1
	add r0, #0xc4
	ldr r0, [r0, #0]
	bl UnkImageStruct_SetSpriteVisibleFlag
	add r2, r5, r7
	add r2, #0x20
	ldrb r2, [r2]
	add r0, r5, #0
	add r1, r4, #0
	bl ov113_021E6AE8
	add r1, r5, r7
	add r1, #0x20
	ldrb r1, [r1]
	ldr r0, [r5, #0x44]
	ldr r2, [r5, #0x50]
	add r1, #0x14
	bl ReadMsgDataIntoString
	cmp r4, #7
	bge _021E6118
	lsl r3, r6, #0x10
	ldr r0, [sp, #8]
	ldr r1, [r5, #0x50]
	mov r2, #0x30
	lsr r3, r3, #0x10
	bl UnownReportApp_PrintText
	b _021E612A
_021E6118:
	add r3, r6, #0
	sub r3, #0xa8
	lsl r3, r3, #0x10
	ldr r0, [sp, #0xc]
	ldr r1, [r5, #0x50]
	mov r2, #0x30
	lsr r3, r3, #0x10
	bl UnownReportApp_PrintText
_021E612A:
	ldr r0, [sp]
	add r4, r4, #1
	add r0, r0, #4
	add r6, #0x18
	str r0, [sp]
	cmp r4, #0xe
	blt _021E60C2
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
}
#endif

void ov113_021E613C(UnownReportApp_Data *data, u8 a1) {
    if (a1 == 0) {
        ov113_021E6238(data, &data->unk150, 6);
        ov113_021E6238(data, &data->unk120, 2);

        for (int i = 0; i < 14; i++) {
            UnkImageStruct_SetSpriteVisibleFlag(data->unkC4[i], FALSE);
        }
    }

    const struct UnkStruct_ov113_021E6BD0* unk = &ov113_021E6BD0[a1];

    if (unk->unk0_8 <= data->unownReportLevel) {
        for (int i = 0; i < unk->unk0_6; i++) {
            ReadMsgDataIntoString(data->msgData, unk->unk0_0 + i, data->tempString);
            if (unk->unk0_0 + i == msg_0001_00015) {
                UnownReportApp_PrintTextWithFont(&data->windows[1], data->tempString, 3, 4, 0);
            } else {
                UnownReportApp_PrintText(&data->windows[1], data->tempString, 4, 24);
            }
        }
    }

    if (unk->unk2_8 <= data->unownReportLevel) {
        for (int i = 0; i < unk->unk2_6; i++) {
            ReadMsgDataIntoString(data->msgData, unk->unk2_0 + i, data->tempString);
            UnownReportApp_PrintText(&data->windows[2], data->tempString, 4, 24);
        }
    }
}

void ov113_021E6238(UnownReportApp_Data *data, UnownReportApp_UnkSubstruct *a1, u32 bgId) {
    CopyToBgTilemapRect(data->bgConfig, bgId, 0, 0, 32, 24, a1->data, 0, 0, a1->width, a1->height);
    ScheduleBgTilemapBufferTransfer(data->bgConfig, bgId);
}

void UnownReportApp_PrintTextWithFont(Window *window, String *string, FontID fontId, u16 x, u16 y) {
    AddTextPrinterParameterizedWithColor(window, fontId, string, x, y, TEXT_SPEED_NOTRANSFER, MAKE_TEXT_COLOR(1, 2, 0), NULL);
}

void UnownReportApp_PrintText(Window *window, String *string, u16 x, u16 y) {
    UnownReportApp_PrintTextWithFont(window, string, 0, x, y);
}

void UnownReportApp_OnVBlank(UnownReportApp_Data *data) {
    if (data->spriteRenderer != NULL) {
        thunk_OamManager_ApplyAndResetBuffers();
    }

    GF_RunVramTransferTasks();
    DoScheduledBgGpuUpdates(data->bgConfig);

    OS_SetIrqCheckFlag(OS_IE_VBLANK);
}

extern const GraphicsBanks ov113_021E6CD0;

void ov113_021E62E0(void) {
    GraphicsBanks banks = ov113_021E6CD0;
    GfGfx_SetBanks(&banks);
}

extern const GraphicsModes ov113_021E6B94;
extern const BgTemplate ov113_021E6BE8[6];

void ov113_021E6300(UnownReportApp_Data *data) {
    ov113_021E62E0();
    data->bgConfig = BgConfig_Alloc(data->heapId);

    GraphicsModes modes = ov113_021E6B94;
    SetBothScreensModesAndDisable(&modes);

    GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);

    BgTemplate sp3C = ov113_021E6BE8[3];
    InitBgFromTemplate(data->bgConfig, 5, &sp3C, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(data->bgConfig, 5);

    BgTemplate sp58 = ov113_021E6BE8[5];
    InitBgFromTemplate(data->bgConfig, 6, &sp58, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(data->bgConfig, 6);

    BgTemplate sp74 = ov113_021E6BE8[0];
    InitBgFromTemplate(data->bgConfig, 7, &sp74, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(data->bgConfig, 7);

    BgTemplate sp90 = ov113_021E6BE8[1];
    InitBgFromTemplate(data->bgConfig, 1, &sp90, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(data->bgConfig, 1);

    BgTemplate spAC = ov113_021E6BE8[2];
    InitBgFromTemplate(data->bgConfig, 2, &spAC, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(data->bgConfig, 2);

    BgTemplate spC8 = ov113_021E6BE8[4];
    InitBgFromTemplate(data->bgConfig, 3, &spC8, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(data->bgConfig, 3);

    BG_ClearCharDataRange(5, 0x20, 0, data->heapId);
    BG_ClearCharDataRange(6, 0x20, 0, data->heapId);
    BG_ClearCharDataRange(7, 0x20, 0, data->heapId);
    BG_ClearCharDataRange(1, 0x20, 0, data->heapId);
    BG_ClearCharDataRange(2, 0x20, 0, data->heapId);
    BG_ClearCharDataRange(3, 0x20, 0, data->heapId);
}

void ov113_021E6490(UnownReportApp_Data *data) {
    FreeBgTilemapBuffer(data->bgConfig, 3);
    FreeBgTilemapBuffer(data->bgConfig, 2);
    FreeBgTilemapBuffer(data->bgConfig, 1);
    FreeBgTilemapBuffer(data->bgConfig, 7);
    FreeBgTilemapBuffer(data->bgConfig, 6);
    FreeBgTilemapBuffer(data->bgConfig, 5);
    FreeToHeap(data->bgConfig);

    GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
}

void ov113_021E64DC(UnownReportApp_UnkSubstruct *a0, NARC *narc, u32 memberNum, HeapID heapId) {
    a0->screenData = GfGfxLoader_GetScrnDataFromOpenNarc(narc, memberNum, TRUE, &a0->g2dScreenData, heapId);
    a0->width = a0->g2dScreenData->screenWidth / 8;
    a0->height = a0->g2dScreenData->screenHeight / 8;
    a0->data = a0->g2dScreenData->rawData;
}

void ov113_021E650C(UnownReportApp_Data *data) {
    NARC *narc = NARC_New(NARC_a_2_3_9, data->heapId);

    GfGfxLoader_GXLoadPalFromOpenNarc(narc, 5, GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_0_OFFSET, 0, data->heapId);
    GfGfxLoader_LoadCharDataFromOpenNarc(narc, 7, data->bgConfig, GF_BG_LYR_MAIN_3, 0, 0, TRUE, data->heapId);
    GfGfxLoader_LoadScrnDataFromOpenNarc(narc, 9, data->bgConfig, GF_BG_LYR_MAIN_3, 0, 0, TRUE, data->heapId);

    GfGfxLoader_GXLoadPalFromOpenNarc(narc, 4, GF_PAL_LOCATION_SUB_BG, GF_PAL_SLOT_0_OFFSET, 0, data->heapId);
    GfGfxLoader_LoadCharDataFromOpenNarc(narc, 6, data->bgConfig, GF_BG_LYR_SUB_3, 0, 0, TRUE, data->heapId);
    GfGfxLoader_LoadScrnDataFromOpenNarc(narc, 8, data->bgConfig, GF_BG_LYR_SUB_3, 0, 0, TRUE, data->heapId);

    ov113_021E64DC(&data->unk130, narc, 10, data->heapId);
    ov113_021E64DC(&data->unk140, narc, 12, data->heapId);
    ov113_021E64DC(&data->unk150, narc, 14, data->heapId);
    ov113_021E64DC(&data->unk100, narc, 11, data->heapId);
    ov113_021E64DC(&data->unk110, narc, 13, data->heapId);
    ov113_021E64DC(&data->unk120, narc, 15, data->heapId);

    NARC_Delete(narc);

    LoadUserFrameGfx2(data->bgConfig, GF_BG_LYR_MAIN_1, 1, 13, data->frame, data->heapId);

    LoadFontPal1(GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_12_OFFSET, data->heapId);
    LoadFontPal1(GF_PAL_LOCATION_SUB_BG, GF_PAL_SLOT_12_OFFSET, data->heapId);
}

void ov113_021E663C(UnownReportApp_Data *data) {
    FreeToHeap(data->unk120.screenData);
    FreeToHeap(data->unk110.screenData);
    FreeToHeap(data->unk100.screenData);
    FreeToHeap(data->unk150.screenData);
    FreeToHeap(data->unk140.screenData);
    FreeToHeap(data->unk130.screenData);
}

void UnownReportApp_SetupText(UnownReportApp_Data *data) {
    FontID_Alloc(4, data->heapId);

    data->msgData = NewMsgDataFromNarc(MSGDATA_LOAD_DIRECT, NARC_msgdata_msg, NARC_msg_msg_0001_bin, data->heapId);
    data->messageFormat = MessageFormat_New_Custom(16, 16, data->heapId);
    data->unk4C = String_New(512, data->heapId);
    data->tempString = String_New(512, data->heapId);
    data->cancelButtonString = NewString_ReadMsgData(data->msgData, msg_0001_00000);
    data->pageNumberString = NewString_ReadMsgData(data->msgData, msg_0001_00005);
    data->playerNameString = PlayerProfile_GetPlayerName_NewString(Save_PlayerData_GetProfileAddr(data->args->savedata), data->heapId);
}

void UnownReportApp_FreeText(UnownReportApp_Data *data) {
    String_Delete(data->playerNameString);
    String_Delete(data->pageNumberString);
    String_Delete(data->cancelButtonString);
    String_Delete(data->tempString);
    String_Delete(data->unk4C);
    MessageFormat_Delete(data->messageFormat);
    DestroyMsgData(data->msgData);

    FontID_Release(4);
}

extern const WindowTemplate ov113_021E6C90[4];

void UnownReportApp_SetupWindows(UnownReportApp_Data *data) {
    for (int i = 0; i < 4; i++) {
        AddWindow(data->bgConfig, &data->windows[i], &ov113_021E6C90[i]);
        FillWindowPixelBuffer(&data->windows[i], 0x00);
    }

    data->unkA8 = YesNoPrompt_Create(data->heapId);
}

void UnownReportApp_FreeWindows(UnownReportApp_Data *data) {
    for (int i = 0; i < 4; i++) {
        ClearWindowTilemapAndCopyToVram(&data->windows[i]);
        RemoveWindow(&data->windows[i]);
    }

    YesNoPrompt_Destroy(data->unkA8);
}

extern const Unk122_021E92D0 ov113_021E6BA4;
extern const Unk122_021E92FC ov113_021E6CB0;
extern const u16 ov113_021E6B74[7];
extern const SpriteResourceCountsListUnion ov113_021E6BB8;

void ov113_021E677C(UnownReportApp_Data *data) {
    GF_CreateVramTransferManager(32, data->heapId);

    data->spriteRenderer = SpriteRenderer_Create(data->heapId);
    sub_0200CF70(data->spriteRenderer, &ov113_021E6CB0, &ov113_021E6BA4, 2);

    sub_0200B2E0(data->heapId);
    sub_0200B2E8(data->heapId);

    data->spriteGfxHandler1 = SpriteRenderer_CreateGfxHandler(data->spriteRenderer);
    sub_0200CFF4(data->spriteRenderer, data->spriteGfxHandler1, 17);
    sub_0200D2A4(data->spriteRenderer, data->spriteGfxHandler1, ov113_021E6B74, 0, 0);

    SpriteResourceCountsListUnion counts = ov113_021E6BB8;
    data->spriteGfxHandler2 = SpriteRenderer_CreateGfxHandler(data->spriteRenderer);
    SpriteRenderer_Init2DGfxResManagersFromCountsArray(data->spriteRenderer, data->spriteGfxHandler2, &counts);
    sub_0200E2B4(data->spriteGfxHandler2, sub_0200E2B0(data->spriteGfxHandler1));

    data->narc = NARC_New(NARC_a_0_2_0, data->heapId);

    SpriteRenderer_LoadPlttResObjFromOpenNarc(data->spriteRenderer, data->spriteGfxHandler2, data->narc, sub_02074490(), FALSE, 1, 3, 1);
    SpriteRenderer_LoadCellResObjFromOpenNarc(data->spriteRenderer, data->spriteGfxHandler2, data->narc, sub_02074494(), FALSE, 1);
    SpriteRenderer_LoadAnimResObjFromNarcId(data->spriteRenderer, data->spriteGfxHandler2, NARC_a_0_2_0, sub_020744A0(), FALSE, 1);
    for (int i = 0; i < 7; i++) {
        SpriteRenderer_LoadCharResObjFromOpenNarc(data->spriteRenderer, data->spriteGfxHandler2, data->narc, GetMonIconNaixEx(SPECIES_UNOWN, FALSE, i), FALSE, 2, i + 1);
    }
    for (int i = 7; i < 14; i++) {
        SpriteRenderer_LoadCharResObjFromOpenNarc(data->spriteRenderer, data->spriteGfxHandler2, data->narc, GetMonIconNaixEx(SPECIES_UNOWN, FALSE, i), FALSE, 1, i + 1);
    }
}

void ov113_021E6930(UnownReportApp_Data *data) {
    SpriteRenderer_UnloadResourcesAndRemoveGfxHandler(data->spriteRenderer, data->spriteGfxHandler2);
    SpriteRenderer_RemoveGfxHandler(data->spriteRenderer, data->spriteGfxHandler1);
    data->spriteGfxHandler2 = NULL;
    data->spriteGfxHandler1 = NULL;

    NARC_Delete(data->narc);

    SpriteRenderer_Delete(data->spriteRenderer);
    data->spriteRenderer = NULL;

    GF_DestroyVramTransferManager();

    sub_0200B2E0(data->heapId);
}

void ov113_021E6988(UnownReportApp_Data *data) {
    ov113_021E677C(data);
    ov113_021E69CC(data);
    GfGfx_EngineATogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_ON);
    GfGfx_EngineBTogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_ON);
}

void ov113_021E69A8(UnownReportApp_Data *data) {
    GfGfx_EngineBTogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_OFF);
    GfGfx_EngineATogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_OFF);
    ov113_021E6AB0(data);
    ov113_021E6930(data);
}

extern const UnkStruct_0200D2B4 ov113_021E6CF8[3];

void ov113_021E69CC(UnownReportApp_Data *data) {
    for (int i = 0; i < 3; i++) {
        data->sprites[i] = SpriteRenderer_CreateSprite(data->spriteRenderer, data->spriteGfxHandler1, &ov113_021E6CF8[i]);
        Set2dSpriteVisibleFlag(data->sprites[i], TRUE);
        Set2dSpriteAnimActiveFlag(data->sprites[i], TRUE);
        Sprite_SetPriority(data->sprites[i], 2);
    }

    UnkTemplate_0200D748 template;
    MI_CpuFill8(&template, 0, sizeof(UnkTemplate_0200D748));
    template.bgPriority = 1;
    template.pal = GetMonIconPaletteEx(SPECIES_UNOWN, 0, FALSE);
    template.vramTransfer = 0;
    template.x = 40;
    template.resIdList[GF_GFX_RES_TYPE_PLTT] = 1;
    template.resIdList[GF_GFX_RES_TYPE_CELL] = 1;
    template.resIdList[GF_GFX_RES_TYPE_ANIM] = 1;
    template.resIdList[GF_GFX_RES_TYPE_MCEL] = -1;
    template.resIdList[GF_GFX_RES_TYPE_MANM] = -1;

    for (int i = 0; i < 14; i++) {
        if (i < 7) {
            template.y = (i * 24) + 29;
            template.vram = NNS_G2D_VRAM_TYPE_2DSUB;
        } else {
            template.y = (int)(i * 24) - 155;
            template.vram = NNS_G2D_VRAM_TYPE_2DMAIN;
        }
        template.resIdList[GF_GFX_RES_TYPE_CHAR] = i + 1;

        data->unkC4[i] = SpriteRenderer_LoadResourcesAndCreateSprite(data->spriteRenderer, data->spriteGfxHandler2, &template);
        UnkImageStruct_SetSpriteVisibleFlag(data->unkC4[i], FALSE);
    }
}

void ov113_021E6AB0(UnownReportApp_Data *data) {
    for (int i = 0; i < 14; i++) {
        if (data->unkC4[i] != NULL) {
            sub_0200D9DC(data->unkC4[i]);
        }
    }

    for (int i = 0; i < 3; i++) {
        if (data->sprites[i] != NULL) {
            Sprite_Delete(data->sprites[i]);
        }
    }
}

void ov113_021E6AE8(UnownReportApp_Data *data, u32 a1, u8 form) {
    sub_0200E2B8(data->spriteRenderer, data->spriteGfxHandler2, data->narc, GetMonIconNaixEx(SPECIES_UNOWN, FALSE, form), FALSE, a1 + 1);
}

void ov113_021E6B1C(UnownReportApp_Data *data) {
    if (data->unk1B == 1 || data->unk1A == 0) {
        Set2dSpriteAnimSeqNo(data->sprites[1], 4);
    } else {
        Set2dSpriteAnimSeqNo(data->sprites[1], 2);
    }

    if (data->unk1B == 1 || data->unk1A == data->unk1B - 1) {
        Set2dSpriteAnimSeqNo(data->sprites[2], 7);
    } else {
        Set2dSpriteAnimSeqNo(data->sprites[2], 5);
    }
}

extern const u32 ov113_021E6B6C[2];
