#ifndef GUARD_POKEHEARTGOLD_UNK_0202E4B0_H
#define GUARD_POKEHEARTGOLD_UNK_0202E4B0_H

#include "save.h"

typedef struct UnkStruct_0202E4B0_sub UnkStruct_0202E4B0_sub;
typedef struct UnkStruct_0202E4B0 UnkStruct_0202E4B0;

u8 sub_0202E4B0(int a0);
u8 sub_0202E4BC(int a0);
u32 sub_0202E4F4(void);  // ???_sizeof
void sub_0202E4FC(UnkStruct_0202E4B0 *a0);  // ???_Init
UnkStruct_0202E4B0 *sub_0202E530(SaveData *saveData);  // ???_Get
void sub_0202E544(UnkStruct_0202E4B0 *a0, int a1, u32 a2);
u32 sub_0202E58C(void);
UnkStruct_0202E4B0_sub *sub_0202E66C(SaveData *saveData, HeapID heapId);
void sub_0202EAFC(UnkStruct_0202E4B0_sub *a0);
void sub_0202E97C(SaveData *saveData, u8 a1, u8 a2, UnkStruct_0202E4B0_sub **a3, HeapID heapId);

#endif //GUARD_POKEHEARTGOLD_UNK_0202E4B0_H
