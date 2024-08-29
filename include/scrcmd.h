#ifndef POKEHEARTGOLD_SCRCMD_H
#define POKEHEARTGOLD_SCRCMD_H

#include "constants/scrcmd.h"

#include "fieldmap.h"
#include "save_special_ribbons.h"
#include "script.h"

static inline u16 ScriptGetVar(ScriptContext *ctx) {
    return FieldSystem_VarGet(ctx->fieldSystem, ScriptReadHalfword(ctx));
}

static inline u16 *ScriptGetVarPointer(ScriptContext *ctx) {
    return GetVarPointer(ctx->fieldSystem, ScriptReadHalfword(ctx));
}

// Basic commands
BOOL ScrCmd_Nop(ScriptContext *ctx);
BOOL ScrCmd_Dummy(ScriptContext *ctx);
BOOL ScrCmd_End(ScriptContext *ctx);
BOOL ScrCmd_Wait(ScriptContext *ctx);
BOOL ScrCmd_LoadByte(ScriptContext *ctx);
BOOL ScrCmd_LoadWord(ScriptContext *ctx);
BOOL ScrCmd_LoadByteFromAddr(ScriptContext *ctx);
BOOL ScrCmd_WriteByteToAddr(ScriptContext *ctx);
BOOL ScrCmd_SetPtrByte(ScriptContext *ctx);
BOOL ScrCmd_CopyLocal(ScriptContext *ctx);
BOOL ScrCmd_CopyByte(ScriptContext *ctx);
BOOL ScrCmd_CompareLocalToLocal(ScriptContext *ctx);
BOOL ScrCmd_CompareLocalToValue(ScriptContext *ctx);
BOOL ScrCmd_CompareLocalToAddr(ScriptContext *ctx);
BOOL ScrCmd_CompareAddrToLocal(ScriptContext *ctx);
BOOL ScrCmd_CompareAddrToValue(ScriptContext *ctx);
BOOL ScrCmd_CompareAddrToAddr(ScriptContext *ctx);
BOOL ScrCmd_CompareVarToValue(ScriptContext *ctx);
BOOL ScrCmd_CompareVarToVar(ScriptContext *ctx);
BOOL ScrCmd_RunScript(ScriptContext *ctx);
BOOL ScrCmd_CallStd(ScriptContext *ctx);
BOOL ScrCmd_RestartCurrentScript(ScriptContext *ctx);
BOOL ScrCmd_GoTo(ScriptContext *ctx);
BOOL ScrCmd_ObjectGoTo(ScriptContext *ctx);
BOOL ScrCmd_BgGoTo(ScriptContext *ctx);
BOOL ScrCmd_DirectionGoTo(ScriptContext *ctx);
BOOL ScrCmd_Call(ScriptContext *ctx);
BOOL ScrCmd_Return(ScriptContext *ctx);
BOOL ScrCmd_GoToIf(ScriptContext *ctx);
BOOL ScrCmd_CallIf(ScriptContext *ctx);
BOOL ScrCmd_SetFlag(ScriptContext *ctx);
BOOL ScrCmd_ClearFlag(ScriptContext *ctx);
BOOL ScrCmd_CheckFlag(ScriptContext *ctx);
BOOL ScrCmd_SetFlagVar(ScriptContext *ctx);
BOOL ScrCmd_ClearFlagVar(ScriptContext *ctx);
BOOL ScrCmd_CheckFlagVar(ScriptContext *ctx);
BOOL ScrCmd_SetTrainerFlag(ScriptContext *ctx);
BOOL ScrCmd_ClearTrainerFlag(ScriptContext *ctx);
BOOL ScrCmd_CheckTrainerFlag(ScriptContext *ctx);
BOOL ScrCmd_AddVar(ScriptContext *ctx);
BOOL ScrCmd_SubVar(ScriptContext *ctx);
BOOL ScrCmd_SetVar(ScriptContext *ctx);
BOOL ScrCmd_CopyVar(ScriptContext *ctx);
BOOL ScrCmd_SetOrCopyVar(ScriptContext *ctx);
BOOL ScrCmd_NonNPCMsg(ScriptContext *ctx);
BOOL ScrCmd_NPCMsg(ScriptContext *ctx);
BOOL ScrCmd_NonNpcMsgVar(ScriptContext *ctx);
BOOL ScrCmd_NpcMsgVar(ScriptContext *ctx);
BOOL ScrCmd_048(ScriptContext *ctx);
BOOL ScrCmd_WaitButton(ScriptContext *ctx);
BOOL ScrCmd_WaitButtonOrWalkAway(ScriptContext *ctx);
BOOL ScrCmd_WaitButtonOrDpad(ScriptContext *ctx);
BOOL ScrCmd_OpenMsg(ScriptContext *ctx);
BOOL ScrCmd_CloseMsg(ScriptContext *ctx);
BOOL ScrCmd_HoldMsg(ScriptContext *ctx);
BOOL ScrCmd_DirectionSignpost(ScriptContext *ctx);
BOOL ScrCmd_055(ScriptContext *ctx);
BOOL ScrCmd_057(ScriptContext *ctx);
BOOL ScrCmd_058(ScriptContext *ctx);
BOOL ScrCmd_TrainerTips(ScriptContext *ctx);
BOOL ScrCmd_060(ScriptContext *ctx);
BOOL ScrCmd_061(ScriptContext *ctx);
BOOL ScrCmd_062(ScriptContext *ctx);
BOOL ScrCmd_YesNo(ScriptContext *ctx);
BOOL ScrCmd_064(ScriptContext *ctx);
BOOL ScrCmd_065(ScriptContext *ctx);
BOOL ScrCmd_066(ScriptContext *ctx);
BOOL ScrCmd_067(ScriptContext *ctx);
BOOL ScrCmd_068(ScriptContext *ctx);
BOOL ScrCmd_069(ScriptContext *ctx);
BOOL ScrCmd_070(ScriptContext *ctx);
BOOL ScrCmd_071(ScriptContext *ctx);
BOOL ScrCmd_072(ScriptContext *ctx);

// Sound-related commands
BOOL ScrCmd_PlaySE(ScriptContext *ctx);
BOOL ScrCmd_StopSE(ScriptContext *ctx);
BOOL ScrCmd_WaitSE(ScriptContext *ctx);
BOOL ScrCmd_PlayCry(ScriptContext *ctx);
BOOL ScrCmd_WaitCry(ScriptContext *ctx);
BOOL ScrCmd_PlayFanfare(ScriptContext *ctx);
BOOL ScrCmd_WaitFanfare(ScriptContext *ctx);
BOOL ScrCmd_PlayBGM(ScriptContext *ctx);
BOOL ScrCmd_StopBGM(ScriptContext *ctx);
BOOL ScrCmd_ResetBGM(ScriptContext *ctx);
BOOL ScrCmd_083(ScriptContext *ctx);
BOOL ScrCmd_FadeOutBGM(ScriptContext *ctx);
BOOL ScrCmd_FadeInBGM(ScriptContext *ctx);
BOOL ScrCmd_086(ScriptContext *ctx);
BOOL ScrCmd_TempBGM(ScriptContext *ctx);
BOOL ScrCmd_088(ScriptContext *ctx);
BOOL ScrCmd_ChatotHasCry(ScriptContext *ctx);
BOOL ScrCmd_ChatotStartRecording(ScriptContext *ctx);
BOOL ScrCmd_ChatotStopRecording(ScriptContext *ctx);
BOOL ScrCmd_ChatotSaveRecording(ScriptContext *ctx);
BOOL ScrCmd_093(ScriptContext *ctx);

