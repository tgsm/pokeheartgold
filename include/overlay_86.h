#ifndef POKEHEARTGOLD_OVY_86_H
#define POKEHEARTGOLD_OVY_86_H

#include "overlay_manager.h"
#include "save.h"

typedef struct Unk0203FAB4 {
    SaveData *unk0;
    u8 unk4;
    u8 unk5;
    u16 unk6;
} Unk0203FAB4;

BOOL ov86_021E5900(OVY_MANAGER *man, int *state);
BOOL ov86_021E5A40(OVY_MANAGER *man, int *state);
BOOL ov86_021E5AA4(OVY_MANAGER *man, int *state);

#endif //POKEHEARTGOLD_OVY_86_H
