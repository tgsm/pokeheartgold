#include "scrcmd.h"
#include "bag.h"
#include "constants/map_sections.h"
#include "fashion_case.h"
#include "math_util.h"
#include "msgdata/msg.naix"
#include "msgdata/msg/msg_0209.h"
#include "photo_album.h"
#include "pokedex.h"
#include "pokewalker.h"
#include "ribbon.h"
#include "script_pokemon_util.h"
#include "sys_vars.h"
#include "trainer_memo.h"

// FIXME: Move this to its own header.
typedef struct SaveStruct11 {
    u16 unk0[12];
    u8 unk18[8];
} SaveStruct11; // size: 0x20
extern String *sub_020290E4(SaveStruct11 *a0, HeapID heapId);

union MysteryGiftUnion {
    struct {
        u8 unk0[4];
        Pokemon pokemon;
    } mon;
    struct {
        u32 itemId;
    } bag;
    struct {
        SaveStruct11 unk;
    } battleRules;
    struct {
        u32 value;
    } decoration;
    struct {
        u32 type;
        u32 value;
    } monDecoration;
    struct {
        u8 courseNum;
    } pokewalker;
    struct {
        PHOTO photo;
    } memorialPhoto;
};

typedef struct MGGmmState {
    FieldSystem *fieldSystem;
    MessageFormat *messageFormat;
    union MysteryGiftUnion *unk8;
} MGGmmState;

typedef BOOL (*CheckFunc)(FieldSystem*, union MysteryGiftUnion*);
typedef void (*GiveFunc)(FieldSystem*, union MysteryGiftUnion*);
typedef void (*MessageSuccessFunc)(MGGmmState*, u16*, u16*);
typedef void (*MessageFailureFunc)(MGGmmState*, u16*, u16*);

struct MysteryGiftAction {
    CheckFunc checkFunc;
    GiveFunc giveFunc;
    MessageSuccessFunc messageSuccessFunc;
    MessageFailureFunc messageFailureFunc;
};

extern u16 GetMysteryGiftTagByIdx(u32 giftIndex);
extern union MysteryGiftUnion *GetMysteryGiftDataByIdx(u32 giftIndex);
extern u32 GetFirstQueuedMysteryGiftIdx(void);
extern void SetMysteryGiftReceivedByIdx(u32 giftIndex);
extern void sub_020291D4(SaveData *saveData, SaveStruct11 *a1);

void FieldSystem_InitGetMysteryGiftGmmState(MGGmmState *state, FieldSystem *fieldSystem, MessageFormat *MessageFormat, union MysteryGiftUnion *a3);
u16 FieldSystem_GetTagOfNextMG(FieldSystem *fieldSystem);
union MysteryGiftUnion *FieldSystem_GetDataOfNextMG(FieldSystem *fieldSystem);
void FieldSystem_SetQueuedMGReceived(FieldSystem *fieldSystem);

#define CHECK_DECL(name) BOOL name(FieldSystem *fieldSystem, union MysteryGiftUnion *data)
#define GIVE_DECL(name) void name(FieldSystem *fieldSystem, union MysteryGiftUnion *data)
#define SUCCESS_DECL(name) void name(MGGmmState *state, u16 *gmmNum, u16 *msgNum)
#define FAILURE_DECL(name) void name(MGGmmState *state, u16 *gmmNum, u16 *msgNum)