// Event objects
BOOL ScrCmd_ApplyMovement(ScriptContext *ctx);
BOOL ScrCmd_WaitMovement(ScriptContext *ctx);
BOOL ScrCmd_LockAll(ScriptContext *ctx);
BOOL ScrCmd_ReleaseAll(ScriptContext *ctx);
BOOL ScrCmd_098(ScriptContext *ctx);
BOOL ScrCmd_099(ScriptContext *ctx);
BOOL ScrCmd_ShowPerson(ScriptContext *ctx);
BOOL ScrCmd_HidePerson(ScriptContext *ctx);
BOOL ScrCmd_102(ScriptContext *ctx);
BOOL ScrCmd_103(ScriptContext *ctx);
BOOL ScrCmd_FacePlayer(ScriptContext *ctx);
BOOL ScrCmd_GetPlayerCoords(ScriptContext *ctx);
BOOL ScrCmd_GetPersonCoords(ScriptContext *ctx);
BOOL ScrCmd_107(ScriptContext *ctx);
BOOL ScrCmd_108(ScriptContext *ctx);
BOOL ScrCmd_109(ScriptContext *ctx);

// scrcmd_money.c
BOOL ScrCmd_AddMoney(ScriptContext *ctx);
BOOL ScrCmd_SubMoneyImmediate(ScriptContext *ctx);
BOOL ScrCmd_HasEnoughMoneyImmediate(ScriptContext *ctx);
BOOL ScrCmd_ShowMoneyBox(ScriptContext *ctx);
BOOL ScrCmd_HideMoneyBox(ScriptContext *ctx);
BOOL ScrCmd_UpdateMoneyBox(ScriptContext *ctx);
BOOL ScrCmd_116(ScriptContext *ctx);
BOOL ScrCmd_117(ScriptContext *ctx);
BOOL ScrCmd_118(ScriptContext *ctx);
BOOL ScrCmd_GetCoinAmount(ScriptContext *ctx);
BOOL ScrCmd_GiveCoins(ScriptContext *ctx);
BOOL ScrCmd_TakeCoins(ScriptContext *ctx);
BOOL ScrCmd_GiveAthletePoints(ScriptContext *ctx);
BOOL ScrCmd_TakeAthletePoints(ScriptContext *ctx);
BOOL ScrCmd_CheckAthletePoints(ScriptContext *ctx);

// scrcmd_items.c
BOOL ScrCmd_GiveItem(ScriptContext *ctx);
BOOL ScrCmd_TakeItem(ScriptContext *ctx);
BOOL ScrCmd_HasSpaceForItem(ScriptContext *ctx);
BOOL ScrCmd_HasItem(ScriptContext *ctx);
BOOL ScrCmd_ItemIsTMOrHM(ScriptContext *ctx);
BOOL ScrCmd_GetItemPocket(ScriptContext *ctx);

BOOL ScrCmd_SetStarterChoice(ScriptContext *ctx);
BOOL ScrCmd_GenderMsgbox(ScriptContext *ctx);
BOOL ScrCmd_GetSealQuantity(ScriptContext *ctx);
BOOL ScrCmd_GiveOrTakeSeal(ScriptContext *ctx);
BOOL ScrCmd_GiveRandomSeal(ScriptContext *ctx);
BOOL ScrCmd_136(ScriptContext *ctx);
BOOL ScrCmd_GiveMon(ScriptContext *ctx);
BOOL ScrCmd_GiveEgg(ScriptContext *ctx);
BOOL ScrCmd_SetMonMove(ScriptContext *ctx);
BOOL ScrCmd_MonHasMove(ScriptContext *ctx);
BOOL ScrCmd_GetPartySlotWithMove(ScriptContext *ctx);
BOOL ScrCmd_GetPhoneBookRematch(ScriptContext *ctx);
BOOL ScrCmd_NameRival(ScriptContext *ctx);
BOOL ScrCmd_GetFriendSprite(ScriptContext *ctx);
BOOL ScrCmd_RegisterPokegearCard(ScriptContext *ctx);
BOOL ScrCmd_RegisterGearNumber(ScriptContext *ctx);
BOOL ScrCmd_CheckRegisteredPhoneNumber(ScriptContext *ctx);
BOOL ScrCmd_148(ScriptContext *ctx);
BOOL ScrCmd_149(ScriptContext *ctx);
BOOL ScrCmd_RestoreOverworld(ScriptContext *ctx);
BOOL ScrCmd_151(ScriptContext *ctx);
BOOL ScrCmd_152(ScriptContext *ctx);
BOOL ScrCmd_153(ScriptContext *ctx);
BOOL ScrCmd_154(ScriptContext *ctx);
BOOL ScrCmd_155(ScriptContext *ctx);
BOOL ScrCmd_156(ScriptContext *ctx);
BOOL ScrCmd_TownMap(ScriptContext *ctx);
BOOL ScrCmd_158(ScriptContext *ctx);
BOOL ScrCmd_159(ScriptContext *ctx);
BOOL ScrCmd_160(ScriptContext *ctx);
BOOL ScrCmd_161(ScriptContext *ctx);
BOOL ScrCmd_162(ScriptContext *ctx);
BOOL ScrCmd_HOF_Credits(ScriptContext *ctx);
BOOL ScrCmd_164(ScriptContext *ctx);
BOOL ScrCmd_165(ScriptContext *ctx);
BOOL ScrCmd_166(ScriptContext *ctx);
BOOL ScrCmd_ChooseStarter(ScriptContext *ctx);
BOOL ScrCmd_GetTrainerPathToPlayer(ScriptContext *ctx);
BOOL ScrCmd_TrainerStepTowardsPlayer(ScriptContext *ctx);
BOOL ScrCmd_GetTrainerEyeType(ScriptContext *ctx);
BOOL ScrCmd_GetEyeTrainerNum(ScriptContext *ctx);
BOOL ScrCmd_NamePlayer(ScriptContext *ctx);
BOOL ScrCmd_NicknameInput(ScriptContext *ctx);
BOOL ScrCmd_FadeScreen(ScriptContext *ctx);
BOOL ScrCmd_WaitFade(ScriptContext *ctx);
BOOL ScrCmd_Warp(ScriptContext *ctx);
BOOL ScrCmd_RockClimb(ScriptContext *ctx);
BOOL ScrCmd_Surf(ScriptContext *ctx);
BOOL ScrCmd_Waterfall(ScriptContext *ctx);
BOOL ScrCmd_180(ScriptContext *ctx);
BOOL ScrCmd_FlashEffect(ScriptContext *ctx);
BOOL ScrCmd_Whirlpool(ScriptContext *ctx);
BOOL ScrCmd_183(ScriptContext *ctx);
BOOL ScrCmd_PlayerOnBikeCheck(ScriptContext *ctx);
BOOL ScrCmd_PlayerOnBikeSet(ScriptContext *ctx);
BOOL ScrCmd_186(ScriptContext *ctx);
BOOL ScrCmd_GetPlayerState(ScriptContext *ctx);
BOOL ScrCmd_SetAvatarBits(ScriptContext *ctx);
BOOL ScrCmd_UpdateAvatarState(ScriptContext *ctx);

// Message buffers
BOOL ScrCmd_BufferPlayersName(ScriptContext *ctx);
BOOL ScrCmd_BufferRivalsName(ScriptContext *ctx);
BOOL ScrCmd_BufferFriendsName(ScriptContext *ctx);
BOOL ScrCmd_BufferMonSpeciesName(ScriptContext *ctx);
BOOL ScrCmd_BufferItemName(ScriptContext *ctx);
BOOL ScrCmd_BufferPocketName(ScriptContext *ctx);
BOOL ScrCmd_BufferTMHMMoveName(ScriptContext *ctx);
BOOL ScrCmd_BufferMoveName(ScriptContext *ctx);
BOOL ScrCmd_BufferInt(ScriptContext *ctx);
BOOL ScrCmd_BufferPartyMonNick(ScriptContext *ctx);
BOOL ScrCmd_BufferTrainerClassName(ScriptContext *ctx);
BOOL ScrCmd_BufferPlayerUnionAvatarClassName(ScriptContext *ctx);
BOOL ScrCmd_BufferSpeciesName(ScriptContext *ctx);
BOOL ScrCmd_BufferStarterSpeciesName(ScriptContext *ctx);
BOOL ScrCmd_BufferDPPtRivalStarterSpeciesName(ScriptContext *ctx);
BOOL ScrCmd_BufferDPPtFriendStarterSpeciesName(ScriptContext *ctx);
BOOL ScrCmd_GetStarterChoice(ScriptContext *ctx);
BOOL ScrCmd_BufferDecorationName(ScriptContext *ctx);
BOOL ScrCmd_208(ScriptContext *ctx);
BOOL ScrCmd_209(ScriptContext *ctx);
BOOL ScrCmd_BufferMapSecName(ScriptContext *ctx);
BOOL ScrCmd_211(ScriptContext *ctx);

