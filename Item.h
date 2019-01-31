#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "AllItems.h"

class Item{
public:
	static std::vector<AllItems*> allItems;

	int itemID;

	enum ItemFlag {
		CRAFTABLE = 0,
		WEAPON = 1,
		FOOD = 2,
		SPECIAL = 3
	};

	enum ItemName {
		STICK = 0,
		ROCK = 1,
		AXE = 2,
		MEAT = 3,
		APPLE = 4
	};

//protected:
	ItemName name;		//stick, rock, axe, meat, apple
	ItemFlag flag;		//craftable, weapon, food, special

	sf::Texture texture;
	sf::Sprite sprite;

protected:
	bool doesExist;
	bool isEquiped;

protected:
	void setupItem(ItemName name);

public:
	Item(ItemName name, sf::Vector2f position);
	Item(ItemName name, sf::Vector2f position, bool isEquiped) :Item(name, position) { this->isEquiped = isEquiped; }
	Item();
	~Item();

	void drawOnGround(sf::RenderWindow &window);

	void setPostionForItem(sf::Vector2f position);

	void deleteThisItem();

	bool doesItemExist();

	bool isThisItemEq() { return isEquiped; }
	void setThisItemEq(bool equiped) { isEquiped = equiped; }
	

	static void *getItem(int itemID, bool pickedUp);
};