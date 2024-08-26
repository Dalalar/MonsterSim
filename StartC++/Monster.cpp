#include "Monster.h"
#include "Names.h"
#include "Makros.h"


  void CMonster::AddBleed(int a_iCount) {
	 m_iBleedStacks += a_iCount;
}

  void CMonster::CheckForStatusDMG() {

	if (m_iBleedStacks > NULL) {
		float fDamage = m_iBleedStacks * F_HUNDRETH * m_fHealth; 
		m_fHealth -= fDamage;
		m_iBleedStacks = NULL;
		std::cout <<  m_sName << " took " << fDamage << " damage from Bleed." << std::endl;
	}
}

  void CMonster::SetBoni(eMonsterStat a_eStat, float a_fBoni) {

	switch (a_eStat) {

	case Health:
		m_fHealth *= a_fBoni;
		break;

	case Attack:
		m_fAttackPower *= a_fBoni;
		break;

	case Defence:
		m_fDefencePower *= a_fBoni;
		break;

	case Speed:
		m_fSpeed *= a_fBoni;
		break;
	}
}

  void CMonster::SetHealth(float a_fHealth) {
	m_fHealth = a_fHealth;
}

  float CMonster::GetHealth() const {
	return  m_fHealth;
}

  float CMonster::GetBaseHealth() const {
	return  m_fBaseHealth;
}

  float CMonster::GetAttack() const {
	return  m_fAttackPower;
}

  float CMonster::GetDefence() const {
	return  m_fDefencePower;
}

  float CMonster::GetSpeed() const {
	return  m_fSpeed;
}

  float CMonster::GetLifeStealValue() const {
	return  m_fLifeSteal;
}

  const char* CMonster::GetName() const {
	return  m_sName;
}

  const char* CMonster::GetTraitAsText() const {

	switch (m_eTrait) {

	case Boss:
		return " Boss";

	case NoTrait:
		return " None";

	case Vampire:
		return " Vampire";

	case StoneSkin:
		return " Stone Skin";

	case Allrounder:
		return " Allrounder";

	case Bleed:
		return" Bleed";
	}
}

  const char* CMonster::GetRaceAsText() const {

	switch (m_eRace) {

	case Bat:
		return " Fledermaus";

	case Gargoyl:
		return " Gargoyl";

	case Orc:
		return " Orc";
	}
}

 const char* CMonster::GetStatAsText(eMonsterStat a_eStat) {

	switch (a_eStat) {

	case Health:
		return "Health";

	case Attack:
		return "Attack";

	case Defence:
		return "Defence";

	case Speed:
		return "Speed";
	}
}

  eMonsterTrait CMonster::GetTrait() const {
	return  m_eTrait;
}

  void CMonster::AdjustDifficulty(int a_iRound) {

	switch (a_iRound) {

	case I_ROUND_TWO:
		AdjustWithBoni(F_ROUND_TWO_BONUS);
		break;

	case I_ROUND_THREE:
		AdjustWithBoni(F_ROUND_THREE_BONUS);
		break;

	case I_BOSS_ROUND:
		AdjustWithBoni(F_BOSS_ROUND_BONUS);
		m_eTrait = Boss;
		CheckForTraits();
		break;
	}
}

  void CMonster::AdjustMonsterInfo(bool a_bForPlayer) {

	  if (a_bForPlayer) {

		  AdjustWithBoni();
		  GetRandomTrait();
	  }
	  else {

		  AdjustStatsForMonsters();
	  }

	  CheckForTraits();
	  m_sName = aNames[Random::RandomforInteger(I_NAMES_TOTAL)];
  }
  CMonster::CMonster() {

}

  CMonster::CMonster(eMonsterRace a_eRace, bool a_bForPlayer)
{
	m_inventory.AddGold(I_START_GOLD);

	switch (a_eRace)
	{

	case Bat:
		m_fHealth = 70.0f;
		m_fBaseHealth = 70.0f;
		m_fSpeed = 16.0f;
		m_fAttackPower = 3.4f;
		m_fDefencePower = 3.0f;
		m_eRace = Bat;

		AdjustMonsterInfo(a_bForPlayer);

		break;

	case Gargoyl:
		m_fHealth = 110.0f;
		m_fBaseHealth = 110.0f;
		m_fSpeed = 3.0f;
		m_fAttackPower = 8.5f;
		m_fDefencePower = 12.0f;
		m_eRace = Gargoyl;

		AdjustMonsterInfo(a_bForPlayer);

		break;

	case Orc:
		m_fHealth = 180.0f;
		m_fBaseHealth = 180.0f;
		m_fSpeed = 2.0f;
		m_fAttackPower = 10.0f;
		m_fDefencePower = 5.0f;
		m_eRace = Orc;

		AdjustMonsterInfo(a_bForPlayer);

		break;
	}
}

  int CMonster::GetGoldAmount() {
	return m_inventory.GetGoldAmount();
}

  void CMonster::AddGold(int a_iCount) {
	m_inventory.AddGold(a_iCount);
}

  void CMonster::PayGold(int a_iCount) {
	m_inventory.PayGold(a_iCount);
}

  void CMonster::AdjustWithBoni(const float a_fBoni) {

	m_fHealth *= a_fBoni;
	m_fBaseHealth = m_fHealth;
	m_fSpeed *= a_fBoni;
	m_fAttackPower *= a_fBoni;
	m_fDefencePower *= a_fBoni;
}

  void CMonster::AdjustWithBoni() {

	m_fHealth *= Random::RandomForMonsterBoni();
	m_fBaseHealth = m_fHealth;
	m_fSpeed *= Random::RandomForMonsterBoni();
	m_fAttackPower *= Random::RandomForMonsterBoni();
	m_fDefencePower *= Random::RandomForMonsterBoni();
}

  void CMonster::AdjustStatsForMonsters() {

	const float fAdjustValue = 1.2f;

	m_fHealth *= fAdjustValue;
	m_fBaseHealth = m_fHealth;
	m_fSpeed *= fAdjustValue;
	m_fAttackPower *= fAdjustValue;
	m_fDefencePower *= fAdjustValue;
}

  void CMonster::GetRandomTrait() {

	m_eTrait = static_cast<eMonsterTrait>(Random::RandomforInteger(I_TRAITS_TOTAL));
	if (m_eTrait != NoTrait) {
		m_bWithTrait = true;
	}
}

  void CMonster::CheckForTraits() {

	if (m_eTrait == Allrounder) {
		AdjustWithBoni(1.2f);
	}
	else if (m_eTrait == StoneSkin) {
		m_fDefencePower *= 1.3f;
	}
	else if (m_eTrait == Vampire) {
		m_fLifeSteal += 0.15f;
	}
	else if (m_eTrait == Boss) {

		switch (m_eRace) {

		case Orc:
			m_fHealth *= 2.0f;
			m_fBaseHealth *= 2.0f;
			m_fSpeed *= 0.3;
			break;
		case Bat:
			m_fHealth *= 0.7f;
			m_fBaseHealth *= 0.7f;
			m_fSpeed *= 1.5f;
			break;
		case Gargoyl:
			m_fHealth *= 1.2f;
			m_fBaseHealth *= 1.2f;
			m_fSpeed *= 0.75f;
			m_fDefencePower *= 1.45f;
			break;
		}
	}
}

  CMonster* PrebuildMonsters(int a_iCount, bool a_bForPlayer) {

	  const int iMonsterCount = a_iCount;

	  CMonster* aMonsters = new CMonster[iMonsterCount];

	  for (int i = NULL; i < iMonsterCount; i++) {

		  aMonsters[i] = CMonster((eMonsterRace)Random::RandomforInteger(I_RACES_TOTAL), a_bForPlayer);
	  }

	  return aMonsters;
  }
