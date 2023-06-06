#include "scrcmd.h"
#include "map_header.h"
#include "pokedex.h"
#include "script_pokemon_util.h"
#include "player_data.h"
#include "get_egg.h"
#include "constants/balls.h"
#include "item.h"
#include "save_arrays.h"
#include "npc_trade.h"
#include "unk_0205BB1C.h"
#include "ribbon.h"

FS_EXTERN_OVERLAY(npc_trade);

BOOL ScrCmd_GiveMon(SCRIPTCONTEXT *ctx) {
    u16 map = MapHeader_GetMapSec(ctx->fsys->location->mapId);
    FieldSystem *fsys = ctx->fsys;
    POKEDEX *pokedex = Sav2_Pokedex_get(fsys->savedata);

    u16 species = ScriptGetVar(ctx);
    u8 level = ScriptGetVar(ctx);
    u16 heldItem = ScriptGetVar(ctx);
    u8 forme = ScriptGetVar(ctx);
    u16 ability = ScriptGetVar(ctx);
    u16 *retPtr = ScriptGetVarPointer(ctx);

    PARTY *party = SavArray_PlayerParty_get(fsys->savedata);
    *retPtr = GiveMon(HEAP_ID_FIELD, fsys->savedata, species, level, forme, ability, heldItem, map, 24);

    return FALSE;
}

BOOL ScrCmd_TakeMon(SCRIPTCONTEXT *ctx) {
    u8 slot = ScriptGetVar(ctx);
    PARTY *party = SavArray_PlayerParty_get(ctx->fsys->savedata);
    RemoveMonFromParty(party, slot);
    return FALSE;
}

BOOL ScrCmd_GetPartyMonSpecies(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 slot = ScriptGetVar(ctx);
    u16 *species = ScriptGetVarPointer(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), slot);
    if (!GetMonData(mon, MON_DATA_IS_EGG, NULL)) {
        *species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    }
    else {
        *species = SPECIES_NONE;
    }

    return FALSE;
}

BOOL ScrCmd_PartymonIsMine(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    SAVEDATA *save = FieldSys_GetSaveDataPtr(fsys);
    PLAYERPROFILE *profile = Sav2_PlayerData_GetProfileAddr(save);

    u16 *slot = ScriptGetVarPointer(ctx);
    u16 *mine = ScriptGetVarPointer(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), *slot);
    u16 pokemonID = GetMonData(mon, MON_DATA_OTID, NULL);
    u16 playerID = PlayerProfile_GetTrainerID(profile);

    if (pokemonID == playerID) {
        *mine = FALSE;
    }
    else {
        *mine = TRUE;
    }

    return FALSE;
}

BOOL ScrCmd_GiveEgg(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    PLAYERPROFILE *profile = Sav2_PlayerData_GetProfileAddr(fsys->savedata);

    u16 species = ScriptGetVar(ctx);
    u16 offset = ScriptGetVar(ctx);

    PARTY *party = SavArray_PlayerParty_get(fsys->savedata);
    u8 partyCount = GetPartyCount(party);
    if (partyCount < PARTY_SIZE) {
        Pokemon *mon = AllocMonZeroed(HEAP_ID_FIELD);
        ZeroMonData(mon);
        int val = sub_02017FE4(MAPSECTYPE_GIFT, offset);
        SetEggStats(mon, species, 1, profile, 3, val);
        AddMonToParty(party, mon);
        FreeToHeap(mon);
    }

    return FALSE;
}

BOOL ScrCmd_SetMonMove(SCRIPTCONTEXT *ctx) {
    u16 monSlot = ScriptGetVar(ctx);
    u16 moveSlot = ScriptGetVar(ctx);
    u16 moveId = ScriptGetVar(ctx);

    PartyMonSetMoveInSlot(SavArray_PlayerParty_get(ctx->fsys->savedata), monSlot, moveSlot, moveId);

    return FALSE;
}

