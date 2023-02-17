#ifndef POKEDIAMOND_POKEMON_H
#define POKEDIAMOND_POKEMON_H

#include "pokemon_types_def.h"
#include "unk_02016EDC.h"
// Enums

#include "constants/species.h"
#include "constants/pokemon.h"
#include "pm_string.h"
#include "player_data.h"
#include "sound_chatot.h"
#include "filesystem.h"

#define WOTBL_END             0xFFFF
#define WOTBL_MAX                 21

#define WOTBL_MOVEID_MASK     0x01FF
#define WOTBL_MOVEID_SHIFT         0
#define WOTBL_LEVEL_MASK      0xFE00
#define WOTBL_LEVEL_SHIFT          9

#define WOTBL_MOVE(x) ((u16)(((x) & WOTBL_MOVEID_MASK) >> WOTBL_MOVEID_SHIFT))
#define WOTBL_LVL(x) ((u8)(((x) & WOTBL_LEVEL_MASK) >> WOTBL_LEVEL_SHIFT))

#define MOVE_APPEND_FULL    0xFFFFu
#define MOVE_APPEND_KNOWN   0xFFFEu

extern const s8 gNatureStatMods[NATURE_NUM][NUM_EV_STATS];

void ZeroMonData(Pokemon * pokemon);
void ZeroBoxMonData(BOXMON * boxmon);
u32 SizeOfStructPokemon(void);
Pokemon * AllocMonZeroed(HeapID heap_id);
BOOL AcquireMonLock(Pokemon * mon);
BOOL ReleaseMonLock(Pokemon * mon, BOOL decrypt_result);
BOOL AcquireBoxMonLock(BOXMON * mon);
BOOL ReleaseBoxMonLock(BOXMON * mon, BOOL decrypt_result);
void CreateMon(Pokemon * pokemon, int species, int level, int fixedIV, int hasFixedPersonality, int fixedPersonality, int otIdType, int fixedOtId);
void CreateBoxMon(BOXMON * boxPokemon, int species, int level, int fixedIV, int hasFixedPersonality, int fixedPersonality, int otIdType, int fixedOtId);
void CreateMonWithNature(Pokemon * pokemon, u16 species, u8 level, u8 fixedIv, u8 nature);
void CreateMonWithGenderNatureLetter(Pokemon * pokemon, u16 species, u8 level, u8 fixedIv, u8 gender, u8 nature, u8 letter);
u32 GenPersonalityByGenderAndNature(u16 species, u8 gender, u8 nature);
void CreateMonWithFixedIVs(Pokemon * pokemon, int species, int level, int ivs, int personality);
void CalcMonLevelAndStats(Pokemon * pokemon);
void CalcMonStats(Pokemon * pokemon);
u32 GetMonData(Pokemon * pokemon, int attr, void * ptr);
u32 GetBoxMonData(BOXMON * boxmon, int attr, void * ptr);
void SetMonData(Pokemon * pokemon, int attr, void * ptr);
void SetBoxMonData(BOXMON * boxmon, int attr, void * ptr);
void AddMonData(Pokemon * pokemon, int attr, int amount);
//void AddBoxMonData(BOXMON * boxmon, int attr, int amount);
BASE_STATS * AllocAndLoadMonPersonal_HandleAlternateForme(int species, int form, HeapID heap_id);
BASE_STATS * AllocAndLoadMonPersonal(int species, HeapID heap_id);
int GetPersonalAttr(const BASE_STATS *baseStats, BaseStat attr);
void FreeMonPersonal(BASE_STATS * personal);
int GetMonBaseStat_HandleAlternateForme(int species, int form, BaseStat stat_id);
int GetMonBaseStat(int species, BaseStat stat_id);
u8 GetPercentProgressTowardsNextLevel(Pokemon * pokemon);
u32 CalcMonExpToNextLevel(Pokemon * pokemon);
u32 CalcBoxMonExpToNextLevel(BOXMON * pokemon);
u32 GetMonBaseExperienceAtCurrentLevel(Pokemon * pokemon);
u32 GetMonExpBySpeciesAndLevel(int species, int level);
void LoadGrowthTable(int growthRate, u32 * table);
u32 GetExpByGrowthRateAndLevel(int rate, int level);
int CalcMonLevel(Pokemon * pokemon);
int CalcBoxMonLevel(BOXMON * boxmon);
int CalcLevelBySpeciesAndExp(u16 species, u32 experience);
int CalcLevelBySpeciesAndExp_PreloadedPersonal(BASE_STATS * personal, u16 species, u32 experience);
u8 GetBoxMonNature(BOXMON * boxmon);
u8 GetMonNature(Pokemon * mon);
u8 GetNatureFromPersonality(u32 pid);
void MonApplyFriendshipMod(Pokemon * pokemon, u8 kind, u16 location);
u8 GetMonGender(Pokemon * pokemon);
u8 GetBoxMonGender(BOXMON * boxmon);
u8 GetGenderBySpeciesAndPersonality(u16 species, u32 pid);
u8 MonIsShiny(Pokemon * pokemon);
u8 BoxMonIsShiny(BOXMON * boxmon);
u8 CalcShininessByOtIdAndPersonality(u32 otid, u32 pid);
u32 GenerateShinyPersonality(u32 otid);
u32 GetArceusTypeByHeldItemEffect(u16 plate);
u8 GetBoxMonUnownLetter(BOXMON * boxmon);
u8 GetMonUnownLetter(Pokemon * pokemon);
u32 TryAppendMonMove(Pokemon *pokemon, u16 move);
u32 TryAppendBoxMonMove(BOXMON *boxmon, u16 move);
void BoxMonSetMoveInSlot(BOXMON *boxmon, u16 move, u8 slot);
void DeleteMonFirstMoveAndAppend(Pokemon *pokemon, u16 move);
void DeleteBoxMonFirstMoveAndAppend(BOXMON *boxmon, u16 move);
void LoadWotbl_HandleAlternateForme(int species, int forme, u16 *wotbl);
void MonSwapMoves(Pokemon *pokemon, int a, int b);
void BoxMonSwapMoves(BOXMON *boxmon, int a, int b);
BOXMON *Mon_GetBoxMon(Pokemon *pokemon);

