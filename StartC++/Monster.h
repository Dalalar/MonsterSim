#pragma once
#include "Random.h"
#include <iomanip>
#include "Inventory.h"

enum eMonsterStatus : int8_t {
	None = 0,
	isBleeding
};
enum eMonsterTrait : int8_t {
	 Boss = -1,
	 NoTrait = 0,
	 Vampire,
	 StoneSkin,
	 Allrounder,
	 Bleed
};

enum eMonsterStat : int8_t {
	
	Health,
	Attack,
	Defence,
	Speed
};
enum eMonsterRace : int8_t {

	Bat,
	Gargoyl,
	Orc,

	YoungVampire,
	SonicBat,

	SpikedGargoyl,
	StoneDragon,

	Berserker,
	ShieldedOrc
};

class CMonster
{
public:

    float GetHealth() const;
	float GetBaseHealth() const;
	float GetAttack() const;
	float GetDefence() const;
	float GetSpeed() const;
	float GetLifeStealValue() const;
	const char* GetName() const;
	const char* GetTraitAsText() const;
	const char* GetRaceAsText() const;
    eMonsterTrait GetTrait() const;

    static const char* GetStatAsText(eMonsterStat a_eStat);

	void AddBleed(int a_iCount);

	void CheckForStatusDMG();

	void SetBoni(eMonsterStat a_eStat, float a_fBoni);
	void SetHealth(float a_fHealth);
	void AdjustDifficulty(int a_iRound);

	CMonster();

	CMonster(eMonsterRace a_eRace, bool a_bForPlayer);

	int GetGoldAmount();
	void AddGold(int a_iCount);
	void PayGold(int a_iCount);

 private:
	 
	 void AdjustWithBoni(const float a_fBoni);
	 void AdjustWithBoni();
	 void AdjustStatsForMonsters();
	 void GetRandomTrait();
	 void CheckForTraits();
     void AdjustMonsterInfo(bool a_bForPlayer);

	 float m_fHealth = NULL;
	 float m_fBaseHealth = NULL;
	 float m_fSpeed = NULL;
	 float m_fAttackPower = NULL;
	 float m_fDefencePower = NULL;

     const char* m_sName = "       ";

	 bool m_bWithTrait = false;
	 eMonsterTrait m_eTrait = NoTrait;
	 eMonsterRace m_eRace = Bat;

	 int m_iBleedStacks = NULL;
	 float m_fLifeSteal = NULL;

	 CInventory m_inventory = CInventory();
};



CMonster* PrebuildMonsters(int s_iCount, bool a_bForPlayer);