BOOL ScrCmd_MonHasMove(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *hasMove = ScriptGetVarPointer(ctx);
    u16 move = ScriptGetVar(ctx);
    u16 slot = ScriptGetVar(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), slot);
    *hasMove = FALSE;
    if (GetMonData(mon, MON_DATA_IS_EGG, NULL)) {
        return FALSE;
    }

    if (GetMonData(mon, MON_DATA_MOVE1, NULL) == move || GetMonData(mon, MON_DATA_MOVE2, NULL) == move ||
        GetMonData(mon, MON_DATA_MOVE3, NULL) == move || GetMonData(mon, MON_DATA_MOVE4, NULL) == move) {
        *hasMove = TRUE;
    }

    return FALSE;
}

BOOL ScrCmd_GetPartySlotWithMove(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *slot = ScriptGetVarPointer(ctx);
    u16 move = ScriptGetVar(ctx);
    u8 i;

    u8 partyCount = GetPartyCount(SavArray_PlayerParty_get(fsys->savedata));
    for (i = 0, *slot = PARTY_SIZE; i < partyCount; i++) {
        Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), i);
        if (GetMonData(mon, MON_DATA_IS_EGG, NULL)) {
            continue;
        }

        if (GetMonData(mon, MON_DATA_MOVE1, NULL) == move || GetMonData(mon, MON_DATA_MOVE2, NULL) == move ||
            GetMonData(mon, MON_DATA_MOVE3, NULL) == move || GetMonData(mon, MON_DATA_MOVE4, NULL) == move) {
            *slot = i;
            break;
        }
    }

    return FALSE;
}

BOOL ScrCmd_SurvivePoisoning(SCRIPTCONTEXT *ctx) {
    u16 *poison = ScriptGetVarPointer(ctx);
    u16 slot = ScriptGetVar(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(ctx->fsys->savedata), slot);
    *poison = SurvivePoisoning(mon);

    return FALSE;
}

BOOL ScrCmd_PartyCountMonsAtOrBelowLevel(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *levelCount = ScriptGetVarPointer(ctx);
    u16 level = ScriptGetVar(ctx);
    u8 i, count;

    u8 partyCount = GetPartyCount(SavArray_PlayerParty_get(fsys->savedata));
    for (i = 0, count = 0, *levelCount = 0; i < partyCount; i++) {
        Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), i);
        if (!GetMonData(mon, MON_DATA_IS_EGG, NULL) && GetMonData(mon, MON_DATA_LEVEL, NULL) <= level) {
            count++;
        }
    }

    *levelCount = count;
    return FALSE;
}

BOOL ScrCmd_MonGetLevel(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *level = ScriptGetVarPointer(ctx);
    u16 slot = ScriptGetVar(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), slot);
    *level = 0;
    if (!GetMonData(mon, MON_DATA_IS_EGG, NULL)) {
        *level = GetMonData(mon, MON_DATA_LEVEL, NULL);
    }

    return FALSE;
}

BOOL ScrCmd_MonGetNature(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *nature = ScriptGetVarPointer(ctx);
    u16 slot = ScriptGetVar(ctx);

    u8 partyCount = GetPartyCount(SavArray_PlayerParty_get(fsys->savedata));
    if (slot >= partyCount) {
        *nature = 0;
        return FALSE;
    }

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), slot);
    if (GetMonData(mon, MON_DATA_IS_EGG, NULL)) {
        *nature = 0;
        return FALSE;
    }

    *nature = GetMonNature(mon);
    return FALSE;
}

BOOL ScrCmd_GetPartySlotWithNature(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *slot = ScriptGetVarPointer(ctx);
    u16 nature = ScriptGetVar(ctx);
    u8 i;

    u8 partyCount = GetPartyCount(SavArray_PlayerParty_get(fsys->savedata));
    for (i = 0, *slot = 255; i < partyCount; i++) {
        Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), i);
        if (!GetMonData(mon , MON_DATA_IS_EGG, NULL) && GetMonNature(mon) == nature) {
            *slot = i;
            break;
        }
    }

    return FALSE;
}

BOOL ScrCmd_MonGetFriendship(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *friendship = ScriptGetVarPointer(ctx);
    u16 slot = ScriptGetVar(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), slot);
    *friendship = GetMonData(mon, MON_DATA_FRIENDSHIP, NULL);

    return FALSE;
}

