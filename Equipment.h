#pragma once

#include <vector>

#include "Item.h"

class Equipment{
public:
	std::vector<Item*> items;

	enum ItemName {
		STICK = 0,
		ROCK = 1,
		AXE = 2,
		MEAT = 3,
		APPLE = 4
	};



public:
	Equipment();
	Equipment(int items);
	~Equipment() {}

	bool addItem(int itemID, bool fromGround);
	void deleteItem(Item *item, int index);
};