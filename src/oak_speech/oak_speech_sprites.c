#include "oak_speech/oak_speech.h"
#include "data/resdat.naix"
#include "gf_gfx_planes.h"
#include "vram_transfer_manager.h"
#include "unk_0200CF18.h"

void ov53_021E7F24(OakSpeechApp_Data *data);
void ov53_021E7F24(OakSpeechApp_Data *data) {
    GfGfx_EngineATogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_ON);
    GfGfx_EngineBTogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_ON);
    GF_CreateVramTransferManager(32, HEAP_ID_OAK_SPEECH);

    data->spriteRenderer = SpriteRenderer_Create(HEAP_ID_OAK_SPEECH);
    data->spriteGfxHandler = SpriteRenderer_CreateGfxHandler(data->spriteRenderer);

    const Unk122_021E92FC unkTemplate = {
        .unk0 = 0,
        .unk4 = 0x80,
        .unk8 = 0,
        .unkC = 0x20,
        .unk10 = 0,
        .unk14 = 0x80,
        .unk18 = 0,
        .unk1C = 0x20,
    };
    const Unk122_021E92D0 unkTemplate2 = {
        .maxTasks = 10,
        .sizeMain = 0x400,
        .sizeSub = 0x400,
        .charModeMain = GX_OBJVRAMMODE_CHAR_1D_32K,
        .charModeSub = GX_OBJVRAMMODE_CHAR_1D_32K,
    };
    sub_0200CF70(data->spriteRenderer, &unkTemplate, &unkTemplate2, 32);

    sub_0200CFF4(data->spriteRenderer, data->spriteGfxHandler, 10);
    G2dRenderer_SetSubSurfaceCoords(SpriteRenderer_GetG2dRendererPtr(data->spriteRenderer), FX32_CONST(0), FX32_CONST(192));

    const u16 fileIds[7] = {
        NARC_resdat_resdat_00000026_bin,
        NARC_resdat_resdat_00000027_bin,
        NARC_resdat_resdat_00000025_bin,
        NARC_resdat_resdat_00000024_bin,
        0xFFFF,
        0xFFFF,
        NARC_resdat_resdat_00000078_bin,
    };
    sub_0200D294(data->spriteRenderer, data->spriteGfxHandler, fileIds);
}

void ov53_021E7FEC(OakSpeechApp_Data *data);
void ov53_021E7FEC(OakSpeechApp_Data *data) {
    SpriteRenderer_RemoveGfxHandler(data->spriteRenderer, data->spriteGfxHandler);
    SpriteRenderer_Delete(data->spriteRenderer);
    GF_DestroyVramTransferManager();
    data->spriteGfxHandler = NULL;
}

void ov53_021E8014(OakSpeechApp_Data *data);
void ov53_021E8014(OakSpeechApp_Data *data) {
    static const UnkStruct_0200D2B4 templates[6] = {
        { .resourceSet = 0, .x = 128, .y = 50, .z = 0, .animSeqNo = 0, .rotation = 2, .unk_10 = 1, .whichScreen = NNS_G2D_VRAM_TYPE_2DMAIN, .unk_18 = 0, .unk_1C = 0, .unk_20 = 0, .unk_24 = 0 },
        { .resourceSet = 1, .x = 64, .y = 104, .z = 0, .animSeqNo = 0, .rotation = 0, .unk_10 = 0, .whichScreen = NNS_G2D_VRAM_TYPE_2DSUB, .unk_18 = 0, .unk_1C = 0, .unk_20 = 0, .unk_24 = 0 },
        { .resourceSet = 2, .x = 192, .y = 104, .z = 0, .animSeqNo = 0, .rotation = 1, .unk_10 = 1, .whichScreen = NNS_G2D_VRAM_TYPE_2DSUB, .unk_18 = 0, .unk_1C = 0, .unk_20 = 0, .unk_24 = 0 },
        { .resourceSet = 3, .x = 256, .y = 192, .z = 0, .animSeqNo = 0, .rotation = 0, .unk_10 = 3, .whichScreen = NNS_G2D_VRAM_TYPE_2DSUB, .unk_18 = 0, .unk_1C = 0, .unk_20 = 0, .unk_24 = 0 },
        { .resourceSet = 4, .x = 0, .y = 0, .z = 0, .animSeqNo = 1, .rotation = 0, .unk_10 = 4, .whichScreen = NNS_G2D_VRAM_TYPE_2DSUB, .unk_18 = 0, .unk_1C = 0, .unk_20 = 0, .unk_24 = 0 },
        { .resourceSet = 5, .x = 160, .y = 80, .z = 0, .animSeqNo = 0, .rotation = 0, .unk_10 = 4, .whichScreen = NNS_G2D_VRAM_TYPE_2DMAIN, .unk_18 = 0, .unk_1C = 0, .unk_20 = 0, .unk_24 = 0 },
    };

    for (u16 i = 0; i < 6; i++) {
        data->sprites[i] = SpriteRenderer_CreateSprite(data->spriteRenderer, data->spriteGfxHandler, &templates[i]);
    }
    Set2dSpriteVisibleFlag(data->sprites[0], FALSE);
    Set2dSpriteVisibleFlag(data->sprites[1], FALSE);
    Set2dSpriteVisibleFlag(data->sprites[2], FALSE);
    Set2dSpriteVisibleFlag(data->sprites[3], FALSE);
    Set2dSpriteVisibleFlag(data->sprites[4], FALSE);

    Sprite_SetPriority(data->sprites[3], 1);
    Set2dSpriteAnimActiveFlag(data->sprites[5], TRUE);
    sub_0202487C(data->sprites[5], 1);
    Set2dSpriteVisibleFlag(data->sprites[5], FALSE);
}

void ov53_021E80B8(OakSpeechApp_Data *data, u32 a1);
void ov53_021E80B8(OakSpeechApp_Data *data, u32 a1) {
    BOOL showSprite1 = FALSE, showSprite2 = FALSE;

    if (a1 == 0) {
        showSprite1 = TRUE;
    } else if (a1 == 1) {
        showSprite2 = TRUE;
    } else if (a1 == 2) {
        showSprite1 = TRUE;
        showSprite2 = TRUE;
    } else if (a1 == 3) {
        showSprite1 = FALSE;
        showSprite2 = FALSE;
    }

    Set2dSpriteVisibleFlag(data->sprites[1], showSprite1);
    Set2dSpriteVisibleFlag(data->sprites[2], showSprite2);
}