u16 GetMonEvolution(PARTY * party, Pokemon * pokemon, u8 context, u16 usedItem, int *method_ret);
u16 ReadFromPersonalPmsNarc(u16 species);
u16 GetEggSpecies(u16 species);
void MonSetMoveInSlot(Pokemon * pokemon, u16 move, u8 slot);
void CopyBoxPokemonToPokemon(const BOXMON * src, Pokemon * dest);
u8 Party_GetMaxLevel(PARTY * party);
u16 SpeciesToSinnohDexNo(u16 species);
u16 SinnohDexNoToSpecies(u16 sinnoh_dex);
void CopyPokemonToPokemon(const Pokemon * src, Pokemon * dest);
void CopyBoxPokemonToBoxPokemon(const BOXMON * src, BOXMON * dest);
void CopyPokemonToBoxPokemon(const Pokemon * src, BOXMON * dest);
s8 MonGetFlavorPreference(Pokemon * pokemon, int flavor);
s8 BoxMonGetFlavorPreference(BOXMON * boxmon, int flavor);
s8 GetFlavorPreferenceFromPID(u32 personality, int flavor);
int Species_LoadLearnsetTable(u16 species, u32 forme, u16 * dest);
void Party_GivePokerusAtRandom(PARTY * party);
u8 Party_MaskMonsWithPokerus(PARTY * party, u8 mask);
void Party_UpdatePokerus(PARTY * party, int r5);
void Party_SpreadPokerus(PARTY * party);
BOOL Pokemon_HasPokerus(Pokemon * pokemon);
BOOL BoxMon_HasPokerus(BOXMON * boxmon);
BOOL Pokemon_IsImmuneToPokerus(Pokemon * pokemon);
BOOL BoxMon_IsImmuneToPokerus(BOXMON * boxmon);
void Pokemon_UpdateArceusForme(Pokemon * pokemon);
void BoxMon_UpdateArceusForme(BOXMON * boxmon);
s32 Mon_UpdateGiratinaForme(Pokemon * pokemon);
s32 BoxMon_UpdateGiratinaForme(BOXMON * boxmon);
void Mon_UpdateShayminForme(Pokemon *pokemon, int forme);
void BoxMon_UpdateShayminForme(BOXMON *pokemon, int forme);
void UpdateMonAbility(Pokemon *boxmon);
void UpdateBoxMonAbility(BOXMON *boxmon);
int LowestFlagNo(u32 mask);
BOOL IsPokemonLegendaryOrMythical(u16 species, u16 forme);
u16 GetLegendaryMon(u32 idx);
void Pokemon_RemoveCapsule(Pokemon * pokemon);
void RestoreBoxMonPP(BOXMON * boxmon);
BOOL SetTrMonCapsule(int a0, Pokemon *pokemon, HeapID heap_id);

