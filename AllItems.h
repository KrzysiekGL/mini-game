#pragma once

struct AllItems {
	void *thisItem;
	int itemID;
	sf::Sprite sprite;
	int itemName;

	bool drawn;
	bool isEquiped;
};