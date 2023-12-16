#include "global.h"
#include "bg_window.h"
#include "delete_savedata_app.h"
#include "font.h"
#include "list_menu_2d.h"
#include "msgdata.h"
#include "msgdata/msg.naix"
#include "msgdata/msg/msg_0007.h"
#include "render_window.h"
#include "system.h"
#include "text.h"
#include "unk_02004A44.h"
#include "unk_02005D10.h"
#include "unk_0200FA24.h"

typedef struct DeleteSavedataApp_Args {
    u8 unk0[8];
    SaveData *savedata;
} DeleteSavedataApp_Args;

typedef struct DeleteSavedataApp_Data {
    HeapID heapId;
    u32 state;
    u32 printState;
    u32 textPrinterId;
    String *textString;
    BgConfig *bgConfig;
    MsgData *msgData;
    Window window;
    struct ListMenu2D *yesNoMenu;
    SaveData *savedata;
    WaitingIcon *waitingIcon;
} DeleteSavedataApp_Data;

static const WindowTemplate _021081B0 = {
    .bgId = GF_BG_LYR_MAIN_0,
    .left = 25,
    .top = 13,
    .width = 6,
    .height = 4,
    .palette = 1,
    .baseTile = 0x155,
};

static const WindowTemplate _021081A8 = {
    .bgId = GF_BG_LYR_MAIN_0,
    .left = 2,
    .top = 19,
    .width = 27,
    .height = 4,
    .palette = 1,
    .baseTile = 0x16D,
};

static const GraphicsModes _021081B8 = {
    .dispMode = GX_DISPMODE_GRAPHICS,
    .bgMode = GX_BGMODE_0,
    .subMode = GX_BGMODE_0,
    ._2d3dMode = GX_BG0_AS_2D,
};

static const BgTemplate _021081C8 = {
    .x = 0,
    .y = 0,
    .bufferSize = 0x800,
    .baseTile = 0,
    .size = GF_BG_SCR_SIZE_256x256,
    .colorMode = GX_BG_COLORMODE_16,
    .screenBase = GX_BG_SCRBASE_0x0000,
    .charBase = GX_BG_CHARBASE_0x18000,
    .bgExtPltt = GX_BG_EXTPLTT_01,
    .priority = 1,
    .areaOver = GX_BG_AREAOVER_XLU,
    .mosaic = FALSE,
};

static const GraphicsBanks _021081E4 = {
    .bg = GX_VRAM_BG_256_AB,
    .bgextpltt = GX_VRAM_BGEXTPLTT_NONE,
    .subbg = GX_VRAM_SUB_BG_NONE,
    .subbgextpltt = GX_VRAM_SUB_BGEXTPLTT_NONE,
    .obj = GX_VRAM_OBJ_NONE,
    .objextpltt = GX_VRAM_OBJEXTPLTT_NONE,
    .subobj = GX_VRAM_SUB_OBJ_NONE,
    .subobjextpltt = GX_VRAM_SUB_OBJEXTPLTT_NONE,
    .tex = GX_VRAM_TEX_NONE,
    .texpltt = GX_VRAM_TEXPLTT_NONE,
};

const OVY_MGR_TEMPLATE _0210820C = {
    .init = DeleteSavedataApp_Init,
    .exec = DeleteSavedataApp_Run,
    .exit = DeleteSavedataApp_Exit,
    .ovy_id = FS_OVERLAY_ID_NONE,
};

static void DeleteSavedataApp_OnVBlank(DeleteSavedataApp_Data *data);
static void DeleteSavedataApp_SetupBgConfig(DeleteSavedataApp_Data *data);
static void DeleteSavedataApp_FreeBgConfig(DeleteSavedataApp_Data *data);
static void DeleteSavedataApp_SetupTextAndWindow(DeleteSavedataApp_Data *data);
static void DeleteSavedataApp_FreeTextAndWindow(DeleteSavedataApp_Data *data);
static BOOL sub_02091FD4(DeleteSavedataApp_Data *data);
static BOOL sub_020920E0(DeleteSavedataApp_Data *data, u32 msgNum, BOOL skipWaitingForAPress, u32 textSpeed);

BOOL DeleteSavedataApp_Init(OVY_MANAGER *manager, int *state) {
    CreateHeap(HEAP_ID_3, HEAP_ID_DELETE_SAVE, 0x20000);

    DeleteSavedataApp_Data *data = OverlayManager_CreateAndGetData(manager, sizeof(DeleteSavedataApp_Data), HEAP_ID_DELETE_SAVE);
    memset(data, 0, sizeof(DeleteSavedataApp_Data));
    data->heapId = HEAP_ID_DELETE_SAVE;
    data->state = 0;
    DeleteSavedataApp_Args *args = OverlayManager_GetArgs(manager);
    data->savedata = args->savedata;

    return TRUE;
}