BOOL ScrCmd_MonAddFriendship(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 friendshipModifier = ScriptGetVar(ctx);
    u16 slot = ScriptGetVar(ctx);
    u16 map = MapHeader_GetMapSec(ctx->fsys->location->mapId);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), slot);
    u16 friendship = GetMonData(mon, MON_DATA_FRIENDSHIP, NULL);
    if (friendshipModifier != 0) {
        if (GetMonData(mon, MON_DATA_POKEBALL, NULL) == BALL_LUXURY) {
            friendshipModifier++;
        }

        if (map == GetMonData(mon, MON_DATA_EGG_MET_LOCATION, NULL)) {
            friendshipModifier++;
        }

        if (GetItemAttr(GetMonData(mon, MON_DATA_HELD_ITEM, NULL), ITEMATTR_HOLD_EFFECT, HEAP_ID_FIELD) == HOLD_EFFECT_FRIENDSHIP_UP) {
            friendshipModifier = friendshipModifier * 150 / 100;
        }
    }

    friendship += friendshipModifier;
    if (friendship > FRIENDSHIP_MAX) {
        friendship = FRIENDSHIP_MAX;
    }
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);

    return FALSE;
}

BOOL ScrCmd_MonSubtractFriendship(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 friendshipModifier = ScriptGetVar(ctx);
    u16 slot = ScriptGetVar(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), slot);
    u16 friendship = GetMonData(mon, MON_DATA_FRIENDSHIP, NULL);
    if (friendshipModifier > friendship) {
        friendship = 0;
    }
    else {
        friendship -= friendshipModifier;
    }
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);

    return FALSE;
}

BOOL ScrCmd_MonGetContestValue(SCRIPTCONTEXT *ctx) {
    u16 slot = ScriptGetVar(ctx);
    u16 contestAttribute = ScriptGetVar(ctx);
    u16 *contestValue = ScriptGetVarPointer(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(ctx->fsys->savedata), slot);
    *contestValue = GetMonData(mon, contestAttribute + MON_DATA_COOL, NULL);

    return FALSE;
}

BOOL ScrCmd_GetPartyLead(SCRIPTCONTEXT *ctx) {
    u16 *slot = ScriptGetVarPointer(ctx);
    *slot = Save_GetPartyLead(ctx->fsys->savedata);
    return FALSE;
}

BOOL ScrCmd_GetPartyLeadAlive(SCRIPTCONTEXT *ctx) {
    u16 *slot = ScriptGetVarPointer(ctx);
    *slot = Save_GetPartyLeadAlive(ctx->fsys->savedata);
    return FALSE;
}

BOOL ScrCmd_GetMonTypes(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *type1 = ScriptGetVarPointer(ctx);
    u16 *type2 = ScriptGetVarPointer(ctx);
    u16 slot = ScriptGetVar(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), slot);
    *type1 = GetMonData(mon, MON_DATA_TYPE_1, NULL);
    *type2 = GetMonData(mon, MON_DATA_TYPE_2, NULL);

    return FALSE;
}

BOOL ScrCmd_GetPartyCount(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *count = ScriptGetVarPointer(ctx);
    *count = GetPartyCount(SavArray_PlayerParty_get(fsys->savedata));
    return FALSE;
}

BOOL ScrCmd_PartyCountNotEgg(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *eggCount = ScriptGetVarPointer(ctx);
    int count, i;

    int partyCount = GetPartyCount(SavArray_PlayerParty_get(fsys->savedata));
    for (i = 0, count = 0; i < partyCount; i++) {
        Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), i);
        if (!GetMonData(mon, MON_DATA_IS_EGG, NULL)) {
            count++;
        }
    }

    *eggCount = count;
    return FALSE;
}

