#ifndef POKEHEARTGOLD_OAK_SPEECH_OAK_SPEECH_H
#define POKEHEARTGOLD_OAK_SPEECH_OAK_SPEECH_H

#include "bg_window.h"
#include "message_format.h"
#include "msgdata.h"
#include "options.h"
#include "overlay_manager.h"
#include "unk_0200CF18.h"
#include "unk_02082908.h"

BOOL OakSpeech_Init(OVY_MANAGER *manager, int *state);
BOOL OakSpeech_Main(OVY_MANAGER *manager, int *state);
BOOL OakSpeech_Exit(OVY_MANAGER *manager, int *state);

typedef struct UnkStruct_ov53_021E80F4 {
    HeapID heapId;
    u8 unk4[8];
    BgConfig *bgConfig;
    Sprite *sprite;
    MessageFormat *messageFormat;
    u8 paletteNum;
    u8 bgId1;
    u8 bgId2;
    u8 unk1B_0:4;
    u8 unk1B_4:4;
    Window windows[2];
} UnkStruct_ov53_021E80F4; // size: 0x3C

typedef struct OakSpeechApp_Args {
    u8 unk0[8];
    SaveData* savedata;
} OakSpeechApp_Args; // size unknown

typedef struct OakSpeechApp_Data {
    HeapID heapId;
    SaveData* savedata;
    Options *options;
    u32 state;
    u32 unk10; // unused, actual type unknown
    OVY_MANAGER *overlayManager;
    BgConfig *bgConfig;
    Window window1C;
    Window window2C;
    Window windows3C[4];
    int windows3CCount;
    u32 unk80; // unused, actual type unknown, was related to text
    u8 unk84[0xD0 - 0x84];
    SpriteRenderer *spriteRenderer;
    SpriteGfxHandler *spriteGfxHandler;
    Sprite *sprites[6];
    u8 unkF0[0x10];
    MsgData* msgData;
    u32 unk104;
    u32 unk108; // actual type unknown
    u32 textPrinter;
    String *string;
    u32 unk114; // actual type unknown
    MessageFormat *messageFormat;
    u8 unk11C[4];
    NamingScreenArgs *playerNamingArgs;
    NamingScreenArgs *rivalNamingArgs;
    u32 unk128;
    u32 unk12C;
    u32 unk130;
    u16 playerGender; // 0: boy, 1: girl
    u16 unk136;
    u8 unk138[0x13C - 0x138];
    int waitFrames;
    u32 unk140;
    u32 unk144;
    u8 unk148[0x160 - 0x148];
    u8 unk160;
    u8 numButtons;
    u8 unk162;
    u8 currentButtonIndex;
    u8 unk164;
    u8 unk165;
    u8 unk166;
    u8 unk167;
    u32 unk168;
    u32 unk16C;
    u32 unk170;
    u16 unk174;
    s16 unk176;
    UnkStruct_ov53_021E80F4 *unk178;
    u32 unk17C;
} OakSpeechApp_Data; // size: 0x180

#endif
