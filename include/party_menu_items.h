#ifndef GUARD_POKEHEARTGOLD_PARTY_MENU_MOVES_H
#define GUARD_POKEHEARTGOLD_PARTY_MENU_MOVES_H

#include "party_menu.h"

#define LEARN_MOVE_CHECK_KNOWN         0xFD
#define LEARN_MOVE_CHECK_FULL          0xFE
#define LEARN_MOVE_CHECK_INCOMPAT      0xFF

void sub_020812E8(PartyMenuStruct *partyMenu);
int sub_02081378(PartyMenuStruct *partyMenu);
BOOL sub_020817C4(u16 itemId);
int PartyMenu_Subtask_SacredAsh(PartyMenuStruct *partyMenu);
int sub_02081ED0(PartyMenuStruct *partyMenu);
u8 sub_020820DC(PartyMenuStruct *partyMenu, Pokemon *mon);
int sub_02082134(PartyMenuStruct *partyMenu);
int sub_020822CC(PartyMenuStruct *partyMenu);
int sub_02082370(PartyMenuStruct *partyMenu);
int PartyMenu_Subtask_SelectMove(PartyMenuStruct *partyMenu);
void sub_02082654(PartyMenuStruct *partyMenu, BOOL a1);
int sub_02082868(PartyMenuStruct *partyMenu);

#endif //GUARD_POKEHEARTGOLD_PARTY_MENU_MOVES_H
