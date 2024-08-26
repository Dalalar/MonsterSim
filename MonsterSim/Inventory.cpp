#include "Inventory.h"

int CInventory::GetGoldAmount()
{
	return CInventory::iGoldCount;
}

void CInventory::AddGold(int a_iCount) {
	CInventory::iGoldCount += a_iCount;
}

void CInventory::PayGold(int a_iCount) {
	CInventory::iGoldCount -= a_iCount;
}
