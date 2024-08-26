#pragma once

CMonster* GetPlayerCharacter(CMonster*& aMonsters);

bool FightingRound(CMonster*& pPlayer, CMonster*& aMonsters, int iRound);
bool Fight(CMonster& player, CMonster& enemy);

bool StandbyPhase(CMonster& monster);

bool AttackPhase(CMonster& attacker, CMonster& defender, float fSpeedMultiplier);

void CheckTraitEffects(CMonster& player, CMonster& enemy, float fSpeedMultiplier, float fDamage);

void Reward(CMonster*& pPlayer, int iRound);