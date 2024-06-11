    .include "macros/btlcmd.inc"

    .data

_000:
    PrintAttackMessage 
    Wait 
    WaitButtonABTime 15
    UpdateVarFromVar OPCODE_SET, BSCRIPT_VAR_MSG_ATTACKER, BSCRIPT_VAR_BATTLER_ATTACKER
    UpdateVarFromVar OPCODE_SET, BSCRIPT_VAR_BATTLER_TARGET, BSCRIPT_VAR_BATTLER_ATTACKER
    UpdateVarFromVar OPCODE_SET, BSCRIPT_VAR_BATTLER_ATTACKER, BSCRIPT_VAR_MSG_BATTLER_TEMP
    UpdateVar OPCODE_SET, BSCRIPT_VAR_MOVE_EFFECT_CHANCE, 1
    UpdateVar OPCODE_SET, BSCRIPT_VAR_MSG_MOVE_TEMP, MOVE_SNATCH
    PlayMoveAnimation BATTLER_CATEGORY_MSG_TEMP
    Wait 
    // {0} snatched {1}’s move!
    PrintMessage msg_0197_00580, TAG_NICKNAME_NICKNAME, BATTLER_CATEGORY_MSG_TEMP, BATTLER_CATEGORY_MSG_ATTACKER
    Wait 
    WaitButtonABTime 30
    UpdateVar OPCODE_SET, BSCRIPT_VAR_MOVE_EFFECT_CHANCE, 0
    UpdateVar OPCODE_FLAG_OFF, BSCRIPT_VAR_BATTLE_STATUS, BATTLE_STATUS_MOVE_ANIMATIONS_OFF
    CompareVarToValue OPCODE_EQU, BSCRIPT_VAR_MOVE_NO_CUR, MOVE_ACUPRESSURE, _052
    UpdateVarFromVar OPCODE_SET, BSCRIPT_VAR_BATTLER_TARGET, BSCRIPT_VAR_MSG_ATTACKER
    End 

_052:
    UpdateVarFromVar OPCODE_SET, BSCRIPT_VAR_BATTLER_TARGET, BSCRIPT_VAR_BATTLER_ATTACKER
    End 