BOOL ScrCmd_CountAliveMons(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *aliveCount = ScriptGetVarPointer(ctx);
    u16 slot = ScriptGetVar(ctx);
    int count, i;

    int partyCount = GetPartyCount(SavArray_PlayerParty_get(fsys->savedata));
    for (i = 0, count = 0; i < partyCount; i++) {
        if (i != slot) {
            Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), i);
            if (!GetMonData(mon, MON_DATA_IS_EGG, NULL) && GetMonData(mon, MON_DATA_HP, NULL) != 0) {
                count++;
            }
        }
    }
    *aliveCount = count;

    return FALSE;
}

BOOL ScrCmd_CountAliveMonsAndPC(SCRIPTCONTEXT *ctx) {
    int partyCount, count, i;
    FieldSystem *fsys = ctx->fsys;
    u16 *pokemonCount = ScriptGetVarPointer(ctx);
    PC_STORAGE *pc = GetStoragePCPointer(fsys->savedata);

    partyCount = GetPartyCount(SavArray_PlayerParty_get(fsys->savedata));
    for (i = 0, count = 0; i < partyCount; i++) {
        Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), i);
        if (!GetMonData(mon, MON_DATA_IS_EGG, NULL) && GetMonData(mon, MON_DATA_HP, NULL) != 0) {
            count++;
        }
    }
    *pokemonCount = count + PCStorage_CountMonsInAllBoxes(pc);

    return FALSE;
}

BOOL ScrCmd_PartyCountEgg(SCRIPTCONTEXT *ctx) {
    int partyCount, count, i;
    FieldSystem *fsys = ctx->fsys;
    u16 *eggCount = ScriptGetVarPointer(ctx);

    partyCount = GetPartyCount(SavArray_PlayerParty_get(fsys->savedata));
    for (i = 0, count = 0; i < partyCount; i++) {
        Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), i);
        if (GetMonData(mon, MON_DATA_IS_EGG, NULL)) {
            count++;
        }
    }
    *eggCount = count;

    return FALSE;
}

BOOL ScrCmd_PartyHasPokerus(SCRIPTCONTEXT *ctx) {
    u16 i, partyCount;
    FieldSystem *fsys = ctx->fsys;
    u16 *pokerus = ScriptGetVarPointer(ctx);

    partyCount = GetPartyCount(SavArray_PlayerParty_get(fsys->savedata));
    for (i = 0, *pokerus = FALSE; i < partyCount; i++) {
        Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), i);
        if (GetMonData(mon, MON_DATA_POKERUS, NULL)) {
            *pokerus = TRUE;
            break;
        }
    }

    return FALSE;
}

BOOL ScrCmd_MonGetGender(SCRIPTCONTEXT *ctx) {
    u16 slot = ScriptGetVar(ctx);
    u16 *gender = ScriptGetVarPointer(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(ctx->fsys->savedata), slot);
    *gender = GetMonData(mon, MON_DATA_GENDER, NULL);

    return FALSE;
}

BOOL ScrCmd_CountMonMoves(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *moveCount = ScriptGetVarPointer(ctx);
    u16 slot = ScriptGetVar(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), slot);
    if (GetMonData(mon, MON_DATA_IS_EGG, NULL)) {
        *moveCount = 0;
        return FALSE;
    }

    u8 count = 0;
    if (GetMonData(mon, MON_DATA_MOVE1, NULL) != MOVE_NONE) {
        count++;
    }

    if (GetMonData(mon, MON_DATA_MOVE2, NULL) != MOVE_NONE) {
        count++;
    }

    if (GetMonData(mon, MON_DATA_MOVE3, NULL) != MOVE_NONE) {
        count++;
    }

    if (GetMonData(mon, MON_DATA_MOVE4, NULL) != MOVE_NONE) {
        count++;
    }

    *moveCount = count;
    return FALSE;
}

BOOL ScrCmd_MonForgetMove(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 pokemonSlot = ScriptGetVar(ctx);
    u16 moveSlot = ScriptGetVar(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), pokemonSlot);
    MonDeleteMoveSlot(mon, moveSlot);

    return FALSE;
}

