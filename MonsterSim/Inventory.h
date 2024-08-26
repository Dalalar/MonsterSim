#pragma once

class CInventory
{
public:
	int GetGoldAmount();
    void AddGold(int count);
    void PayGold(int count);
private:
	int iGoldCount = 0;
};

