
#include "Intro.h"
#include "Input.h"
#include <iostream>
#include "Random.h"
#include "Makros.h"
#include "Inventory.h"
#include "Names.h"
#include "Monster.h"
#include "Fight.h"


int main()
{

   Random::SetSRand();

   const bool bForPlayer = true;
  
   CMonster* pMonsters = PrebuildMonsters(3,  bForPlayer);
   CMonster* pEnemies = PrebuildMonsters(4, !bForPlayer);
   
   Introduction();

   CMonster* pPlayer = GetPlayerCharacter(pMonsters);

   bool bWin = false;
  

   for (int iRound = I_ONE; iRound <= I_TOTAL_ROUNDS; iRound++) {

       bWin = FightingRound(pPlayer, pEnemies, iRound); 
       
       if (bWin) {
          
           if (iRound != I_TOTAL_ROUNDS) { 
              
               if(pPlayer != nullptr) pPlayer->SetHealth(pPlayer->GetBaseHealth());
               Reward(pPlayer, iRound);
           }
       }
       else {

          std::cout << "You lost" << std::endl;

          DELETE(pMonsters);
          pPlayer = nullptr;
          DELETE(pEnemies);

          return 0;
       }
   }
    
   std::cout << "You won. You are the new Champion!" << std::endl;

   DELETE(pMonsters);
   pPlayer = nullptr;
   DELETE(pEnemies);
   
   return 0;
}



