#include "Intro.h"


void Introduction() {

	std::cout << "Hello Arena Master,\n many of the three Races have gathered to fight.\n";
	std::cout << "There are 3 rounds to win befor facing our currant Champion.\n We will give you some talentet Individuals to choose from for your first battle." << std::endl;
}

/// <summary>
/// Gibt die primären MonsterStats
/// </summary>
/// <param name="monster"></param>
void GiveMonsterStats(CMonster monster) {

	std::cout << " Health: " << monster.GetHealth() << " Attack: " << monster.GetAttack() << " Defence: " << monster.GetDefence() << " Speed: " << monster.GetSpeed() << monster.GetTraitAsText() << monster.GetRaceAsText() << std::endl;
}