BOOL DeleteSavedataApp_Run(OVY_MANAGER *manager, int *state) {
    DeleteSavedataApp_Data *data = OverlayManager_GetData(manager);
    BOOL ret = FALSE;

    switch (*state) {
        case 0:
            StopBGM(SEQ_GS_POKEMON_THEME, 0);
            sub_02005AF8(0);
            sub_02004AD8(0);

            sub_0200FBF4(0, 0);
            sub_0200FBF4(1, 0);

            Main_SetVBlankIntrCB(NULL, NULL);
            Main_SetHBlankIntrCB(NULL, NULL);

            GfGfx_DisableEngineAPlanes();
            GfGfx_DisableEngineBPlanes();
            GX_SetVisiblePlane(GX_PLANEMASK_NONE);
            GXS_SetVisiblePlane(GX_PLANEMASK_NONE);

            SetKeyRepeatTimers(4, 8);

            DeleteSavedataApp_SetupBgConfig(data);
            DeleteSavedataApp_SetupTextAndWindow(data);

            Main_SetVBlankIntrCB((GFIntrCB)DeleteSavedataApp_OnVBlank, data);

            GfGfx_BothDispOn();

            BeginNormalPaletteFade(0, 1, 1, RGB_BLACK, 6, 1, data->heapId);

            *state = 1;
            break;
        case 1:
            if (IsPaletteFadeFinished() != TRUE) {
                break;
            }

            *state = 2;
            break;
        case 2:
            if (sub_02091FD4(data) != TRUE) {
                break;
            }

            BeginNormalPaletteFade(0, 0, 0, RGB_BLACK, 6, 1, data->heapId);
            *state = 3;
            break;
        case 3:
            if (IsPaletteFadeFinished() != TRUE) {
                break;
            }

            DeleteSavedataApp_FreeTextAndWindow(data);
            DeleteSavedataApp_FreeBgConfig(data);

            Main_SetVBlankIntrCB(NULL, NULL);
            ret = TRUE;
            break;
    }

    return ret;
}

BOOL DeleteSavedataApp_Exit(OVY_MANAGER *manager, int *state) {
    DeleteSavedataApp_Data *data = OverlayManager_GetData(manager);
    HeapID heapId = data->heapId;

    OverlayManager_FreeData(manager);

    DestroyHeap(heapId);

    OS_ResetSystem(0);

    return TRUE;
}

static void DeleteSavedataApp_OnVBlank(DeleteSavedataApp_Data *data) {
    DoScheduledBgGpuUpdates(data->bgConfig);
}

static void DeleteSavedataApp_SetupBgConfig(DeleteSavedataApp_Data *data) {
    GraphicsBanks banks = _021081E4;
    GfGfx_SetBanks(&banks);

    data->bgConfig = BgConfig_Alloc(data->heapId);

    GraphicsModes modes = _021081B8;
    SetBothScreensModesAndDisable(&modes);

    BgTemplate template = _021081C8;
    InitBgFromTemplate(data->bgConfig, GF_BG_LYR_MAIN_0, &template, GX_BGMODE_0);
    BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_0);
    LoadUserFrameGfx2(data->bgConfig, GF_BG_LYR_MAIN_0, 0x1E2, 2, 0, data->heapId);
    LoadUserFrameGfx1(data->bgConfig, GF_BG_LYR_MAIN_0, 0x1D9, 3, 0, data->heapId);
    LoadFontPal0(GF_BG_LYR_MAIN_0, GF_PAL_SLOT_OFFSET_1, data->heapId);
    BG_ClearCharDataRange(GF_BG_LYR_MAIN_0, 32, 0, data->heapId);
    BG_SetMaskColor(GF_BG_LYR_MAIN_0, RGB(1, 1, 27));
    BG_SetMaskColor(GF_BG_LYR_SUB_0, RGB(1, 1, 27));
}

static void DeleteSavedataApp_FreeBgConfig(DeleteSavedataApp_Data *data) {
    ToggleBgLayer(GF_BG_LYR_MAIN_0, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_1, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_2, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_MAIN_3, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_0, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_1, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_2, GF_PLANE_TOGGLE_OFF);
    ToggleBgLayer(GF_BG_LYR_SUB_3, GF_PLANE_TOGGLE_OFF);

    FreeBgTilemapBuffer(data->bgConfig, GF_BG_LYR_MAIN_0);
    FreeToHeap(data->bgConfig);
}