BOOL ScrCmd_MonGetMove(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *move = ScriptGetVarPointer(ctx);
    u16 pokemonSlot = ScriptGetVar(ctx);
    u16 moveSlot = ScriptGetVar(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), pokemonSlot);
    *move = GetMonData(mon, moveSlot + MON_DATA_MOVE1, NULL);

    return FALSE;
}

BOOL ScrCmd_KenyaCheck(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *kenya = ScriptGetVarPointer(ctx);
    u16 slot = ScriptGetVar(ctx);
    u8 val = ScriptReadByte(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), slot);
    if (!ItemIdIsMail(GetMonData(mon, MON_DATA_HELD_ITEM, NULL))) {
        *kenya = FALSE;
        return FALSE;
    }

    if (val == 0) {
        *kenya = TRUE;
        return FALSE;
    }

    HandleLoadOverlay(FS_OVERLAY_ID(npc_trade), OVY_LOAD_ASYNC);
    MAIL *kenyaMail = NPCTrade_MakeKenyaMail();
    MAIL *mail = Mail_New(HEAP_ID_FIELD);
    GetMonData(mon, MON_DATA_MAIL_STRUCT, mail);
    *kenya = Mail_compare(kenyaMail, mail);
    FreeToHeap(mail);
    FreeToHeap(kenyaMail);
    UnloadOverlayByID(FS_OVERLAY_ID(npc_trade));

    return FALSE;
}

BOOL ScrCmd_KenyaCheckPartyOrMailbox(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *kenya = ScriptGetVarPointer(ctx);
    *kenya = FALSE;
    int i;

    PARTY *party = SavArray_PlayerParty_get(fsys->savedata);
    HandleLoadOverlay(FS_OVERLAY_ID(npc_trade), OVY_LOAD_ASYNC);
    MAIL *kenyaMail = NPCTrade_MakeKenyaMail();
    MAIL *mail = Mail_New(HEAP_ID_FIELD);
    UnloadOverlayByID(FS_OVERLAY_ID(npc_trade));

    for (i = 0; i < GetPartyCount(party); i++) {
        Pokemon *mon = GetPartyMonByIndex(party, i);
        if (ItemIdIsMail(GetMonData(mon, MON_DATA_HELD_ITEM, NULL))) {
            GetMonData(mon, MON_DATA_MAIL_STRUCT, mail);
            if (Mail_compare(kenyaMail, mail)) {
                *kenya = TRUE;
                FreeToHeap(mail);
                FreeToHeap(kenyaMail);
                return FALSE;
            }
        }
    }

    MAILBOX *mailbox = Sav2_Mailbox_get(fsys->savedata);
    i = 0;
    while (TRUE) {
        Mailbox_FetchMailToBuffer(mailbox->msgs, 0, i, mail);
        if (Mail_TypeIsValid(mail) && Mail_compare(kenyaMail, mail)) {
            *kenya = TRUE;
            break;
        }

        i++;
        if (i >= MAILBOX_MSG_COUNT) {
            break;
        }
    }

    FreeToHeap(mail);
    FreeToHeap(kenyaMail);
    return FALSE;
}

BOOL ScrCmd_MonGiveMail(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 slot = ScriptGetVar(ctx);
    u16 item;

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), slot);
    if (!ItemIdIsMail(GetMonData(mon, MON_DATA_HELD_ITEM, NULL))) {
        return FALSE;
    }

    item = ITEM_NONE;
    MAIL *mail = Mail_New(HEAP_ID_FIELD);
    Mail_init(mail);
    SetMonData(mon, MON_DATA_MAIL_STRUCT, mail);
    SetMonData(mon, MON_DATA_HELD_ITEM, &item);
    FreeToHeap(mail);

    return FALSE;
}

BOOL ScrCmd_PlayerHasSpecies(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *playerHasSpecies = ScriptGetVarPointer(ctx);
    u16 species = ScriptGetVar(ctx);
    u8 i;

    u8 partyCount = GetPartyCount(SavArray_PlayerParty_get(fsys->savedata));
    for (i = 0, *playerHasSpecies = FALSE; i < partyCount; i++) {
        Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), i);
        if (!GetMonData(mon, MON_DATA_IS_EGG, NULL) && (u16)GetMonData(mon, MON_DATA_SPECIES, NULL) == species) {
            *playerHasSpecies = TRUE;
            break;
        }
    }

    return FALSE;
}