// Trainer-related
BOOL ScrCmd_GetTrainerNum(ScriptContext *ctx);
BOOL ScrCmd_TrainerBattle(ScriptContext *ctx);
BOOL ScrCmd_TrainerMessage(ScriptContext *ctx);
BOOL ScrCmd_GetTrainerMsgParams(ScriptContext *ctx);
BOOL ScrCmd_GetRematchMsgParams(ScriptContext *ctx);
BOOL ScrCmd_TrainerIsDoubleBattle(ScriptContext *ctx);
BOOL ScrCmd_EncounterMusic(ScriptContext *ctx);
BOOL ScrCmd_WhiteOut(ScriptContext *ctx);
BOOL ScrCmd_CheckBattleWon(ScriptContext *ctx);
BOOL ScrCmd_StaticWildWonOrCaughtCheck(ScriptContext *ctx);
BOOL ScrCmd_PartyCheckForDouble(ScriptContext *ctx);
BOOL ScrCmd_223(ScriptContext *ctx);
BOOL ScrCmd_224(ScriptContext *ctx);
BOOL ScrCmd_GotoIfTrainerDefeated(ScriptContext *ctx);
BOOL ScrCmd_226(ScriptContext *ctx);
BOOL ScrCmd_227(ScriptContext *ctx);
BOOL ScrCmd_228(ScriptContext *ctx);
BOOL ScrCmd_229(ScriptContext *ctx);
BOOL ScrCmd_230(ScriptContext *ctx);
BOOL ScrCmd_231(ScriptContext *ctx);
BOOL ScrCmd_232(ScriptContext *ctx);
BOOL ScrCmd_233(ScriptContext *ctx);
BOOL ScrCmd_234(ScriptContext *ctx);
BOOL ScrCmd_235(ScriptContext *ctx);
BOOL ScrCmd_236(ScriptContext *ctx);
BOOL ScrCmd_237(ScriptContext *ctx);
BOOL ScrCmd_PartyHasPokerus(ScriptContext *ctx);
BOOL ScrCmd_MonGetGender(ScriptContext *ctx);
BOOL ScrCmd_SetDynamicWarp(ScriptContext *ctx);
BOOL ScrCmd_GetDynamicWarpFloorNo(ScriptContext *ctx);
BOOL ScrCmd_ElevatorCurFloorBox(ScriptContext *ctx);

// Dex-related
BOOL ScrCmd_CountJohtoDexSeen(ScriptContext *ctx);
BOOL ScrCmd_CountJohtoDexOwned(ScriptContext *ctx);
BOOL ScrCmd_CountNationalDexSeen(ScriptContext *ctx);
BOOL ScrCmd_CountNationalDexOwned(ScriptContext *ctx);
BOOL ScrCmd_247(ScriptContext *ctx);
BOOL ScrCmd_GetDexEvalResult(ScriptContext *ctx);
BOOL ScrCmd_RocketTrapBattle(ScriptContext *ctx);
BOOL ScrCmd_250(ScriptContext *ctx);
BOOL ScrCmd_CatchingTutorial(ScriptContext *ctx);
BOOL ScrCmd_252(ScriptContext *ctx);
BOOL ScrCmd_GetSaveFileState(ScriptContext *ctx);
BOOL ScrCmd_SaveGameNormal(ScriptContext *ctx);
BOOL ScrCmd_255(ScriptContext *ctx);
BOOL ScrCmd_256(ScriptContext *ctx);
BOOL ScrCmd_257(ScriptContext *ctx);
BOOL ScrCmd_258(ScriptContext *ctx);
BOOL ScrCmd_259(ScriptContext *ctx);
BOOL ScrCmd_260(ScriptContext *ctx);
BOOL ScrCmd_261(ScriptContext *ctx);
BOOL ScrCmd_262(ScriptContext *ctx);
BOOL ScrCmd_263(ScriptContext *ctx);
BOOL ScrCmd_264(ScriptContext *ctx);
BOOL ScrCmd_265(ScriptContext *ctx);
BOOL ScrCmd_266(ScriptContext *ctx);
BOOL ScrCmd_267(ScriptContext *ctx);
BOOL ScrCmd_268(ScriptContext *ctx);
BOOL ScrCmd_269(ScriptContext *ctx);
BOOL ScrCmd_270(ScriptContext *ctx);
BOOL ScrCmd_271(ScriptContext *ctx);
BOOL ScrCmd_272(ScriptContext *ctx);
BOOL ScrCmd_273(ScriptContext *ctx);
BOOL ScrCmd_274(ScriptContext *ctx);

