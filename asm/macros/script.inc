	.ifndef ASM_SCRIPT_INC
	.set ASM_SCRIPT_INC, 1
#pragma once
#include "constants/scrcmd.h"
	.option alignment off

	.macro scrdef offset
	.word \offset - . - 4
	.endm

	.macro scrdef_end
	.short SCRDEF_END
	.endm

	; Dummy command
	.macro nop
	.short 0
	.endm

	; Dummy command
	.macro dummy
	.short 1
	.endm

	; Exits script execution and returns control to the player
	.macro end
	.short 2
	.endm

	; Pauses for some frames, tracks the timer in a script variable
	.macro wait frames, var
	.short 3
	.short \frames
	.short \var
	.endm

	; Loads 8-bit value into the specified script register
	.macro loadbyte reg, val
	.short 4
	.byte \reg
	.byte \val
	.endm

	; Loads 32-bit value into the specified script register
	.macro loadword reg, val
	.short 5
	.byte \reg
	.word \val
	.endm

	; Reads byte at a specific memory address into a script register
	; Because scripts are compiled in a code-agnostic fashion,
	; this command can never be assembled.
	.macro loadbytefromaddr reg, addr
	.short 6
	.byte \reg
	.word \addr
	.endm

	; Writes byte to a specific memory address from a script register
	; Because scripts are compiled in a code-agnostic fashion,
	; this command can never be assembled.
	.macro writebytetoaddr addr, reg
	.short 7
	.word \addr
	.byte \reg
	.endm

	; Writes byte literal to a specific memory address
	; Because scripts are compiled in a code-agnostic fashion,
	; this command can never be assembled.
	.macro setptrbyte addr, val
	.short 8
	.word \addr
	.byte \val
	.endm

	; Copies a byte between script registers
	.macro copylocal to, from
	.short 9
	.byte \to
	.byte \from
	.endm

	; Copies a byte between two memory addresses
	; Because scripts are compiled in a code-agnostic fashion,
	; this command can never be assembled.
	.macro copybyte to, from
	.short 10
	.word \to
	.word \from
	.endm

	; Compares values between script reg and script reg
	.macro comparelocaltolocal a, b
	.short 11
	.byte \a
	.byte \b
	.endm

	; Compares script reg to byte literal
	.macro comparelocaltovalue reg, val
	.short 12
	.byte \reg
	.byte \val
	.endm

	; Compares script reg to memory address
	; Because scripts are compiled in a code-agnostic fashion,
	; this command can never be assembled.
	.macro comparelocaltoaddr reg, addr
	.short 13
	.byte \reg
	.word \addr
	.endm

	; Compares memory address to script reg
	; Because scripts are compiled in a code-agnostic fashion,
	; this command can never be assembled.
	.macro compareaddrtolocal addr, reg
	.short 14
	.word \addr
	.byte \reg
	.endm

	; Compares memory address to byte literal
	; Because scripts are compiled in a code-agnostic fashion,
	; this command can never be assembled.
	.macro compareaddrtovalue addr, val
	.short 15
	.word \addr
	.byte \val
	.endm

	; Compares bytes at two memory addresses
	; Because scripts are compiled in a code-agnostic fashion,
	; this command can never be assembled.
	.macro compareaddrtoaddr a, b
	.short 16
	.word \a
	.word \b
	.endm

	; Compares variable to 16-bit literal
	.macro comparevartovalue var, val
	.short 17
	.short \var
	.short \val
	.endm

	; Compares two variables
	.macro comparevartovar a, b
	.short 18
	.short \a
	.short \b
	.endm

	; Creates a new script context to run the indicated script asynchronously
	.macro runscript id
	.short 19
	.short \id
	.endm

	; Creates a new script context to run the indicated script and wait
	.macro runscriptwait id
	.short 20
	.short \id
	.endm

	; Yield to parent context
	.macro restartcurrentscript
	.short 21
	.endm

	; Absolute branch to offset in script
	.macro goto dest
	.short 22
	.word \dest-.-4
	.endm

	; Branch to offset in script if interacting with a specific object
	.macro objectgoto object, dest
	.short 23
	.byte \object
	.word \dest-.-4
	.endm

	; Branch to offset in script if interacting with a specific bg event
	.macro bggoto bg, dest
	.short 24
	.byte \bg
	.word \dest-.-4
	.endm

	; Branch to offset in script if facing a specific direction
	.macro directiongoto dir, dest
	.short 25
	.byte \dir
	.word \dest-.-4
	.endm

	; Call script as a subroutine
	.macro call sub
	.short 26
	.word \sub-.-4
	.endm

	; Return from subroutine
	.macro return
	.short 27
	.endm

	; Conditional branch to offset in script
	.macro gotoif condition, dest
	.short 28
	.byte \condition
	.word \dest-.-4
	.endm

	; Conditional call subroutine
	.macro callif condition, sub
	.short 29
	.byte \condition
	.word \sub-.-4
	.endm

	; Set event flag
	.macro setflag flag
	.short 30
	.short \flag
	.endm

	; Clear event flag
	.macro clearflag flag
	.short 31
	.short \flag
	.endm

	; Check event flag, store result on context
	.macro checkflag flag
	.short 32
	.short \flag
	.endm

	; Set event flag referenced in var
	.macro setflagvar var
	.short 33
	.short \var
	.endm

	; Clear event flag referenced in var
	.macro clearflagvar var
	.short 34
	.short \var
	.endm

	; Check event flag referenced in var, store result in other var
	.macro checkflagvar var_flag, var_dest
	.short 35
	.short \var_flag
	.short \var_dest
	.endm

	; Set trainer defeated flag
	.macro settrainerflag var_or_trno
	.short 36
	.short \var_or_trno
	.endm

	; Clear trainer defeated flag
	.macro cleartrainerflag var_or_trno
	.short 37
	.short \var_or_trno
	.endm

	; Check trainer defeated flag, store result on context
	.macro checktrainerflag var_or_trno
	.short 38
	.short \var_or_trno
	.endm

	; Increment var value by value
	.macro addvar var, var_or_addend
	.short 39
	.short \var
	.short \var_or_addend
	.endm

	; Decrement var value by value
	.macro subvar var, var_or_addend
	.short 40
	.short \var
	.short \var_or_addend
	.endm

	; Set var to short literal
	.macro setvar var, val
	.short 41
	.short \var
	.short \val
	.endm

	; Set var from other var
	.macro copyvar dst, src
	.short 42
	.short \dst
	.short \src
	.endm

	; Set var from other var or short literal
	.macro setorcopyvar dst, src
	.short 43
	.short \dst
	.short \src
	.endm

	; Print message in field window from current map message bank
	.macro message msg_id
	.short 44
	.byte \msg_id
	.endm

	.macro scrcmd_045 a
	.short 45
	.byte \a
	.endm

	.macro scrcmd_046 a
	.short 46
	.short \a
	.endm

	.macro scrcmd_047 a
	.short 47
	.short \a
	.endm

	.macro scrcmd_048 a
	.short 48
	.byte \a
	.endm

	.macro scrcmd_049
	.short 49
	.endm

	.macro scrcmd_050
	.short 50
	.endm

	.macro scrcmd_051
	.short 51
	.endm

	.macro scrcmd_052
	.short 52
	.endm

	.macro scrcmd_053
	.short 53
	.endm

	.macro scrcmd_054
	.short 54
	.endm

	.macro scrcmd_055 a, b, c, d
	.short 55
	.byte \a
	.byte \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_056 a, b
	.short 56
	.byte \a
	.short \b
	.endm

	.macro scrcmd_057 a
	.short 57
	.byte \a
	.endm

	.macro scrcmd_058
	.short 58
	.endm

	.macro scrcmd_059 a, b
	.short 59
	.byte \a
	.short \b
	.endm

	.macro scrcmd_060 a
	.short 60
	.short \a
	.endm

	.macro scrcmd_061
	.short 61
	.endm

	.macro scrcmd_062 a, b, c, d, e, f
	.short 62
	.byte \a
	.byte \b
	.byte \c
	.byte \d
	.byte \e
	.byte \f
	.endm

	.macro scrcmd_063 a
	.short 63
	.short \a
	.endm

	.macro scrcmd_064 a, b, c, d, e
	.short 64
	.byte \a
	.byte \b
	.byte \c
	.byte \d
	.short \e
	.endm

	.macro scrcmd_065 a, b, c, d, e
	.short 65
	.byte \a
	.byte \b
	.byte \c
	.byte \d
	.short \e
	.endm

	.macro scrcmd_066 a, b
	.short 66
	.byte \a
	.byte \b
	.endm

	.macro scrcmd_067
	.short 67
	.endm

	.macro scrcmd_068 a, b, c, d, e
	.short 68
	.byte \a
	.byte \b
	.byte \c
	.byte \d
	.short \e
	.endm

	.macro scrcmd_069 a, b, c, d, e
	.short 69
	.byte \a
	.byte \b
	.byte \c
	.byte \d
	.short \e
	.endm

	.macro scrcmd_070 a, b, c
	.short 70
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_071
	.short 71
	.endm

	.macro scrcmd_072 a
	.short 72
	.byte \a
	.endm

	.macro scrcmd_073 a
	.short 73
	.short \a
	.endm

	.macro scrcmd_074 a
	.short 74
	.short \a
	.endm

	.macro scrcmd_075 a
	.short 75
	.short \a
	.endm

	.macro scrcmd_076 a, b
	.short 76
	.short \a
	.short \b
	.endm

	.macro scrcmd_077
	.short 77
	.endm

	.macro scrcmd_078 a
	.short 78
	.short \a
	.endm

	.macro scrcmd_079
	.short 79
	.endm

	.macro scrcmd_080 a
	.short 80
	.short \a
	.endm

	.macro scrcmd_081 a
	.short 81
	.short \a
	.endm

	.macro scrcmd_082
	.short 82
	.endm

	.macro scrcmd_083 a
	.short 83
	.short \a
	.endm

	.macro scrcmd_084 a, b
	.short 84
	.short \a
	.short \b
	.endm

	.macro scrcmd_085 a
	.short 85
	.short \a
	.endm

	.macro scrcmd_086 a, b
	.short 86
	.byte \a
	.byte \b
	.endm

	.macro scrcmd_087 a
	.short 87
	.short \a
	.endm

	.macro scrcmd_088 a
	.short 88
	.byte \a
	.endm

	.macro scrcmd_089 a
	.short 89
	.short \a
	.endm

	.macro scrcmd_090 a
	.short 90
	.short \a
	.endm

	.macro scrcmd_091
	.short 91
	.endm

	.macro scrcmd_092
	.short 92
	.endm

	.macro scrcmd_093
	.short 93
	.endm

	.macro scrcmd_094 a, b
	.short 94
	.short \a
	.word \b
	.endm

	.macro scrcmd_095
	.short 95
	.endm

	.macro scrcmd_096
	.short 96
	.endm

	.macro scrcmd_097
	.short 97
	.endm

	.macro scrcmd_098 a
	.short 98
	.short \a
	.endm

	.macro scrcmd_099 a
	.short 99
	.short \a
	.endm

	.macro scrcmd_100 a
	.short 100
	.short \a
	.endm

	.macro scrcmd_101 a
	.short 101
	.short \a
	.endm

	.macro scrcmd_102 a, b
	.short 102
	.short \a
	.short \b
	.endm

	.macro scrcmd_103
	.short 103
	.endm

	.macro scrcmd_104
	.short 104
	.endm

	.macro scrcmd_105 a, b
	.short 105
	.short \a
	.short \b
	.endm

	.macro scrcmd_106 a, b, c
	.short 106
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_107 a, b, c
	.short 107
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_108 a, b
	.short 108
	.short \a
	.byte \b
	.endm

	.macro scrcmd_109 a, b
	.short 109
	.short \a
	.short \b
	.endm

	.macro scrcmd_110 a
	.short 110
	.word \a
	.endm

	.macro scrcmd_111 a
	.short 111
	.word \a
	.endm

	.macro scrcmd_112 a, b
	.short 112
	.short \a
	.word \b
	.endm

	.macro scrcmd_113 a, b
	.short 113
	.short \a
	.short \b
	.endm

	.macro scrcmd_114
	.short 114
	.endm

	.macro scrcmd_115
	.short 115
	.endm

	.macro scrcmd_116 a
	.short 116
	.byte \a
	.endm

	.macro scrcmd_117
	.short 117
	.endm

	.macro scrcmd_118 a
	.short 118
	.byte \a
	.endm

	.macro scrcmd_119 a
	.short 119
	.short \a
	.endm

	.macro scrcmd_120 a
	.short 120
	.short \a
	.endm

	.macro scrcmd_121 a
	.short 121
	.short \a
	.endm

	.macro scrcmd_122 a, b, c
	.short 122
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_123
	.short 123
	.endm

	.macro scrcmd_124 a, b, c
	.short 124
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_125 a, b, c
	.short 125
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_126 a, b, c
	.short 126
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_127 a, b, c
	.short 127
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_128 a, b, c
	.short 128
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_129 a, b
	.short 129
	.short \a
	.short \b
	.endm

	.macro scrcmd_130 a, b
	.short 130
	.short \a
	.short \b
	.endm

	.macro scrcmd_131 a
	.short 131
	.short \a
	.endm

	.macro scrcmd_132 a, b
	.short 132
	.byte \a
	.byte \b
	.endm

	.macro scrcmd_133 a, b
	.short 133
	.short \a
	.short \b
	.endm

	.macro scrcmd_134 a, b
	.short 134
	.short \a
	.short \b
	.endm

	.macro scrcmd_135 a, b, c
	.short 135
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_136 a, b
	.short 136
	.short \a
	.short \b
	.endm

	.macro scrcmd_137 a, b, c, d, e, f
	.short 137
	.short \a
	.short \b
	.short \c
	.short \d
	.short \e
	.short \f
	.endm

	.macro scrcmd_138 a, b
	.short 138
	.short \a
	.short \b
	.endm

	.macro scrcmd_139 a, b, c
	.short 139
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_140 a, b, c
	.short 140
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_141 a, b
	.short 141
	.short \a
	.short \b
	.endm

	.macro scrcmd_142 a, b
	.short 142
	.short \a
	.short \b
	.endm

	.macro scrcmd_143 a, b, c
	.short 143
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_144 a
	.short 144
	.short \a
	.endm

	.macro scrcmd_145 a
	.short 145
	.byte \a
	.endm

	.macro scrcmd_146 a
	.short 146
	.short \a
	.endm

	.macro scrcmd_147 a, b
	.short 147
	.short \a
	.short \b
	.endm

	.macro scrcmd_148 a, b
	.short 148
	.short \a
	.short \b
	.endm

	.macro scrcmd_149 a
	.short 149
	.byte \a
	.endm

	.macro scrcmd_150
	.short 150
	.endm

	.macro scrcmd_151
	.short 151
	.endm

	.macro scrcmd_152
	.short 152
	.endm

	.macro scrcmd_153 a, b, c
	.short 153
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_154 a, b, c
	.short 154
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_155 a, b
	.short 155
	.short \a
	.short \b
	.endm

	.macro scrcmd_156
	.short 156
	.endm

	.macro scrcmd_157
	.short 157
	.endm

	.macro scrcmd_158 a
	.short 158
	.byte \a
	.endm

	.macro scrcmd_159
	.short 159
	.endm

	.macro scrcmd_160
	.short 160
	.endm

	.macro scrcmd_161
	.short 161
	.endm

	.macro scrcmd_162
	.short 162
	.endm

	.macro scrcmd_163 a
	.short 163
	.short \a
	.endm

	.macro scrcmd_164 a, b, c, d
	.short 164
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_165 a, b
	.short 165
	.short \a
	.short \b
	.endm

	.macro scrcmd_166 a
	.short 166
	.short \a
	.endm

	.macro scrcmd_167
	.short 167
	.endm

	.macro scrcmd_168 a
	.short 168
	.short \a
	.endm

	.macro scrcmd_169 a, b
	.short 169
	.short \a
	.short \b
	.endm

	.macro scrcmd_170 a
	.short 170
	.short \a
	.endm

	.macro scrcmd_171 a, b
	.short 171
	.short \a
	.short \b
	.endm

	.macro scrcmd_172
	.short 172
	.endm

	.macro scrcmd_173 a, b
	.short 173
	.short \a
	.short \b
	.endm

	.macro scrcmd_174 a, b, c, d
	.short 174
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_175
	.short 175
	.endm

	.macro scrcmd_176 a, b, c, d, e
	.short 176
	.short \a
	.short \b
	.short \c
	.short \d
	.short \e
	.endm

	.macro scrcmd_177 a
	.short 177
	.short \a
	.endm

	.macro scrcmd_178 a, b, c, d
	.short 178
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_179 a
	.short 179
	.short \a
	.endm

	.macro scrcmd_180
	.short 180
	.endm

	.macro scrcmd_181
	.short 181
	.endm

	.macro scrcmd_182 a
	.short 182
	.short \a
	.endm

	.macro scrcmd_183 a
	.short 183
	.short \a
	.endm

	.macro scrcmd_184 a
	.short 184
	.short \a
	.endm

	.macro scrcmd_185 a
	.short 185
	.byte \a
	.endm

	.macro scrcmd_186 a
	.short 186
	.byte \a
	.endm

	.macro scrcmd_187 a
	.short 187
	.short \a
	.endm

	.macro scrcmd_188 a
	.short 188
	.short \a
	.endm

	.macro scrcmd_189
	.short 189
	.endm

	.macro scrcmd_190 a
	.short 190
	.byte \a
	.endm

	.macro scrcmd_191 a
	.short 191
	.byte \a
	.endm

	.macro scrcmd_192 a
	.short 192
	.byte \a
	.endm

	.macro scrcmd_193 a, b
	.short 193
	.byte \a
	.short \b
	.endm

	.macro scrcmd_194 a, b
	.short 194
	.byte \a
	.short \b
	.endm

	.macro scrcmd_195 a, b
	.short 195
	.byte \a
	.short \b
	.endm

	.macro scrcmd_196 a, b
	.short 196
	.byte \a
	.short \b
	.endm

	.macro scrcmd_197 a, b
	.short 197
	.byte \a
	.short \b
	.endm

	.macro scrcmd_198 a, b
	.short 198
	.byte \a
	.short \b
	.endm

	.macro scrcmd_199 a, b
	.short 199
	.byte \a
	.short \b
	.endm

	.macro scrcmd_200 a, b
	.short 200
	.byte \a
	.short \b
	.endm

	.macro scrcmd_201 a
	.short 201
	.byte \a
	.endm

	.macro scrcmd_202 a, b, c, d
	.short 202
	.byte \a
	.short \b
	.short \c
	.byte \d
	.endm

	.macro scrcmd_203 a
	.short 203
	.byte \a
	.endm

	.macro scrcmd_204 a
	.short 204
	.byte \a
	.endm

	.macro scrcmd_205 a
	.short 205
	.byte \a
	.endm

	.macro scrcmd_206 a
	.short 206
	.short \a
	.endm

	.macro scrcmd_207 a
	.short 207
	.byte \a
	.endm

	.macro scrcmd_208 a, b
	.short 208
	.byte \a
	.short \b
	.endm

	.macro scrcmd_209 a, b
	.short 209
	.byte \a
	.short \b
	.endm

	.macro scrcmd_210 a, b
	.short 210
	.byte \a
	.short \b
	.endm

	.macro scrcmd_211 a, b
	.short 211
	.byte \a
	.short \b
	.endm

	.macro scrcmd_212 a
	.short 212
	.short \a
	.endm

	.macro scrcmd_213 a, b, c, d
	.short 213
	.short \a
	.short \b
	.byte \c
	.byte \d
	.endm

	.macro scrcmd_214 a, b
	.short 214
	.short \a
	.short \b
	.endm

	.macro scrcmd_215 a, b, c
	.short 215
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_216 a, b, c
	.short 216
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_217 a
	.short 217
	.short \a
	.endm

	.macro scrcmd_218 a
	.short 218
	.short \a
	.endm

	.macro scrcmd_219
	.short 219
	.endm

	.macro scrcmd_220 a
	.short 220
	.short \a
	.endm

	.macro scrcmd_221 a, b
	.short 221
	.short \a
	.byte \b
	.endm

	.macro scrcmd_222 a
	.short 222
	.short \a
	.endm

	.macro scrcmd_223 a, b
	.short 223
	.byte \a
	.short \b
	.endm

	.macro scrcmd_224 a, b
	.short 224
	.byte \a
	.short \b
	.endm

	.macro scrcmd_225 a, b
	.short 225
	.byte \a
	.short \b
	.endm

	.macro scrcmd_226 a, b, c, d
	.short 226
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_227 a, b, c, d
	.short 227
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_228 a
	.short 228
	.short \a
	.endm

	.macro scrcmd_229 a, b
	.short 229
	.short \a
	.short \b
	.endm

	.macro scrcmd_230
	.short 230
	.endm

	.macro scrcmd_231 a, b, c
	.short 231
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_232 a, b, c
	.short 232
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_233 a
	.short 233
	.short \a
	.endm

	.macro scrcmd_234 a, b, c, d
	.short 234
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_235 a
	.short 235
	.short \a
	.endm

	.macro scrcmd_236 a, b, c, d, e
	.short 236
	.short \a
	.short \b
	.short \c
	.short \d
	.short \e
	.endm

	.macro scrcmd_237
	.short 237
	.endm

	.macro scrcmd_238 a, b, c, d
	.short 238
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_239 a, b
	.short 239
	.short \a
	.short \b
	.endm

	.macro scrcmd_240 a, b, c, d, e
	.short 240
	.short \a
	.short \b
	.short \c
	.short \d
	.short \e
	.endm

	.macro scrcmd_241 a
	.short 241
	.short \a
	.endm

	.macro scrcmd_242 a, b, c, d
	.short 242
	.byte \a
	.byte \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_243 a
	.short 243
	.short \a
	.endm

	.macro scrcmd_244 a
	.short 244
	.short \a
	.endm

	.macro scrcmd_245 a
	.short 245
	.short \a
	.endm

	.macro scrcmd_246 a
	.short 246
	.short \a
	.endm

	.macro scrcmd_247
	.short 247
	.endm

	.macro scrcmd_248 a
	.short 248
	.short \a
	.endm

	.macro scrcmd_249 a, b
	.short 249
	.short \a
	.short \b
	.endm

	.macro scrcmd_250 a, b
	.short 250
	.short \a
	.short \b
	.endm

	.macro scrcmd_251
	.short 251
	.endm

	.macro scrcmd_252
	.short 252
	.endm

	.macro scrcmd_253 a
	.short 253
	.short \a
	.endm

	.macro scrcmd_254 a
	.short 254
	.short \a
	.endm

	.macro scrcmd_255 a, b
	.short 255
	.short \a
	.short \b
	.endm

	.macro scrcmd_256 a
	.short 256
	.short \a
	.endm

	.macro scrcmd_257 a
	.short 257
	.short \a
	.endm

	.macro scrcmd_258 a, b
	.short 258
	.short \a
	.short \b
	.endm

	.macro scrcmd_259 a, b
	.short 259
	.byte \a
	.byte \b
	.endm

	.macro scrcmd_260 a
	.short 260
	.short \a
	.endm

	.macro scrcmd_261 a
	.short 261
	.short \a
	.endm

	.macro scrcmd_262
	.short 262
	.endm

	.macro scrcmd_263
	.short 263
	.endm

	.macro scrcmd_264 a
	.short 264
	.short \a
	.endm

	.macro scrcmd_265
	.short 265
	.endm

	.macro scrcmd_266
	.short 266
	.endm

	.macro scrcmd_267 a, b
	.short 267
	.short \a
	.short \b
	.endm

	.macro scrcmd_268 a
	.short 268
	.short \a
	.endm

	.macro scrcmd_269 a, b, c, d
	.short 269
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_270 a
	.short 270
	.short \a
	.endm

	.macro scrcmd_271 a, b
	.short 271
	.short \a
	.short \b
	.endm

	.macro scrcmd_272 a
	.short 272
	.short \a
	.endm

	.macro scrcmd_273 a
	.short 273
	.short \a
	.endm

	.macro scrcmd_274 a, b
	.short 274
	.short \a
	.short \b
	.endm

	.macro scrcmd_275 a
	.short 275
	.short \a
	.endm

	.macro scrcmd_276 a
	.short 276
	.short \a
	.endm

	.macro scrcmd_277 a
	.short 277
	.short \a
	.endm

	.macro scrcmd_278 a, b, c, d
	.short 278
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_279
	.short 279
	.endm

	.macro scrcmd_280
	.short 280
	.endm

	.macro scrcmd_281 a
	.short 281
	.short \a
	.endm

	.macro scrcmd_282
	.short 282
	.endm

	.macro scrcmd_283
	.short 283
	.endm

	.macro scrcmd_284
	.short 284
	.endm

	.macro scrcmd_285 a, b
	.short 285
	.short \a
	.short \b
	.endm

	.macro scrcmd_286 a
	.short 286
	.short \a
	.endm

	.macro scrcmd_287 a, b
	.short 287
	.short \a
	.short \b
	.endm

	.macro scrcmd_288 a, b
	.short 288
	.short \a
	.short \b
	.endm

	.macro scrcmd_289 a
	.short 289
	.short \a
	.endm

	.macro scrcmd_290 a, b
	.short 290
	.short \a
	.short \b
	.endm

	.macro scrcmd_291
	.short 291
	.endm

	.macro scrcmd_292
	.short 292
	.endm

	.macro scrcmd_293
	.short 293
	.endm

	.macro scrcmd_294 a, b
	.short 294
	.short \a
	.short \b
	.endm

	.macro scrcmd_295 a
	.short 295
	.short \a
	.endm

	.macro scrcmd_296 a
	.short 296
	.short \a
	.endm

	.macro scrcmd_297
	.short 297
	.endm

	.macro scrcmd_298 a, b, c, d
	.short 298
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_299 a
	.short 299
	.short \a
	.endm

	.macro scrcmd_300 a
	.short 300
	.short \a
	.endm

	.macro scrcmd_301 a
	.short 301
	.short \a
	.endm

	.macro scrcmd_302 a, b
	.short 302
	.short \a
	.short \b
	.endm

	.macro scrcmd_303 a, b
	.short 303
	.short \a
	.short \b
	.endm

	.macro scrcmd_304 a
	.short 304
	.short \a
	.endm

	.macro scrcmd_305
	.short 305
	.endm

	.macro scrcmd_306 a, b, c, d
	.short 306
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_307 a, b, c, d, e
	.short 307
	.short \a
	.short \b
	.short \c
	.short \d
	.byte \e
	.endm

	.macro scrcmd_308 a
	.short 308
	.byte \a
	.endm

	.macro scrcmd_309 a
	.short 309
	.byte \a
	.endm

	.macro scrcmd_310 a
	.short 310
	.byte \a
	.endm

	.macro scrcmd_311 a
	.short 311
	.byte \a
	.endm

	.macro scrcmd_312
	.short 312
	.endm

	.macro scrcmd_313 a
	.short 313
	.short \a
	.endm

	.macro scrcmd_314
	.short 314
	.endm

	.macro scrcmd_315
	.short 315
	.endm

	.macro scrcmd_316
	.short 316
	.endm

	.macro scrcmd_317 a
	.short 317
	.byte \a
	.endm

	.macro scrcmd_318
	.short 318
	.endm

	.macro scrcmd_319 a
	.short 319
	.short \a
	.endm

	.macro scrcmd_320 a
	.short 320
	.short \a
	.endm

	.macro scrcmd_321 a
	.short 321
	.short \a
	.endm

	.macro scrcmd_322 a, b
	.short 322
	.byte \a
	.short \b
	.endm

	.macro scrcmd_323 a, b
	.short 323
	.short \a
	.short \b
	.endm

	.macro scrcmd_324
	.short 324
	.endm

	.macro scrcmd_325
	.short 325
	.endm

	.macro scrcmd_326
	.short 326
	.endm

	.macro scrcmd_327 a
	.short 327
	.byte \a
	.endm

	.macro scrcmd_328 a
	.short 328
	.byte \a
	.endm

	.macro scrcmd_329
	.short 329
	.endm

	.macro scrcmd_330
	.short 330
	.endm

	.macro scrcmd_331
	.short 331
	.endm

	.macro scrcmd_332 a
	.short 332
	.short \a
	.endm

	.macro scrcmd_333 a
	.short 333
	.short \a
	.endm

	.macro scrcmd_334
	.short 334
	.endm

	.macro scrcmd_335
	.short 335
	.endm

	.macro scrcmd_336
	.short 336
	.endm

	.macro scrcmd_337
	.short 337
	.endm

	.macro scrcmd_338 a, b, c
	.short 338
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_339 a, b, c, d, e
	.short 339
	.short \a
	.short \b
	.short \c
	.short \d
	.short \e
	.endm

	.macro scrcmd_340 a, b
	.short 340
	.short \a
	.short \b
	.endm

	.macro scrcmd_341 a, b
	.short 341
	.short \a
	.short \b
	.endm

	.macro scrcmd_342 a, b, c
	.short 342
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_343
	.short 343
	.endm

	.macro scrcmd_344 a, b
	.short 344
	.short \a
	.short \b
	.endm

	.macro scrcmd_345
	.short 345
	.endm

	.macro scrcmd_346
	.short 346
	.endm

	.macro scrcmd_347 a, b
	.short 347
	.short \a
	.short \b
	.endm

	.macro scrcmd_348 a
	.short 348
	.short \a
	.endm

	.macro scrcmd_349
	.short 349
	.endm

	.macro scrcmd_350
	.short 350
	.endm

	.macro scrcmd_351 a
	.short 351
	.short \a
	.endm

	.macro scrcmd_352 a, b, c
	.short 352
	.byte \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_353 a, b
	.short 353
	.byte \a
	.short \b
	.endm

	.macro scrcmd_354 a, b
	.short 354
	.short \a
	.short \b
	.endm

	.macro scrcmd_355 a, b
	.short 355
	.short \a
	.short \b
	.endm

	.macro scrcmd_356 a
	.short 356
	.short \a
	.endm

	.macro scrcmd_357 a, b
	.short 357
	.short \a
	.short \b
	.endm

	.macro scrcmd_358 a
	.short 358
	.short \a
	.endm

	.macro scrcmd_359 a
	.short 359
	.short \a
	.endm

	.macro scrcmd_360 a
	.short 360
	.short \a
	.endm

	.macro scrcmd_361 a, b
	.short 361
	.short \a
	.short \b
	.endm

	.macro scrcmd_362 a, b
	.short 362
	.short \a
	.short \b
	.endm

	.macro scrcmd_363 a, b, c
	.short 363
	.byte \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_364 a
	.short 364
	.short \a
	.endm

	.macro scrcmd_365
	.short 365
	.endm

	.macro scrcmd_366
	.short 366
	.endm

	.macro scrcmd_367 a, b
	.short 367
	.short \a
	.short \b
	.endm

	.macro scrcmd_368 a, b
	.short 368
	.short \a
	.short \b
	.endm

	.macro scrcmd_369
	.short 369
	.endm

	.macro scrcmd_370
	.short 370
	.endm

	.macro scrcmd_371 a, b
	.short 371
	.short \a
	.short \b
	.endm

	.macro scrcmd_372 a, b
	.short 372
	.short \a
	.short \b
	.endm

	.macro scrcmd_373 a
	.short 373
	.short \a
	.endm

	.macro scrcmd_374 a
	.short 374
	.short \a
	.endm

	.macro scrcmd_375 a
	.short 375
	.short \a
	.endm

	.macro scrcmd_376
	.short 376
	.endm

	.macro scrcmd_377 a
	.short 377
	.short \a
	.endm

	.macro scrcmd_378 a, b
	.short 378
	.short \a
	.short \b
	.endm

	.macro scrcmd_379 a
	.short 379
	.short \a
	.endm

	.macro scrcmd_380 a, b
	.short 380
	.short \a
	.short \b
	.endm

	.macro scrcmd_381 a
	.short 381
	.short \a
	.endm

	.macro scrcmd_382 a, b
	.short 382
	.short \a
	.short \b
	.endm

	.macro scrcmd_383 a, b
	.short 383
	.short \a
	.short \b
	.endm

	.macro scrcmd_384 a
	.short 384
	.byte \a
	.endm

	.macro scrcmd_385 a, b
	.short 385
	.short \a
	.short \b
	.endm

	.macro scrcmd_386 a
	.short 386
	.short \a
	.endm

	.macro scrcmd_387 a
	.short 387
	.short \a
	.endm

	.macro scrcmd_388 a
	.short 388
	.short \a
	.endm

	.macro scrcmd_389 a
	.short 389
	.short \a
	.endm

	.macro scrcmd_390 a, b
	.short 390
	.short \a
	.short \b
	.endm

	.macro scrcmd_391 a
	.short 391
	.short \a
	.endm

	.macro scrcmd_392 a, b, c
	.short 392
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_393 a, b, c
	.short 393
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_394 a
	.short 394
	.short \a
	.endm

	.macro scrcmd_395 a
	.short 395
	.short \a
	.endm

	.macro scrcmd_396 a, b
	.short 396
	.short \a
	.short \b
	.endm

	.macro scrcmd_397 a, b
	.short 397
	.short \a
	.short \b
	.endm

	.macro scrcmd_398 a, b, c
	.short 398
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_399 a, b, c
	.short 399
	.byte \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_400
	.short 400
	.endm

	.macro scrcmd_401
	.short 401
	.endm

	.macro scrcmd_402
	.short 402
	.endm

	.macro scrcmd_403 a, b
	.short 403
	.short \a
	.short \b
	.endm

	.macro scrcmd_404 a, b, c
	.short 404
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_405 a, b
	.short 405
	.short \a
	.short \b
	.endm

	.macro scrcmd_406 a
	.short 406
	.short \a
	.endm

	.macro scrcmd_407 a, b
	.short 407
	.short \a
	.short \b
	.endm

	.macro scrcmd_408 a, b
	.short 408
	.short \a
	.short \b
	.endm

	.macro scrcmd_409
	.short 409
	.endm

	.macro scrcmd_410 a, b
	.short 410
	.short \a
	.short \b
	.endm

	.macro scrcmd_411
	.short 411
	.endm

	.macro scrcmd_412 a, b, c
	.short 412
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_413 a, b, c, d
	.short 413
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_414 a
	.short 414
	.short \a
	.endm

	.macro scrcmd_415 a
	.short 415
	.short \a
	.endm

	.macro scrcmd_416 a, b, c
	.short 416
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_417 a, b
	.short 417
	.short \a
	.short \b
	.endm

	.macro scrcmd_418 a, b
	.short 418
	.short \a
	.short \b
	.endm

	.macro scrcmd_419 a, b, c
	.short 419
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_420 a
	.short 420
	.short \a
	.endm

	.macro scrcmd_421
	.short 421
	.endm

	.macro scrcmd_422
	.short 422
	.endm

	.macro scrcmd_423 a
	.short 423
	.short \a
	.endm

	.macro scrcmd_424 a
	.short 424
	.short \a
	.endm

	.macro scrcmd_425 a
	.short 425
	.short \a
	.endm

	.macro scrcmd_426 a, b, c
	.short 426
	.byte \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_427 a, b
	.short 427
	.short \a
	.short \b
	.endm

	.macro scrcmd_428 a
	.short 428
	.short \a
	.endm

	.macro scrcmd_429 a
	.short 429
	.short \a
	.endm

	.macro scrcmd_430 a, b, c
	.short 430
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_431 a, b, c
	.short 431
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_432 a, b
	.short 432
	.short \a
	.short \b
	.endm

	.macro scrcmd_433 a, b, c
	.short 433
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_434 a, b
	.short 434
	.short \a
	.short \b
	.endm

	.macro scrcmd_435 a, b
	.short 435
	.short \a
	.short \b
	.endm

	.macro scrcmd_436
	.short 436
	.endm

	.macro scrcmd_437 a
	.short 437
	.short \a
	.endm

	.macro scrcmd_438 a, b
	.short 438
	.short \a
	.short \b
	.endm

	.macro scrcmd_439 a, b
	.short 439
	.short \a
	.short \b
	.endm

	.macro scrcmd_440 a, b
	.short 440
	.short \a
	.short \b
	.endm

	.macro scrcmd_441 a, b
	.short 441
	.short \a
	.short \b
	.endm

	.macro scrcmd_442 a, b
	.short 442
	.short \a
	.short \b
	.endm

	.macro scrcmd_443
	.short 443
	.endm

	.macro scrcmd_444 a, b
	.short 444
	.short \a
	.short \b
	.endm

	.macro scrcmd_445 a
	.short 445
	.short \a
	.endm

	.macro scrcmd_446 a
	.short 446
	.short \a
	.endm

	.macro scrcmd_447 a
	.short 447
	.short \a
	.endm

	.macro scrcmd_448 a, b, c, d, e
	.short 448
	.short \a
	.short \b
	.short \c
	.short \d
	.short \e
	.endm

	.macro scrcmd_449 a, b
	.short 449
	.short \a
	.short \b
	.endm

	.macro scrcmd_450 a
	.short 450
	.short \a
	.endm

	.macro scrcmd_451 a
	.short 451
	.short \a
	.endm

	.macro scrcmd_452 a, b
	.short 452
	.short \a
	.short \b
	.endm

	.macro scrcmd_453
	.short 453
	.endm

	.macro scrcmd_454
	.short 454
	.endm

	.macro scrcmd_455 a
	.short 455
	.short \a
	.endm

	.macro scrcmd_456 a, b
	.short 456
	.short \a
	.short \b
	.endm

	.macro scrcmd_457 a, b
	.short 457
	.short \a
	.short \b
	.endm

	.macro scrcmd_458 a, b, c
	.short 458
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_459
	.short 459
	.endm

	.macro scrcmd_460 a, b
	.short 460
	.short \a
	.short \b
	.endm

	.macro scrcmd_461 a, b, c
	.short 461
	.byte \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_462 a
	.short 462
	.short \a
	.endm

	.macro scrcmd_463
	.short 463
	.endm

	.macro scrcmd_464 a
	.short 464
	.byte \a
	.endm

	.macro scrcmd_465 a, b, c
	.short 465
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_466 a, b
	.short 466
	.short \a
	.short \b
	.endm

	.macro scrcmd_467 a
	.short 467
	.short \a
	.endm

	.macro scrcmd_468 a, b
	.short 468
	.short \a
	.short \b
	.endm

	.macro scrcmd_469 a
	.short 469
	.short \a
	.endm

	.macro scrcmd_470 a
	.short 470
	.byte \a
	.endm

	.macro scrcmd_471
	.short 471
	.endm

	.macro scrcmd_472 a
	.short 472
	.short \a
	.endm

	.macro scrcmd_473 a
	.short 473
	.short \a
	.endm

	.macro scrcmd_474
	.short 474
	.endm

	.macro scrcmd_475 a, b
	.short 475
	.short \a
	.short \b
	.endm

	.macro scrcmd_476
	.short 476
	.endm

	.macro scrcmd_477 a, b
	.short 477
	.byte \a
	.short \b
	.endm

	.macro scrcmd_478 a, b, c, d
	.short 478
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_479
	.short 479
	.endm

	.macro scrcmd_480 a, b, c
	.short 480
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_481 a, b
	.short 481
	.short \a
	.short \b
	.endm

	.macro scrcmd_482 a, b
	.short 482
	.short \a
	.short \b
	.endm

	.macro scrcmd_483 a, b
	.short 483
	.short \a
	.short \b
	.endm

	.macro scrcmd_484 a
	.short 484
	.short \a
	.endm

	.macro scrcmd_485 a
	.short 485
	.short \a
	.endm

	.macro scrcmd_486
	.short 486
	.endm

	.macro scrcmd_487 a
	.short 487
	.short \a
	.endm

	.macro scrcmd_488 a, b
	.short 488
	.short \a
	.short \b
	.endm

	.macro scrcmd_489
	.short 489
	.endm

	.macro scrcmd_490 a
	.short 490
	.short \a
	.endm

	.macro scrcmd_491 a
	.short 491
	.short \a
	.endm

	.macro scrcmd_492 a, b, c
	.short 492
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_493 a, b, c
	.short 493
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_494 a, b
	.short 494
	.short \a
	.short \b
	.endm

	.macro scrcmd_495 a
	.short 495
	.short \a
	.endm

	.macro scrcmd_496
	.short 496
	.endm

	.macro scrcmd_497 a, b, c
	.short 497
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_498 a, b, c, d, e
	.short 498
	.short \a
	.short \b
	.short \c
	.short \d
	.short \e
	.endm

	.macro scrcmd_499 a, b, c, d, e
	.short 499
	.short \a
	.short \b
	.short \c
	.short \d
	.short \e
	.endm

	.macro scrcmd_500 a
	.short 500
	.byte \a
	.endm

	.macro scrcmd_501 a
	.short 501
	.byte \a
	.endm

	.macro scrcmd_502 a, b
	.short 502
	.short \a
	.short \b
	.endm

	.macro scrcmd_503 a
	.short 503
	.short \a
	.endm

	.macro scrcmd_504 a, b, c, d
	.short 504
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_505
	.short 505
	.endm

	.macro scrcmd_506 a, b
	.short 506
	.byte \a
	.short \b
	.endm

	.macro scrcmd_507 a
	.short 507
	.short \a
	.endm

	.macro scrcmd_508 a
	.short 508
	.short \a
	.endm

	.macro scrcmd_509 a
	.short 509
	.short \a
	.endm

	.macro scrcmd_510
	.short 510
	.endm

	.macro scrcmd_511 a, b
	.short 511
	.short \a
	.short \b
	.endm

	.macro scrcmd_512 a
	.short 512
	.short \a
	.endm

	.macro scrcmd_513 a, b, c
	.short 513
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_514 a
	.short 514
	.short \a
	.endm

	.macro scrcmd_515 a
	.short 515
	.short \a
	.endm

	.macro scrcmd_516 a, b
	.short 516
	.byte \a
	.short \b
	.endm

	.macro scrcmd_517 a, b
	.short 517
	.short \a
	.short \b
	.endm

	.macro scrcmd_518 a
	.short 518
	.short \a
	.endm

	.macro scrcmd_519 a, b
	.short 519
	.byte \a
	.short \b
	.endm

	.macro scrcmd_520
	.short 520
	.endm

	.macro scrcmd_521
	.short 521
	.endm

	.macro scrcmd_522 a
	.short 522
	.short \a
	.endm

	.macro scrcmd_523 a, b, c, d, e
	.short 523
	.short \a
	.short \b
	.short \c
	.short \d
	.short \e
	.endm

	.macro scrcmd_524 a, b, c, d, e
	.short 524
	.short \a
	.short \b
	.short \c
	.short \d
	.short \e
	.endm

	.macro scrcmd_525 a
	.short 525
	.short \a
	.endm

	.macro scrcmd_526
	.short 526
	.endm

	.macro scrcmd_527 a
	.short 527
	.short \a
	.endm

	.macro scrcmd_528 a
	.short 528
	.short \a
	.endm

	.macro scrcmd_529 a
	.short 529
	.short \a
	.endm

	.macro scrcmd_530 a, b
	.short 530
	.short \a
	.byte \b
	.endm

	.macro scrcmd_531 a, b
	.short 531
	.byte \a
	.short \b
	.endm

	.macro scrcmd_532 a, b, c
	.short 532
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_533 a, b, c
	.short 533
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_534 a
	.short 534
	.short \a
	.endm

	.macro scrcmd_535 a, b
	.short 535
	.short \a
	.short \b
	.endm

	.macro scrcmd_536 a
	.short 536
	.short \a
	.endm

	.macro scrcmd_537
	.short 537
	.endm

	.macro scrcmd_538 a, b
	.short 538
	.short \a
	.short \b
	.endm

	.macro scrcmd_539
	.short 539
	.endm

	.macro scrcmd_540 a
	.short 540
	.short \a
	.endm

	.macro scrcmd_541 a, b, c, d
	.short 541
	.byte \a
	.short \b
	.byte \c
	.byte \d
	.endm

	.macro scrcmd_542
	.short 542
	.endm

	.macro scrcmd_543 a
	.short 543
	.short \a
	.endm

	.macro scrcmd_544 a, b
	.short 544
	.short \a
	.short \b
	.endm

	.macro scrcmd_545 a
	.short 545
	.short \a
	.endm

	.macro scrcmd_546 a, b
	.short 546
	.byte \a
	.short \b
	.endm

	.macro scrcmd_547 a
	.short 547
	.short \a
	.endm

	.macro scrcmd_548
	.short 548
	.endm

	.macro scrcmd_549 a
	.short 549
	.short \a
	.endm

	.macro scrcmd_550 a
	.short 550
	.byte \a
	.endm

	.macro scrcmd_551 a
	.short 551
	.short \a
	.endm

	.macro scrcmd_552 a, b
	.short 552
	.short \a
	.short \b
	.endm

	.macro scrcmd_553 a, b
	.short 553
	.byte \a
	.short \b
	.endm

	.macro scrcmd_554
	.short 554
	.endm

	.macro scrcmd_555 a
	.short 555
	.short \a
	.endm

	.macro scrcmd_556 a
	.short 556
	.short \a
	.endm

	.macro scrcmd_557 a, b
	.short 557
	.short \a
	.short \b
	.endm

	.macro scrcmd_558 a, b
	.short 558
	.short \a
	.short \b
	.endm

	.macro scrcmd_559 a
	.short 559
	.short \a
	.endm

	.macro scrcmd_560 a, b
	.short 560
	.short \a
	.short \b
	.endm

	.macro scrcmd_561 a, b, c, d
	.short 561
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_562 a, b, c, d
	.short 562
	.short \a
	.short \b
	.short \c
	.byte \d
	.endm

	.macro scrcmd_563 a, b
	.short 563
	.short \a
	.short \b
	.endm

	.macro scrcmd_564 a
	.short 564
	.short \a
	.endm

	.macro scrcmd_565 a
	.short 565
	.short \a
	.endm

	.macro scrcmd_566
	.short 566
	.endm

	.macro scrcmd_567 a, b, c, d
	.short 567
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_568 a, b
	.short 568
	.short \a
	.short \b
	.endm

	.macro scrcmd_569 a
	.short 569
	.short \a
	.endm

	.macro scrcmd_570 a, b, c
	.short 570
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_571 a
	.short 571
	.short \a
	.endm

	.macro scrcmd_572 a
	.short 572
	.short \a
	.endm

	.macro scrcmd_573
	.short 573
	.endm

	.macro scrcmd_574 a, b
	.short 574
	.short \a
	.short \b
	.endm

	.macro scrcmd_575
	.short 575
	.endm

	.macro scrcmd_576 a
	.short 576
	.short \a
	.endm

	.macro scrcmd_577
	.short 577
	.endm

	.macro scrcmd_578
	.short 578
	.endm

	.macro scrcmd_579
	.short 579
	.endm

	.macro scrcmd_580 a, b
	.short 580
	.byte \a
	.short \b
	.endm

	.macro scrcmd_581 a, b
	.short 581
	.short \a
	.short \b
	.endm

	.macro scrcmd_582 a, b, c
	.short 582
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_583 a
	.short 583
	.short \a
	.endm

	.macro scrcmd_584 a
	.short 584
	.short \a
	.endm

	.macro scrcmd_585
	.short 585
	.endm

	.macro scrcmd_586 a
	.short 586
	.short \a
	.endm

	.macro scrcmd_587
	.short 587
	.endm

	.macro scrcmd_588 a
	.short 588
	.short \a
	.endm

	.macro scrcmd_589 a, b, c
	.short 589
	.short \a
	.short \b
	.byte \c
	.endm

	.macro scrcmd_590 a
	.short 590
	.short \a
	.endm

	.macro scrcmd_591
	.short 591
	.endm

	.macro scrcmd_592 a
	.short 592
	.short \a
	.endm

	.macro scrcmd_593
	.short 593
	.endm

	.macro scrcmd_594
	.short 594
	.endm

	.macro scrcmd_595 a
	.short 595
	.byte \a
	.endm

	.macro scrcmd_596 a
	.short 596
	.short \a
	.endm

	.macro scrcmd_597
	.short 597
	.endm

	.macro scrcmd_598 a
	.short 598
	.short \a
	.endm

	.macro scrcmd_599
	.short 599
	.endm

	.macro scrcmd_600
	.short 600
	.endm

	.macro scrcmd_601
	.short 601
	.endm

	.macro scrcmd_602 a
	.short 602
	.short \a
	.endm

	.macro scrcmd_603
	.short 603
	.endm

	.macro scrcmd_604 a
	.short 604
	.short \a
	.endm

	.macro scrcmd_605 a, b
	.short 605
	.byte \a
	.byte \b
	.endm

	.macro scrcmd_606
	.short 606
	.endm

	.macro scrcmd_607
	.short 607
	.endm

	.macro scrcmd_608
	.short 608
	.endm

	.macro scrcmd_609
	.short 609
	.endm

	.macro scrcmd_610
	.short 610
	.endm

	.macro scrcmd_611 a, b, c, d, e, f
	.short 611
	.short \a
	.short \b
	.short \c
	.short \d
	.short \e
	.short \f
	.endm

	.macro scrcmd_612 a
	.short 612
	.short \a
	.endm

	.macro scrcmd_613 a
	.short 613
	.short \a
	.endm

	.macro scrcmd_614 a
	.short 614
	.short \a
	.endm

	.macro scrcmd_615 a, b
	.short 615
	.short \a
	.short \b
	.endm

	.macro scrcmd_616 a
	.short 616
	.short \a
	.endm

	.macro scrcmd_617 a, b
	.short 617
	.short \a
	.short \b
	.endm

	.macro scrcmd_618 a
	.short 618
	.short \a
	.endm

	.macro scrcmd_619 a
	.short 619
	.short \a
	.endm

	.macro scrcmd_620 a
	.short 620
	.byte \a
	.endm

	.macro scrcmd_621 a
	.short 621
	.short \a
	.endm

	.macro scrcmd_622 a, b
	.short 622
	.short \a
	.short \b
	.endm

	.macro scrcmd_623 a
	.short 623
	.short \a
	.endm

	.macro scrcmd_624 a
	.short 624
	.short \a
	.endm

	.macro scrcmd_625 a, b, c
	.short 625
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_626 a, b
	.short 626
	.byte \a
	.short \b
	.endm

	.macro scrcmd_627 a
	.short 627
	.byte \a
	.endm

	.macro scrcmd_628 a, b
	.short 628
	.short \a
	.short \b
	.endm

	.macro scrcmd_629 a
	.short 629
	.short \a
	.endm

	.macro scrcmd_630 a, b, c
	.short 630
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_631 a, b, c
	.short 631
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_632 a, b
	.short 632
	.short \a
	.short \b
	.endm

	.macro scrcmd_633 a, b, c
	.short 633
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_634 a, b
	.short 634
	.short \a
	.short \b
	.endm

	.macro scrcmd_635 a, b
	.short 635
	.short \a
	.short \b
	.endm

	.macro scrcmd_636 a
	.short 636
	.short \a
	.endm

	.macro scrcmd_637 a, b, c
	.short 637
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_638 a, b, c
	.short 638
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_639 a, b, c
	.short 639
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_640 a, b, c
	.short 640
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_641 a, b, c
	.short 641
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_642 a, b, c
	.short 642
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_643 a, b, c
	.short 643
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_644 a, b, c
	.short 644
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_645 a, b, c
	.short 645
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_646 a
	.short 646
	.short \a
	.endm

	.macro scrcmd_647 a
	.short 647
	.short \a
	.endm

	.macro scrcmd_648 a
	.short 648
	.short \a
	.endm

	.macro scrcmd_649
	.short 649
	.endm

	.macro scrcmd_650 a
	.short 650
	.short \a
	.endm

	.macro scrcmd_651 a, b, c
	.short 651
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_652 a, b, c
	.short 652
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_653 a, b, c, d
	.short 653
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_654 a, b, c
	.short 654
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_655 a, b
	.short 655
	.short \a
	.short \b
	.endm

	.macro scrcmd_656 a, b
	.short 656
	.short \a
	.short \b
	.endm

	.macro scrcmd_657 a, b, c, d
	.short 657
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_658 a, b
	.short 658
	.byte \a
	.short \b
	.endm

	.macro scrcmd_659 a
	.short 659
	.short \a
	.endm

	.macro scrcmd_660 a
	.short 660
	.short \a
	.endm

	.macro scrcmd_661
	.short 661
	.endm

	.macro scrcmd_662 a, b, c
	.short 662
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_663 a
	.short 663
	.short \a
	.endm

	.macro scrcmd_664
	.short 664
	.endm

	.macro scrcmd_665 a
	.short 665
	.short \a
	.endm

	.macro scrcmd_666 a, b
	.short 666
	.short \a
	.short \b
	.endm

	.macro scrcmd_667 a, b, c, d
	.short 667
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_668 a, b
	.short 668
	.byte \a
	.short \b
	.endm

	.macro scrcmd_669 a, b
	.short 669
	.short \a
	.short \b
	.endm

	.macro scrcmd_670 a, b
	.short 670
	.short \a
	.short \b
	.endm

	.macro scrcmd_671
	.short 671
	.endm

	.macro scrcmd_672 a, b, c
	.short 672
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_673 a, b, c, d, e
	.short 673
	.short \a
	.short \b
	.short \c
	.short \d
	.short \e
	.endm

	.macro scrcmd_674 a, b
	.short 674
	.short \a
	.short \b
	.endm

	.macro scrcmd_675 a, b, c, d
	.short 675
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_676 a, b
	.short 676
	.short \a
	.short \b
	.endm

	.macro scrcmd_677
	.short 677
	.endm

	.macro scrcmd_678 a, b, c
	.short 678
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_679 a, b
	.short 679
	.short \a
	.short \b
	.endm

	.macro scrcmd_680 a, b
	.short 680
	.short \a
	.short \b
	.endm

	.macro scrcmd_681 a
	.short 681
	.short \a
	.endm

	.macro scrcmd_682 a
	.short 682
	.short \a
	.endm

	.macro scrcmd_683 a
	.short 683
	.short \a
	.endm

	.macro scrcmd_684
	.short 684
	.endm

	.macro scrcmd_685 a, b
	.short 685
	.short \a
	.short \b
	.endm

	.macro scrcmd_686
	.short 686
	.endm

	.macro scrcmd_687 a
	.short 687
	.short \a
	.endm

	.macro scrcmd_688 a
	.short 688
	.short \a
	.endm

	.macro scrcmd_689 a
	.short 689
	.short \a
	.endm

	.macro scrcmd_690 a, b
	.short 690
	.short \a
	.short \b
	.endm

	.macro scrcmd_691 a
	.short 691
	.short \a
	.endm

	.macro scrcmd_692
	.short 692
	.endm

	.macro scrcmd_693 a
	.short 693
	.short \a
	.endm

	.macro scrcmd_694 a
	.short 694
	.short \a
	.endm

	.macro scrcmd_695 a
	.short 695
	.short \a
	.endm

	.macro scrcmd_696 a
	.short 696
	.short \a
	.endm

	.macro scrcmd_697
	.short 697
	.endm

	.macro scrcmd_698 a, b, c
	.short 698
	.byte \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_699
	.short 699
	.endm

	.macro scrcmd_700 a
	.short 700
	.short \a
	.endm

	.macro scrcmd_701 a, b, c, d
	.short 701
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_702
	.short 702
	.endm

	.macro scrcmd_703
	.short 703
	.endm

	.macro scrcmd_704 a
	.short 704
	.short \a
	.endm

	.macro scrcmd_705
	.short 705
	.endm

	.macro scrcmd_706 a
	.short 706
	.short \a
	.endm

	.macro scrcmd_707 a, b
	.short 707
	.short \a
	.short \b
	.endm

	.macro scrcmd_708 a
	.short 708
	.short \a
	.endm

	.macro scrcmd_709
	.short 709
	.endm

	.macro scrcmd_710
	.short 710
	.endm

	.macro scrcmd_711
	.short 711
	.endm

	.macro scrcmd_712 a
	.short 712
	.byte \a
	.endm

	.macro scrcmd_713 a
	.short 713
	.byte \a
	.endm

	.macro scrcmd_714 a
	.short 714
	.byte \a
	.endm

	.macro scrcmd_715
	.short 715
	.endm

	.macro scrcmd_716
	.short 716
	.endm

	.macro scrcmd_717 a
	.short 717
	.short \a
	.endm

	.macro scrcmd_718 a, b
	.short 718
	.byte \a
	.short \b
	.endm

	.macro scrcmd_719 a, b
	.short 719
	.short \a
	.short \b
	.endm

	.macro scrcmd_720 a
	.short 720
	.short \a
	.endm

	.macro scrcmd_721 a
	.short 721
	.short \a
	.endm

	.macro scrcmd_722 a, b, c, d, e
	.short 722
	.byte \a
	.byte \b
	.short \c
	.short \d
	.short \e
	.endm

	.macro scrcmd_723 a, b, c
	.short 723
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_724 a, b
	.short 724
	.short \a
	.short \b
	.endm

	.macro scrcmd_725 a, b
	.short 725
	.byte \a
	.short \b
	.endm

	.macro scrcmd_726
	.short 726
	.endm

	.macro scrcmd_727 a
	.short 727
	.short \a
	.endm

	.macro scrcmd_728 a, b
	.short 728
	.byte \a
	.byte \b
	.endm

	.macro scrcmd_729 a
	.short 729
	.short \a
	.endm

	.macro scrcmd_730 a
	.short 730
	.short \a
	.endm

	.macro scrcmd_731
	.short 731
	.endm

	.macro scrcmd_732 a
	.short 732
	.byte \a
	.endm

	.macro scrcmd_733 a, b
	.short 733
	.byte \a
	.short \b
	.endm

	.macro scrcmd_734 a
	.short 734
	.byte \a
	.endm

	.macro scrcmd_735 a
	.short 735
	.short \a
	.endm

	.macro scrcmd_736
	.short 736
	.endm

	.macro scrcmd_737 a
	.short 737
	.short \a
	.endm

	.macro scrcmd_738 a
	.short 738
	.short \a
	.endm

	.macro scrcmd_739
	.short 739
	.endm

	.macro scrcmd_740 a, b, c
	.short 740
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_741 a, b, c, d
	.short 741
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_742 a, b, c
	.short 742
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_743 a
	.short 743
	.short \a
	.endm

	.macro scrcmd_744
	.short 744
	.endm

	.macro scrcmd_745 a, b
	.short 745
	.byte \a
	.short \b
	.endm

	.macro scrcmd_746
	.short 746
	.endm

	.macro scrcmd_747
	.short 747
	.endm

	.macro scrcmd_748 a
	.short 748
	.short \a
	.endm

	.macro scrcmd_749 a, b, c, d, e
	.short 749
	.byte \a
	.byte \b
	.byte \c
	.byte \d
	.short \e
	.endm

	.macro scrcmd_750 a, b, c, d, e
	.short 750
	.byte \a
	.byte \b
	.byte \c
	.byte \d
	.short \e
	.endm

	.macro scrcmd_751 a, b, c
	.short 751
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_752
	.short 752
	.endm

	.macro scrcmd_753 a, b, c
	.short 753
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_754 a
	.short 754
	.short \a
	.endm

	.macro scrcmd_755
	.short 755
	.endm

	.macro scrcmd_756
	.short 756
	.endm

	.macro scrcmd_757 a, b
	.short 757
	.short \a
	.short \b
	.endm

	.macro scrcmd_758 a, b, c
	.short 758
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_759
	.short 759
	.endm

	.macro scrcmd_760
	.short 760
	.endm

	.macro scrcmd_761 a
	.short 761
	.short \a
	.endm

	.macro scrcmd_762 a
	.short 762
	.short \a
	.endm

	.macro scrcmd_763
	.short 763
	.endm

	.macro scrcmd_764
	.short 764
	.endm

	.macro scrcmd_765
	.short 765
	.endm

	.macro scrcmd_766 a, b
	.short 766
	.short \a
	.short \b
	.endm

	.macro scrcmd_767 a, b
	.short 767
	.short \a
	.short \b
	.endm

	.macro scrcmd_768
	.short 768
	.endm

	.macro scrcmd_769
	.short 769
	.endm

	.macro scrcmd_770 a
	.short 770
	.short \a
	.endm

	.macro scrcmd_771
	.short 771
	.endm

	.macro scrcmd_772 a, b, c, d
	.short 772
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_773 a
	.short 773
	.short \a
	.endm

	.macro scrcmd_774 a, b
	.short 774
	.short \a
	.short \b
	.endm

	.macro scrcmd_775 a, b
	.short 775
	.short \a
	.short \b
	.endm

	.macro scrcmd_776
	.short 776
	.endm

	.macro scrcmd_777 a, b
	.short 777
	.short \a
	.short \b
	.endm

	.macro scrcmd_778
	.short 778
	.endm

	.macro scrcmd_779 a, b
	.short 779
	.short \a
	.short \b
	.endm

	.macro scrcmd_780 a
	.short 780
	.short \a
	.endm

	.macro scrcmd_781 a
	.short 781
	.short \a
	.endm

	.macro scrcmd_782
	.short 782
	.endm

	.macro scrcmd_783 a
	.short 783
	.byte \a
	.endm

	.macro scrcmd_784 a
	.short 784
	.short \a
	.endm

	.macro scrcmd_785 a, b
	.short 785
	.short \a
	.byte \b
	.endm

	.macro scrcmd_786 a
	.short 786
	.byte \a
	.endm

	.macro scrcmd_787 a, b, c
	.short 787
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_788 a, b
	.short 788
	.byte \a
	.short \b
	.endm

	.macro scrcmd_789 a
	.short 789
	.byte \a
	.endm

	.macro scrcmd_790 a, b
	.short 790
	.short \a
	.short \b
	.endm

	.macro scrcmd_791 a, b, c
	.short 791
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_792 a, b
	.short 792
	.short \a
	.short \b
	.endm

	.macro scrcmd_793 a, b
	.short 793
	.short \a
	.short \b
	.endm

	.macro scrcmd_794 a, b, c
	.short 794
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_795 a, b
	.short 795
	.short \a
	.short \b
	.endm

	.macro scrcmd_796
	.short 796
	.endm

	.macro scrcmd_797 a
	.short 797
	.short \a
	.endm

	.macro scrcmd_798 a
	.short 798
	.short \a
	.endm

	.macro scrcmd_799 a
	.short 799
	.short \a
	.endm

	.macro scrcmd_800 a
	.short 800
	.short \a
	.endm

	.macro scrcmd_801 a
	.short 801
	.short \a
	.endm

	.macro scrcmd_802
	.short 802
	.endm

	.macro scrcmd_803 a, b
	.short 803
	.short \a
	.short \b
	.endm

	.macro scrcmd_804 a
	.short 804
	.byte \a
	.endm

	.macro scrcmd_805
	.short 805
	.endm

	.macro scrcmd_806
	.short 806
	.endm

	.macro scrcmd_807 a, b
	.short 807
	.short \a
	.short \b
	.endm

	.macro scrcmd_808 a
	.short 808
	.short \a
	.endm

	.macro scrcmd_809 a
	.short 809
	.short \a
	.endm

	.macro scrcmd_810
	.short 810
	.endm

	.macro scrcmd_811 a, b
	.short 811
	.short \a
	.short \b
	.endm

	.macro scrcmd_812 a, b, c, d
	.short 812
	.short \a
	.short \b
	.short \c
	.short \d
	.endm

	.macro scrcmd_813 a
	.short 813
	.short \a
	.endm

	.macro scrcmd_814
	.short 814
	.endm

	.macro scrcmd_815 a
	.short 815
	.short \a
	.endm

	.macro scrcmd_816
	.short 816
	.endm

	.macro scrcmd_817 a
	.short 817
	.byte \a
	.endm

	.macro scrcmd_818
	.short 818
	.endm

	.macro scrcmd_819 a
	.short 819
	.short \a
	.endm

	.macro scrcmd_820 a
	.short 820
	.byte \a
	.endm

	.macro scrcmd_821 a, b
	.short 821
	.short \a
	.short \b
	.endm

	.macro scrcmd_822 a
	.short 822
	.short \a
	.endm

	.macro scrcmd_823 a
	.short 823
	.short \a
	.endm

	.macro scrcmd_824 a
	.short 824
	.short \a
	.endm

	.macro scrcmd_825 a, b
	.short 825
	.short \a
	.short \b
	.endm

	.macro scrcmd_826 a
	.short 826
	.short \a
	.endm

	.macro scrcmd_827 a, b
	.short 827
	.short \a
	.short \b
	.endm

	.macro scrcmd_828 a, b, c
	.short 828
	.short \a
	.short \b
	.byte \c
	.endm

	.macro scrcmd_829 a
	.short 829
	.short \a
	.endm

	.macro scrcmd_830 a
	.short 830
	.short \a
	.endm

	.macro scrcmd_831 a
	.short 831
	.short \a
	.endm

	.macro scrcmd_832 a
	.short 832
	.short \a
	.endm

	.macro scrcmd_833 a
	.short 833
	.short \a
	.endm

	.macro scrcmd_834 a
	.short 834
	.short \a
	.endm

	.macro scrcmd_835 a
	.short 835
	.short \a
	.endm

	.macro scrcmd_836 a
	.short 836
	.short \a
	.endm

	.macro scrcmd_837 a
	.short 837
	.short \a
	.endm

	.macro scrcmd_838 a, b
	.short 838
	.short \a
	.short \b
	.endm

	.macro scrcmd_839 a
	.short 839
	.short \a
	.endm

	.macro scrcmd_840 a, b
	.short 840
	.short \a
	.short \b
	.endm

	.macro scrcmd_841 a
	.short 841
	.byte \a
	.endm

	.macro scrcmd_842 a
	.short 842
	.byte \a
	.endm

	.macro scrcmd_843 a, b
	.short 843
	.byte \a
	.short \b
	.endm

	.macro scrcmd_844 a, b
	.short 844
	.byte \a
	.short \b
	.endm

	.macro scrcmd_845 a, b
	.short 845
	.byte \a
	.short \b
	.endm

	.macro scrcmd_846 a, b, c
	.short 846
	.short \a
	.short \b
	.short \c
	.endm

	.macro scrcmd_847 a
	.short 847
	.byte \a
	.endm

	.macro scrcmd_848 a, b
	.short 848
	.byte \a
	.short \b
	.endm

	.macro scrcmd_849 a, b
	.short 849
	.byte \a
	.short \b
	.endm

	.macro scrcmd_850 a, b
	.short 850
	.byte \a
	.short \b
	.endm

	.macro scrcmd_851 a
	.short 851
	.byte \a
	.endm

	.macro scrcmd_852 a, b
	.short 852
	.byte \a
	.byte \b
	.endm

	.endif ; ASM_SCRIPT_INC
