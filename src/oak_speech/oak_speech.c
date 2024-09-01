#include "global.h"
#include <nitro/spi/ARM9/pm.h>
#include "oak_speech/oak_speech.h"
#include "brightness.h"
#include "constants/species.h"
#include "font.h"
#include "gf_gfx_loader.h"
#include "main.h"
#include "math_util.h"
#include "msgdata/msg.naix"
#include "msgdata/msg/msg_0219.h"
#include "player_data.h"
#include "render_text.h"
#include "render_window.h"
#include "save.h"
#include "sound.h"
#include "sound_02004A44.h"
#include "system.h"
#include "touchscreen.h"
#include "unk_02005D10.h"
#include "unk_0200FA24.h"

BOOL OakSpeech_Init(OVY_MANAGER *manager, int *state) {
    CreateHeap(HEAP_ID_3, HEAP_ID_OAK_SPEECH, 0x40000);

    OakSpeechApp_Data *data = OverlayManager_CreateAndGetData(manager, sizeof(OakSpeechApp_Data), HEAP_ID_OAK_SPEECH);
    memset(data, 0, sizeof(OakSpeechApp_Data));
    data->heapId = HEAP_ID_OAK_SPEECH;

    OakSpeechApp_Args *args = OverlayManager_GetArgs(manager);
    SaveData *savedata = args->savedata;
    data->savedata = savedata;
    data->options = Save_PlayerData_GetOptionsAddr(savedata);

    data->state = 0;
    data->unk10 = 0;
    data->overlayManager = NULL;
    data->playerNamingArgs = NamingScreen_CreateArgs(HEAP_ID_OAK_SPEECH, 0, 0, PLAYER_NAME_LENGTH, data->options, NULL);
    data->rivalNamingArgs = NamingScreen_CreateArgs(HEAP_ID_OAK_SPEECH, 3, 0, PLAYER_NAME_LENGTH, data->options, NULL);
    data->unk17C = 0;
    data->waitFrames = 0;

    sub_02002B8C(FALSE);

    FontID_Alloc(4, data->heapId);

    return TRUE;
}

extern void OakSpeech_SetupGraphics(OakSpeechApp_Data *data);
extern void OakSpeech_SetupText(OakSpeechApp_Data *data);
extern void OakSpeech_FreeText(OakSpeechApp_Data *data);
extern void ov53_021E7F24(OakSpeechApp_Data *data);
extern void ov53_021E8014(OakSpeechApp_Data *data);
extern void OakSpeech_OnVBlank(OakSpeechApp_Data *data);
extern void ov53_021E7ECC(OakSpeechApp_Data *data);
extern void ov53_021E7FEC(OakSpeechApp_Data *data);
extern void OakSpeech_FreeGraphics(OakSpeechApp_Data *data);
extern BOOL ov53_021E6F9C(OakSpeechApp_Data *data);
extern void ov53_021E814C(UnkStruct_ov53_021E80F4 *a0);
extern UnkStruct_ov53_021E80F4 *ov53_021E80F4();

BOOL OakSpeech_Main(OVY_MANAGER *manager, int *state) {
    OakSpeechApp_Data *data = OverlayManager_GetData(manager);
    BOOL ret = FALSE;

    switch (*state) {
        case 0:
            sub_0200FBF4(PM_LCD_TOP, 0);
            sub_0200FBF4(PM_LCD_BOTTOM, 0);

            Main_SetVBlankIntrCB(NULL, NULL);
            Main_SetHBlankIntrCB(NULL, NULL);

            GfGfx_DisableEngineAPlanes();
            GfGfx_DisableEngineBPlanes();
            GX_SetVisiblePlane(0);
            GXS_SetVisiblePlane(0);

            SetKeyRepeatTimers(4, 8);

            OakSpeech_SetupGraphics(data);
            OakSpeech_SetupText(data);

            BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_0);
            ov53_021E7F24(data);
            ov53_021E8014(data);

            data->unk178 = ov53_021E80F4(data->bgConfig, data->sprites[4], GF_BG_LYR_SUB_2, GF_BG_LYR_SUB_0, 14, data->heapId);

            Main_SetVBlankIntrCB((GFIntrCB)OakSpeech_OnVBlank, data);

            GfGfx_BothDispOn();

            *state = 1;
            break;

        case 1: {
            ov53_021E7ECC(data);
            if (ov53_021E6F9C(data) == TRUE) { // Finished with speech if true
                BeginNormalPaletteFade(0, 0, 0, RGB_BLACK, 6, 1, data->heapId);
                *state = 2;
            }
            if (data->overlayManager != NULL) {
                BeginNormalPaletteFade(0, 0, 0, RGB_BLACK, 6, 1, data->heapId);
                *state = 3;
            }
            break;
        }

        case 2:
            if (IsPaletteFadeFinished() == TRUE) {
                ov53_021E814C(data->unk178);
                ov53_021E7FEC(data);
                OakSpeech_FreeText(data);
                OakSpeech_FreeGraphics(data);
                Main_SetVBlankIntrCB(NULL, NULL);
                ret = TRUE;
            }
            break;

        case 3:
            if (IsPaletteFadeFinished() == TRUE) {
                ov53_021E814C(data->unk178);
                ov53_021E7FEC(data);
                OakSpeech_FreeText(data);
                OakSpeech_FreeGraphics(data);
                Main_SetVBlankIntrCB(NULL, NULL);
                *state = 4;
            }
            break;

        case 4:
            if (OverlayManager_Run(data->overlayManager) == TRUE) {
                OverlayManager_Delete(data->overlayManager);
                data->overlayManager = NULL;
                *state = 5;
            }
            break;

        case 5:
            *state = 0;
            break;
    }

    if (data->overlayManager == NULL && data->spriteGfxHandler != NULL) {
        sub_0200D020(data->spriteGfxHandler);
    }

    return ret;
}

FS_EXTERN_OVERLAY(OVY_36);
extern OVY_MGR_TEMPLATE ov36_App_InitGameState_AfterOakSpeech;

BOOL OakSpeech_Exit(OVY_MANAGER *manager, int* state) {
    OakSpeechApp_Data *data = OverlayManager_GetData(manager);
    HeapID heapId = data->heapId;

    FontID_Release(4);

    PlayerName_StringToFlat(Save_PlayerData_GetProfileAddr(data->savedata), data->playerNamingArgs->unk18);
    PlayerProfile_SetTrainerGender(Save_PlayerData_GetProfileAddr(data->savedata), data->playerNamingArgs->unk4);
    Save_Misc_RivalName_Set(Save_Misc_Get(data->savedata), data->rivalNamingArgs->unk18);
    sub_0208311C(data->playerNamingArgs);
    sub_0208311C(data->rivalNamingArgs);

    OverlayManager_FreeData(manager);

    DestroyHeap(heapId);

    RegisterMainOverlay(FS_OVERLAY_ID(OVY_36), &ov36_App_InitGameState_AfterOakSpeech);

    sub_02002B8C(FALSE);

    return TRUE;
}

void OakSpeech_OnVBlank(OakSpeechApp_Data *data) {
    DoScheduledBgGpuUpdates(data->bgConfig);
    thunk_OamManager_ApplyAndResetBuffers();
}

extern void ov53_021E65E0(OakSpeechApp_Data *data);

extern GraphicsModes ov53_021E8548;
extern GraphicsBanks ov53_021E8628;
extern BgTemplate ov53_021E85CC;
extern BgTemplate ov53_021E85E8;

void OakSpeech_SetupGraphics(OakSpeechApp_Data *data) {
    GraphicsBanks banks = ov53_021E8628;
    GfGfx_SetBanks(&banks);

    data->bgConfig = BgConfig_Alloc(data->heapId);

    GraphicsModes modes = ov53_021E8548;
    SetBothScreensModesAndDisable(&modes);

    BgTemplate template0x64 = ov53_021E85CC;

    template0x64.screenBase = GX_BG_SCRBASE_0x7800;
    template0x64.charBase = GX_BG_CHARBASE_0x18000;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_0, &template0x64, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_0);

    template0x64.screenBase = GX_BG_SCRBASE_0x7000;
    template0x64.charBase = GX_BG_CHARBASE_0x14000;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_1, &template0x64, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_1);

    template0x64.screenBase = GX_BG_SCRBASE_0x6800;
    template0x64.charBase = GX_BG_CHARBASE_0x10000;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_2, &template0x64, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_2);

    template0x64.screenBase = GX_BG_SCRBASE_0x6000;
    template0x64.charBase = GX_BG_CHARBASE_0x0c000;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_3, &template0x64, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_3);

    LoadUserFrameGfx2(data->bgConfig, GF_BG_LYR_MAIN_0, 0x3E2, 4, 0, data->heapId);
    LoadUserFrameGfx1(data->bgConfig, GF_BG_LYR_MAIN_0, 0x3D9, 3, 0, data->heapId);
    LoadFontPal0(GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_5_OFFSET, data->heapId);
    LoadFontPal1(GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_6_OFFSET, data->heapId);

    BgTemplate template0x80 = ov53_021E85E8;

    template0x80.screenBase = GX_BG_SCRBASE_0x7800;
    template0x80.charBase = GX_BG_CHARBASE_0x18000;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_SUB_0, &template0x80, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_0);

    template0x80.screenBase = GX_BG_SCRBASE_0x7000;
    template0x80.charBase = GX_BG_CHARBASE_0x14000;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_SUB_1, &template0x80, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_1);

    template0x80.screenBase = GX_BG_SCRBASE_0x6800;
    template0x80.charBase = GX_BG_CHARBASE_0x10000;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_SUB_2, &template0x80, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_2);

    template0x80.screenBase = GX_BG_SCRBASE_0x6000;
    template0x80.charBase = GX_BG_CHARBASE_0x0c000;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_SUB_3, &template0x80, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_3);

    SetBgPriority(GF_BG_LYR_SUB_3, 3);

    LoadFontPal0(GF_PAL_LOCATION_SUB_BG, GF_PAL_SLOT_14_OFFSET, data->heapId);
    BG_ClearCharDataRange(GF_BG_LYR_SUB_0, 0x20, 0, data->heapId);

    ToggleBgLayer(GF_BG_LYR_MAIN_0, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_1, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_2, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_3, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_0, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_1, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_2, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_3, GF_PLANE_TOGGLE_OFF);

    ov53_021E65E0(data);

    data->unk128 = 0;
}

