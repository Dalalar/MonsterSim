#pragma once

#define DELETE(x)                  \
if (x != nullptr) delete x;         \
x = nullptr;                         \


const int I_ONE = 1;
const int I_REROLL_COST = 1;
const int I_STANDARD_BLEED_AMOUNT = 1;

const int I_FIRST_MONSTER = 0;
const int I_SECOND_MONSTER = 1;
const int I_THIRD_MONSTER = 2;
const int I_MONSTER_COUNT = 3;
const int I_TWO = 2;
const int I_GOLD_MULTIPLY = 2;
const int I_START_GOLD = 3;

const int I_ROUND_TWO = 2;
const int I_ROUND_THREE = 3;
const int I_STAT_COUNT = 4;
const int I_TOTAL_ROUNDS = 4;
const int I_BOSS_ROUND = 4;
const int I_TRAITS_TOTAL = 5;
const int I_NAMES_TOTAL = 6;
const int I_RACES_TOTAL = 3;

const int I_MOD = 10;
const float F_ONE = 1.0f;
const float F_TENTH = 0.1f;
const float F_HUNDRETH = 0.01f;

const float F_ROUND_TWO_BONUS = 1.3f;
const float F_ROUND_THREE_BONUS = 1.7f;
const float F_BOSS_ROUND_BONUS = 2.0f;


