    .include "macros/btlcmd.inc"

    .data

_000:
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_DISOBEDIENCE, _147
    CompareVarToValue OPCODE_NEQ, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_MOVE_EFFECT, _055
    CheckAbility CHECK_OPCODE_HAVE, BATTLER_CATEGORY_SIDE_EFFECT_MON, ABILITY_INSOMNIA, _202
    CheckAbility CHECK_OPCODE_HAVE, BATTLER_CATEGORY_SIDE_EFFECT_MON, ABILITY_VITAL_SPIRIT, _202
    CheckIgnoreWeather _031
    CompareVarToValue OPCODE_FLAG_NOT, BSCRIPT_VAR_FIELD_CONDITION, FIELD_CONDITION_SUN_ALL, _031
    CheckAbility CHECK_OPCODE_HAVE, BATTLER_CATEGORY_SIDE_EFFECT_MON, ABILITY_LEAF_GUARD, _202

_031:
    CompareMonDataToValue OPCODE_FLAG_SET, BATTLER_CATEGORY_SIDE_EFFECT_MON, BMON_DATA_STATUS, STATUS_SLEEP, _274
    CheckAbility CHECK_OPCODE_HAVE, BATTLER_CATEGORY_SIDE_EFFECT_MON, ABILITY_SOUNDPROOF, _047
    CompareVarToValue OPCODE_FLAG_SET, BSCRIPT_VAR_FIELD_CONDITION, FIELD_CONDITION_UPROAR, _292

_047:
    CompareMonDataToValue OPCODE_NEQ, BATTLER_CATEGORY_SIDE_EFFECT_MON, BMON_DATA_STATUS, STATUS_NONE, _237
    GoTo _147

_055:
    CheckIgnorableAbility CHECK_OPCODE_HAVE, BATTLER_CATEGORY_SIDE_EFFECT_MON, ABILITY_INSOMNIA, _202
    CheckIgnorableAbility CHECK_OPCODE_HAVE, BATTLER_CATEGORY_SIDE_EFFECT_MON, ABILITY_VITAL_SPIRIT, _202
    CheckIgnoreWeather _077
    CompareVarToValue OPCODE_FLAG_NOT, BSCRIPT_VAR_FIELD_CONDITION, FIELD_CONDITION_SUN_ALL, _077
    CheckIgnorableAbility CHECK_OPCODE_HAVE, BATTLER_CATEGORY_SIDE_EFFECT_MON, ABILITY_LEAF_GUARD, _202

_077:
    CompareVarToValue OPCODE_NEQ, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_INDIRECT, _087
    CheckIgnorableAbility CHECK_OPCODE_HAVE, BATTLER_CATEGORY_SIDE_EFFECT_MON, ABILITY_SHIELD_DUST, _237

_087:
    CompareVarToValue OPCODE_NEQ, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_DIRECT, _094
    PrintAttackMessage 
    Wait 

_094:
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_ABILITY, _102
    CheckSubstitute BATTLER_CATEGORY_SIDE_EFFECT_MON, _237

_102:
    CompareMonDataToValue OPCODE_FLAG_SET, BATTLER_CATEGORY_SIDE_EFFECT_MON, BMON_DATA_STATUS, STATUS_SLEEP, _274
    CheckAbility CHECK_OPCODE_HAVE, BATTLER_CATEGORY_SIDE_EFFECT_MON, ABILITY_SOUNDPROOF, _118
    CompareVarToValue OPCODE_FLAG_SET, BSCRIPT_VAR_FIELD_CONDITION, FIELD_CONDITION_UPROAR, _292

_118:
    CompareMonDataToValue OPCODE_NEQ, BATTLER_CATEGORY_SIDE_EFFECT_MON, BMON_DATA_STATUS, STATUS_NONE, _237
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_ABILITY, _147
    CompareVarToValue OPCODE_FLAG_SET, BSCRIPT_VAR_MOVE_STATUS_FLAGS, MOVE_STATUS_MISSED|MOVE_STATUS_SEMI_INVULNERABLE, _237
    CompareVarToValue OPCODE_FLAG_SET, BSCRIPT_VAR_SIDE_CONDITION_STAT_CHANGE, SIDE_CONDITION_SAFEGUARD, _319
    CompareVarToValue OPCODE_NEQ, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_DIRECT, _147
    PlayMoveAnimation BATTLER_CATEGORY_ATTACKER
    Wait 

_147:
    PlayBattleAnimation BATTLER_CATEGORY_SIDE_EFFECT_MON, BATTLE_ANIMATION_ASLEEP
    Wait 
    Random 3, 2
    UpdateMonDataFromVar OPCODE_FLAG_ON, BATTLER_CATEGORY_SIDE_EFFECT_MON, BMON_DATA_STATUS, BSCRIPT_VAR_CALC_TEMP
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_ABILITY, _170
    // {0} fell asleep!
    PrintMessage msg_0197_00047, TAG_NICKNAME, BATTLER_CATEGORY_SIDE_EFFECT_MON
    GoTo _176