// scrcmd_mart.c
BOOL ScrCmd_MartBuy(ScriptContext *ctx);
BOOL ScrCmd_SpecialMartBuy(ScriptContext *ctx);
BOOL ScrCmd_DecorationMart(ScriptContext *ctx);
BOOL ScrCmd_SealMart(ScriptContext *ctx);
BOOL ScrCmd_OverworldWhiteOut(ScriptContext *ctx);
BOOL ScrCmd_SetSpawn(ScriptContext *ctx);
BOOL ScrCmd_GetPlayerGender(ScriptContext *ctx);
BOOL ScrCmd_HealParty(ScriptContext *ctx);
BOOL ScrCmd_283(ScriptContext *ctx);
BOOL ScrCmd_284(ScriptContext *ctx);
BOOL ScrCmd_285(ScriptContext *ctx);
BOOL ScrCmd_286(ScriptContext *ctx);
BOOL ScrCmd_BufferUnionRoomAvatarChoices(ScriptContext *ctx);
BOOL ScrCmd_UnionRoomAvatarIdxToTrainerClass(ScriptContext *ctx);
BOOL ScrCmd_289(ScriptContext *ctx);
BOOL ScrCmd_CheckPokedex(ScriptContext *ctx);
BOOL ScrCmd_GivePokedex(ScriptContext *ctx);
BOOL ScrCmd_CheckRunningShoes(ScriptContext *ctx);
BOOL ScrCmd_GiveRunningShoes(ScriptContext *ctx);
BOOL ScrCmd_CheckBadge(ScriptContext *ctx);
BOOL ScrCmd_GiveBadge(ScriptContext *ctx);
BOOL ScrCmd_CountBadges(ScriptContext *ctx);
BOOL ScrCmd_297(ScriptContext *ctx);
BOOL ScrCmd_298(ScriptContext *ctx);
BOOL ScrCmd_CheckEscortMode(ScriptContext *ctx);
BOOL ScrCmd_SetEscortMode(ScriptContext *ctx);
BOOL ScrCmd_ClearEscortMode(ScriptContext *ctx);
BOOL ScrCmd_302(ScriptContext *ctx);
BOOL ScrCmd_303(ScriptContext *ctx);
BOOL ScrCmd_304(ScriptContext *ctx);
BOOL ScrCmd_305(ScriptContext *ctx);
BOOL ScrCmd_306(ScriptContext *ctx);
BOOL ScrCmd_307(ScriptContext *ctx);
BOOL ScrCmd_308(ScriptContext *ctx);
BOOL ScrCmd_309(ScriptContext *ctx);
BOOL ScrCmd_310(ScriptContext *ctx);
BOOL ScrCmd_311(ScriptContext *ctx);
BOOL ScrCmd_BufferDaycareMonNicks(ScriptContext *ctx);
BOOL ScrCmd_GetDaycareState(ScriptContext *ctx);
BOOL ScrCmd_EcruteakGymInit(ScriptContext *ctx);
BOOL ScrCmd_315(ScriptContext *ctx);
BOOL ScrCmd_316(ScriptContext *ctx);
BOOL ScrCmd_317(ScriptContext *ctx);
BOOL ScrCmd_CianwoodGymInit(ScriptContext *ctx);
BOOL ScrCmd_CianwoodGymTurnWinch(ScriptContext *ctx);
BOOL ScrCmd_VermilionGymInit(ScriptContext *ctx);
BOOL ScrCmd_VermilionGymLockAction(ScriptContext *ctx);
BOOL ScrCmd_VermilionGymCanCheck(ScriptContext *ctx);
BOOL ScrCmd_ResampleVermilionGymCans(ScriptContext *ctx);
BOOL ScrCmd_VioletGymInit(ScriptContext *ctx);
BOOL ScrCmd_VioletGymElevator(ScriptContext *ctx);
BOOL ScrCmd_AzaleaGymInit(ScriptContext *ctx);
BOOL ScrCmd_AzaleaGymSpinarak(ScriptContext *ctx);
BOOL ScrCmd_AzaleaGymSwitch(ScriptContext *ctx);
BOOL ScrCmd_BlackthornGymInit(ScriptContext *ctx);
BOOL ScrCmd_FuchsiaGymInit(ScriptContext *ctx);
BOOL ScrCmd_ViridianGymInit(ScriptContext *ctx);
BOOL ScrCmd_GetPartyCount(ScriptContext *ctx);
BOOL ScrCmd_333(ScriptContext *ctx);
BOOL ScrCmd_334(ScriptContext *ctx);
BOOL ScrCmd_335(ScriptContext *ctx);
BOOL ScrCmd_BufferBerryName(ScriptContext *ctx);
BOOL ScrCmd_BufferNatureName(ScriptContext *ctx);
BOOL ScrCmd_MovePerson(ScriptContext *ctx);
BOOL ScrCmd_MovePersonFacing(ScriptContext *ctx);
BOOL ScrCmd_SetObjectMovementType(ScriptContext *ctx);
BOOL ScrCmd_SetObjectFacing(ScriptContext *ctx);
BOOL ScrCmd_MoveWarp(ScriptContext *ctx);
BOOL ScrCmd_MoveBgEvent(ScriptContext *ctx);
BOOL ScrCmd_344(ScriptContext *ctx);
BOOL ScrCmd_AddWaitingIcon(ScriptContext *ctx);
BOOL ScrCmd_RemoveWaitingIcon(ScriptContext *ctx);
BOOL ScrCmd_347(ScriptContext *ctx);
BOOL ScrCmd_WaitButtonOrDelay(ScriptContext *ctx);
BOOL ScrCmd_PartySelectUI(ScriptContext *ctx);
BOOL ScrCmd_350(ScriptContext *ctx);
BOOL ScrCmd_PartySelect(ScriptContext *ctx);
BOOL ScrCmd_PokemonSummaryScreen(ScriptContext *ctx);
BOOL ScrCmd_GetMoveSelection(ScriptContext *ctx);
BOOL ScrCmd_GetPartyMonSpecies(ScriptContext *ctx);
BOOL ScrCmd_PartymonIsMine(ScriptContext *ctx);
BOOL ScrCmd_PartyCountNotEgg(ScriptContext *ctx);
BOOL ScrCmd_CountAliveMons(ScriptContext *ctx);
BOOL ScrCmd_CountAliveMonsAndPC(ScriptContext *ctx);
BOOL ScrCmd_PartyCountEgg(ScriptContext *ctx);

