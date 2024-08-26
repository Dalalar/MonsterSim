#pragma once
#include "Monster.h"
#include <iostream>
#include "Intro.h"
#include "Fight.h"
#include "Input.h"

CMonster* GetPlayerCharacter(CMonster*& a_pMonsters) {

	CMonster* pPlayerChar = nullptr;
	std::cout << "Choose from the following Combatants:" << std::endl;

	std::cout << "1. " << a_pMonsters[I_FIRST_MONSTER].GetName();  GiveMonsterStats(a_pMonsters[I_FIRST_MONSTER]);
	std::cout << "2. " << a_pMonsters[I_SECOND_MONSTER].GetName(); GiveMonsterStats(a_pMonsters[I_SECOND_MONSTER]);
	std::cout << "3. " << a_pMonsters[I_THIRD_MONSTER].GetName();  GiveMonsterStats(a_pMonsters[I_THIRD_MONSTER]);

	int iInput = Input::GetNumberMinMax(I_ONE, I_MONSTER_COUNT);
	
	if (pPlayerChar == nullptr) { pPlayerChar = &a_pMonsters[iInput - I_ONE]; }
	if (pPlayerChar != nullptr) std::cout << "You have chosen " << pPlayerChar->GetName() << " as your warrior." << std::endl;

	return pPlayerChar;
}

bool FightingRound(CMonster*& a_pPlayer, CMonster*& a_pMonsters, int a_iRound) {

	CMonster pMonster = a_pMonsters[a_iRound - I_ONE];

	pMonster.AdjustDifficulty(a_iRound);
	std::cout << "Your enemy is: " << pMonster.GetName() << std::endl;
	GiveMonsterStats(pMonster);
	std::cout << "Fight? " << std::endl;

	system("pause");

	bool bWin = Fight(*a_pPlayer, pMonster);

	return bWin;
}



bool Fight(CMonster& aPlayer, CMonster& aEnemy) {

	bool bWin = false;
    float fSpeedMultiplier = NULL;
	
	if (aPlayer.GetSpeed() >= aEnemy.GetSpeed()) {

		fSpeedMultiplier = aPlayer.GetSpeed() / aEnemy.GetSpeed();

		while (true) {

			bool bMonsterKO = StandbyPhase(aPlayer);
			if (bMonsterKO) { bWin = false; break; }

			bool bEnemyKO = AttackPhase(aPlayer, aEnemy, fSpeedMultiplier);
			if (bEnemyKO) { bWin = true; break; }

			bMonsterKO = StandbyPhase(aEnemy);
			if (bMonsterKO) { bWin = true; break; }

			bEnemyKO = AttackPhase(aEnemy, aPlayer, F_ONE);
			if (bEnemyKO) { bWin = false; break; }
		}
	}
	else {

		fSpeedMultiplier = aEnemy.GetSpeed()/  aPlayer.GetSpeed();
		
		while (true) {

			bool bMonsterKO = StandbyPhase(aEnemy);
			if (bMonsterKO) { bWin = true; break; }

			bool bEnemyKO = AttackPhase(aEnemy, aPlayer, fSpeedMultiplier);
			if (bEnemyKO) { bWin = false; break; }

			     bMonsterKO = StandbyPhase(aPlayer);
			if (bMonsterKO) { bWin = false; break; }

			     bEnemyKO = AttackPhase(aPlayer, aEnemy, F_ONE);
			if (bEnemyKO) { bWin = true; break; }
		}
	}


	return bWin;

}

bool StandbyPhase(CMonster& aMonster) {

	bool bMonsterKO = false;
	aMonster.CheckForStatusDMG();

	if (aMonster.GetHealth() <= NULL) {

		aMonster.SetHealth(NULL);
		bMonsterKO = true;
		std::cout << aMonster.GetName() << " is at " << aMonster.GetHealth() << " HP." << std::endl;
	}
	return bMonsterKO;
}

bool AttackPhase(CMonster& aAttacker, CMonster& aDefender, float fSpeedMultiplier) {

	bool bEnemyKO = false;
	float fDamage = NULL;

	fDamage = (aAttacker.GetAttack() / aDefender.GetDefence()) * fSpeedMultiplier;
	aDefender.SetHealth(aDefender.GetHealth() - fDamage);
	if (aDefender.GetHealth() <= NULL) {

		aDefender.SetHealth(NULL);
		bEnemyKO = true;
	}
	std::cout << aAttacker.GetName() << " dealt " << fDamage << " damage. " << aDefender.GetName() << " is at " << aDefender.GetHealth() << " HP." << std::endl;
    CheckTraitEffects(aAttacker, aDefender, fSpeedMultiplier, fDamage);
	std::cout << std::endl;

	return bEnemyKO;
}
void CheckTraitEffects(CMonster& aMonsterToCheck, CMonster& aOpponent, float fSpeedMultiplier, float fDamage) {

	if (aMonsterToCheck.GetTrait() == Bleed) {

		aOpponent.AddBleed(static_cast<int>(fSpeedMultiplier));
	}
	if (aMonsterToCheck.GetTrait() == Vampire) {
		
		float fValue = fDamage * aMonsterToCheck.GetLifeStealValue();
		aMonsterToCheck.SetHealth(aMonsterToCheck.GetHealth() + fValue);
		std::cout << aMonsterToCheck.GetName() << " healed for " << fValue << ". ";
	}
}

void Reward(CMonster*& pPlayer, int iRound) {

	int iGoldAmount = iRound * I_GOLD_MULTIPLY;
	pPlayer->AddGold(iGoldAmount);
	float fBoni = Random::RandomForMonsterBoni();
	int iStat = Random::RandomforInteger(I_STAT_COUNT);
	std::cout << "You won! You gained " << iGoldAmount << " gold." << std::endl;
	std::cout << "Please select your reward:" << std::endl;

	bool bTakesReroll = true;
	while (bTakesReroll) {

		if (pPlayer != nullptr) std::cout << fBoni << "x Multiplyer for: " << CMonster::GetStatAsText(static_cast<eMonsterStat>(iStat)) << " ?" << " You can reroll for 1 gold. Your currently have " << pPlayer->GetGoldAmount() << " gold." << std::endl;
		std::cout << " Enter yes if you want to reroll. No if not." << std::endl;
		bTakesReroll = Input::GetYesOrNo();
		if (bTakesReroll) {
			if (pPlayer != nullptr) if (pPlayer->GetGoldAmount() <= NULL) { std::cout << " You don´t have any gold to spend." << std::endl; continue; }
			if (pPlayer != nullptr) pPlayer->PayGold(I_REROLL_COST);
			fBoni = Random::RandomForMonsterBoni();
			iStat = Random::RandomforInteger(I_STAT_COUNT);
		}
		else {

			if(pPlayer != nullptr) pPlayer->SetBoni(static_cast<eMonsterStat>(iStat), fBoni);
		}
	}

	GiveMonsterStats(*pPlayer);
	std::cin;
}