_170:
    // {0}’s {1} made {2} fall asleep!
    PrintMessage msg_0197_00050, TAG_NICKNAME_ABILITY_NICKNAME, BATTLER_CATEGORY_MSG_TEMP, BATTLER_CATEGORY_MSG_BATTLER_TEMP, BATTLER_CATEGORY_SIDE_EFFECT_MON

_176:
    Wait 
    WaitButtonABTime 30
    SetHealthbarStatus BATTLER_CATEGORY_SIDE_EFFECT_MON, BATTLE_ANIMATION_ASLEEP
    Wait 
    CompareMonDataToValue OPCODE_FLAG_SET, BATTLER_CATEGORY_SIDE_EFFECT_MON, BMON_DATA_MOVE_EFFECT, MOVE_EFFECT_FLAG_SEMI_INVULNERABLE, _193
    UnlockMoveChoice BATTLER_CATEGORY_SIDE_EFFECT_MON
    GoTo _201

_193:
    UnlockMoveChoice BATTLER_CATEGORY_SIDE_EFFECT_MON
    UpdateVarFromVar OPCODE_SET, BSCRIPT_VAR_MSG_BATTLER_TEMP, BSCRIPT_VAR_BATTLER_STAT_CHANGE
    Call BATTLE_SUBSCRIPT_VANISH_OFF

_201:
    End 

_202:
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_INDIRECT, _337
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_ABILITY, _337
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_MOVE_EFFECT, _221
    PrintAttackMessage 
    Wait 
    WaitButtonABTime 30

_221:
    // {0} stayed awake because of its {1}!
    PrintMessage msg_0197_00329, TAG_NICKNAME_ABILITY, BATTLER_CATEGORY_SIDE_EFFECT_MON, BATTLER_CATEGORY_SIDE_EFFECT_MON
    GoTo _330
    // {0}’s {1} suppressed {2}’s {3}!
    PrintMessage msg_0197_00727, TAG_NICKNAME_ABILITY_NICKNAME_ABILITY, BATTLER_CATEGORY_SIDE_EFFECT_MON, BATTLER_CATEGORY_SIDE_EFFECT_MON, BATTLER_CATEGORY_MSG_TEMP, BATTLER_CATEGORY_MSG_BATTLER_TEMP
    GoTo _330

_237:
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_INDIRECT, _337
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_ABILITY, _337
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_MOVE_EFFECT, _337
    WaitButtonABTime 30
    GetCurrentMoveData MOVE_ATTRIBUTE_RANGE
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_CALC_TEMP, 0x00000004, _270
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_CALC_TEMP, 0x00000008, _270
    Call BATTLE_SUBSCRIPT_BUT_IT_FAILED
    GoTo _337

_270:
    Call BATTLE_SUBSCRIPT_MOVE_FAIL_MISSED
    GoTo _337

_274:
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_INDIRECT, _337
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_ABILITY, _337
    WaitButtonABTime 30
    // {0} is already asleep!
    PrintMessage msg_0197_00057, TAG_NICKNAME, BATTLER_CATEGORY_SIDE_EFFECT_MON
    GoTo _330

_292:
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_INDIRECT, _337
    CompareMonDataToValue OPCODE_FLAG_SET, BATTLER_CATEGORY_SIDE_EFFECT_MON, BMON_DATA_STATUS2, STATUS2_UPROAR, _311
    WaitButtonABTime 30
    // But the uproar kept {0} awake!
    PrintMessage msg_0197_00326, TAG_NICKNAME, BATTLER_CATEGORY_SIDE_EFFECT_MON
    GoTo _330

_311:
    WaitButtonABTime 30
    // But {0} can’t sleep in an uproar!
    PrintMessage msg_0197_00323, TAG_NICKNAME, BATTLER_CATEGORY_SIDE_EFFECT_MON
    GoTo _330

_319:
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_SIDE_EFFECT_TYPE, SIDE_EFFECT_TYPE_INDIRECT, _337
    WaitButtonABTime 30
    // {0} is protected by Safeguard!
    PrintMessage msg_0197_00200, TAG_NICKNAME, BATTLER_CATEGORY_SIDE_EFFECT_MON

_330:
    Wait 
    WaitButtonABTime 30
    UpdateVar OPCODE_FLAG_ON, BSCRIPT_VAR_MOVE_STATUS_FLAGS, MOVE_STATUS_NO_MORE_WORK

_337:
    End 
