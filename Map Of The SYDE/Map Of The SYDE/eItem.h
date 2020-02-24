#pragma once
#include <functional>
#include <string>
#include "SYDEstdafx.h"
class eItem {
public:
	eItem() {}
	eItem(std::function<void(eItem& item)> newFunc, std::string itemname, CustomAsset _IMG, std::string description) { useItem = newFunc; _Name = itemname; _imgObj = _IMG; _desc = description; }
	virtual ~eItem() {}
	std::function<void(eItem& item)> useItem;
	std::string _Name = "";
	CustomAsset _imgObj;
	std::string _desc = "";

	bool ItemUsed = false;
};