BOOL ScrCmd_CountPartyMonsOfSpecies(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *speciesCount = ScriptGetVarPointer(ctx);
    u16 species = ScriptGetVar(ctx);
    u16 array[6];
    u8 i, j;

    for (i = 0; i < 6; i++) {
        array[i] = 0;
    }

    u8 partyCount = GetPartyCount(SavArray_PlayerParty_get(fsys->savedata));
    for (i = 0, *speciesCount = 0; i < partyCount; i++) {
        Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), i);
        if (!GetMonData(mon, MON_DATA_IS_EGG, NULL)) {
            u16 monSpecies = GetMonData(mon, MON_DATA_SPECIES, NULL);
            if (species == 0) {
                array[i] = monSpecies;
                for (j = 0; j < i; j++) {
                    if (array[j] == array[i]) {
                        *speciesCount = 1;
                        return FALSE;
                    }
                }
            }
            else if (species == monSpecies) {
                *speciesCount = *speciesCount + 1;
            }
        }
    }

    return FALSE;
}

BOOL ScrCmd_GetPartySlotWithSpecies(SCRIPTCONTEXT *ctx) {
    FieldSystem *fsys = ctx->fsys;
    u16 *slot = ScriptGetVarPointer(ctx);
    u16 species = ScriptGetVar(ctx);
    u8 i;

    u8 partyCount = GetPartyCount(SavArray_PlayerParty_get(fsys->savedata));
    for (i = 0, *slot = 255; i < partyCount; i++) {
        Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), i);
        if (!GetMonData(mon, MON_DATA_IS_EGG, NULL) && (u16)GetMonData(mon, MON_DATA_SPECIES, NULL) == species) {
            *slot = i;
            break;
        }
    }

    return FALSE;
}

BOOL ScrCmd_MonGetRibbonCount(SCRIPTCONTEXT *ctx) {
    u16 *ribbons = ScriptGetVarPointer(ctx);
    u16 slot = ScriptGetVar(ctx);
    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(ctx->fsys->savedata), slot);

    u16 i, count;
    for (i = 0, count = 0; i < RIBBON_MAX; i++) {
        if (GetMonData(mon, GetRibbonAttr(i, RIBBONDAT_MONDATNO), NULL)) {
            count++;
        }
    }
    *ribbons = count;

    return FALSE;
}

BOOL ScrCmd_GetPartyRibbonCount(SCRIPTCONTEXT *ctx) {
    PARTY *party;
    u16 i, j, count;

    u16 *ribbons = ScriptGetVarPointer(ctx);
    u16 partyCount = GetPartyCount(SavArray_PlayerParty_get(ctx->fsys->savedata));
    party = SavArray_PlayerParty_get(ctx->fsys->savedata);

    for (i = 0, count = 0; i < RIBBON_MAX; i++) {
        for (j = 0; j < partyCount; j++) {
            Pokemon *mon = GetPartyMonByIndex(party, j);
            if (!GetMonData(mon, MON_DATA_IS_EGG, NULL) && GetMonData(mon, GetRibbonAttr(i, RIBBONDAT_MONDATNO), NULL)) {
                count++;
                break;
            }
        }
    }
    *ribbons = count;

    return FALSE;
}

BOOL ScrCmd_MonHasRibbon(SCRIPTCONTEXT *ctx) {
    u16 *hasRibbon = ScriptGetVarPointer(ctx);
    u16 slot = ScriptGetVar(ctx);
    u16 ribbon = ScriptGetVar(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(ctx->fsys->savedata), slot);
    *hasRibbon = GetMonData(mon, GetRibbonAttr(ribbon, RIBBONDAT_MONDATNO), NULL);

    return FALSE;
}