int GetMonBaseStatEx_HandleAlternateForme(NARC *narc, int species, int forme, BaseStat attr);
u16 ModifyStatByNature(u8 nature, u16 n, u8 statIndex);
u8 GetGenderBySpeciesAndPersonality_PreloadedPersonal(const BASE_STATS *personal, u16 species, u32 pid);
BOOL BoxMonIsHoldingMail(BOXMON *boxmon);
void GetPokemonSpriteCharAndPlttNarcIds(struct SomeDrawPokemonStruct *a0, BOXMON *boxmon, u8 whichFacing);
void sub_02070130(struct SomeDrawPokemonStruct *a0, BOXMON *boxmon, u8 whichFacing);
void GetBoxmonSpriteCharAndPlttNarcIds(struct SomeDrawPokemonStruct *spC, BOXMON *boxmon, u8 whichFacing, BOOL sp14);
void GetMonSpriteCharAndPlttNarcIdsEx(struct SomeDrawPokemonStruct * spC, u16 species, u8 gender, u8 whichFacing, u8 shiny, u8 forme, u32 personality);
u8 sub_02070438(u16 species, u8 forme);
void sub_02070560(struct SomeDrawPokemonStruct * spC, u16 species, u8 whichFacing, u8 gender, u32 shiny);
void DP_GetMonSpriteCharAndPlttNarcIdsEx(struct SomeDrawPokemonStruct * spC, u16 species, u8 gender, u8 whichFacing, u8 shiny, u8 forme, u32 personality);
u8 sub_0207083C(BOXMON *boxmon, u8 whichFacing);
u8 sub_02070848(BOXMON *boxmon, u8 whichFacing);
u8 sub_02070854(BOXMON *boxmon, u8 whichFacing, BOOL a2);
u8 sub_020708D8(u16 species, u8 gender, u8 whichFacing, u8 forme, u32 pid);
u8 sub_02070A64(u16 species, u8 gender, u8 whichFacing, u8 forme, u32 pid);
void sub_02070D3C(s32 trainer_class, s32 a1, s32 a2, struct UnkStruct_02070D3C *a3);
void sub_02070D84(s32 trainer_class, s32 a1, struct UnkStruct_02070D3C *a2);
u32 sub_02070D90(void);
u32 sub_02070D94(void);
BOXMON * Mon_GetBoxMon(Pokemon * pokemon);
BOOL Pokemon_TryLevelUp(Pokemon * pokemon);
void InitBoxMonMoveset(BOXMON * boxmon);
void MonSetMoveInSlot_ResetPpUp(Pokemon* pokemon, u16 move, u8 slot);
u32 MonTryLearnMoveOnLevelUp(Pokemon * pokemon, int * last_i, u16 * sp0);
void MonDeleteMoveSlot(Pokemon * pokemon, u32 slot);
BOOL MonHasMove(Pokemon* pokemon, u16 move);
u16 SpeciesToJohtoDexNo(u16 species);
void Mon_ForceSetGiratinaOriginForme(Pokemon *pokemon);
void Party_UpdateAllGiratina_DistortionWorld(PARTY *party, BOOL force_origin);
BOOL Mon_CanUseGracidea(Pokemon *pokemon);
void Party_ResetAllShayminToLandForme(PARTY *party);
BOOL Party_TryResetShaymin(PARTY *party, int min_max, const RTCTime *time);
BOOL Mon_UpdateRotomForme(Pokemon *pokemon, int forme, int defaultSlot);
void sub_02071FDC(SOUND_CHATOT *r6, u32 r5, u16 r4, s32 unused, s32 sp18, u32 sp1C, u32 sp20, u32 sp24);
void sub_0207204C(SOUND_CHATOT *r7, u32 r6, u16 r5, s32 r4, s32 sp20, u32 sp24, u32 sp28, u32 sp2C, u8 sp30);
void sub_020720D4(Pokemon *pokemon);
void sub_020720FC(Pokemon * pokemon, PLAYERPROFILE *a1, u32 pokeball, u32 a3, u32 encounterType, HeapID heap_id);
void sub_0207213C(BOXMON * boxmon, PLAYERPROFILE *playerProfile, u32 pokeball, u32 a3, u32 encounterType, HeapID heap_id);
void sub_0207217C(Pokemon *pokemon, PLAYERPROFILE *a1, u32 pokeball, u32 a3, u32 encounterType, HeapID heap_id);
void sub_02072190(BOXMON *boxmon, PLAYERPROFILE *a1, u32 pokeball, u32 a3, u32 encounterType, HeapID heap_id);
void WildMonSetRandomHeldItem(Pokemon * pokemon, u32 a1, u32 a2);
BOOL GetMonTMHMCompat(Pokemon *pokemon, u8 tmhm);
BOOL GetBoxMonTMHMCompat(BOXMON *boxmon, u8 tmhm);
BOOL GetTMHMCompatBySpeciesAndForme(u16 species, u32 forme, u8 tmhm);
void SetMonPersonality(Pokemon * r5, u32 personality);
u32 ChangePersonalityToNatureGenderAndAbility(u32 pid, u16 species, u8 nature, u8 gender, u8 ability, BOOL gen_mode);
void LoadMonPersonal(int species, BASE_STATS *personal);
void LoadMonBaseStats_HandleAlternateForme(int species, int forme, BASE_STATS *personal);
void LoadMonEvolutionTable(u16 species, struct Evolution *evo);
void MonEncryptSegment(void *data, u32 size, u32 seed);
void MonDecryptSegment(void *data, u32 size, u32 seed);
u32 CalcMonChecksum(void * _data, u32 size);
int ResolveMonForme(int species, int forme);
u32 MaskOfFlagNo(int flagno);
BOOL SpeciesIsMythical(u16 species);
BOOL MonCheckFrontierIneligibility(Pokemon *pokemon);
BOOL BoxmonBelongsToPlayer(BOXMON * boxmon, PLAYERPROFILE * profile, HeapID heap_id);
int TrainerClassToBackpicID(int trainerClass, int a1);
void sub_02072914(NARC *narc, struct UnkStruct_02072914_sub *dest, u16 a2, u16 a3);
void sub_0207294C(NARC *narc, void *a1, void *a2, u16 a3, int a4, int a5, int a6);
void sub_020729A4(NARC *narc, u8 *ret, u16 a2, u16 a3);
void sub_020729D8(NARC *narc, s8 *ret, u16 a2, u16 a3);
void sub_020729FC(NARC *narc, s8 *ret, u16 a2, u16 a3);
void sub_02072A20(NARC *narc, u8 *ret, u16 a2, u16 a3);
void sub_02072A98(Pokemon *pokemon, struct UnkPokemonStruct_02072A98 *dest);
void sub_02072D64(const struct UnkPokemonStruct_02072A98 *src, Pokemon *pokemon);
u32 _u32_getDigitN(u32 num, u8 digit);
s16 PokeathlonStatScoreToStars(s16 a0);
void CalcBoxMonPokeathlonPerformance(BOXMON *boxmon, struct PokeathlonTodayPerformance *dest);
void CalcMonPokeathlonPerformance(Pokemon *pokemon, struct PokeathlonTodayPerformance *dest);
void CalcBoxmonPokeathlonStars(struct PokeathlonPerformanceStars *dest, BOXMON *boxmon, const s8 *aprijuice, HeapID heap_id);
void CalcMonPokeathlonStars(struct PokeathlonPerformanceStars *dest, Pokemon *pokemon, const s8 *aprijuice, HeapID heap_id);

#endif //POKEDIAMOND_POKEMON_H
