#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Makros.h"


class Random {

public:

    /// <summary>
    /// Setzt den Seed
    /// </summary>
    static void SetSRand() { std::srand(time(NULL)); }
		
	
	/// <summary>
	/// Gibt random Wert von 0 bis Max Excluded
	/// </summary>
	/// <param name="maxEx"></param>
	/// <returns></returns>
	static int RandomforInteger(int maxEx) {

		int result = 0;
		result = std::rand();
		while (result >= maxEx) {
			result -= maxEx;
		}

		return result;
	}
	/// <summary>
	/// Gibt einen spielspezifischen FLoat von 1.0 - 1.9
	/// </summary>
	/// <returns></returns>
	static float RandomForMonsterBoni() {   

		int number = 0;

		number = std::rand();
		number = number % I_MOD;
		float result = static_cast<float>(number);
		
		result = (result * F_TENTH) + F_ONE;
		
		return result;
	}
	

private:

	
	Random() {

	}

};