void OakSpeech_FreeGraphics(OakSpeechApp_Data *data) {
    ToggleBgLayer(GF_BG_LYR_MAIN_0, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_1, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_2, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_3, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_0, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_1, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_2, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_3, GF_PLANE_TOGGLE_OFF);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_0);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_1);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_2);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_3);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_SUB_0);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_SUB_1);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_SUB_2);
    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_SUB_3);

    FreeToHeap(data->bgConfig);
}

// FIXME: Returns a struct
extern u32 sub_020163E0(PaletteData *paletteData, u32 screen, u32 a2, HeapID heapId);
// FIXME: a0 is the struct returned by sub_020163E0
extern void sub_020164C4(u32 a0);

void OakSpeech_SetupText(OakSpeechApp_Data *data) {
    data->msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_msgdata_msg, NARC_msg_msg_0219_bin, data->heapId);
    ResetAllTextPrinters();
    data->unk114 = sub_020163E0(NULL, PM_LCD_TOP, 6, data->heapId);
    data->messageFormat = MessageFormat_New(data->heapId);
    data->unk104 = 0;
    data->unk108 = 0;
    data->unk80 = 0;
}

void OakSpeech_FreeText(OakSpeechApp_Data *data) {
    MessageFormat_Delete(data->messageFormat);
    sub_020164C4(data->unk114);
    DestroyMsgData(data->msgData);
}

u32 ov53_021E5EDC(OakSpeechApp_Data *data, int a1, u32 a2);

u32 ov53_021E5EDC(OakSpeechApp_Data *data, int a1, u32 a2) {
    u32 ret = 0;

    u32 unkInt;
    u32 screen;
    switch (a1) {
        default:
        case 0:
        case 3:
            unkInt = 1;
            screen = 0;
            break;
        case 1:
            unkInt = 2;
            screen = 0;
            break;
        case 2:
            unkInt = 4;
            screen = 0;
            break;
        case 4:
            unkInt = 1;
            screen = 1;
            break;
        case 5:
            unkInt = 2;
            screen = 1;
            break;
        case 6:
            unkInt = 4;
            screen = 1;
            break;
        case 101:
            unkInt = 16;
            screen = 0;
            break;
        case 102:
            unkInt = 16;
            screen = 1;
            break;
    }

    switch (data->unk128) {
        case 0:
            if (a2 == 0) {
                data->unk12C = 0;
                data->unk130 = 16;
                data->unk128 = 1;
                if (screen == 0) {
                    G2_SetBlendAlpha(unkInt, 14, data->unk12C, data->unk130);
                } else {
                    G2S_SetBlendAlpha(unkInt, 14, data->unk12C, data->unk130);
                }
                if (a1 == 101) {
                    GfGfx_EngineATogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_ON);
                } else if (a1 == 102) {
                    GfGfx_EngineBTogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_ON);
                } else {
                    ToggleBgLayer((u8)a1, GF_PLANE_TOGGLE_ON);
                }
            } else {
                data->unk12C = 16;
                data->unk130 = 0;
                data->unk128 = 2;
            }
            break;

        case 1:
            if (data->unk130 != 0) {
                data->unk12C++;
                data->unk130--;
                if (screen == 0) {
                    G2_SetBlendAlpha(unkInt, 14, data->unk12C, data->unk130);
                } else {
                    G2S_SetBlendAlpha(unkInt, 14, data->unk12C, data->unk130);
                }
            } else {
                data->unk128 = 3;
            }
            break;

        case 2:
            if (data->unk12C != 0) {
                data->unk12C--;
                data->unk130++;
                if (screen == 0) {
                    G2_SetBlendAlpha(unkInt, 14, data->unk12C, data->unk130);
                } else {
                    G2S_SetBlendAlpha(unkInt, 14, data->unk12C, data->unk130);
                }
            } else {
                data->unk128 = 3;
                if (a1 == 101) {
                    GfGfx_EngineATogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_OFF);
                } else if (a1 == 102) {
                    GfGfx_EngineBTogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_OFF);
                } else {
                    ToggleBgLayer((u8)a1, GF_PLANE_TOGGLE_OFF);
                }
            }
            break;

        case 3:
            G2_BlendNone();
            G2S_BlendNone();
            ret = 1;
            data->unk128 = 0;
            break;
    }

    return ret;
}

BOOL OakSpeech_WaitFrames(OakSpeechApp_Data *data, int frames);
BOOL OakSpeech_WaitFrames(OakSpeechApp_Data *data, int frames) {
    if (data->waitFrames < frames) {
        data->waitFrames++;
        return 0;
    } else {
        data->waitFrames = 0;
        return 1;
    }
}

void ov53_021E60E8(OakSpeechApp_Data *data, u32 bgId, u32 palette);
void ov53_021E60E8(OakSpeechApp_Data *data, u32 bgId, u32 palette) {
    BgTilemapRectChangePalette(data->bgConfig, bgId, 0, 0, 32, 24, palette);
    BgCommitTilemapBufferToVram(data->bgConfig, bgId);
}

extern const WindowTemplate ov53_021E8500;

u32 ov53_021E611C(OakSpeechApp_Data *data, u32 msgNum, BOOL a2);
u32 ov53_021E611C(OakSpeechApp_Data *data, u32 msgNum, BOOL a2) {
    u32 ret = 0;

    switch (data->unk104) {
        case 0: {
            AddWindow(data->bgConfig, &data->window2C, &ov53_021E8500);
            FillWindowPixelRect(&data->window2C, 0xF, 0, 0, 216, 32);
            DrawFrameAndWindow2(&data->window2C, FALSE, 0x3E2, 4);

            TextFlags_SetCanABSpeedUpPrint(TRUE);
            sub_02002B50(FALSE);

            String *temp = String_New(0x400, data->heapId);
            data->string = String_New(0x400, data->heapId);
            ReadMsgDataIntoString(data->msgData, msgNum, temp);
            BufferString(data->messageFormat, 0, data->playerNamingArgs->unk18, data->playerGender, 1, 2);
            BufferString(data->messageFormat, 1, data->rivalNamingArgs->unk18, 0, 1, 2);
            StringExpandPlaceholders(data->messageFormat, data->string, temp);
            String_Delete(temp);

            data->textPrinter = AddTextPrinterParameterized(&data->window2C, 1, data->string, 0, 0, Options_GetTextFrameDelay(data->options), NULL);
            data->unk104 = 1;
            break;
        }
        case 1:
            if (!TextPrinterCheckActive(data->textPrinter)) {
                String_Delete(data->string);
                data->unk104 = 2;
            }
            break;
        case 2:
            if (!a2) {
                if ((gSystem.newKeys & PAD_BUTTON_A) == TRUE) {
                    data->unk16C = 0;
                    PlaySE(SEQ_SE_DP_SELECT);
                    ret = 1;
                }
            } else {
                ret = 1;
            }
            if (ret != 0) {
                RemoveWindow(&data->window2C);
                data->unk104 = 0;
            }
            break;
    }

    return ret;
}

extern const WindowTemplate ov53_021E8520;
extern const WindowTemplate ov53_021E8528;

extern u8 ov53_021E84F8; // FIXME: not actually a u8

