#ifndef GUARD_POKEHEARTGOLD_UNK_02108424_H
#define GUARD_POKEHEARTGOLD_UNK_02108424_H

#include "bg_window.h"
#include "heap.h"
#include "list_menu_items.h"

typedef struct Ov122_021E9282 {
    u8 unk0_0 : 1;
    u8 unk0_1 : 7;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u16 unk6;
    u16 unk8;
    u16 unkA;
} Ov122_021E9282;

typedef struct Ov122_021E7488 {
    Ov122_021E9282 unk0;
    LISTMENUITEM *unkC;
    BgConfig *unk10;
    u8 unk14;
    u8 unk15[0x3];
} Ov122_021E7488;

typedef struct UnkStruct_02018424 {
    HeapID heapId;
    NNSG2dCharacterData *pCharData;
    NNSG2dPaletteData *pPlttData;
    void *charDataRaw;
    void *plttDataRaw;
    int unk_14;
} UnkStruct_02018424;

typedef struct UnkStruct_020185FC {
    UnkStruct_02018424 *unk_00;
    Ov122_021E7488 unk_04;
    u8 filler_18[8];
    u8 unk_24;
    u8 unk_25;
    u8 unk_26;
    u8 unk_27_0 : 1;
    u8 unk_27_1 : 7;
    u8 unk_28;
    u8 unk_29;
    HeapID unk_2C;
    int unk_30;
    int unk_34;
} UnkStruct_020185FC;

UnkStruct_02018424 *sub_02018424(HeapID heapId, int a1);
void sub_02018474(UnkStruct_02018424 *a0);
void *sub_020185FC(UnkStruct_02018424 *a0, Ov122_021E7488 *a1, s32 a2, u8 a3, u8 a4, u8 a5, u8 a6);
int sub_020186A4(UnkStruct_02018424 *);
u8 sub_02018674(UnkStruct_02018424 *);
void sub_02018680(UnkStruct_02018424 *);
#endif // GUARD_POKEHEARTGOLD_UNK_02108424_H