// scrcmd_money.c
BOOL ScrCmd_SubMoneyVar(ScriptContext *ctx);
BOOL ScrCmd_RetrieveDaycareMon(ScriptContext *ctx);
BOOL ScrCmd_GiveLoanMon(ScriptContext *ctx);
BOOL ScrCmd_CheckReturnLoanMon(ScriptContext *ctx);
BOOL ScrCmd_TakeMon(ScriptContext *ctx);
BOOL ScrCmd_ResetDaycareEgg(ScriptContext *ctx);
BOOL ScrCmd_GiveDaycareEgg(ScriptContext *ctx);
BOOL ScrCmd_BufferDaycareWithdrawCost(ScriptContext *ctx);
BOOL ScrCmd_HasEnoughMoneyVar(ScriptContext *ctx);
BOOL ScrCmd_EggHatchAnim(ScriptContext *ctx);
BOOL ScrCmd_370(ScriptContext *ctx);
BOOL ScrCmd_BufferDaycareMonGrowth(ScriptContext *ctx);
BOOL ScrCmd_GetTailDaycareMonSpeciesAndNick(ScriptContext *ctx);
BOOL ScrCmd_PutMonInDaycare(ScriptContext *ctx);
BOOL ScrCmd_374(ScriptContext *ctx);
BOOL ScrCmd_MakeObjectVisible(ScriptContext *ctx);
BOOL ScrCmd_376(ScriptContext *ctx);
BOOL ScrCmd_377(ScriptContext *ctx);
BOOL ScrCmd_378(ScriptContext *ctx);
BOOL ScrCmd_379(ScriptContext *ctx);
BOOL ScrCmd_Random(ScriptContext *ctx);
BOOL ScrCmd_381(ScriptContext *ctx);
BOOL ScrCmd_MonGetFriendship(ScriptContext *ctx);
BOOL ScrCmd_MonAddFriendship(ScriptContext *ctx);
BOOL ScrCmd_MonSubtractFriendship(ScriptContext *ctx);
BOOL ScrCmd_BufferDaycareMonStats(ScriptContext *ctx);
BOOL ScrCmd_GetPlayerFacing(ScriptContext *ctx);
BOOL ScrCmd_GetDaycareCompatibility(ScriptContext *ctx);
BOOL ScrCmd_CheckDaycareEgg(ScriptContext *ctx);
BOOL ScrCmd_PlayerHasSpecies(ScriptContext *ctx);
BOOL ScrCmd_SizeRecordCompare(ScriptContext *ctx);
BOOL ScrCmd_SizeRecordUpdate(ScriptContext *ctx);
BOOL ScrCmd_BufferMonSize(ScriptContext *ctx);
BOOL ScrCmd_BufferRecordSize(ScriptContext *ctx);
BOOL ScrCmd_394(ScriptContext *ctx);
BOOL ScrCmd_395(ScriptContext *ctx);
BOOL ScrCmd_CountMonMoves(ScriptContext *ctx);
BOOL ScrCmd_MonForgetMove(ScriptContext *ctx);
BOOL ScrCmd_MonGetMove(ScriptContext *ctx);
BOOL ScrCmd_BufferPartyMonMoveName(ScriptContext *ctx);
BOOL ScrCmd_StrengthFlagAction(ScriptContext *ctx);
BOOL ScrCmd_FlashAction(ScriptContext *ctx);
BOOL ScrCmd_DefogAction(ScriptContext *ctx);
BOOL ScrCmd_403(ScriptContext *ctx);
BOOL ScrCmd_404(ScriptContext *ctx);
BOOL ScrCmd_405(ScriptContext *ctx);
BOOL ScrCmd_406(ScriptContext *ctx);
BOOL ScrCmd_407(ScriptContext *ctx);
BOOL ScrCmd_408(ScriptContext *ctx);
BOOL ScrCmd_409(ScriptContext *ctx);
BOOL ScrCmd_410(ScriptContext *ctx);
BOOL ScrCmd_411(ScriptContext *ctx);
BOOL ScrCmd_412(ScriptContext *ctx);
BOOL ScrCmd_413(ScriptContext *ctx);
BOOL ScrCmd_414(ScriptContext *ctx);
BOOL ScrCmd_415(ScriptContext *ctx);
BOOL ScrCmd_416(ScriptContext *ctx);
BOOL ScrCmd_417(ScriptContext *ctx);
BOOL ScrCmd_418(ScriptContext *ctx);
BOOL ScrCmd_419(ScriptContext *ctx);
BOOL ScrCmd_420(ScriptContext *ctx);
BOOL ScrCmd_421(ScriptContext *ctx);
BOOL ScrCmd_422(ScriptContext *ctx);
BOOL ScrCmd_CheckJohtoDexComplete(ScriptContext *ctx);
BOOL ScrCmd_CheckNationalDexComplete(ScriptContext *ctx);
BOOL ScrCmd_ShowCertificate(ScriptContext *ctx);
BOOL ScrCmd_KenyaCheck(ScriptContext *ctx);
BOOL ScrCmd_427(ScriptContext *ctx);
BOOL ScrCmd_MonGiveMail(ScriptContext *ctx);
BOOL ScrCmd_CountFossils(ScriptContext *ctx);
BOOL ScrCmd_SetPhoneCall(ScriptContext *ctx);
BOOL ScrCmd_RunPhoneCall(ScriptContext *ctx);
BOOL ScrCmd_GetFossilPokemon(ScriptContext *ctx);
BOOL ScrCmd_GetFossilMinimumAmount(ScriptContext *ctx);
BOOL ScrCmd_PartyCountMonsAtOrBelowLevel(ScriptContext *ctx);
BOOL ScrCmd_SurvivePoisoning(ScriptContext *ctx);
BOOL ScrCmd_436(ScriptContext *ctx);
BOOL ScrCmd_DebugWatch(ScriptContext *ctx);
BOOL ScrCmd_GetStdMsgNaix(ScriptContext *ctx);
BOOL ScrCmd_NonNpcMsgExtern(ScriptContext *ctx);
BOOL ScrCmd_MsgboxExtern(ScriptContext *ctx);
BOOL ScrCmd_441(ScriptContext *ctx);
BOOL ScrCmd_442(ScriptContext *ctx);
BOOL ScrCmd_443(ScriptContext *ctx);
BOOL ScrCmd_444(ScriptContext *ctx);
BOOL ScrCmd_445(ScriptContext *ctx);
BOOL ScrCmd_446(ScriptContext *ctx);
BOOL ScrCmd_SafariZoneAction(ScriptContext *ctx);
BOOL ScrCmd_448(ScriptContext *ctx);
BOOL ScrCmd_449(ScriptContext *ctx);
BOOL ScrCmd_450(ScriptContext *ctx);
BOOL ScrCmd_451(ScriptContext *ctx);
BOOL ScrCmd_452(ScriptContext *ctx);
BOOL ScrCmd_453(ScriptContext *ctx);
BOOL ScrCmd_454(ScriptContext *ctx);
BOOL ScrCmd_455(ScriptContext *ctx);
BOOL ScrCmd_456(ScriptContext *ctx);
BOOL ScrCmd_MonGetNature(ScriptContext *ctx);
BOOL ScrCmd_GetPartySlotWithNature(ScriptContext *ctx);
BOOL ScrCmd_459(ScriptContext *ctx);
BOOL ScrCmd_LoadPhoneDat(ScriptContext *ctx);
BOOL ScrCmd_GetPhoneContactMsgIds(ScriptContext *ctx);
BOOL ScrCmd_462(ScriptContext *ctx);
BOOL ScrCmd_EnableMassOutbreaks(ScriptContext *ctx);
BOOL ScrCmd_CreateRoamer(ScriptContext *ctx);
BOOL ScrCmd_465(ScriptContext *ctx);
BOOL ScrCmd_466(ScriptContext *ctx);
BOOL ScrCmd_MoveRelearner(ScriptContext *ctx);
BOOL ScrCmd_MoveTutor(ScriptContext *ctx);
BOOL ScrCmd_MoveRelearnerGetResult(ScriptContext *ctx);
BOOL ScrCmd_LoadNPCTrade(ScriptContext *ctx);
BOOL ScrCmd_GetOfferedSpecies(ScriptContext *ctx);
BOOL ScrCmd_NPCTradeGetReqSpecies(ScriptContext *ctx);
BOOL ScrCmd_NPCTradeExec(ScriptContext *ctx);
BOOL ScrCmd_NPCTradeEnd(ScriptContext *ctx);
BOOL ScrCmd_475(ScriptContext *ctx);
BOOL ScrCmd_476(ScriptContext *ctx);
BOOL ScrCmd_NatDexFlagAction(ScriptContext *ctx);
BOOL ScrCmd_MonGetRibbonCount(ScriptContext *ctx);
BOOL ScrCmd_GetPartyRibbonCount(ScriptContext *ctx);
BOOL ScrCmd_MonHasRibbon(ScriptContext *ctx);
BOOL ScrCmd_GiveRibbon(ScriptContext *ctx);
BOOL ScrCmd_BufferRibbonName(ScriptContext *ctx);
BOOL ScrCmd_GetEVTotal(ScriptContext *ctx);
BOOL ScrCmd_GetWeekday(ScriptContext *ctx);
BOOL ScrCmd_485(ScriptContext *ctx);
// BOOL ScrCmd_Dummy(ScriptContext* ctx);
BOOL ScrCmd_PokeCenAnim(ScriptContext *ctx);
BOOL ScrCmd_ElevatorAnim(ScriptContext *ctx);
BOOL ScrCmd_MysteryGift(ScriptContext *ctx);
BOOL ScrCmd_NopVar490(ScriptContext *ctx);
BOOL ScrCmd_491(ScriptContext *ctx);
BOOL ScrCmd_492(ScriptContext *ctx);
BOOL ScrCmd_PromptEasyChat(ScriptContext *ctx);
BOOL ScrCmd_494(ScriptContext *ctx);
BOOL ScrCmd_GetGameVersion(ScriptContext *ctx);
BOOL ScrCmd_GetPartyLead(ScriptContext *ctx);
BOOL ScrCmd_GetMonTypes(ScriptContext *ctx);
BOOL ScrCmd_PrimoPasswordCheck1(ScriptContext *ctx);
BOOL ScrCmd_PrimoPasswordCheck2(ScriptContext *ctx);
BOOL ScrCmd_500(ScriptContext *ctx);
BOOL ScrCmd_501(ScriptContext *ctx);
BOOL ScrCmd_502(ScriptContext *ctx);
BOOL ScrCmd_LotoIdGet(ScriptContext *ctx);
BOOL ScrCmd_LotoIdSearch(ScriptContext *ctx);
BOOL ScrCmd_LotoIdSet(ScriptContext *ctx);
BOOL ScrCmd_BufferBoxMonNick(ScriptContext *ctx);
BOOL ScrCmd_CountPCEmptySpace(ScriptContext *ctx);
BOOL ScrCmd_PalParkAction(ScriptContext *ctx);
BOOL ScrCmd_509(ScriptContext *ctx);
BOOL ScrCmd_510(ScriptContext *ctx);
BOOL ScrCmd_PalParkScoreGet(ScriptContext *ctx);
BOOL ScrCmd_PlayerMovementSavingSet(ScriptContext *ctx);
BOOL ScrCmd_PlayerMovementSavingClear(ScriptContext *ctx);
BOOL ScrCmd_HallOfFameAnim(ScriptContext *ctx);
BOOL ScrCmd_AddSpecialGameStat(ScriptContext *ctx);
BOOL ScrCmd_BufferFashionName(ScriptContext *ctx);
BOOL ScrCmd_517(ScriptContext *ctx);
BOOL ScrCmd_518(ScriptContext *ctx);
BOOL ScrCmd_519(ScriptContext *ctx);
BOOL ScrCmd_520(ScriptContext *ctx);
BOOL ScrCmd_521(ScriptContext *ctx);
BOOL ScrCmd_522(ScriptContext *ctx);
BOOL ScrCmd_523(ScriptContext *ctx);
BOOL ScrCmd_524(ScriptContext *ctx);
BOOL ScrCmd_525(ScriptContext *ctx);
BOOL ScrCmd_526(ScriptContext *ctx);
BOOL ScrCmd_527(ScriptContext *ctx);
BOOL ScrCmd_528(ScriptContext *ctx);
BOOL ScrCmd_GetPartyLeadAlive(ScriptContext *ctx);
BOOL ScrCmd_530(ScriptContext *ctx);
BOOL ScrCmd_BufferBackgroundName(ScriptContext *ctx);
BOOL ScrCmd_CheckCoinsImmediate(ScriptContext *ctx);
BOOL ScrCmd_CheckGiveCoins(ScriptContext *ctx);
BOOL ScrCmd_534(ScriptContext *ctx);
BOOL ScrCmd_MonGetLevel(ScriptContext *ctx);
BOOL ScrCmd_536(ScriptContext *ctx);
BOOL ScrCmd_537(ScriptContext *ctx);
BOOL ScrCmd_538(ScriptContext *ctx);
BOOL ScrCmd_539(ScriptContext *ctx);
BOOL ScrCmd_540(ScriptContext *ctx);
BOOL ScrCmd_BufferIntEx(ScriptContext *ctx);
BOOL ScrCmd_MonGetContestValue(ScriptContext *ctx);
BOOL ScrCmd_543(ScriptContext *ctx);
BOOL ScrCmd_544(ScriptContext *ctx);
BOOL ScrCmd_545(ScriptContext *ctx);
BOOL ScrCmd_546(ScriptContext *ctx);
BOOL ScrCmd_547(ScriptContext *ctx);
BOOL ScrCmd_548(ScriptContext *ctx);
BOOL ScrCmd_549(ScriptContext *ctx);
BOOL ScrCmd_550(ScriptContext *ctx);
BOOL ScrCmd_551(ScriptContext *ctx);
BOOL ScrCmd_552(ScriptContext *ctx);
BOOL ScrCmd_553(ScriptContext *ctx);
BOOL ScrCmd_554(ScriptContext *ctx);
BOOL ScrCmd_555(ScriptContext *ctx);
BOOL ScrCmd_556(ScriptContext *ctx);
BOOL ScrCmd_CheckBattlePoints(ScriptContext *ctx);
BOOL ScrCmd_UnionRoomAvatarIdxToSprite(ScriptContext *ctx);
BOOL ScrCmd_559(ScriptContext *ctx);
BOOL ScrCmd_560(ScriptContext *ctx);
BOOL ScrCmd_ScreenShake(ScriptContext *ctx);
BOOL ScrCmd_MultiBattle(ScriptContext *ctx);
BOOL ScrCmd_563(ScriptContext *ctx);
BOOL ScrCmd_564(ScriptContext *ctx);
BOOL ScrCmd_565(ScriptContext *ctx);
BOOL ScrCmd_566(ScriptContext *ctx);
BOOL ScrCmd_GetDPPlPrizeItemIdAndCost(ScriptContext *ctx);
BOOL ScrCmd_568(ScriptContext *ctx);
BOOL ScrCmd_569(ScriptContext *ctx);
BOOL ScrCmd_CheckCoinsVar(ScriptContext *ctx);
BOOL ScrCmd_571(ScriptContext *ctx);
BOOL ScrCmd_GetUniqueSealsQuantity(ScriptContext *ctx);
BOOL ScrCmd_573(ScriptContext *ctx);
BOOL ScrCmd_574(ScriptContext *ctx);
BOOL ScrCmd_575(ScriptContext *ctx);
BOOL ScrCmd_576(ScriptContext *ctx);
BOOL ScrCmd_577(ScriptContext *ctx);
BOOL ScrCmd_578(ScriptContext *ctx);
BOOL ScrCmd_579(ScriptContext *ctx);
BOOL ScrCmd_BufferSealName(ScriptContext *ctx);
BOOL ScrCmd_LockLastTalked(ScriptContext *ctx);
BOOL ScrCmd_582(ScriptContext *ctx);
BOOL ScrCmd_583(ScriptContext *ctx);
BOOL ScrCmd_PartyLegalCheck(ScriptContext *ctx);
BOOL ScrCmd_585(ScriptContext *ctx);
BOOL ScrCmd_586(ScriptContext *ctx);
BOOL ScrCmd_587(ScriptContext *ctx);
BOOL Scrcmd_LatiCaughtCheck(ScriptContext *ctx);
BOOL ScrCmd_WildBattle(ScriptContext *ctx);
BOOL ScrCmd_GetTrcardStars(ScriptContext *ctx);
BOOL ScrCmd_591(ScriptContext *ctx);
BOOL ScrCmd_592(ScriptContext *ctx);
BOOL ScrCmd_ShowSaveStats(ScriptContext *ctx);
BOOL ScrCmd_HideSaveStats(ScriptContext *ctx);
BOOL ScrCmd_595(ScriptContext *ctx);
BOOL ScrCmd_596(ScriptContext *ctx);
BOOL ScrCmd_597(ScriptContext *ctx);
BOOL ScrCmd_598(ScriptContext *ctx);
BOOL ScrCmd_599(ScriptContext *ctx);
BOOL ScrCmd_600(ScriptContext *ctx);
BOOL ScrCmd_FollowMonFacePlayer(ScriptContext *ctx);
BOOL ScrCmd_ToggleFollowingPokemonMovement(ScriptContext *ctx);
BOOL ScrCmd_WaitFollowingPokemonMovement(ScriptContext *ctx);
BOOL ScrCmd_FollowingPokemonMovement(ScriptContext *ctx);
BOOL ScrCmd_605(ScriptContext *ctx);
BOOL ScrCmd_606(ScriptContext *ctx);
BOOL ScrCmd_607(ScriptContext *ctx);
BOOL ScrCmd_608(ScriptContext *ctx);
BOOL ScrCmd_609(ScriptContext *ctx);
BOOL ScrCmd_610(ScriptContext *ctx);
BOOL ScrCmd_Pokeathlon(ScriptContext *ctx);
BOOL ScrCmd_GetNpcTradeUnusedFlag(ScriptContext *ctx);
BOOL ScrCmd_GetPhoneContactRandomGiftBerry(ScriptContext *ctx);
BOOL ScrCmd_GetPhoneContactGiftItem(ScriptContext *ctx);
BOOL ScrCmd_CameronPhoto(ScriptContext *ctx);
BOOL ScrCmd_CountSavedPhotos(ScriptContext *ctx);
BOOL ScrCmd_OpenPhotoAlbum(ScriptContext *ctx);
BOOL ScrCmd_PhotoAlbumIsFull(ScriptContext *ctx);
BOOL ScrCmd_RocketCostumeFlagCheck(ScriptContext *ctx);
BOOL ScrCmd_RocketCostumeFlagAction(ScriptContext *ctx);
BOOL ScrCmd_PlaceStarterBallsInElmsLab(ScriptContext *ctx);
BOOL ScrCmd_622(ScriptContext *ctx);
BOOL ScrCmd_AnimApricornTree(ScriptContext *ctx);
BOOL ScrCmd_ApricornTreeGetApricorn(ScriptContext *ctx);
BOOL ScrCmd_GiveApricornFromTree(ScriptContext *ctx);
BOOL ScrCmd_BufferApricornName(ScriptContext *ctx);
BOOL ScrCmd_627(ScriptContext *ctx);
BOOL ScrCmd_628(ScriptContext *ctx);
BOOL ScrCmd_629(ScriptContext *ctx);
BOOL ScrCmd_630(ScriptContext *ctx);
BOOL ScrCmd_631(ScriptContext *ctx);
BOOL ScrCmd_CountPartyMonsOfSpecies(ScriptContext *ctx);
BOOL ScrCmd_633(ScriptContext *ctx);
BOOL ScrCmd_634(ScriptContext *ctx);
BOOL ScrCmd_635(ScriptContext *ctx);
BOOL ScrCmd_636(ScriptContext *ctx);
BOOL ScrCmd_637(ScriptContext *ctx);
BOOL ScrCmd_638(ScriptContext *ctx);
BOOL ScrCmd_639(ScriptContext *ctx);
BOOL ScrCmd_640(ScriptContext *ctx);
BOOL ScrCmd_SaveWipeExtraChunks(ScriptContext *ctx);
BOOL ScrCmd_642(ScriptContext *ctx);
BOOL ScrCmd_643(ScriptContext *ctx);
BOOL ScrCmd_644(ScriptContext *ctx);
BOOL ScrCmd_645(ScriptContext *ctx);
BOOL ScrCmd_646(ScriptContext *ctx);
BOOL ScrCmd_GetPartySlotWithSpecies(ScriptContext *ctx);
BOOL ScrCmd_648(ScriptContext *ctx);
BOOL ScrCmd_ScratchOffCard(ScriptContext *ctx);
BOOL ScrCmd_ScratchOffCardEnd(ScriptContext *ctx);
BOOL ScrCmd_GetScratchOffPrize(ScriptContext *ctx);
BOOL ScrCmd_652(ScriptContext *ctx);
BOOL ScrCmd_MoveTutorChooseMove(ScriptContext *ctx);
BOOL ScrCmd_TutorMoveTeachInSlot(ScriptContext *ctx);
BOOL ScrCmd_TutorMoveGetPrice(ScriptContext *ctx);
BOOL ScrCmd_656(ScriptContext *ctx);
BOOL ScrCmd_StatJudge(ScriptContext *ctx);
BOOL ScrCmd_BufferStatName(ScriptContext *ctx);
BOOL ScrCmd_SetMonForm(ScriptContext *ctx);
BOOL ScrCmd_BufferTrainerName(ScriptContext *ctx);
BOOL ScrCmd_661(ScriptContext *ctx);
BOOL ScrCmd_662(ScriptContext *ctx);
BOOL ScrCmd_663(ScriptContext *ctx);
BOOL ScrCmd_664(ScriptContext *ctx);
BOOL ScrCmd_665(ScriptContext *ctx);
BOOL ScrCmd_666(ScriptContext *ctx);
BOOL ScrCmd_667(ScriptContext *ctx);
BOOL ScrCmd_BufferTypeName(ScriptContext *ctx);
BOOL ScrCmd_GetItemQuantity(ScriptContext *ctx);
BOOL ScrCmd_GetHiddenPowerType(ScriptContext *ctx);
BOOL ScrCmd_SetFavoriteMon(ScriptContext *ctx);
BOOL ScrCmd_GetFavoriteMon(ScriptContext *ctx);
BOOL ScrCmd_GetOwnedRotomForms(ScriptContext *ctx);
BOOL ScrCmd_CountTranformedRotomsInParty(ScriptContext *ctx);
BOOL ScrCmd_UpdateRotomForm(ScriptContext *ctx);
BOOL ScrCmd_GetPartyMonForm(ScriptContext *ctx);
BOOL ScrCmd_677(ScriptContext *ctx);
BOOL ScrCmd_678(ScriptContext *ctx);
BOOL ScrCmd_679(ScriptContext *ctx);
BOOL ScrCmd_AddSpecialGameStat(ScriptContext *ctx);
BOOL ScrCmd_681(ScriptContext *ctx);
BOOL ScrCmd_682(ScriptContext *ctx);
BOOL ScrCmd_GetStaticEncounterOutcomeFlag(ScriptContext *ctx);
BOOL ScrCmd_684(ScriptContext *ctx);
BOOL ScrCmd_GetPlayerXYZ(ScriptContext *ctx);
BOOL ScrCmd_686(ScriptContext *ctx);
BOOL ScrCmd_687(ScriptContext *ctx);
BOOL ScrCmd_GetPartySlotWithFatefulEncounter(ScriptContext *ctx);
BOOL ScrCmd_CommSanitizeParty(ScriptContext *ctx);
BOOL ScrCmd_DaycareSanitizeMon(ScriptContext *ctx);
BOOL ScrCmd_691(ScriptContext *ctx);
BOOL ScrCmd_BufferBattleHallStreak(ScriptContext *ctx);
BOOL ScrCmd_BattleHallCountUsedSpecies(ScriptContext *ctx);
BOOL ScrCmd_BattleHallGetTotalStreak(ScriptContext *ctx);
BOOL ScrCmd_695(ScriptContext *ctx);
BOOL ScrCmd_696(ScriptContext *ctx);
BOOL ScrCmd_697(ScriptContext *ctx);
BOOL ScrCmd_FollowerPokeIsEventTrigger(ScriptContext *ctx);
BOOL ScrCmd_699(ScriptContext *ctx);
BOOL ScrCmd_700(ScriptContext *ctx);
BOOL ScrCmd_MonHasItem(ScriptContext *ctx);
BOOL ScrCmd_BattleTowerSetUpMultiBattle(ScriptContext *ctx);
BOOL ScrCmd_SetPlayerVolume(ScriptContext *ctx);
BOOL ScrCmd_704(ScriptContext *ctx);
BOOL ScrCmd_705(ScriptContext *ctx);
BOOL ScrCmd_706(ScriptContext *ctx);
BOOL ScrCmd_CheckMonSeen(ScriptContext *ctx);
BOOL ScrCmd_708(ScriptContext *ctx);
BOOL ScrCmd_709(ScriptContext *ctx);
BOOL ScrCmd_710(ScriptContext *ctx);
BOOL ScrCmd_FollowMonInteract(ScriptContext *ctx);
BOOL ScrCmd_712(ScriptContext *ctx);
BOOL ScrCmd_AlphPuzzle(ScriptContext *ctx);
BOOL ScrCmd_OpenAlphHiddenRoom(ScriptContext *ctx);
BOOL ScrCmd_UpdateDaycareMonObjects(ScriptContext *ctx);
BOOL ScrCmd_716(ScriptContext *ctx);
BOOL ScrCmd_717(ScriptContext *ctx);
BOOL ScrCmd_718(ScriptContext *ctx);
BOOL ScrCmd_719(ScriptContext *ctx);
BOOL ScrCmd_720(ScriptContext *ctx);
BOOL ScrCmd_721(ScriptContext *ctx);
BOOL ScrCmd_722(ScriptContext *ctx);
BOOL ScrCmd_723(ScriptContext *ctx);
BOOL ScrCmd_724(ScriptContext *ctx);
BOOL ScrCmd_725(ScriptContext *ctx);
BOOL ScrCmd_726(ScriptContext *ctx);
BOOL ScrCmd_GetFollowPokePartyIndex(ScriptContext *ctx);
BOOL ScrCmd_728(ScriptContext *ctx);
BOOL ScrCmd_729(ScriptContext *ctx);
BOOL ScrCmd_730(ScriptContext *ctx);
BOOL ScrCmd_731(ScriptContext *ctx);
BOOL ScrCmd_732(ScriptContext *ctx);
BOOL ScrCmd_733(ScriptContext *ctx);
BOOL ScrCmd_734(ScriptContext *ctx);
BOOL ScrCmd_735(ScriptContext *ctx);
BOOL ScrCmd_ClearKurtApricorn(ScriptContext *ctx);
BOOL ScrCmd_737(ScriptContext *ctx);
BOOL ScrCmd_GetTotalApricornCount(ScriptContext *ctx);
BOOL ScrCmd_739(ScriptContext *ctx);
BOOL ScrCmd_740(ScriptContext *ctx);
BOOL ScrCmd_741(ScriptContext *ctx);
BOOL ScrCmd_742(ScriptContext *ctx);
BOOL ScrCmd_743(ScriptContext *ctx);
BOOL ScrCmd_CreatePokeathlonFriendshipRoomStatues(ScriptContext *ctx);
BOOL ScrCmd_BufferPokeathlonCourseName(ScriptContext *ctx);
BOOL ScrCmd_TouchscreenMenuHide(ScriptContext *ctx);
BOOL ScrCmd_TouchscreenMenuShow(ScriptContext *ctx);
BOOL ScrCmd_GetMenuChoice(ScriptContext *ctx);
BOOL ScrCmd_MenuInitStdGmm(ScriptContext *ctx);
BOOL ScrCmd_MenuInit(ScriptContext *ctx);
BOOL ScrCmd_MenuItemAdd(ScriptContext *ctx);
BOOL ScrCmd_MenuExec(ScriptContext *ctx);
BOOL ScrCmd_RockSmashItemCheck(ScriptContext *ctx);
BOOL ScrCmd_TryHeadbuttEncounter(ScriptContext *ctx);
BOOL ScrCmd_LegendCutsceneClearBellAnimBegin(ScriptContext *ctx);
BOOL ScrCmd_LegendCutsceneClearBellAnimEnd(ScriptContext *ctx);
BOOL ScrCmd_LegendCutsceneClearBellRiseFromBag(ScriptContext *ctx);
BOOL ScrCmd_LegendCutsceneClearBellShimmer(ScriptContext *ctx);
BOOL ScrCmd_LegendCutsceneLugiaEyeGlimmerEffect(ScriptContext *ctx);
BOOL ScrCmd_760(ScriptContext *ctx);
BOOL ScrCmd_LegendCutsceneMoveCameraTo(ScriptContext *ctx);
BOOL ScrCmd_LegendCutscenePanCameraTo(ScriptContext *ctx);
BOOL ScrCmd_LegendCutsceneWaitCameraPan(ScriptContext *ctx);
BOOL ScrCmd_LegendCutsceneBirdFinalApproach(ScriptContext *ctx);
BOOL ScrCmd_LegendCutsceneWavesOrLeavesEffectBegin(ScriptContext *ctx);
BOOL ScrCmd_LegendCutsceneWavesOrLeavesEffectEnd(ScriptContext *ctx);
BOOL ScrCmd_LegendCutsceneLugiaArrivesEffectBegin(ScriptContext *ctx);
BOOL ScrCmd_LegendCutsceneLugiaArrivesEffectEnd(ScriptContext *ctx);
BOOL ScrCmd_LegendCutsceneLugiaArrivesEffectCameraPan(ScriptContext *ctx);
BOOL ScrCmd_CheckSeenAllLetterUnown(ScriptContext *ctx);
BOOL ScrCmd_771(ScriptContext *ctx);
BOOL ScrCmd_772(ScriptContext *ctx);
BOOL ScrCmd_Cinematic(ScriptContext *ctx);
BOOL ScrCmd_ShowLegendaryWing(ScriptContext *ctx);
BOOL ScrCmd_775(ScriptContext *ctx);
BOOL ScrCmd_GiveTogepiEgg(ScriptContext *ctx);
BOOL ScrCmd_777(ScriptContext *ctx);
BOOL ScrCmd_GiveSpikyEarPichu(ScriptContext *ctx);
BOOL ScrCmd_RadioMusicIsPlaying(ScriptContext *ctx);
BOOL ScrCmd_CasinoGame(ScriptContext *ctx);
BOOL ScrCmd_KenyaCheckPartyOrMailbox(ScriptContext *ctx);
BOOL ScrCmd_MartSell(ScriptContext *ctx);
BOOL ScrCmd_SetFollowMonInhibitState(ScriptContext *ctx);
BOOL ScrCmd_ScriptOverlayCmd(ScriptContext *ctx);
BOOL ScrCmd_BugContestAction(ScriptContext *ctx);
BOOL ScrCmd_BufferBugContestWinner(ScriptContext *ctx);
BOOL ScrCmd_JudgeBugContest(ScriptContext *ctx);
BOOL ScrCmd_BufferBugContestMonNick(ScriptContext *ctx);
BOOL ScrCmd_BugContestGetTimeLeft(ScriptContext *ctx);
BOOL ScrCmd_IsBugContestantRegistered(ScriptContext *ctx);
BOOL ScrCmd_791(ScriptContext *ctx);
BOOL ScrCmd_792(ScriptContext *ctx);
BOOL ScrCmd_BankTransaction(ScriptContext *ctx);
BOOL ScrCmd_CheckBankBalance(ScriptContext *ctx);
BOOL ScrCmd_795(ScriptContext *ctx);
BOOL ScrCmd_796(ScriptContext *ctx);
BOOL ScrCmd_797(ScriptContext *ctx);
BOOL ScrCmd_BufferRulesetName(ScriptContext *ctx);
BOOL ScrCmd_799(ScriptContext *ctx);
BOOL ScrCmd_800(ScriptContext *ctx);
BOOL ScrCmd_801(ScriptContext *ctx);
BOOL ScrCmd_802(ScriptContext *ctx);
BOOL ScrCmd_803(ScriptContext *ctx);
BOOL ScrCmd_804(ScriptContext *ctx);
BOOL ScrCmd_805(ScriptContext *ctx);
BOOL ScrCmd_806(ScriptContext *ctx);
BOOL ScrCmd_SetTrainerHouseSprite(ScriptContext *ctx);
BOOL ScrCmd_808(ScriptContext *ctx);
BOOL ScrCmd_ShowTrainerHouseIntroMessage(ScriptContext *ctx);
BOOL ScrCmd_810(ScriptContext *ctx);
BOOL ScrCmd_811(ScriptContext *ctx);
BOOL ScrCmd_812(ScriptContext *ctx);
BOOL ScrCmd_MomGiftCheck(ScriptContext *ctx);
BOOL ScrCmd_814(ScriptContext *ctx);
BOOL ScrCmd_815(ScriptContext *ctx);
BOOL ScrCmd_UnownCircle(ScriptContext *ctx);
BOOL ScrCmd_817(ScriptContext *ctx);
BOOL ScrCmd_MystriStageGymmickInit(ScriptContext *ctx);
BOOL ScrCmd_819(ScriptContext *ctx);
BOOL ScrCmd_820(ScriptContext *ctx);
BOOL ScrCmd_GetBuenasPassword(ScriptContext *ctx);
BOOL ScrCmd_822(ScriptContext *ctx);
BOOL ScrCmd_823(ScriptContext *ctx);
BOOL ScrCmd_824(ScriptContext *ctx);
BOOL ScrCmd_GetShinyLeafCount(ScriptContext *ctx);
BOOL ScrCmd_TryGiveShinyLeafCrown(ScriptContext *ctx);
BOOL ScrCmd_GetPartymonForm(ScriptContext *ctx);
BOOL ScrCmd_MonAddContestValue(ScriptContext *ctx);
BOOL ScrCmd_829(ScriptContext *ctx);
BOOL ScrCmd_830(ScriptContext *ctx);
BOOL ScrCmd_831(ScriptContext *ctx);
BOOL ScrCmd_832(ScriptContext *ctx);
BOOL ScrCmd_833(ScriptContext *ctx);
BOOL ScrCmd_834(ScriptContext *ctx);
BOOL ScrCmd_835(ScriptContext *ctx);
BOOL ScrCmd_CheckKyogreGroudonInParty(ScriptContext *ctx);
BOOL ScrCmd_837(ScriptContext *ctx);
BOOL ScrCmd_BankOrWalletIsFull(ScriptContext *ctx);
BOOL ScrCmd_SysSetSleepFlag(ScriptContext *ctx);
BOOL ScrCmd_840(ScriptContext *ctx);
BOOL ScrCmd_841(ScriptContext *ctx);
BOOL ScrCmd_842(ScriptContext *ctx);
BOOL ScrCmd_BufferItemNameIndef(ScriptContext *ctx);
BOOL ScrCmd_BufferItemNamePlural(ScriptContext *ctx);
BOOL ScrCmd_BufferPartyMonSpeciesNameIndef(ScriptContext *ctx);
BOOL ScrCmd_BufferSpeciesNameIndef(ScriptContext *ctx);
BOOL ScrCmd_BufferDPPtFriendStarterSpeciesNameIndef(ScriptContext *ctx);
BOOL ScrCmd_BufferFashionNameIndef(ScriptContext *ctx);
BOOL ScrCmd_BufferTrainerClassNameIndef(ScriptContext *ctx);
BOOL ScrCmd_BufferSealNamePlural(ScriptContext *ctx);
BOOL ScrCmd_Capitalize(ScriptContext *ctx);
BOOL ScrCmd_BufferDeptStoreFloorNo(ScriptContext *ctx);

MessageFormat *sub_0204B538(SaveData *saveData, u16 numEligblePokemon, u16 a2, u8 a3, u8 *numLegendaryPokemonSeen);
void ov01_021EF564(ScriptContext *ctx, u16 messageBank, u16 messageNum, u16 word1, s16 word2, u8 canABSpeedUp);

#endif
