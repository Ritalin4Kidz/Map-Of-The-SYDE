#include "pch.h"
#include "Inventory.h"

void Inventory::addInv(eItem add)
{
	if (_playerInventory.size() < 10)
	{
		_playerInventory.push_back(add);
	}
}
