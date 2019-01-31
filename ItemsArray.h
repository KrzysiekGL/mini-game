#pragma once
#include <vector>
#include <time.h>
#include <stdio.h>
#include <random>
#include "Item.h"

class ItemsArray {
	static std::vector<Item*> itemsArray;

public:
	static void beginItemsArray();

	static void drawItems(sf::RenderWindow &renderWndow);

	static void newRandomItem(sf::Vector2f atPosition);
	static void addAxeForPlayer(sf::Vector2f atPosition);
	static void addItemToArray(Item item);
	static std::vector<Item*> getItemsArray();
};