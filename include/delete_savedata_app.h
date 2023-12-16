#ifndef POKEHEARTGOLD_DELETE_SAVEDATA_APP_H
#define POKEHEARTGOLD_DELETE_SAVEDATA_APP_H

#include "overlay_manager.h"

BOOL DeleteSavedataApp_Init(OVY_MANAGER *manager, int *state);
BOOL DeleteSavedataApp_Run(OVY_MANAGER *manager, int *state);
BOOL DeleteSavedataApp_Exit(OVY_MANAGER *manager, int *state);

#endif
