#ifndef POKEHEARTGOLD_ALPH_PUZZLE_H
#define POKEHEARTGOLD_ALPH_PUZZLE_H

#include "bg_window.h"
#include "overlay_manager.h"
#include "unk_0200CF18.h"
#include "palette.h"
#include "message_format.h"
#include "msgdata.h"
#include "save.h"
#include "task.h"
#include "unk_0201660C.h"

typedef enum AlphPuzzles {
    ALPH_PUZZLE_KABUTO,
    ALPH_PUZZLE_AEROACTYL,
    ALPH_PUZZLE_OMANYTE,
    ALPH_PUZZLE_HO_OH,
    ALPH_PUZZLE_MAX
} AlphPuzzles;

typedef struct AlphPuzzleArgs {
    u8 unk0[0x5];
    u8 puzzle;
    u8 unk6[0x2];
    u32 *unk8;
    SaveData *saveData;
} AlphPuzzleArgs;

BOOL AlphPuzzle_OvyInit(OVY_MANAGER *man, int *state);
BOOL AlphPuzzle_OvyExec(OVY_MANAGER *man, int *state);
BOOL AlphPuzzle_OvyExit(OVY_MANAGER *man, int *state);

#endif //POKEHEARTGOLD_ALPH_PUZZLE_H