BOOL ScrCmd_GiveRibbon(SCRIPTCONTEXT *ctx) {
    u16 slot = ScriptGetVar(ctx);
    u16 ribbon = ScriptGetVar(ctx);
    u8 hasRibbon = TRUE;

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(ctx->fsys->savedata), slot);
    SetMonData(mon, GetRibbonAttr(ribbon, RIBBONDAT_MONDATNO), &hasRibbon);

    return FALSE;
}

BOOL ScrCmd_PartyLegalCheck(SCRIPTCONTEXT *ctx) {
    u16 i, j;

    u16 *legal = ScriptGetVarPointer(ctx);
    u16 partyCount = GetPartyCount(SavArray_PlayerParty_get(ctx->fsys->savedata));
    PARTY *party = SavArray_PlayerParty_get(ctx->fsys->savedata);

    for (i = 0; i < RIBBON_MAX; i++) {
        for (j = 0; j < partyCount; j++) {
            Pokemon *mon = GetPartyMonByIndex(party, j);
            if (GetMonData(mon, MON_DATA_IS_EGG, NULL) && GetMonData(mon, MON_DATA_CHECKSUM_FAILED, NULL)) {
                *legal = TRUE;
                return FALSE;
            }
        }
    }

    *legal = FALSE;
    return FALSE;
}

BOOL ScrCmd_GetPartySlotWithFatefulEncounter(SCRIPTCONTEXT *ctx) {
    u8 partyCount, i;
    FieldSystem *fsys = ctx->fsys;
    u16 *slot = ScriptGetVarPointer(ctx);
    u16 species = ScriptGetVar(ctx);

    partyCount = GetPartyCount(SavArray_PlayerParty_get(fsys->savedata));
    for (i = 0, *slot = 255; i < partyCount; i++) {
        Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), i);
        if (!GetMonData(mon, MON_DATA_IS_EGG, NULL)) {
            if ((u16)GetMonData(mon, MON_DATA_SPECIES, NULL) == species && GetMonData(mon, MON_DATA_FATEFUL_ENCOUNTER, NULL) == TRUE) {
                *slot = i;
                break;
            }
        }
    }

    return FALSE;
}

BOOL ScrCmd_MonHasItem(SCRIPTCONTEXT *ctx) {
    int i;
    FieldSystem *fsys = ctx->fsys;
    u16 item = ScriptGetVar(ctx);
    u16 *hasItem = ScriptGetVarPointer(ctx);

    int partyCount = GetPartyCount(SavArray_PlayerParty_get(fsys->savedata));
    for (i = 0, *hasItem = FALSE; i < partyCount; i++) {
        Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(fsys->savedata), i);
        if (GetMonData(mon, MON_DATA_HELD_ITEM, NULL) == item) {
            *hasItem = TRUE;
            break;
        }
    }

    return FALSE;
}

BOOL ScrCmd_GetPartymonForme(SCRIPTCONTEXT *ctx) {
    u16 slot = ScriptGetVar(ctx);
    u16 *forme = ScriptGetVarPointer(ctx);

    Pokemon *mon = GetPartyMonByIndex(SavArray_PlayerParty_get(ctx->fsys->savedata), slot);
    *forme = GetMonData(mon, MON_DATA_FORME, NULL);

    return FALSE;
}


BOOL ScrCmd_MonAddContestValue(SCRIPTCONTEXT *ctx) {
    Pokemon *mon;
    u8 contestValue = 0;
    u16 slot = ScriptGetVar(ctx);
    u8 contestAttribute = ScriptReadByte(ctx);
    int contestModifier = ScriptGetVar(ctx);

    if (contestAttribute >= 6) {
        return FALSE;
    }

    mon = GetPartyMonByIndex(SavArray_PlayerParty_get(ctx->fsys->savedata), slot);
    if (GetMonData(mon, MON_DATA_SHEEN, NULL) == 255) {
        return FALSE;
    }

    contestAttribute += MON_DATA_COOL;
    contestValue = GetMonData(mon, contestAttribute, NULL);

    if ((contestModifier + contestValue) > 255) {
        contestValue = 255;
    }
    else {
        contestValue += contestModifier;
    }
    SetMonData(mon, contestAttribute, &contestValue);

    return FALSE;
}