u32 ov53_021E628C(OakSpeechApp_Data *data, u32 msgNum, u32 a2, u32 yMaybe, u32 heightMaybe);
#ifdef NONMATCHING
u32 ov53_021E628C(OakSpeechApp_Data *data, u32 msgNo, u32 a2, u32 yMaybe, u32 heightMaybe) {
    u32 ret = 0;

    switch (data->unk108) {
        case 0:
            ToggleBgLayer(GF_BG_LYR_MAIN_0, GF_PLANE_TOGGLE_OFF);
            data->string = String_New(1024, data->heapId);
            ReadMsgDataIntoString(data->msgData, msgNo, data->string);

            if (yMaybe == 0xFFFF) {
                int thing = 24 - (String_CountLines(data->string) * 2);
                yMaybe = thing / 2;
            }

            if (heightMaybe == 0xFFFF) {
                int thing = String_CountLines(data->string);
                heightMaybe = thing * 2;
            }

            switch (a2) {
                case 1: {
                    WindowTemplate template20 = ov53_021E8520;
                    template20.top = yMaybe;
                    template20.height = heightMaybe;
                    AddWindow(data->bgConfig, &data->window1C, &template20);
                    FillWindowPixelRect(&data->window1C, 0x0, 0, 0, 192, 192);
                    AddTextPrinterParameterizedWithColor(&data->window1C, 0, data->string, 0, 0, 0, MAKE_TEXT_COLOR(1, 2, 0), NULL);
                    break;
                }
                case 0:
                case 2:
                case 3: {
                    WindowTemplate template20 = ov53_021E8520;
                    template20.top = yMaybe;
                    template20.height = heightMaybe;
                    if (a2 == 3) {
                        template20.left += 4;
                    }
                    AddWindow(data->bgConfig, &data->window1C, &template20);
                    FillWindowPixelRect(&data->window1C, 0x0, 0, 0, 192, 192);
                    AddTextPrinterParameterizedWithColor(&data->window1C, 0, data->string, 0, 0, 0, MAKE_TEXT_COLOR(15, 2, 0), NULL);
                    break;
                }
            }

            String_Delete(data->string);
            data->unk108 = 1;
            break;
        case 1:
            CopyWindowToVram(&data->window1C);
            data->unk108 = 2;
            break;
        case 2:
            if (ov53_021E5EDC(data, 0, 0) == 1) {
                data->unk108 = 3;
                if (a2 == 2) {
                    data->unk108 = 4;
                    ret = 1;
                }
            }
            break;
        case 3:
            if ((gSystem.newKeys & PAD_BUTTON_A) == PAD_BUTTON_A || (gSystem.newKeys & PAD_BUTTON_B) == PAD_BUTTON_B) {
                data->unk16C = gSystem.touchNew != 0;
                PlaySE(SEQ_SE_DP_SELECT);
                data->unk108 = 4;
            }
            break;
        case 4:
            if (ov53_021E5EDC(data, 0, 1) == 1) {
                data->unk108 = 5;
            }
            break;
        case 5:
            RemoveWindow(&data->window1C);
            BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_0);
            data->unk108 = 0;
            ret = 1;
            break;
    }

    return ret;
}
#else
asm u32 ov53_021E628C(OakSpeechApp_Data *data, u32 msgNum, u32 a2, u32 yMaybe, u32 heightMaybe) {
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r1, [sp, #0x10]
	mov r1, #0
	str r1, [sp, #0x14]
	mov r1, #0x42
	add r4, r0, #0
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	add r5, r2, #0
	add r7, r3, #0
	ldr r6, [sp, #0x38]
	cmp r1, #5
	bls _021E62AA
	b _021E6490
_021E62AA:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021E62B6: // jump table
	DCD 0x013E000A // .short _021E62C2 - _021E62B6 - 2 ; case 0
	               // .short _021E63F6 - _021E62B6 - 2 ; case 1
    DCD 0x0170014E // .short _021E6406 - _021E62B6 - 2 ; case 2
	               // .short _021E6428 - _021E62B6 - 2 ; case 3
    DCD 0x01BE01A8 // .short _021E6460 - _021E62B6 - 2 ; case 4
	               // .short _021E6476 - _021E62B6 - 2 ; case 5
_021E62C2:
	ldr r0, [sp, #0x14]
	add r1, r0, #0
	bl ToggleBgLayer
	mov r0, #1
	ldr r1, [r4, #0]
	lsl r0, r0, #0xa
	bl String_New
	mov r2, #0x11
	lsl r2, r2, #4
	str r0, [r4, r2]
	add r0, r2, #0
	sub r0, #0x10
	ldr r0, [r4, r0]
	ldr r1, [sp, #0x10]
	ldr r2, [r4, r2]
	bl ReadMsgDataIntoString
	ldr r0, =0x0000FFFF
	cmp r7, r0
	bne _021E6304
	mov r0, #0x11
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl String_CountLines
	lsl r1, r0, #1
	mov r0, #0x18
	sub r1, r0, r1
	lsr r0, r1, #0x1f
	add r0, r1, r0
	asr r7, r0, #1
_021E6304:
	ldr r0, =0x0000FFFF
	cmp r6, r0
	bne _021E6316
	mov r0, #0x11
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl String_CountLines
	lsl r6, r0, #1
_021E6316:
	cmp r5, #3
	bhi _021E63E2
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E6326: // jump table
	DCD 0x0006005C // .short _021E6384 - _021E6326 - 2 ; case 0
	               // .short _021E632E - _021E6326 - 2 ; case 1
	DCD 0x005C005C // .short _021E6384 - _021E6326 - 2 ; case 2
	               // .short _021E6384 - _021E6326 - 2 ; case 3
_021E632E:
	ldr r1, =ov53_021E84F8
	add r0, sp, #0x18
	ldrh r3, [r1, #0x28]
	add r2, sp, #0x18
	strh r3, [r0]
	ldrh r3, [r1, #0x2a]
	strh r3, [r0, #2]
	ldrh r3, [r1, #0x2c]
	ldrh r1, [r1, #0x2e]
	strh r3, [r0, #4]
	strh r1, [r0, #6]
	strb r7, [r0, #2]
	strb r6, [r0, #4]
	add r1, r4, #0
	ldr r0, [r4, #0x18]
	add r1, #0x1c
	bl AddWindow
	mov r1, #0
	mov r0, #0xc0
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x1c
	add r2, r1, #0
	add r3, r1, #0
	bl FillWindowPixelRect
	mov r1, #0
	str r1, [sp]
	mov r2, #0x11
	ldr r0, =0x00010200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r4, #0
	str r1, [sp, #0xc]
	lsl r2, r2, #4
	ldr r2, [r4, r2]
	add r0, #0x1c
	add r3, r1, #0
	bl AddTextPrinterParameterizedWithColor
	b _021E63E2
_021E6384:
	ldr r1, =ov53_021E84F8
	add r0, sp, #0x18
	ldrh r2, [r1, #0x30]
	cmp r5, #3
	strh r2, [r0]
	ldrh r2, [r1, #0x32]
	strh r2, [r0, #2]
	ldrh r2, [r1, #0x34]
	ldrh r1, [r1, #0x36]
	strh r2, [r0, #4]
	strh r1, [r0, #6]
	strb r7, [r0, #2]
	strb r6, [r0, #4]
	bne _021E63A6
	ldrb r1, [r0, #1]
	add r1, r1, #4
	strb r1, [r0, #1]
_021E63A6:
	add r1, r4, #0
	ldr r0, [r4, #0x18]
	add r1, #0x1c
	add r2, sp, #0x18
	bl AddWindow
	mov r1, #0
	mov r0, #0xc0
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r4, #0
	add r0, #0x1c
	add r2, r1, #0
	add r3, r1, #0
	bl FillWindowPixelRect
	mov r1, #0
	str r1, [sp]
	mov r2, #0x11
	ldr r0, =0x000F0200
	str r1, [sp, #4]
	str r0, [sp, #8]
	add r0, r4, #0
	str r1, [sp, #0xc]
	lsl r2, r2, #4
	ldr r2, [r4, r2]
	add r0, #0x1c
	add r3, r1, #0
	bl AddTextPrinterParameterizedWithColor
_021E63E2:
	mov r0, #0x11
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	bl String_Delete
	mov r0, #0x42
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021E6490
_021E63F6:
	add r0, #0x1c
	bl CopyWindowToVram
	mov r0, #0x42
	mov r1, #2
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021E6490
_021E6406:
	ldr r1, [sp, #0x14]
	add r2, r1, #0
	bl ov53_021E5EDC
	cmp r0, #1
	bne _021E6490
	mov r0, #0x42
	mov r1, #3
	lsl r0, r0, #2
	str r1, [r4, r0]
	cmp r5, #2
	bne _021E6490
	mov r1, #4
	str r1, [r4, r0]
	mov r0, #1
	str r0, [sp, #0x14]
	b _021E6490
_021E6428:
	ldr r0, =gSystem
	ldr r1, [r0, #0x48]
	mov r0, #1
	and r0, r1
	cmp r0, #1
	beq _021E643C
	mov r0, #2
	and r0, r1
	cmp r0, #2
	bne _021E6490
_021E643C:
	ldr r0, =gSystem + 0x40
	ldrh r0, [r0, #0x24]
	cmp r0, #0
	beq _021E6448
	mov r1, #1
	b _021E644A
_021E6448:
	mov r1, #0
_021E644A:
	mov r0, #0x5b
	lsl r0, r0, #2
	str r1, [r4, r0]
	ldr r0, =SEQ_SE_DP_SELECT
	bl PlaySE
	mov r0, #0x42
	mov r1, #4
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021E6490
_021E6460:
	ldr r1, [sp, #0x14]
	mov r2, #1
	bl ov53_021E5EDC
	cmp r0, #1
	bne _021E6490
	mov r0, #0x42
	mov r1, #5
	lsl r0, r0, #2
	str r1, [r4, r0]
	b _021E6490
_021E6476:
	add r0, #0x1c
	bl RemoveWindow
	ldr r0, [r4, #0x18]
	mov r1, #0
	bl BgClearTilemapBufferAndCommit
	mov r0, #0x42
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	mov r0, #1
	str r0, [sp, #0x14]
_021E6490:
	ldr r0, [sp, #0x14]
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
}
#endif

u32 ov53_021E64B4(OakSpeechApp_Data *data, u32 msgNum, u32 a2);
u32 ov53_021E64B4(OakSpeechApp_Data *data, u32 msgNum, u32 a2) {
    return ov53_021E628C(data, msgNum, a2, 0xFFFF, 0xFFFF);
}

extern const WindowTemplate ov53_021E8680[6];

void ov53_021E64C4(OakSpeechApp_Data *data, u32 a1, u32 a2, u32 a3, int windowCount);
#ifdef NONMATCHING
void ov53_021E64C4(OakSpeechApp_Data *data, u32 a1, u32 a2, u32 a3, int windowCount) {
    data->windows3CCount = windowCount;

    u32 y;
    if (windowCount == 2) {
        y = 4;
    }
    if (windowCount == 3) {
        y = 8;
    }

    for (int i = 0; i < windowCount; i++) {
        Window *window = &data->windows3C[i];
        const WindowTemplate *template = &ov53_021E8680[(windowCount - 2) * 3];

        String *temp = String_New(1024, data->heapId);
        ReadMsgDataIntoString(data->msgData, a1, temp);
        int stringWidth = FontID_String_GetWidth(0, temp, 0);

        AddWindow(data->bgConfig, window, template);
        FillWindowPixelRect(window, 0x0, 0, 0, 192, 192);
        AddTextPrinterParameterizedWithColor(window, 4, temp, (template->width * 8 - stringWidth) / 2, y, TEXT_SPEED_INSTANT, MAKE_TEXT_COLOR(15, 1, 0), NULL);
        CopyWindowToVram(window);

        String_Delete(temp);
    }
}
#else
asm void ov53_021E64C4(OakSpeechApp_Data *data, u32 a1, u32 a2, u32 a3, int windowCount) {
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	add r7, r0, #0
	ldr r0, [sp, #0x48]
	str r1, [sp, #0x28]
	str r2, [sp, #0x2c]
	str r3, [sp, #0x30]
	str r0, [sp, #0x48]
	str r0, [r7, #0x7c]
	cmp r0, #2
	bne _021E64DE
	mov r0, #4
	str r0, [sp, #0x10]
_021E64DE:
	ldr r0, [sp, #0x48]
	cmp r0, #3
	bne _021E64E8
	mov r0, #8
	str r0, [sp, #0x10]
_021E64E8:
	mov r0, #0
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x48]
	cmp r0, #0
	ble _021E65A6
	add r0, sp, #0x28
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x48]
	add r4, r7, #0
	sub r1, r0, #2
	mov r0, #0x18
	add r2, r1, #0
	mul r2, r0
	ldr r0, =ov53_021E8680
	add r4, #0x3c
	add r0, r0, r2
	str r0, [sp, #0x18]
	str r0, [sp, #0x14]
_021E650C:
	mov r0, #1
	ldr r1, [r7, #0]
	lsl r0, r0, #0xa
	bl String_New
	add r6, r0, #0
	mov r0, #1
	ldr r1, [sp, #0x24]
	lsl r0, r0, #8
	ldr r0, [r7, r0]
	ldr r1, [r1, #0]
	add r2, r6, #0
	bl ReadMsgDataIntoString
	mov r0, #0
	add r1, r6, #0
	add r2, r0, #0
	bl FontID_String_GetWidth
	str r0, [sp, #0x20]
	ldr r0, [r7, #0x18]
	ldr r2, [sp, #0x18]
	add r1, r4, #0
	bl AddWindow
	mov r1, #0
	mov r0, #0xc0
	str r0, [sp]
	str r0, [sp, #4]
	add r0, r4, #0
	add r2, r1, #0
	add r3, r1, #0
	bl FillWindowPixelRect
	ldr r0, [sp, #0x10]
	ldr r3, [sp, #0x14]
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, =0x000F0100
	mov r1, #4
	str r0, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	ldrb r3, [r3, #3]
	add r0, r4, #0
	add r2, r6, #0
	lsl r5, r3, #3
	ldr r3, [sp, #0x20]
	sub r5, r5, r3
	lsr r3, r5, #0x1f
	add r3, r5, r3
	asr r3, r3, #1
	bl AddTextPrinterParameterizedWithColor
	add r0, r4, #0
	bl CopyWindowToVram
	add r0, r6, #0
	bl String_Delete
	ldr r0, [sp, #0x24]
	add r4, #0x10
	add r0, r0, #4
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x18]
	add r0, #8
	str r0, [sp, #0x18]
	ldr r0, [sp, #0x14]
	add r0, #8
	str r0, [sp, #0x14]
	ldr r0, [sp, #0x1c]
	add r1, r0, #1
	ldr r0, [sp, #0x48]
	str r1, [sp, #0x1c]
	cmp r1, r0
	blt _021E650C
_021E65A6:
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	nop
}
#endif

void OakSpeech_FreeWindows(OakSpeechApp_Data *data);
void OakSpeech_FreeWindows(OakSpeechApp_Data *data) {
    for (int i = 0; i < data->windows3CCount; i++) {
        RemoveWindow(&data->windows3C[i]);
    }
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_0);
}

void ov53_021E66A8(OakSpeechApp_Data *data, int a1);
void ov53_021E66E8(OakSpeechApp_Data *data, int a1, int a2);
void ov53_021E67C4(OakSpeechApp_Data *data, int a1);

void ov53_021E65E0(OakSpeechApp_Data *data) {
    // FIXME: Use NAIX constants once a/1/2/0 has been dumped.

    GfGfxLoader_LoadCharData(NARC_a_1_2_0, 0, data->bgConfig, GF_BG_LYR_MAIN_3, 0, 0, FALSE, data->heapId);
    BG_ClearCharDataRange(GF_BG_LYR_MAIN_0, 32, 0, data->heapId);
    GfGfxLoader_LoadCharData(NARC_a_1_2_0, 32, data->bgConfig, GF_BG_LYR_SUB_3, 0, 0, FALSE, data->heapId);

    s32 palette1, palette2;
    if (gGameVersion == VERSION_HEARTGOLD) {
        palette1 = 1;
        palette2 = 30;
    } else {
        palette1 = 2;
        palette2 = 31;
    }
    GfGfxLoader_GXLoadPal(NARC_a_1_2_0, palette1, GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_0_OFFSET, 0x60, data->heapId);
    GfGfxLoader_GXLoadPal(NARC_a_1_2_0, palette2, GF_PAL_LOCATION_SUB_BG, GF_PAL_SLOT_0_OFFSET, 0xA0, data->heapId);

    NNSG2dPaletteData *g2dPaletteData;
    void *paletteData = GfGfxLoader_GetPlttData(NARC_a_1_2_0, palette2, &g2dPaletteData, data->heapId);
    data->unk136 = *(u16*)(g2dPaletteData->pRawData + 0x18);
    FreeToHeap(paletteData);

    ov53_021E66A8(data, 1);
    ov53_021E66E8(data, 0, 0);
    ov53_021E67C4(data, 0);

    BG_SetMaskColor(GF_BG_LYR_MAIN_0, RGB_BLACK);
    BG_SetMaskColor(GF_BG_LYR_SUB_0, RGB_BLACK);
}

void ov53_021E66A8(OakSpeechApp_Data *data, int a1) {
    extern const u32 ov53_021E856C[6];
    // FIXME: Pikalax is gonna hate this one.
    u32 screenDataMembers[6];
    screenDataMembers = ov53_021E856C;

    if (a1 < 6) {
        GfGfxLoader_LoadScrnData(NARC_a_1_2_0, screenDataMembers[a1], data->bgConfig, GF_BG_LYR_MAIN_3, 0, 0, FALSE, data->heapId);
    }
}

extern const s32 ov53_021E86F0[10][2];

void ov53_021E66E8(OakSpeechApp_Data *data, int a1, int a2) {
    const s32 members[10][2] = {
        { 0, 0 },
        { 10, 11 },
        { 12, 16 },
        { 13, 16 },
        { 14, 16 },
        { 15, 16 },
        { 17, 21 },
        { 18, 21 },
        { 19, 21 },
        { 20, 21 },
    };

    if (a1 != 0 && a2 < 12) {
        GfGfxLoader_LoadCharData(NARC_a_1_2_0, members[a1][0], data->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, FALSE, data->heapId);
        GfGfxLoader_GXLoadPal(NARC_a_1_2_0, members[a1][1], GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_7_OFFSET, 0x20, data->heapId);
        GfGfxLoader_LoadScrnData(NARC_a_1_2_0, 9, data->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, FALSE, data->heapId);
        ov53_021E60E8(data, GF_BG_LYR_MAIN_1, 7);
    }
    if (a2 != 0 && a2 < 12) {
        GfGfxLoader_LoadCharData(NARC_a_1_2_0, members[a2][0], data->bgConfig, GF_BG_LYR_MAIN_2, 0, 0, FALSE, data->heapId);
        GfGfxLoader_GXLoadPal(NARC_a_1_2_0, members[a2][1], GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_8_OFFSET, 0x20, data->heapId);
        GfGfxLoader_LoadScrnData(NARC_a_1_2_0, 9, data->bgConfig, GF_BG_LYR_MAIN_2, 0, 0, FALSE, data->heapId);
        ov53_021E60E8(data, GF_BG_LYR_MAIN_2, 8);
    }
}

void ov53_021E67C4(OakSpeechApp_Data *data, int a1) {
    extern const u32 ov53_021E8558[5];
    // FIXME: Pikalax is gonna hate this one.
    u32 screenDataMembers[5];
    screenDataMembers = ov53_021E8558;

    if (a1 >= 5) {
        return;
    }

    GfGfxLoader_LoadScrnData(NARC_a_1_2_0, screenDataMembers[a1], data->bgConfig, GF_BG_LYR_SUB_3, 0, 0, FALSE, data->heapId);
    if (a1 == 1) {
        ov53_021E60E8(data, GF_BG_LYR_SUB_3, 3);
    } else if (a1 == 2) {
        ov53_021E60E8(data, GF_BG_LYR_SUB_3, 2);
    }
}

void ov53_021E6824(OakSpeechApp_Data *data, int a1);
void ov53_021E6824(OakSpeechApp_Data *data, int a1) {
    extern const u32 ov53_021E8584[3][2];
    // FIXME: Pikalax is gonna hate this one.
    u32 dataMembers[3][2];
    dataMembers = ov53_021E8584;

    GfGfxLoader_LoadScrnData(NARC_a_1_2_0, dataMembers[a1][0], data->bgConfig, GF_BG_LYR_SUB_2, 0, 0, FALSE, data->heapId);
    ov53_021E60E8(data, GF_BG_LYR_SUB_2, 7);
    GfGfxLoader_GXLoadPal(NARC_a_1_2_0, 33, GF_PAL_LOCATION_SUB_BG, GF_PAL_SLOT_7_OFFSET, 0x60, data->heapId);
    BG_ClearCharDataRange(GF_BG_LYR_SUB_2, 32, 0, data->heapId);
    GfGfxLoader_LoadCharData(NARC_a_1_2_0, dataMembers[a1][1], data->bgConfig, GF_BG_LYR_SUB_2, 0, 0, FALSE, data->heapId);
    ScheduleSetBgPosText(data->bgConfig, GF_BG_LYR_SUB_1, BG_POS_OP_SET_Y, 0);

    if (a1 == 1) {
        if (data->playerGender == 0) {
            ScheduleSetBgPosText(data->bgConfig, GF_BG_LYR_SUB_0, BG_POS_OP_SET_X, 136);
            ScheduleSetBgPosText(data->bgConfig, GF_BG_LYR_SUB_2, BG_POS_OP_SET_X, 136);
            ScheduleSetBgPosText(data->bgConfig, GF_BG_LYR_SUB_1, BG_POS_OP_SET_X, 136);
        } else {
            ScheduleSetBgPosText(data->bgConfig, GF_BG_LYR_SUB_0, BG_POS_OP_SET_X, 0);
            ScheduleSetBgPosText(data->bgConfig, GF_BG_LYR_SUB_2, BG_POS_OP_SET_X, 0);
            ScheduleSetBgPosText(data->bgConfig, GF_BG_LYR_SUB_1, BG_POS_OP_SET_X, 0);
        }
    }
}

void ov53_021E6908(u8 *a0, u32 a1);
void ov53_021E6908(u8 *a0, u32 a1) {
    extern const u32 ov53_021E86B0[4][4];

    // FIXME: a0 is a struct.

    a0[3] = 0;
    a0[0] = 0;
    a0[1] = ov53_021E86B0[a1][1];
    a0[6] = 0;
    a0[4] = 0;
    a0[5] = 16;
    a0[2] = 0;
}

void ov53_021E6928(OakSpeechApp_Data *data, u32 a1);
void ov53_021E6928(OakSpeechApp_Data *data, u32 a1) {
    extern const u32 ov53_021E86B0[4][4];

    data->unk160 = 0;
    data->numButtons = ov53_021E86B0[a1][1];
    data->unk164 = 0;
    data->unk165 = 16;

    GfGfxLoader_LoadScrnData(NARC_a_1_2_0, ov53_021E86B0[a1][0], data->bgConfig, GF_BG_LYR_SUB_1, 0, 0, FALSE, data->heapId);
    GfGfxLoader_LoadCharData(NARC_a_1_2_0, 42, data->bgConfig, GF_BG_LYR_SUB_1, 0, 0, FALSE, data->heapId);
}

extern const u32 ov53_021E8604[3][3];
extern const TouchscreenHitbox ov53_021E8650[12];

int ov53_021E6988(OakSpeechApp_Data *data, u32 a1);
int ov53_021E6988(OakSpeechApp_Data *data, u32 a1) {
    int ret = -1;

    // FIXME: Pikalax is gonna hate this, probably.
    TouchscreenHitbox hitboxes[12];
    hitboxes = ov53_021E8650;

    if (data->unk166 != 0) {
        data->unk166++;
        if (data->unk166 > 20) {
            data->unk166 = 0;
            ret = data->currentButtonIndex;
        }
    } else {
        if (gSystem.touchNew != 0) {
            int rect = TouchscreenHitbox_FindRectAtTouchNew(&hitboxes[a1 * 4]);
            if (rect != -1) {
                ov53_021E6928(data, a1);
                ToggleBgLayer(GF_BG_LYR_SUB_1, GF_PLANE_TOGGLE_ON);

                data->currentButtonIndex = rect;
                ScheduleSetBgPosText(data->bgConfig, GF_BG_LYR_SUB_1, BG_POS_OP_SET_Y, ov53_021E8604[a1][data->currentButtonIndex]);

                data->unk166 = 1;
                data->unk165 = 2;
                PlaySE(SEQ_SE_DP_SELECT);
            }
        } else {
            if (data->unk162 == 0) {
                if ((gSystem.newKeys & (PAD_KEY_UP | PAD_KEY_DOWN | PAD_BUTTON_B | PAD_BUTTON_A)) != 0) {
                    PlaySE(SEQ_SE_DP_SELECT);
                    ov53_021E6928(data, a1);
                    ToggleBgLayer(GF_BG_LYR_SUB_1, GF_PLANE_TOGGLE_ON);
                    data->unk162 = 1;
                }
            } else {
                if (gSystem.newKeys & PAD_KEY_UP) {
                    if (data->currentButtonIndex != 0) {
                        data->currentButtonIndex--;
                        ScheduleSetBgPosText(data->bgConfig, GF_BG_LYR_SUB_1, BG_POS_OP_SET_Y, ov53_021E8604[a1][data->currentButtonIndex]);
                        PlaySE(SEQ_SE_DP_SELECT);
                    }
                } else if (gSystem.newKeys & PAD_KEY_DOWN) {
                    if (data->currentButtonIndex != data->numButtons - 1) {
                        data->currentButtonIndex++;
                        ScheduleSetBgPosText(data->bgConfig, GF_BG_LYR_SUB_1, BG_POS_OP_SET_Y, ov53_021E8604[a1][data->currentButtonIndex]);
                        PlaySE(SEQ_SE_DP_SELECT);
                    }
                } else if (gSystem.newKeys & PAD_BUTTON_A) {
                    data->unk166 = 1;
                    data->unk165 = 2;
                    PlaySE(SEQ_SE_DP_SELECT);
                } else if (gSystem.newKeys & PAD_BUTTON_B) {
                    data->currentButtonIndex = data->numButtons - 1;
                    data->unk166 = 1;
                    data->unk165 = 2;
                    ScheduleSetBgPosText(data->bgConfig, GF_BG_LYR_SUB_1, BG_POS_OP_SET_Y, ov53_021E8604[a1][data->currentButtonIndex]);
                    PlaySE(SEQ_SE_DP_SELECT);
                }
            }
        }
    }

    if (data->unk166 != 0) {
        data->unk164++;
        if (data->unk164 > data->unk165) {
            data->unk167 ^= 1;
            data->unk164 = 0;
            if (data->unk167 != 0) {
                ToggleBgLayer(GF_BG_LYR_SUB_1, GF_PLANE_TOGGLE_ON);
            } else {
                ToggleBgLayer(GF_BG_LYR_SUB_1, GF_PLANE_TOGGLE_OFF);
            }
        }
    }

    return ret;
}

u16 GetAdditiveColor(int firstColor, int secondColor);
u16 GetAdditiveColor(int firstColor, int secondColor) {
    int red = (firstColor & 0x1F);
    int green = ((firstColor >> 5) & 0x1F);
    int blue = (firstColor >> 10);

    red += secondColor;
    green += secondColor;
    blue += secondColor;

    if (red > 0x1F) {
        red = 0x1F;
    } else if (red < 0) {
        red = 0;
    }
    if (green > 0x1F) {
        green = 0x1F;
    } else if (green < 0) {
        green = 0;
    }
    if (blue > 0x1F) {
        blue = 0x1F;
    } else if (blue < 0) {
        blue = 0;
    }

    return (blue << 10 | green << 5 | red);
}

extern const u32 ov53_021E8508[2];

void ov53_021E6BEC(OakSpeechApp_Data *data, u32 a1);
void ov53_021E6BEC(OakSpeechApp_Data *data, u32 a1) {
    u8 cVar1 = data->currentButtonIndex;
    u32 cVar5 = 0;

    BOOL bVar2 = TRUE;
    if (cVar1 != 0 && cVar1 != 1) {
        bVar2 = FALSE;
    }
    GF_ASSERT(bVar2);

    if (a1 == 0) {
        u32 uVar4 = data->unk168++;
        cVar5 = FX_Whole(8 * GF_SinDeg(uVar4 * 10));
    } else {
        data->unk168 = 0;
    }

    u16 colors[2];

    colors[0] = GetAdditiveColor(data->unk136, (s8)cVar5);
    colors[1] = GetAdditiveColor(RGB(31, 7, 7), 0);
    BG_LoadPlttData(GF_PAL_LOCATION_SUB_BGEXT, colors, sizeof(colors), (u16)(ov53_021E8508[data->currentButtonIndex] * 2));

    colors[0] = data->unk136;
    colors[1] = RGB(27, 28, 28);
    BG_LoadPlttData(GF_PAL_LOCATION_SUB_BGEXT, colors, sizeof(colors), (u16)(ov53_021E8508[data->currentButtonIndex == 0] * 2));
}

void ov53_021E6CB0(OakSpeechApp_Data *data);
void ov53_021E6CB0(OakSpeechApp_Data *data) {
	u16 colors[2];
	colors[0] = data->unk136;
	colors[1] = RGB(27, 28, 28);
	BG_LoadPlttData(GF_PAL_LOCATION_SUB_BGEXT, colors, sizeof(colors), 0x18);
	BG_LoadPlttData(GF_PAL_LOCATION_SUB_BGEXT, colors, sizeof(colors), 0x1C);
}

extern const TouchscreenHitbox ov53_021E8530[3];

BOOL OakSpeech_PromptPlayerForGender(OakSpeechApp_Data *data);
BOOL OakSpeech_PromptPlayerForGender(OakSpeechApp_Data *data) {
    BOOL done = FALSE;

    // FIXME: Pikalax is gonna hate this, probably.
    TouchscreenHitbox hitboxes[3];
    hitboxes = ov53_021E8530;

    if (gSystem.touchNew != 0) {
        int rect = TouchscreenHitbox_FindRectAtTouchNew(hitboxes);
        if (rect != -1) {
            data->currentButtonIndex = rect;
            data->unk166 = 1;
            data->unk165 = 2;
            ov53_021E6BEC(data, 1);
            PlaySE(SEQ_SE_DP_SELECT);
            data->unk17C = rect;
            done = TRUE;
        }
    } else {
        if (data->unk162 == 0) {
            if ((gSystem.newKeys & (PAD_KEY_LEFT | PAD_KEY_RIGHT | PAD_BUTTON_A)) != 0) {
                PlaySE(SEQ_SE_DP_SELECT);
                data->unk162 = 1;
                ov53_021E6BEC(data, 1);
            }
        } else {
            ov53_021E6BEC(data, 0);
            if (gSystem.newKeys & PAD_KEY_LEFT) {
                if (data->currentButtonIndex != 0) {
                    data->currentButtonIndex--;
                    PlaySE(SEQ_SE_DP_SELECT);
                }
            } else if (gSystem.newKeys & PAD_KEY_RIGHT) {
                if (data->currentButtonIndex != data->numButtons - 1) {
                    data->currentButtonIndex++;
                    PlaySE(SEQ_SE_DP_SELECT);
                }
            } else if (gSystem.newKeys & PAD_BUTTON_A) {
                data->unk162 = 0;
                data->unk166 = 1;
                data->unk165 = 2;
                ov53_021E6BEC(data, 1);
                PlaySE(SEQ_SE_DP_SELECT);
                done = TRUE;
                data->unk17C = data->currentButtonIndex;
            }
        }
    }

    return done;
}

void ov53_021E6DF0(OakSpeechApp_Data *data);
void ov53_021E6DF0(OakSpeechApp_Data *data) {
	data->unk140 = 0;
	data->unk144 = 0;
}

extern const u32 ov53_021E859C[6];
extern const u32 ov53_021E85B4[6];

BOOL ov53_021E6E00(OakSpeechApp_Data *data);
#ifdef NONMATCHING
BOOL ov53_021E6E00(OakSpeechApp_Data *data) {
    u32 yeah[6];
    if (data->unk144 != 0) {
        data->unk144--;
    } else {
        data->unk140++;
        data->unk144 = 8;
    }
    if (data->playerGender == 0) {
        yeah = ov53_021E859C;
    } else {
        yeah = ov53_021E85B4;
    }

    s32 member = yeah[data->unk140];
    BOOL ret;
    if (member == 0xFF) {
        ret = TRUE;
    } else {
        ret = FALSE;
        GfGfxLoader_LoadCharData(NARC_a_1_2_0, member, data->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, FALSE, data->heapId);
    }

    return ret;
}
#else
asm BOOL ov53_021E6E00(OakSpeechApp_Data *data) {
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	mov r1, #0x51
	add r2, r0, #0
	lsl r1, r1, #2
	ldr r0, [r2, r1]
	mov r7, #0
	cmp r0, #0
	beq _021E6E16
	sub r0, r0, #1
	b _021E6E22
_021E6E16:
	sub r0, r1, #4
	ldr r0, [r2, r0]
	add r3, r0, #1
	sub r0, r1, #4
	str r3, [r2, r0]
	mov r0, #8
_021E6E22:
	mov r3, #0x4d
	lsl r3, r3, #2
	str r0, [r2, r1]
	ldrh r0, [r2, r3]
	cmp r0, #0
	bne _021E6E34
	ldr r6, =ov53_021E859C
	add r5, sp, #0x28
	b _021E6E38
_021E6E34:
	ldr r6, =ov53_021E85B4
	add r5, sp, #0x10
_021E6E38:
	add r4, r5, #0
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	ldmia r6!, {r0, r1}
	stmia r5!, {r0, r1}
	ldmia r6!, {r0, r1}
	add r3, #0xc
	stmia r5!, {r0, r1}
	ldr r0, [r2, r3]
	lsl r0, r0, #2
	ldr r1, [r4, r0]
	cmp r1, #0xff
	bne _021E6E56
	mov r7, #1
	b _021E6E6C
_021E6E56:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	str r0, [sp, #8]
	ldr r0, [r2, #0]
	mov r3, #1
	str r0, [sp, #0xc]
	ldr r2, [r2, #0x18]
	mov r0, #0x78
	bl GfGfxLoader_LoadCharData
_021E6E6C:
	add r0, r7, #0
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
}
#endif

u32 ov53_021E6E7C(void);
u32 ov53_021E6E7C(void) {
    u32 ret = msg_0219_00001;

    RTCDate date;
    RTCTime time;
    GF_RTC_CopyDateTime(&date, &time);
    u32 timeValue = time.hour * 100 + time.minute;

    if (timeValue >= 400 && timeValue <= 1059) { // 4:00am-10:59am
        ret = msg_0219_00001;
    } else if (timeValue >= 1100 && timeValue <= 1559) { // 11:00am-3:59pm
        ret = msg_0219_00002;
    } else if (timeValue >= 1600 && timeValue <= 1859) { // 4:00pm-6:59pm
        ret = msg_0219_00003;
    } else if (timeValue >= 1900 && timeValue <= 2359) { // 7:00pm-11:59pm
        ret = msg_0219_00004;
    } else if (timeValue <= 359) { // 12:00am-3:59am
        ret = msg_0219_00005;
    }

    return ret;
}

extern const s16 ov53_021E853C[2][3];

BOOL ov53_021E6F00(OakSpeechApp_Data *data, u32 bgId, u32 a2);
BOOL ov53_021E6F00(OakSpeechApp_Data *data, u32 bgId, u32 a2) {
	switch (data->unk174) {
		case 0:
			data->unk174 = 1;
			data->unk176 = ov53_021E853C[a2][0];
			break;
		case 1: {
			data->unk176 += ov53_021E853C[a2][2];
			if (ov53_021E853C[a2][2] > 0) {
				if (data->unk176 >= ov53_021E853C[a2][1]) {
					data->unk176 = ov53_021E853C[a2][1];
					data->unk174 = 2;
				}
			} else if (data->unk176 <= ov53_021E853C[a2][1]) {
				data->unk176 = ov53_021E853C[a2][1];
				data->unk174 = 2;
			}

			BgSetPosTextAndCommit(data->bgConfig, bgId, BG_POS_OP_SET_X, data->unk176);
			break;
		}
		case 2:
			data->unk174 = 0;
			return TRUE;
	}

	return FALSE;
}

void ov53_021E7D04(OakSpeechApp_Data *data);
void ov53_021E7D58(OakSpeechApp_Data *data);
void ov53_021E7E08(OakSpeechApp_Data *data, u32 action);
extern ov53_021E80B8();
extern ov53_021E816C();
extern ov53_021E81F4();
extern ov53_021E8248();

BOOL ov53_021E6F9C(OakSpeechApp_Data *data) {
    BOOL ret = FALSE;

    switch (data->state) {
        case 0:
            ToggleBgLayer(GF_BG_LYR_SUB_2, GF_PLANE_TOGGLE_OFF);
            sub_02004EC4(2, SEQ_GS_POKEMON_THEME, 1);
            StopBGM(SEQ_GS_POKEMON_THEME, 0);
            PlayBGM(SEQ_GS_STARTING);
            data->state = 7;
            break;

        case 7:
            ov53_021E6824(data, 0);
            ov53_021E66A8(data, 1);
            ov53_021E67C4(data, 0);
            ToggleBgLayer(GF_BG_LYR_MAIN_3, GF_PLANE_TOGGLE_ON);
            ToggleBgLayer(GF_BG_LYR_MAIN_0, GF_PLANE_TOGGLE_ON);
            ToggleBgLayer(GF_BG_LYR_SUB_0, GF_PLANE_TOGGLE_ON);
            ToggleBgLayer(GF_BG_LYR_SUB_3, GF_PLANE_TOGGLE_ON);
            BeginNormalPaletteFade(0, 1, 1, RGB_BLACK, 6, 1, data->heapId);
            data->state = 1;
            break;

        case 1:
            if (IsPaletteFadeFinished() != TRUE) {
                break;
            }

            if (OakSpeech_WaitFrames(data, 40) != TRUE) {
                break;
            }

            data->state = 2;
            break;

        case 2:
            if (ov53_021E64B4(data, msg_0219_00007, 2) != TRUE) {
                break;
            }

            ToggleBgLayer(GF_BG_LYR_SUB_2, GF_PLANE_TOGGLE_ON);
            data->state = 3;
            ov53_021E64C4(data, msg_0219_00044, msg_0219_00045, msg_0219_00046, 3);
            data->unk162 = 0;
            data->currentButtonIndex = 0;
            break;

        case 3:
            if (ov53_021E6988(data, 0) == -1) {
                break;
            }

            data->state = 4;
            break;

        case 4:
            if (ov53_021E64B4(data, msg_0219_00007, 2) != TRUE) {
                break;
            }

            OakSpeech_FreeWindows(data);
            ToggleBgLayer(GF_BG_LYR_SUB_0, GF_PLANE_TOGGLE_OFF);
            ToggleBgLayer(GF_BG_LYR_SUB_2, GF_PLANE_TOGGLE_OFF);
            ToggleBgLayer(GF_BG_LYR_SUB_1, GF_PLANE_TOGGLE_OFF);

            data->state = 5;
            break;

        case 5:
            BeginNormalPaletteFade(0, 0, 0, RGB_BLACK, 6, 1, data->heapId);
            data->state = 6;
            break;

        case 6:
            if (IsPaletteFadeFinished() != TRUE) {
                break;
            }

            switch (data->currentButtonIndex) {
                case 0: // Control info
                    data->state = 8;
                    break;
                case 1: // Adventure info
                    data->state = 34;
                    break;
                case 2: // No info needed
                    data->state = 44;
                    break;
            }
            break;

        case 8:
            BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_0);
            ov53_021E66A8(data, 1);
            ov53_021E67C4(data, 1);
            ov53_021E7E08(data, 1);
            ToggleBgLayer(GF_BG_LYR_SUB_0, GF_PLANE_TOGGLE_ON);
            ToggleBgLayer(GF_BG_LYR_SUB_3, GF_PLANE_TOGGLE_ON);
            BeginNormalPaletteFade(0, 1, 1, RGB_BLACK, 6, 1, data->heapId);
            data->state = 9;
            break;

        case 9:
            if (IsPaletteFadeFinished() != TRUE) {
                break;
            }

            data->state = 11;
            break;

        case 11:
            if (ov53_021E64B4(data, msg_0219_00009, 0) != TRUE) {
                break;
            }

            data->state = 12;
            break;

        case 12:
            if (ov53_021E64B4(data, msg_0219_00010, 0) != TRUE) {
                break;
            }

            data->state = 13;
            break;

        case 13:
            if (ov53_021E64B4(data, msg_0219_00011, 0) != TRUE) {
                break;
            }

            data->state = 14;
            break;

        case 14:
            if (ov53_021E64B4(data, msg_0219_00012, 0) != TRUE) {
                break;
            }

            data->state = 15;
            break;

        case 15:
            if (ov53_021E64B4(data, msg_0219_00023, 2) != TRUE) {
                break;
            }

            ToggleBgLayer(GF_BG_LYR_MAIN_0, GF_PLANE_TOGGLE_ON);
            data->state = 16;
            break;

        case 16:
            if (ov53_021E611C(data, msg_0219_00025, 0) != TRUE) {
                break;
            }

            data->state = 17;
            break;

        case 17:
            if (ov53_021E64B4(data, msg_0219_00013, 0) != TRUE) {
                break;
            }

            ov53_021E66A8(data, 2);
            data->state = 18;
            break;

        case 18:
            if (ov53_021E64B4(data, msg_0219_00014, 3) != TRUE) {
                break;
            }

            ov53_021E66A8(data, 1);
            data->state = 19;
            break;

        case 19:
            if (ov53_021E64B4(data, msg_0219_00015, 0) != TRUE) {
                break;
            }

            ov53_021E66A8(data, 3);
            data->state = 20;
            break;

        case 20:
            if (ov53_021E64B4(data, msg_0219_00016, 3) != TRUE) {
                break;
            }

            ov53_021E66A8(data, 4);
            data->state = 21;
            break;

        case 21:
            if (ov53_021E64B4(data, msg_0219_00017, 3) != TRUE) {
                break;
            }

            data->state = 22;
            ToggleBgLayer(GF_BG_LYR_MAIN_0, GF_PLANE_TOGGLE_ON);
            ov53_021E66A8(data, 1);
            break;

        case 22:
            if (ov53_021E611C(data, msg_0219_00026, 1) != TRUE) {
                break;
            }

            data->state = 23;
            break;

        case 23:
            ov53_021E7E08(data, 0);
            BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_0);
            ov53_021E816C(data->unk178, 7);
            ov53_021E81F4(data->unk178, NARC_msg_msg_0219_bin, msg_0219_00061, msg_0219_00062);
            data->state = 24;
            break;

        case 24:
            switch (ov53_021E8248(data->unk178)) {
                case 1: // Yes
                    data->state = 27;
                    break;
                case 2: // No
                    data->state = 29;
                    break;
            }
            break;

        // 25, 26 don't exist

        case 27:
            if (ov53_021E5EDC(data, 6, 1) != TRUE) {
                break;
            }

            BeginNormalPaletteFade(0, 0, 0, RGB_BLACK, 6, 1, data->heapId);
            data->state = 28;
            break;

        case 28:
            if (IsPaletteFadeFinished() != TRUE) {
                break;
            }

            ov53_021E7D58(data);
            data->state = 7;
            break;

        case 29:
            if (ov53_021E5EDC(data, 6, 1) != TRUE) {
                break;
            }

            ov53_021E7E08(data, 3);
            ToggleBgLayer(GF_BG_LYR_SUB_2, GF_PLANE_TOGGLE_OFF);
            ov53_021E7D58(data);
            data->state = 8;
            break;

        // 30-33 don't exist

        case 34:
            ov53_021E66A8(data, 5);
            ov53_021E67C4(data, 2);
            ov53_021E7D58(data);
            ov53_021E7E08(data, 1);
            ToggleBgLayer(GF_BG_LYR_SUB_0, GF_PLANE_TOGGLE_ON);
            ToggleBgLayer(GF_BG_LYR_SUB_3, GF_PLANE_TOGGLE_ON);
            BeginNormalPaletteFade(0, 1, 1, RGB_BLACK, 6, 1, data->heapId);
            data->state = 35;
            break;

        case 35:
            if (IsPaletteFadeFinished() != TRUE) {
                break;
            }

            data->state = 36;
            break;

        case 36:
            if (ov53_021E64B4(data, msg_0219_00028, 1) != TRUE) {
                break;
            }

            data->state = 37;
            break;

        case 37:
            if (ov53_021E64B4(data, msg_0219_00029, 1) != TRUE) {
                break;
            }

            data->state = 38;
            break;

        case 38:
            if (ov53_021E64B4(data, msg_0219_00030, 1) != TRUE) {
                break;
            }

            data->state = 39;
            break;

        case 39:
            if (ov53_021E64B4(data, msg_0219_00031, 1) != TRUE) {
                break;
            }

            data->state = 40;
            break;

        case 40:
            if (ov53_021E64B4(data, msg_0219_00032, 1) != TRUE) {
                break;
            }

            data->state = 41;
            break;

        case 41:
            if (ov53_021E64B4(data, msg_0219_00033, 1) != TRUE) {
                break;
            }

            data->state = 42;
            break;

        case 42:
            BeginNormalPaletteFade(0, 0, 0, RGB_BLACK, 6, 1, data->heapId);
            data->state = 43;
            break;

        case 43:
            if (IsPaletteFadeFinished() != TRUE) {
                break;
            }

            ov53_021E7D58(data);
            ov53_021E7E08(data, 0);
            ToggleBgLayer(GF_BG_LYR_MAIN_0, GF_PLANE_TOGGLE_ON);
            data->state = 7;
            break;

        case 44:
            ov53_021E7D58(data);
            ov53_021E7E08(data, 1);
            ov53_021E66A8(data, 0);
            BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_1);
            ToggleBgLayer(GF_BG_LYR_MAIN_0, GF_PLANE_TOGGLE_ON);
            ToggleBgLayer(GF_BG_LYR_MAIN_3, GF_PLANE_TOGGLE_OFF);
            ToggleBgLayer(GF_BG_LYR_SUB_0, GF_PLANE_TOGGLE_ON);
            ToggleBgLayer(GF_BG_LYR_SUB_3, GF_PLANE_TOGGLE_ON);
            data->state = 45;
            BeginNormalPaletteFade(0, 1, 1, RGB_BLACK, 6, 1, data->heapId);
            break;

        case 45:
            if (IsPaletteFadeFinished() != TRUE) {
                break;
            }

            if (OakSpeech_WaitFrames(data, 40) != TRUE) {
                break;
            }

            data->state = 46;
            data->unk170 = ov53_021E6E7C();
            break;

        case 46:
            if (ov53_021E611C(data, data->unk170, 1) != TRUE) {
                break;
            }

            GF_SndStartFadeOutBGM(0, 6);
            data->state = 47;
            break;

        case 47:
            if (GF_SndGetFadeTimer() != 0) {
                break;
            }

            StopBGM(SEQ_GS_STARTING, 0);
            PlayBGM(SEQ_GS_STARTING2);
            ov53_021E66E8(data, 1, 0);
            ToggleBgLayer(GF_BG_LYR_MAIN_3, GF_PLANE_TOGGLE_ON);
            ToggleBgLayer(GF_BG_LYR_MAIN_1, GF_PLANE_TOGGLE_ON);
            StartBrightnessTransition(16, 0, -16, (GXBlendPlaneMask)(GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ), SCREEN_MASK_MAIN);
            data->state = 48;
            break;

        case 48:
            if (IsBrightnessTransitionActive(SCREEN_MASK_MAIN)) {
                data->state = 49;
            }
            break;

        case 49:
            if (ov53_021E611C(data, msg_0219_00006, 1) == TRUE) {
                data->state = 50;
            }
            break;

        case 50:
            if (ov53_021E6F00(data, GF_BG_LYR_MAIN_1, 0) == TRUE) {
                data->state = 51;
            }
            break;

        case 51:
            if (ov53_021E611C(data, msg_0219_00034, 1) != TRUE) {
                break;
            }

            Set2dSpriteAnimSeqNo(data->sprites[5], 3);
            Sprite_SetPalIndex(data->sprites[5], 5);
            Set2dSpriteVisibleFlag(data->sprites[5], TRUE);
            data->state = 52;
            break;

        case 52:
            if (OakSpeech_WaitFrames(data, 30) != TRUE) {
                break;
            }

            StartBrightnessTransition(4, 0, 16, (GXBlendPlaneMask)(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ), SCREEN_MASK_MAIN);
            StartBrightnessTransition(4, 0, 16, (GXBlendPlaneMask)(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ), SCREEN_MASK_SUB);
            PlaySE(SEQ_SE_DP_BOWA2);
            data->unk140 = 0;
            data->state = 53;
            break;

        case 53:
            if (IsBrightnessTransitionActive(SCREEN_MASK_MAIN) != TRUE || IsBrightnessTransitionActive(SCREEN_MASK_SUB) != TRUE) {
                break;
            }

            Set2dSpriteAnimSeqNo(data->sprites[5], 1);
            Sprite_SetPalIndex(data->sprites[5], 4);

            data->unk140 = 16;
            G2_SetBlendBrightness(16, data->unk140);

            data->state = 54;
            break;

        case 54:
            if (Sprite_IsCellAnimationRunning(data->sprites[5])) {
                break;
            }

            G2_SetBlendBrightness(16, --data->unk140);
            if (data->unk140 == 0) {
                Set2dSpriteAnimSeqNo(data->sprites[5], 2);
                PlayCry(SPECIES_MARILL, 0);
                data->state = 55;
            }

            break;

        case 55:
            if (OakSpeech_WaitFrames(data, 40) != TRUE) {
                break;
            }

            data->state = 56;
            break;

        case 56:
            if (ov53_021E611C(data, msg_0219_00035, 1) != TRUE) {
                break;
            }

            data->state = 57;
            break;

        case 57:
            if (ov53_021E5EDC(data, 101, 1) != TRUE) {
                break;
            }

            data->state = 58;
            break;

        case 58:
            if (OakSpeech_WaitFrames(data, 30) != TRUE) {
                break;
            }

            data->state = 59;
            break;

        case 59:
            if (ov53_021E6F00(data, GF_BG_LYR_MAIN_1, 1) == TRUE) {
                data->state = 60;
            }
            break;

        case 60:
            if (ov53_021E611C(data, msg_0219_00036, 1) != TRUE) {
                break;
            }

            data->state = 61;
            data->currentButtonIndex = 0;
            data->numButtons = 2;
            break;

        case 61:
            if (ov53_021E611C(data, msg_0219_00037, 1) != TRUE) {
                break;
            }

            data->state = 62;
            BeginNormalPaletteFade(4, 0, 0, RGB_BLACK, 6, 1, data->heapId);
            break;

        case 62:
            if (IsPaletteFadeFinished() == TRUE) {
                data->state = 63;
            }
            break;

        case 63:
            ov53_021E7E08(data, 0);
            ToggleBgLayer(GF_BG_LYR_SUB_0, GF_PLANE_TOGGLE_OFF);
            ov53_021E67C4(data, 4);
            ov53_021E80B8(data, 2);
            BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_2);
            BeginNormalPaletteFade(4, 1, 1, RGB_BLACK, 6, 1, data->heapId);
            data->state = 64;
            break;

        case 64:
            if (IsPaletteFadeFinished() != TRUE) {
                break;
            }

            data->currentButtonIndex = data->unk17C;
            data->state = 65;
            break;

        case 65:
            if (!OakSpeech_PromptPlayerForGender(data)) {
                break;
            }

            data->state = 66;
            data->playerGender = data->currentButtonIndex;
            break;

        case 66:
            FillBgTilemapRect(data->bgConfig, GF_BG_LYR_SUB_3, 0x1, (data->currentButtonIndex ^ 1) * 16, 0, 16, 23, 0);
            BgCommitTilemapBufferToVram(data->bgConfig, GF_BG_LYR_SUB_2);
            BgCommitTilemapBufferToVram(data->bgConfig, GF_BG_LYR_SUB_3);
            BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_0);
            ov53_021E80B8(data, data->playerGender);
            if (data->playerGender == 0) {
                data->unk170 = msg_0219_00038; // Boy
            } else {
                data->unk170 = msg_0219_00039; // Girl
            }
            data->state = 67;
            break;

        case 67:
            if (ov53_021E611C(data, data->unk170, 1) == TRUE) {
                data->state = 68;
            }
            break;

        case 68:
            ov53_021E6908(&data->unk160, 1);
            ov53_021E6824(data, 1);
            ov53_021E64C4(data, msg_0219_00047, msg_0219_00048, msg_0219_00000, 2);
            data->state = 69;
            data->currentButtonIndex = 0;
            break;

        case 69:
            ToggleBgLayer(GF_BG_LYR_SUB_0, GF_PLANE_TOGGLE_ON);
            ToggleBgLayer(GF_BG_LYR_SUB_2, GF_PLANE_TOGGLE_ON);
            if (ov53_021E6988(data, data->playerGender + 1) != -1) {
                OakSpeech_FreeWindows(data);
                data->state = 70;
            }
            break;

        case 70:
            switch (data->currentButtonIndex) {
                case 0: // Yes
                    data->state = 93;
                    break;
                case 1: // No
                    data->state = 71;
                    BeginNormalPaletteFade(4, 0, 0, RGB_BLACK, 6, 1, data->heapId);
                    break;
            }
            break;

        case 71:
            if (IsPaletteFadeFinished() != TRUE) {
                break;
            }

            ToggleBgLayer(GF_BG_LYR_SUB_1, GF_PLANE_TOGGLE_OFF);
            ToggleBgLayer(GF_BG_LYR_SUB_2, GF_PLANE_TOGGLE_OFF);
            ov53_021E80B8(data, 3);
            ov53_021E67C4(data, 1);
            BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_0);
            ScheduleSetBgPosText(data->bgConfig, GF_BG_LYR_SUB_0, BG_POS_OP_SET_X, 0);
            ov53_021E6CB0(data);
            BeginNormalPaletteFade(4, 1, 1, RGB_BLACK, 6, 1, data->heapId);
            data->state = 72;
            break;

        case 72:
            if (IsPaletteFadeFinished() != TRUE) {
                break;
            }

            ov53_021E7E08(data, 1);
            data->state = 61;
            break;

        // 73-92 don't exist

        case 93:
            if (ov53_021E611C(data, msg_0219_00040, 1) == TRUE) {
                data->state = 94;
            }
            break;

        case 94:
            if (OakSpeech_WaitFrames(data, 40) == FALSE) {
                break;
            }

            data->state = 95;
            break;

        case 95:
            extern const OVY_MGR_TEMPLATE _02102610;
            String_SetEmpty(data->playerNamingArgs->unk18);
            data->playerNamingArgs->unk4 = data->playerGender;
            data->overlayManager = OverlayManager_New(&_02102610, data->playerNamingArgs, data->heapId);
            data->state = 96;
            break;

        case 96:
            ToggleBgLayer(GF_BG_LYR_MAIN_0, GF_PLANE_TOGGLE_ON);
            ToggleBgLayer(GF_BG_LYR_MAIN_1, GF_PLANE_TOGGLE_ON);
            ToggleBgLayer(GF_BG_LYR_MAIN_3, GF_PLANE_TOGGLE_ON);
            ToggleBgLayer(GF_BG_LYR_SUB_0, GF_PLANE_TOGGLE_ON);
            ToggleBgLayer(GF_BG_LYR_SUB_3, GF_PLANE_TOGGLE_ON);
            ToggleBgLayer(GF_BG_LYR_SUB_2, GF_PLANE_TOGGLE_ON);
            BgSetPosTextAndCommit(data->bgConfig, GF_BG_LYR_MAIN_1, BG_POS_OP_SET_X, 0);
            ov53_021E7D04(data);
            BeginNormalPaletteFade(0, 1, 1, RGB_BLACK, 6, 1, data->heapId);
            data->state = 97;
            ov53_021E66E8(data, 1, 0);
            ov53_021E80B8(data, data->playerGender);
            if (data->playerGender == 0) {
                data->unk170 = msg_0219_00041;
            } else {
                data->unk170 = msg_0219_00042;
            }
            break;

        case 97:
            if (ov53_021E611C(data, data->unk170, 1) == TRUE) {
                data->state = 98;
                ov53_021E6908(&data->unk160, 1);
            }
            break;

        case 98:
            if (ov53_021E6988(data, data->playerGender + 1) != -1) {
                OakSpeech_FreeWindows(data);
                data->state = 99;
            }
            break;

        case 99:
            switch (data->currentButtonIndex) {
                case 0: // Yes
                    data->state = 100;
                    break;
                case 1: // No
                    BeginNormalPaletteFade(4, 0, 0, RGB_BLACK, 6, 1, data->heapId);
                    data->state = 71;
                    break;
            }
            break;

        case 100:
            BeginNormalPaletteFade(4, 0, 0, RGB_BLACK, 6, 1, data->heapId);
            data->state = 101;
            break;

        case 101:
            if (IsPaletteFadeFinished() != TRUE) {
                break;
            }

            ToggleBgLayer(GF_BG_LYR_SUB_2, GF_PLANE_TOGGLE_OFF);
            ToggleBgLayer(GF_BG_LYR_SUB_1, GF_PLANE_TOGGLE_OFF);
            ov53_021E67C4(data, 1);
            ov53_021E80B8(data, 3);
            BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_0);
            ScheduleSetBgPosText(data->bgConfig, GF_BG_LYR_SUB_0, BG_POS_OP_SET_X, 0);
            ov53_021E7E08(data, 1);
            BeginNormalPaletteFade(4, 1, 1, RGB_BLACK, 6, 1, data->heapId);
            data->state = 102;
            break;

        case 102:
            if (IsPaletteFadeFinished() == TRUE) {
                data->state = 103;
            }
            break;

        case 103:
            if (ov53_021E611C(data, msg_0219_00043, 1) == TRUE) {
                data->state = 110;
            }
            break;

        // 104-109 don't exist

        case 110:
            BeginNormalPaletteFade(0, 0, 0, RGB_BLACK, 6, 1, data->heapId);
            data->state = 111;
            break;

        case 111:
            if (IsPaletteFadeFinished() == TRUE) {
                data->state = 120;
            }
            break;

        // 112-119 don't exist

        case 120:
            if (data->playerGender == 0) {
                ov53_021E66E8(data, 2, 0);
            } else {
                ov53_021E66E8(data, 6, 0);
            }
            BeginNormalPaletteFade(0, 1, 1, RGB_BLACK, 6, 1, data->heapId);
            data->state = 121;
            ToggleBgLayer(GF_BG_LYR_MAIN_0, GF_PLANE_TOGGLE_OFF);
            break;

        case 121:
            if (IsPaletteFadeFinished() == TRUE) {
                data->state = 123;
            }
            // Fallthrough into case 123

        // 122 doesn't exist

        case 123:
            data->state = 124;
            break;

        case 124:
            ov53_021E7E08(data, 0);
            ov53_021E6DF0(data);
            data->state = 125;
            break;

        case 125:
            if (OakSpeech_WaitFrames(data, 30) != TRUE) {
                break;
            }

            PlaySE(SEQ_SE_GS_HERO_SHUKUSHOU);
            data->state = 126;
            break;

        case 126:
            if (ov53_021E6E00(data) == TRUE) {
                ret = TRUE;
            }
            break;
    }

    return ret;
}

void ov53_021E7D04(OakSpeechApp_Data *data) {
	ov53_021E6824(data, 1);
	ov53_021E67C4(data, 4);
	ov53_021E64C4(data, msg_0219_00047, msg_0219_00048, msg_0219_00000, 2);
	FillBgTilemapRect(data->bgConfig, GF_BG_LYR_SUB_3, 0x1, (data->playerGender ^ 1) * 16, 0, 16, 23, 0);
	BgCommitTilemapBufferToVram(data->bgConfig, GF_BG_LYR_SUB_3);
}

void ov53_021E7D58(OakSpeechApp_Data *data) {
	BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_0);
	BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_SUB_0);
}

extern const WindowTemplate ov53_021E8518;

void ov53_021E7D70(OakSpeechApp_Data *data);
void ov53_021E7D70(OakSpeechApp_Data *data) {
	String *temp = String_New(1024, data->heapId);
	Window *window = &data->windows3C[3];

	ReadMsgDataIntoString(data->msgData, msg_0219_00060, temp);
	AddWindow(data->bgConfig, window, &ov53_021E8518);
	FillWindowPixelBuffer(window, 0x0);
	AddTextPrinterParameterizedWithColor(window, 4, temp, 0, 0, TEXT_SPEED_INSTANT, MAKE_TEXT_COLOR(15, 1, 0), NULL);
	CopyWindowToVram(window);

	RemoveWindow(window);
	String_Delete(temp);
}

void ov53_021E7DDC(OakSpeechApp_Data *data);
void ov53_021E7DDC(OakSpeechApp_Data *data) {
	Window *window = &data->windows3C[3];

	AddWindow(data->bgConfig, window, &ov53_021E8518);
	FillWindowPixelBuffer(window, 0x0);
	CopyWindowToVram(window);

	RemoveWindow(window);
}

void ov53_021E7E08(OakSpeechApp_Data *data, u32 action) {
    GF_ASSERT(data != NULL);

    switch (action) {
        case 0:
            GF_ASSERT(Get2dSpriteVisibleFlag(data->sprites[3]) == TRUE);
            ov53_021E7DDC(data);
            Set2dSpriteVisibleFlag(data->sprites[3], FALSE);
            return;
        case 1:
            GF_ASSERT(Get2dSpriteVisibleFlag(data->sprites[3]) == FALSE);
            ov53_021E7D70(data);
            Set2dSpriteVisibleFlag(data->sprites[3], TRUE);
            return;
        case 2:
            Set2dSpriteAnimSeqNo(data->sprites[3], 1);
            return;
        case 3:
            Set2dSpriteAnimSeqNo(data->sprites[3], 0);
            return;
        default:
            GF_ASSERT(FALSE);
            return;
    }
}

BOOL ov53_021E7E94(OakSpeechApp_Data *data);
BOOL ov53_021E7E94(OakSpeechApp_Data *data) {
    return Get2dSpriteCurrentAnimSeqNo(data->sprites[3]) == 1;
}

BOOL ov53_021E7EAC(OakSpeechApp_Data *data);
BOOL ov53_021E7EAC(OakSpeechApp_Data *data) {
    GF_ASSERT(data != NULL);
    return Get2dSpriteVisibleFlag(data->sprites[3]) == TRUE;
}

void ov53_021E7ECC(OakSpeechApp_Data *data) {
    if (!ov53_021E7EAC(data)) {
        return;
    }

    extern const TouchscreenHitbox ov53_021E8510[2];
    int rect = TouchscreenHitbox_FindRectAtTouchHeld(ov53_021E8510);
    if (rect == 0 && System_GetTouchNew()) {
        gSystem.simulatedInputs = 1;
        ov53_021E7E08(data, 2);
    } else if (rect == 0 && ov53_021E7E94(data)) {
        gSystem.simulatedInputs = 1;
    } else {
        ov53_021E7E08(data, 3);
    }
}
