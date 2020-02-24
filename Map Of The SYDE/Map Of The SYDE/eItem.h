#pragma once
#include <functional>
#include <string>
class eItem {
public:
	eItem() {}
	eItem(std::function<void()> newFunc, std::string itemname) { useItem = newFunc; _Name = itemname; }
	virtual ~eItem() {}
	std::function<void()> useItem;
	std::string _Name = "";
};
