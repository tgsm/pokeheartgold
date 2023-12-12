#ifndef POKEHEARTGOLD_UNOWN_REPORT_APP_H
#define POKEHEARTGOLD_UNOWN_REPORT_APP_H

#include "overlay_manager.h"

BOOL UnownReportApp_Init(OVY_MANAGER *manager, int *state);
BOOL UnownReportApp_Run(OVY_MANAGER *manager, int *state);
BOOL UnownReportApp_Exit(OVY_MANAGER *manager, int *state);

#endif
