#pragma once
#include <vector>
#include "eItem.h"

class Inventory {
public:
	Inventory() {}
	virtual ~Inventory() {}

	void addInv(eItem add);

	std::vector<eItem> _playerInventory = std::vector<eItem>();
private:
};