#define GEN_DECLS(name) \
    CHECK_DECL(MGCheck_##name); \
    GIVE_DECL(MGGive_##name); \
    SUCCESS_DECL(MGMessageSuccess_##name); \
    FAILURE_DECL(MGMessageFailure_##name)

CHECK_DECL(MGCheck_PartySpace);
GIVE_DECL(MGGive_ManaphyEgg);
SUCCESS_DECL(MGMessageSuccess_ManaphyEgg);
GIVE_DECL(MGGive_Mon);
SUCCESS_DECL(MGMessageSuccess_GiveMon);
FAILURE_DECL(MGMessageFailure_GiveMon);
GIVE_DECL(MGGive_Egg);
SUCCESS_DECL(MGMessageSuccess_Egg);

GEN_DECLS(Item);
GEN_DECLS(BattleRules);
GEN_DECLS(Decoration);
GEN_DECLS(MonDeco);
GEN_DECLS(MemberCard);
GEN_DECLS(OaksLetter);
GEN_DECLS(AzureFlute);
GEN_DECLS(PoketchApp);
GEN_DECLS(SecretKey);
GEN_DECLS(PokewalkerCourse);
GEN_DECLS(MemorialPhoto);

static const struct MysteryGiftAction sScriptMysteryGiftActionTable[] = {
    { MGCheck_PartySpace, MGGive_Mon, MGMessageSuccess_GiveMon, MGMessageFailure_GiveMon },
    { MGCheck_PartySpace, MGGive_Egg, MGMessageSuccess_Egg, MGMessageFailure_GiveMon },
    { MGCheck_Item, MGGive_Item, MGMessageSuccess_Item, MGMessageFailure_Item },
    { MGCheck_BattleRules, MGGive_BattleRules, MGMessageSuccess_BattleRules, MGMessageFailure_BattleRules },
    { MGCheck_Decoration, MGGive_Decoration, MGMessageSuccess_Decoration, MGMessageFailure_Decoration },
    { MGCheck_MonDeco, MGGive_MonDeco, MGMessageSuccess_MonDeco, MGMessageFailure_MonDeco },
    { MGCheck_PartySpace, MGGive_ManaphyEgg, MGMessageSuccess_ManaphyEgg, MGMessageFailure_GiveMon },
    { MGCheck_MemberCard, MGGive_MemberCard, MGMessageSuccess_MemberCard, MGMessageFailure_MemberCard },
    { MGCheck_OaksLetter, MGGive_OaksLetter, MGMessageSuccess_OaksLetter, MGMessageFailure_OaksLetter },
    { MGCheck_AzureFlute, MGGive_AzureFlute, MGMessageSuccess_AzureFlute, MGMessageFailure_AzureFlute },
    { MGCheck_PoketchApp, MGGive_PoketchApp, MGMessageSuccess_PoketchApp, MGMessageFailure_PoketchApp },
    { MGCheck_SecretKey, MGGive_SecretKey, MGMessageSuccess_SecretKey, MGMessageFailure_SecretKey },
    { MGCheck_PartySpace, MGGive_Mon, MGMessageSuccess_GiveMon, MGMessageFailure_GiveMon },
    { MGCheck_PokewalkerCourse, MGGive_PokewalkerCourse, MGMessageSuccess_PokewalkerCourse, MGMessageFailure_PokewalkerCourse },
    { MGCheck_MemorialPhoto, MGGive_MemorialPhoto, MGMessageSuccess_MemorialPhoto, MGMessageFailure_MemorialPhoto },
};

void FieldSystem_InitGetMysteryGiftGmmState(MGGmmState *state, FieldSystem *fieldSystem, MessageFormat *messageFormat, union MysteryGiftUnion *a3) {
    state->fieldSystem = fieldSystem;
    state->messageFormat = messageFormat;
    state->unk8 = a3;
}

u16 FieldSystem_GetTagOfNextMG(FieldSystem *fieldSystem) {
    return GetMysteryGiftTagByIdx(GetFirstQueuedMysteryGiftIdx());
}

union MysteryGiftUnion *FieldSystem_GetDataOfNextMG(FieldSystem *fieldSystem) {
    return GetMysteryGiftDataByIdx(GetFirstQueuedMysteryGiftIdx());
}

void FieldSystem_SetQueuedMGReceived(FieldSystem *fieldSystem) {
    SetMysteryGiftReceivedByIdx(GetFirstQueuedMysteryGiftIdx());
}

extern DeleteStaticPointerToMysteryGift();
extern GetStaticPointerToMysteryGift();
extern GetStaticPointerToSaveMysteryGift();

BOOL ScrCmd_MysteryGift(ScriptContext *ctx) {
    u16 action = ScriptReadHalfword(ctx);

    switch (action) {
        case 0:
            GetStaticPointerToSaveMysteryGift(ctx->fieldSystem->saveData, 32);
            break;
        case 7:
            DeleteStaticPointerToMysteryGift(ctx->fieldSystem->saveData, 0);
            break;
        case 8:
            DeleteStaticPointerToMysteryGift(ctx->fieldSystem->saveData, 1);
            break;
        case 1: {
            u16 *retPtr = ScriptGetVarPointer(ctx);
            if (FieldSystem_GetTagOfNextMG(ctx->fieldSystem) != 0) {
                *retPtr = TRUE;
            } else {
                *retPtr = FALSE;
            }
            break;
        }
        case 2: {
            u16 *retPtr = ScriptGetVarPointer(ctx);
            *retPtr = FieldSystem_GetTagOfNextMG(ctx->fieldSystem);
            break;
        }
        case 3: {
            u16 *retPtr = ScriptGetVarPointer(ctx);
            const struct MysteryGiftAction *action = &sScriptMysteryGiftActionTable[FieldSystem_GetTagOfNextMG(ctx->fieldSystem) - 1];
            *retPtr = action->checkFunc(ctx->fieldSystem, FieldSystem_GetDataOfNextMG(ctx->fieldSystem));
            break;
        }
        case 4: {
            const struct MysteryGiftAction *action = &sScriptMysteryGiftActionTable[FieldSystem_GetTagOfNextMG(ctx->fieldSystem) - 1];
            action->giveFunc(ctx->fieldSystem, FieldSystem_GetDataOfNextMG(ctx->fieldSystem));
            FieldSystem_SetQueuedMGReceived(ctx->fieldSystem);
            break;
        }
        case 5: {
            const struct MysteryGiftAction *action = &sScriptMysteryGiftActionTable[FieldSystem_GetTagOfNextMG(ctx->fieldSystem) - 1];
            MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
            u16 *gmmNumPtr = ScriptGetVarPointer(ctx);
            u16 *msgNumPtr = ScriptGetVarPointer(ctx);

            MGGmmState state;
            FieldSystem_InitGetMysteryGiftGmmState(&state, ctx->fieldSystem, *messageFormat, FieldSystem_GetDataOfNextMG(ctx->fieldSystem));
            action->messageSuccessFunc(&state, gmmNumPtr, msgNumPtr);
            break;
        }
        case 6: {
            const struct MysteryGiftAction *action = &sScriptMysteryGiftActionTable[FieldSystem_GetTagOfNextMG(ctx->fieldSystem) - 1];
            MessageFormat **messageFormat = FieldSysGetAttrAddr(ctx->fieldSystem, SCRIPTENV_MESSAGE_FORMAT);
            u16 *gmmNumPtr = ScriptGetVarPointer(ctx);
            u16 *msgNumPtr = ScriptGetVarPointer(ctx);

            MGGmmState state;
            FieldSystem_InitGetMysteryGiftGmmState(&state, ctx->fieldSystem, *messageFormat, FieldSystem_GetDataOfNextMG(ctx->fieldSystem));
            action->messageFailureFunc(&state, gmmNumPtr, msgNumPtr);
            break;
        }
    }

    return FALSE;
}

BOOL MGCheck_PartySpace(FieldSystem *fieldSystem, union MysteryGiftUnion *data) {
    return Party_GetCount(SaveArray_Party_Get(fieldSystem->saveData)) < PARTY_SIZE;
}

void MGGive_ManaphyEgg(FieldSystem *fieldSystem, union MysteryGiftUnion *data) {
    GiveEgg(HEAP_ID_32, fieldSystem->saveData, SPECIES_MANAPHY, EGG_MANAPHY, MAPSECTYPE_EXTERNAL, 1);
}

void MGMessageSuccess_ManaphyEgg(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00013;
    BufferPlayersName(state->messageFormat, 0, Save_PlayerData_GetProfileAddr(state->fieldSystem->saveData));
}

#ifdef NONMATCHING
void MGGive_Mon(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(fieldSystem);
    PlayerProfile *profile = Save_PlayerData_GetProfileAddr(fieldSystem->saveData);
    SaveVarsFlags *varsFlags = Save_VarsFlags_Get(fieldSystem->saveData);
    Pokemon *mon = &data->mon.pokemon;
    struct MGMonRibbons *ribbons = &data->mon.ribbons;
    Pokemon *unk = NULL;
    u32 eggMetLocation = GetMonData(mon, MON_DATA_EGG_MET_LOCATION, NULL);
    u32 personality = GetMonData(mon, MON_DATA_PERSONALITY, NULL);
    u32 otId = GetMonData(mon, MON_DATA_OTID, NULL);
    u32 rand = PRandom(OS_GetTick());

    u32 newPersonality = rand;
    if (personality != 0) {
        if (personality == 1) {
            while (CalcShininessByOtIdAndPersonality(otId, newPersonality) != 0) {
                newPersonality = PRandom(newPersonality);
            }
        } else {
            newPersonality = personality;
        }
    }

    SetMonPersonality(mon, newPersonality);

    u32 gender = GetMonGender(mon);
    SetMonData(mon, MON_DATA_GENDER, &gender);

    u32 spDefIv = GetMonData(mon, MON_DATA_SPDEF_IV, NULL);
    u32 spAtkIv = GetMonData(mon, MON_DATA_SPATK_IV, NULL);
    u32 speedIv = GetMonData(mon, MON_DATA_SPEED_IV, NULL);
    u32 defenseIv = GetMonData(mon, MON_DATA_DEF_IV, NULL);
    u32 hpIv = GetMonData(mon, MON_DATA_HP_IV, NULL);
    u32 attackIv = GetMonData(mon, MON_DATA_ATK_IV, NULL);
    u32 ivTotal = spDefIv + spAtkIv + speedIv + defenseIv + hpIv + attackIv;
    if (ivTotal == 0) {
        u32 rand = LCRandom();
        u32 newHpIv = (rand & 0x1F) >> 0;
        SetMonData(mon, MON_DATA_HP_IV, &newHpIv);
        u32 newAttackIv = (rand & 0x3E0) >> 5;
        SetMonData(mon, MON_DATA_ATK_IV, &newAttackIv);
        u32 newDefenseIv = (rand & 0x7C00) >> 10;
        SetMonData(mon, MON_DATA_DEF_IV, &newDefenseIv);

        rand = LCRandom();
        u32 newSpeedIv = (rand & 0x1F) >> 0;
        SetMonData(mon, MON_DATA_SPEED_IV, &newSpeedIv);
        u32 newSpAtkIv = (rand & 0x3E0) >> 5;
        SetMonData(mon, MON_DATA_SPATK_IV, &newSpAtkIv);
        u32 newSpDefIv = (rand & 0x7C00) >> 10;
        SetMonData(mon, MON_DATA_SPDEF_IV, &newSpDefIv);
    }

    SaveSpecialRibbons *specialRibbons = Save_SpecialRibbons_Get(fieldSystem->saveData);

    if (GetMonData(mon, MON_DATA_RED_RIBBON, NULL) != FALSE) {
        specialRibbons->ribbons[GetSpecialRibbonNo(RIBBON_RED)] = ribbons->redRibbon;
    }
    if (GetMonData(mon, MON_DATA_GREEN_RIBBON, NULL) != FALSE) {
        specialRibbons->ribbons[GetSpecialRibbonNo(RIBBON_GREEN)] = ribbons->greenRibbon;
    }
    if (GetMonData(mon, MON_DATA_BLUE_RIBBON, NULL) != FALSE) {
        specialRibbons->ribbons[GetSpecialRibbonNo(RIBBON_BLUE)] = ribbons->blueRibbon;
    }
    if (GetMonData(mon, MON_DATA_FESTIVAL_RIBBON, NULL) != FALSE) {
        specialRibbons->ribbons[GetSpecialRibbonNo(RIBBON_FESTIVAL)] = ribbons->festivalRibbon;
    }
    if (GetMonData(mon, MON_DATA_CARNIVAL_RIBBON, NULL) != FALSE) {
        specialRibbons->ribbons[GetSpecialRibbonNo(RIBBON_CARNIVAL)] = ribbons->carnivalRibbon;
    }
    if (GetMonData(mon, MON_DATA_CLASSIC_RIBBON, NULL) != FALSE) {
        specialRibbons->ribbons[GetSpecialRibbonNo(RIBBON_CLASSIC)] = ribbons->classicRibbon;
    }
    if (GetMonData(mon, MON_DATA_PREMIER_RIBBON, NULL) != FALSE) {
        specialRibbons->ribbons[GetSpecialRibbonNo(RIBBON_PREMIER)] = ribbons->premierRibbon;
    }
    if (GetMonData(mon, MON_DATA_HOENN_MARINE_RIBBON, NULL) != FALSE) {
        specialRibbons->ribbons[GetSpecialRibbonNo(RIBBON_HOENN_MARINE)] = ribbons->premierRibbon;
    }
    if (GetMonData(mon, MON_DATA_HOENN_LAND_RIBBON, NULL) != FALSE) {
        specialRibbons->ribbons[GetSpecialRibbonNo(RIBBON_HOENN_LAND)] = ribbons->premierRibbon;
    }
    if (GetMonData(mon, MON_DATA_HOENN_SKY_RIBBON, NULL) != FALSE) {
        specialRibbons->ribbons[GetSpecialRibbonNo(RIBBON_HOENN_SKY)] = ribbons->premierRibbon;
    }

    Pokemon *newMon = mon;
    if (data->mon.unk0 == 0) {
        String *playerName = PlayerProfile_GetPlayerName_NewString(profile, HEAP_ID_32);
        u32 playerOtId = PlayerProfile_GetTrainerID(profile);
        u32 playerGender = PlayerProfile_GetTrainerGender(profile);
        newMon = AllocMonZeroed(HEAP_ID_32);
        CopyPokemonToPokemon(mon, newMon);
        SetMonData(newMon, MON_DATA_OT_NAME_2, playerName);
        SetMonData(newMon, MON_DATA_OTID, &playerOtId);
        SetMonData(newMon, MON_DATA_MET_GENDER, &playerGender);
        String_Delete(playerName);
        unk = newMon;
    }

    MonSetTrainerMemo(newMon, profile, 4, sub_02017FE4(2, eggMetLocation), 32);

    if (GetMonData(newMon, MON_DATA_SPECIES, NULL) == SPECIES_ARCEUS &&
        GetMonData(newMon, MON_DATA_FATEFUL_ENCOUNTER, NULL) == TRUE &&
        Save_VarsFlags_GetVar404C(varsFlags) == 0)
    {
        Save_VarsFlags_SetVar404C(varsFlags, 1);
    }

    CalcMonLevelAndStats(newMon);

    if (Party_AddMon(SaveArray_Party_Get(fieldSystem->saveData), newMon)) {
        UpdatePokedexWithReceivedSpecies(fieldSystem->saveData, newMon);
    }

    if (unk != NULL) {
        FreeToHeap(unk);
    }
}
#else
asm void MGGive_Mon(FieldSystem *fieldSystem, union MysteryGiftUnion *data) {
    push {r4, r5, r6, r7, lr}
    sub sp, #0x3c
    add r7, r0, #0
    bl FieldSystem_GetDataOfNextMG
    str r0, [sp, #0x14]
    ldr r0, [r7, #0xc]
    bl Save_PlayerData_GetProfileAddr
    str r0, [sp, #0x10]
    ldr r0, [r7, #0xc]
    bl Save_VarsFlags_Get
    str r0, [sp, #0xc]
    mov r0, #0
    str r0, [sp, #8]
    ldr r0, [sp, #0x14]
    ldr r2, [sp, #8]
    add r5, r0, #0
    add r4, r0, #4
    add r0, r4, #0
    mov r1, #0x98
    add r5, #0xf0
    bl GetMonData
    mov r1, #0
    str r0, [sp, #4]
    add r0, r4, #0
    add r2, r1, #0
    bl GetMonData
    str r0, [sp, #0x18]
    add r0, r4, #0
    mov r1, #7
    mov r2, #0
    bl GetMonData
    add r6, r0, #0
    bl OS_GetTick
    bl PRandom
    add r1, r0, #0
    ldr r0, [sp, #0x18]
    str r1, [sp, #0x38]
    cmp r0, #0
    beq _0204C074
    cmp r0, #1
    bne _0204C072
    add r0, r6, #0
    bl CalcShininessByOtIdAndPersonality
    cmp r0, #0
    beq _0204C074
_0204C05C:
    ldr r0, [sp, #0x38]
    bl PRandom
    add r1, r0, #0
    add r0, r6, #0
    str r1, [sp, #0x38]
    bl CalcShininessByOtIdAndPersonality
    cmp r0, #0
    bne _0204C05C
    b _0204C074
_0204C072:
    str r0, [sp, #0x38]
_0204C074:
    ldr r1, [sp, #0x38]
    add r0, r4, #0
    bl SetMonPersonality
    add r0, r4, #0
    bl GetMonGender
    str r0, [sp, #0x34]
    add r0, r4, #0
    mov r1, #0x6f
    add r2, sp, #0x34
    bl SetMonData
    add r0, r4, #0
    mov r1, #0x4b
    mov r2, #0
    bl GetMonData
    str r0, [sp, #0x1c]
    add r0, r4, #0
    mov r1, #0x4a
    mov r2, #0
    bl GetMonData
    str r0, [sp, #0x20]
    add r0, r4, #0
    mov r1, #0x49
    mov r2, #0
    bl GetMonData
    str r0, [sp, #0x24]
    add r0, r4, #0
    mov r1, #0x48
    mov r2, #0
    bl GetMonData
    str r0, [sp, #0x28]
    add r0, r4, #0
    mov r1, #0x46
    mov r2, #0
    bl GetMonData
    add r6, r0, #0
    add r0, r4, #0
    mov r1, #0x47
    mov r2, #0
    bl GetMonData
    add r1, r6, r0
    ldr r0, [sp, #0x28]
    add r1, r0, r1
    ldr r0, [sp, #0x24]
    add r1, r0, r1
    ldr r0, [sp, #0x20]
    add r1, r0, r1
    ldr r0, [sp, #0x1c]
    add r0, r0, r1
    str r0, [sp, #0x34]
    bne _0204C166
    bl LCRandom
    add r6, r0, #0
    mov r0, #0x1f
    and r0, r6
    str r0, [sp, #0x38]
    add r0, r4, #0
    mov r1, #0x46
    add r2, sp, #0x38
    bl SetMonData
    mov r0, #0x3e
    lsl r0, r0, #4
    and r0, r6
    lsr r0, r0, #5
    str r0, [sp, #0x38]
    add r0, r4, #0
    mov r1, #0x47
    add r2, sp, #0x38
    bl SetMonData
    mov r0, #0x1f
    lsl r0, r0, #0xa
    and r0, r6
    lsr r0, r0, #0xa
    str r0, [sp, #0x38]
    add r0, r4, #0
    mov r1, #0x48
    add r2, sp, #0x38
    bl SetMonData
    bl LCRandom
    add r6, r0, #0
    mov r0, #0x1f
    and r0, r6
    str r0, [sp, #0x38]
    add r0, r4, #0
    mov r1, #0x49
    add r2, sp, #0x38
    bl SetMonData
    mov r0, #0x3e
    lsl r0, r0, #4
    and r0, r6
    lsr r0, r0, #5
    str r0, [sp, #0x38]
    add r0, r4, #0
    mov r1, #0x4a
    add r2, sp, #0x38
    bl SetMonData
    mov r0, #0x1f
    lsl r0, r0, #0xa
    and r0, r6
    lsr r0, r0, #0xa
    str r0, [sp, #0x38]
    add r0, r4, #0
    mov r1, #0x4b
    add r2, sp, #0x38
    bl SetMonData
_0204C166:
    ldr r0, [r7, #0xc]
    bl Save_SpecialRibbons_Get
    add r6, r0, #0
    add r0, r4, #0
    mov r1, #0x2e
    mov r2, #0
    bl GetMonData
    cmp r0, #0
    beq _0204C186
    mov r0, #RIBBON_RED
    bl GetSpecialRibbonNo
    ldrb r1, [r5]
    strb r1, [r6, r0]
_0204C186:
    add r0, r4, #0
    mov r1, #0x2f
    mov r2, #0
    bl GetMonData
    cmp r0, #0
    beq _0204C19E
    mov r0, #RIBBON_GREEN
    bl GetSpecialRibbonNo
    ldrb r1, [r5, #1]
    strb r1, [r6, r0]
_0204C19E:
    add r0, r4, #0
    mov r1, #0x30
    mov r2, #0
    bl GetMonData
    cmp r0, #0
    beq _0204C1B6
    mov r0, #RIBBON_BLUE
    bl GetSpecialRibbonNo
    ldrb r1, [r5, #2]
    strb r1, [r6, r0]
_0204C1B6:
    add r0, r4, #0
    mov r1, #0x31
    mov r2, #0
    bl GetMonData
    cmp r0, #0
    beq _0204C1CE
    mov r0, #RIBBON_FESTIVAL
    bl GetSpecialRibbonNo
    ldrb r1, [r5, #3]
    strb r1, [r6, r0]
_0204C1CE:
    add r0, r4, #0
    mov r1, #0x32
    mov r2, #0
    bl GetMonData
    cmp r0, #0
    beq _0204C1E6
    mov r0, #RIBBON_CARNIVAL
    bl GetSpecialRibbonNo
    ldrb r1, [r5, #4]
    strb r1, [r6, r0]
_0204C1E6:
    add r0, r4, #0
    mov r1, #0x33
    mov r2, #0
    bl GetMonData
    cmp r0, #0
    beq _0204C1FE
    mov r0, #RIBBON_CLASSIC
    bl GetSpecialRibbonNo
    ldrb r1, [r5, #5]
    strb r1, [r6, r0]
_0204C1FE:
    add r0, r4, #0
    mov r1, #0x34
    mov r2, #0
    bl GetMonData
    cmp r0, #0
    beq _0204C216
    mov r0, #RIBBON_PREMIER
    bl GetSpecialRibbonNo
    ldrb r1, [r5, #6]
    strb r1, [r6, r0]
_0204C216:
    add r0, r4, #0
    mov r1, #0x67
    mov r2, #0
    bl GetMonData
    cmp r0, #0
    beq _0204C22E
    mov r0, #RIBBON_HOENN_MARINE
    bl GetSpecialRibbonNo
    ldrb r1, [r5, #7]
    strb r1, [r6, r0]
_0204C22E:
    add r0, r4, #0
    mov r1, #0x68
    mov r2, #0
    bl GetMonData
    cmp r0, #0
    beq _0204C246
    mov r0, #RIBBON_HOENN_LAND
    bl GetSpecialRibbonNo
    ldrb r1, [r5, #8]
    strb r1, [r6, r0]
_0204C246:
    add r0, r4, #0
    mov r1, #0x69
    mov r2, #0
    bl GetMonData
    cmp r0, #0
    beq _0204C25E
    mov r0, #RIBBON_HOENN_SKY
    bl GetSpecialRibbonNo
    ldrb r1, [r5, #9]
    strb r1, [r6, r0]
_0204C25E:
    ldr r0, [sp, #0x14]
    ldr r0, [r0, #0]
    cmp r0, #0
    bne _0204C2B6
    ldr r0, [sp, #0x10]
    mov r1, #0x20
    bl PlayerProfile_GetPlayerName_NewString
    add r5, r0, #0
    ldr r0, [sp, #0x10]
    bl PlayerProfile_GetTrainerID
    str r0, [sp, #0x30]
    ldr r0, [sp, #0x10]
    bl PlayerProfile_GetTrainerGender
    str r0, [sp, #0x2c]
    mov r0, #0x20
    bl AllocMonZeroed
    str r0, [sp, #8]
    ldr r1, [sp, #8]
    add r0, r4, #0
    bl CopyPokemonToPokemon
    ldr r0, [sp, #8]
    mov r1, #0x91
    add r2, r5, #0
    bl SetMonData
    ldr r0, [sp, #8]
    mov r1, #7
    add r2, sp, #0x30
    bl SetMonData
    ldr r0, [sp, #8]
    mov r1, #0x9d
    add r2, sp, #0x2c
    bl SetMonData
    add r0, r5, #0
    ldr r4, [sp, #8]
    bl String_Delete
_0204C2B6:
    ldr r1, [sp, #4]
    mov r0, #2
    bl sub_02017FE4
    add r3, r0, #0
    mov r0, #0x20
    str r0, [sp]
    ldr r1, [sp, #0x10]
    add r0, r4, #0
    mov r2, #4
    bl MonSetTrainerMemo
    add r0, r4, #0
    mov r1, #5
    mov r2, #0
    bl GetMonData
    ldr r1, [pc, #0x50] // _0204C32C ; =SPECIES_ARCEUS
    cmp r0, r1
    bne _0204C2FE
    add r0, r4, #0
    mov r1, #0x6e
    mov r2, #0
    bl GetMonData
    cmp r0, #1
    bne _0204C2FE
    ldr r0, [sp, #0xc]
    bl Save_VarsFlags_GetVar404C
    cmp r0, #0
    bne _0204C2FE
    ldr r0, [sp, #0xc]
    mov r1, #1
    bl Save_VarsFlags_SetVar404C
_0204C2FE:
    add r0, r4, #0
    bl CalcMonLevelAndStats
    ldr r0, [r7, #0xc]
    bl SaveArray_Party_Get
    add r1, r4, #0
    bl Party_AddMon
    cmp r0, #0
    beq _0204C31C
    ldr r0, [r7, #0xc]
    add r1, r4, #0
    bl UpdatePokedexWithReceivedSpecies
_0204C31C:
    ldr r0, [sp, #8]
    cmp r0, #0
    beq _0204C326
    bl FreeToHeap
_0204C326:
    add sp, #0x3c
    pop {r4, r5, r6, r7, pc}
    nop
_0204C32C: DCD SPECIES_ARCEUS
}
#endif

void MGMessageSuccess_GiveMon(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(state->fieldSystem);

    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00007;

    BufferPlayersName(state->messageFormat, 0, Save_PlayerData_GetProfileAddr(state->fieldSystem->saveData));
    BufferBoxMonSpeciesNameWithArticle(state->messageFormat, 1, Mon_GetBoxMon(&data->mon.pokemon));
}

void MGMessageFailure_GiveMon(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00004;
}

void MGGive_Egg(FieldSystem *fieldSystem, union MysteryGiftUnion *data) {
    MGGive_Mon(fieldSystem, data);
}

void MGMessageSuccess_Egg(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(state->fieldSystem);

    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00008;

    BufferPlayersName(state->messageFormat, 0, Save_PlayerData_GetProfileAddr(state->fieldSystem->saveData));
    BufferBoxMonSpeciesName(state->messageFormat, 1, Mon_GetBoxMon(&data->mon.pokemon));
}

BOOL MGCheck_Item(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    Bag *bag = Save_Bag_Get(fieldSystem->saveData);
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(fieldSystem);

    return Bag_HasSpaceForItem(bag, data->bag.itemId, 1, HEAP_ID_32);
}

void MGGive_Item(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    Bag *bag = Save_Bag_Get(fieldSystem->saveData);
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(fieldSystem);

    u16 itemId = data->bag.itemId;
    if (itemId == ITEM_ENIGMA_STONE) {
        sub_02066B9C(Save_VarsFlags_Get(fieldSystem->saveData), 0);
    }

    Bag_AddItem(bag, itemId, 1, HEAP_ID_32);
}

void MGMessageSuccess_Item(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(state->fieldSystem);
    u16 itemId = data->bag.itemId;

    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00009;

    BufferPlayersName(state->messageFormat, 0, Save_PlayerData_GetProfileAddr(state->fieldSystem->saveData));
    BufferItemName(state->messageFormat, 1, itemId);
}

void MGMessageFailure_Item(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    Bag *bag = Save_Bag_Get(state->fieldSystem->saveData);
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(state->fieldSystem);
    u16 itemId = data->bag.itemId;

    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00005;

    BufferItemName(state->messageFormat, 0, itemId);
}

BOOL MGCheck_BattleRules(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    return TRUE;
}

void MGGive_BattleRules(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(fieldSystem);
    sub_020291D4(fieldSystem->saveData, &data->battleRules.unk);
}

void MGMessageSuccess_BattleRules(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(state->fieldSystem);
    u16 itemId = data->bag.itemId;

    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00010;

    BufferPlayersName(state->messageFormat, 0, Save_PlayerData_GetProfileAddr(state->fieldSystem->saveData));
    String *string = sub_020290E4(&data->battleRules.unk, HEAP_ID_32);
    BufferString(state->messageFormat, 1, string, 0, 1, 2);
    String_Delete(string);
}

void MGMessageFailure_BattleRules(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00006;
}

BOOL MGCheck_Decoration(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    return FALSE;
}

void MGGive_Decoration(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {

}

void MGMessageSuccess_Decoration(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(state->fieldSystem);
    u32 decoration = data->decoration.value;

    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00011;

    BufferPlayersName(state->messageFormat, 0, Save_PlayerData_GetProfileAddr(state->fieldSystem->saveData));
    BufferDecorationName(state->messageFormat, 1, decoration);
}

void MGMessageFailure_Decoration(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00031;
}

BOOL MGCheck_MonDeco(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(fieldSystem);
    u32 value = data->monDecoration.value;
    u32 type = data->monDecoration.type;

    switch (type) {
        case 1:
            return SealCase_CheckSealQuantity(Save_SealCase_Get(fieldSystem->saveData), value, 1);
        case 2:
            return TRUE;
        case 3:
            return TRUE;
    }

    return FALSE;
}

void MGGive_MonDeco(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(fieldSystem);
    u32 value = data->monDecoration.value;
    u32 type = data->monDecoration.type;

    switch (type) {
        case 1:
            GiveOrTakeSeal(Save_SealCase_Get(fieldSystem->saveData), value, 1);
            return;
        case 2:
            sub_0202BB08(Save_FashionData_GetFashionCase(Save_FashionData_Get(fieldSystem->saveData)), value, 1);
            return;
        case 3:
            sub_0202BBD8(Save_FashionData_GetFashionCase(Save_FashionData_Get(fieldSystem->saveData)), value);
            return;
    }
}

void MGMessageSuccess_MonDeco(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(state->fieldSystem);
    u32 value = data->monDecoration.value;
    u32 type = data->monDecoration.type;

    switch (type) {
        case 1:
            BufferSealName(state->messageFormat, 1, value);
            break;
        case 2:
            BufferFashionName(state->messageFormat, 1, value);
            break;
        case 3:
            BufferContestBackgroundName(state->messageFormat, 1, value);
            break;
    }

    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00012;

    BufferPlayersName(state->messageFormat, 0, Save_PlayerData_GetProfileAddr(state->fieldSystem->saveData));
}

void MGMessageFailure_MonDeco(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00006;
}

BOOL MGCheck_MemberCard(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    return FALSE;
}

void MGGive_MemberCard(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {

}

void MGMessageSuccess_MemberCard(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {

}

void MGMessageFailure_MemberCard(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00031;
}

BOOL MGCheck_OaksLetter(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    return FALSE;
}

void MGGive_OaksLetter(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {

}

void MGMessageSuccess_OaksLetter(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {

}

void MGMessageFailure_OaksLetter(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00031;
}

BOOL MGCheck_SecretKey(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    return FALSE;
}

void MGGive_SecretKey(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {

}

void MGMessageSuccess_SecretKey(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {

}

void MGMessageFailure_SecretKey(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00031;
}

BOOL MGCheck_AzureFlute(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    return FALSE;
}

void MGGive_AzureFlute(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {

}

void MGMessageSuccess_AzureFlute(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {

}

void MGMessageFailure_AzureFlute(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00031;
}

BOOL MGCheck_PoketchApp(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    return FALSE;
}

void MGGive_PoketchApp(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {

}

void MGMessageSuccess_PoketchApp(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {

}

void MGMessageFailure_PoketchApp(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00031;
}

BOOL MGCheck_PokewalkerCourse(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(fieldSystem);
    POKEWALKER *pokewalker = Save_Pokewalker_Get(fieldSystem->saveData);

    u32 courseNum = 0;
    if (data->pokewalker.courseNum < WALKER_COURSE_COUNT) {
        courseNum = data->pokewalker.courseNum;
    }

    return !Pokewalker_CourseIsUnlocked(pokewalker, courseNum);
}

void MGGive_PokewalkerCourse(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    POKEWALKER *pokewalker = Save_Pokewalker_Get(fieldSystem->saveData);
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(fieldSystem);

    if (data->pokewalker.courseNum < WALKER_COURSE_COUNT) {
        Pokewalker_UnlockCourse(pokewalker, data->pokewalker.courseNum);
    }
}

void MGMessageSuccess_PokewalkerCourse(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(state->fieldSystem);

    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00019;

    BufferPlayersName(state->messageFormat, 0, Save_PlayerData_GetProfileAddr(state->fieldSystem->saveData));
    BufferPokewalkerCourseName(state->messageFormat, 1, data->pokewalker.courseNum);
}

void MGMessageFailure_PokewalkerCourse(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(state->fieldSystem);
    POKEWALKER *pokewalker = Save_Pokewalker_Get(state->fieldSystem->saveData);

    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00026;

    BufferPlayersName(state->messageFormat, 0, Save_PlayerData_GetProfileAddr(state->fieldSystem->saveData));
    BufferPokewalkerCourseName(state->messageFormat, 1, data->pokewalker.courseNum);
}

BOOL MGCheck_MemorialPhoto(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    Bag *bag = Save_Bag_Get(fieldSystem->saveData);

    return PhotoAlbum_GetNumSaved(Save_PhotoAlbum_Get(fieldSystem->saveData)) < PHOTO_ALBUM_MAX;
}

void MGGive_MemorialPhoto(FieldSystem *fieldSystem, union MysteryGiftUnion *unused) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(fieldSystem);
    PHOTO_ALBUM *photoAlbum = Save_PhotoAlbum_Get(FieldSystem_GetSaveData(fieldSystem));
    u32 firstEmptySlot = PhotoAlbum_GetIndexOfFirstEmptySlot(photoAlbum);
    if (firstEmptySlot == 0xFF) {
        GF_ASSERT(FALSE);
        return;
    }

    PhotoAlbum_SetPhotoAtIndex(photoAlbum, &data->memorialPhoto.photo, firstEmptySlot);
}

void MGMessageSuccess_MemorialPhoto(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(state->fieldSystem);

    *gmmNum = NARC_msg_msg_0209_bin;
    *msgNum = msg_0209_00018;

    BufferPlayersName(state->messageFormat, 0, Save_PlayerData_GetProfileAddr(state->fieldSystem->saveData));
}

void MGMessageFailure_MemorialPhoto(MGGmmState *state, u16 *gmmNum, u16 *msgNum) {
    union MysteryGiftUnion *data = FieldSystem_GetDataOfNextMG(state->fieldSystem);
    Bag *bag = Save_Bag_Get(state->fieldSystem->saveData);

    *gmmNum = NARC_msg_msg_0209_bin;
    if (!Bag_HasItem(bag, ITEM_PHOTO_ALBUM, 1, HEAP_ID_FIELD)) {
        *msgNum = msg_0209_00024;
    } else {
        *msgNum = msg_0209_00025;
    }

    BufferPlayersName(state->messageFormat, 0, Save_PlayerData_GetProfileAddr(state->fieldSystem->saveData));
}