static void DeleteSavedataApp_SetupTextAndWindow(DeleteSavedataApp_Data *data) {
    data->msgData = NewMsgDataFromNarc(MSGDATA_LOAD_LAZY, NARC_msgdata_msg, NARC_msg_msg_0007_bin, data->heapId);
    ResetAllTextPrinters();

    data->printState = 0;

    AddWindow(data->bgConfig, &data->window, &_021081A8);
    FillWindowPixelRect(&data->window, 0xF, 0, 0, 216, 32);
}

static void DeleteSavedataApp_FreeTextAndWindow(DeleteSavedataApp_Data *data) {
    RemoveWindow(&data->window);
    DestroyMsgData(data->msgData);
}

static BOOL sub_02091FD4(DeleteSavedataApp_Data *data) {
    BOOL ret = FALSE;

    enum {
        STATE_ASK_TO_DELETE,
        STATE_HANDLE_INPUT,
        STATE_ASK_TO_CONFIRM,
        STATE_HANDLE_CONFIRMATION,
    };

    switch (data->state) {
        case 0:
            if (sub_020920E0(data, msg_0007_00000, TRUE, 4) != TRUE) {
                break;
            }

            data->yesNoMenu = CreateYesNoMenu(data->bgConfig, &_021081B0, 0x1D9, 3, 1, data->heapId);
            data->state = 1;
            break;
        case 1: {
            int result = Handle2dMenuInput_DeleteOnFinish(data->yesNoMenu, data->heapId);

            // FIXME: Fakematch
            if (result == LIST_NO_MULTIPLE_SCROLL) {
                goto no_multiple_scroll1;
            } else if (result != LIST_CANCEL) {
                break;
            } else {
                goto cancel1;
            }

            no_multiple_scroll1: {
                data->state = 2;
                break;
            }

            cancel1: {
                data->state = 6;
                break;
            }
        }
        case 2:
            if (sub_020920E0(data, msg_0007_00001, TRUE, 4) != TRUE) {
                break;
            }

            data->yesNoMenu = CreateYesNoMenu(data->bgConfig, &_021081B0, 0x1D9, 3, 1, data->heapId);
            data->state = 3;
            break;
        case 3: {
            int result = Handle2dMenuInput_DeleteOnFinish(data->yesNoMenu, data->heapId);

            // FIXME: Fakematch
            if (result == LIST_NO_MULTIPLE_SCROLL) {
                goto no_multiple_scroll2;
            } else if (result != LIST_CANCEL) {
                break;
            } else {
                goto cancel2;
            }

            no_multiple_scroll2: {
                data->state = 4;
                break;
            }

            cancel2: {
                data->state = 6;
                break;
            }
        }
        case 4:
            if (sub_020920E0(data, msg_0007_00002, TRUE, TEXT_SPEED_INSTANT) != TRUE) {
                break;
            }

            data->waitingIcon = WaitingIcon_New(&data->window, 0x1E2);
            data->state = 5;
            break;
        case 5:
            Save_DeleteAllData(data->savedata);
            sub_0200F450(data->waitingIcon);
            data->state = 6;
            break;
        case 6:
            BgClearTilemapBufferAndCommit(data->bgConfig, GF_BG_LYR_MAIN_0);
            ret = TRUE;
            break;
    }

    return ret;
}

static BOOL sub_020920E0(DeleteSavedataApp_Data *data, u32 msgNum, BOOL skipWaitingForAPress, u32 textSpeed) {
    BOOL ret = FALSE;

    switch (data->printState) {
        case 0:
            FillWindowPixelRect(&data->window, 0xF, 0, 0, 216, 32);
            DrawFrameAndWindow2(&data->window, FALSE, 0x1E2, 2);

            data->textString = String_New(1024, data->heapId);
            ReadMsgDataIntoString(data->msgData, msgNum, data->textString);
            data->textPrinterId = AddTextPrinterParameterized(&data->window, 1, data->textString, 0, 0, textSpeed, NULL);

            if (textSpeed == TEXT_SPEED_INSTANT) {
                String_Delete(data->textString);

                // Skip waiting for the text printer to finish since the speed here was instant
                data->printState++;
            }

            data->printState++;
            break;
        case 1:
            if (TextPrinterCheckActive(data->textPrinterId)) {
                break;
            }

            String_Delete(data->textString);
            data->printState++;
            break;
        case 2:
            if (skipWaitingForAPress || (gSystem.newKeys & PAD_BUTTON_A)) {
                data->printState = 0;
                ret = TRUE;
            }
            break;
    }

    return ret;
}
