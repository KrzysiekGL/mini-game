#include "Item.h"

std::vector<AllItems*> Item::allItems;

Item::Item(ItemName name, sf::Vector2f position) {
	doesExist = true;
	this->name = name;
	setupItem(name);
	setPostionForItem(position);
}

Item::Item() {
	doesExist = true;
	srand(time(NULL));
	int randomItemNAME = rand() % 5;
	name = ItemName(randomItemNAME);
	setPostionForItem(sf::Vector2f(rand()% 700 + 50, rand()% 470 + 20));
	setupItem(name);
}

Item::~Item() {
}

void Item::setupItem(ItemName name) {
	switch (name) {
	case Item::STICK:
		flag = CRAFTABLE;
		texture.loadFromFile("images/items/stick.png");
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setScale(sf::Vector2f(0.035f, 0.035f));
		break;

	case Item::ROCK:
		flag = CRAFTABLE;
		texture.loadFromFile("images/items/rock.png");
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setScale(sf::Vector2f(0.9f, 0.9f));
		break;

	case Item::AXE:
		flag = WEAPON;
		texture.loadFromFile("images/items/axe.png");
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setScale(sf::Vector2f(0.1f, 0.14f));
		break;

	case Item::MEAT:
		flag = FOOD;
		texture.loadFromFile("images/items/meat.png");
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setScale(sf::Vector2f(0.035f, 0.035f));
		break;

	case Item::APPLE:
		flag = FOOD;
		texture.loadFromFile("images/items/apple.png");
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setColor(sf::Color::Red);
		sprite.setScale(sf::Vector2f(1, 1));
		break;

	default:
		flag = SPECIAL;
		break;
	}

	allItems.push_back(new AllItems());
	allItems.at(allItems.size() - 1)->itemID = allItems.size() - 1;
	itemID = allItems.at(allItems.size() - 1)->itemID;
	allItems.at(itemID)->thisItem = this;
	allItems.at(itemID)->itemName = name;
	allItems.at(itemID)->drawn = false;
	allItems.at(itemID)->isEquiped = isEquiped;

	std::cout << "Item created: " << name << " " << itemID << " " << allItems.at(itemID)->thisItem << "\n";
	std::cout << "Adress of allItems vector at this itemID is " << allItems.at(itemID) << "\n";
}

void Item::setPostionForItem(sf::Vector2f position) {
	sprite.setPosition(position);
	allItems.at(itemID)->sprite = sprite;
}

void *Item::getItem(int itemID, bool pickedUp) {
	AllItems *item = allItems.at(itemID);

	if (pickedUp) {
		if (!allItems.at(itemID)->drawn) return NULL;

		allItems.at(itemID)->drawn = false;
		allItems.at(itemID)->isEquiped = true;
	}

	return allItems.at(itemID)->thisItem;
}

void Item::drawOnGround(sf::RenderWindow &window) {
	if (doesExist && !isEquiped) {
		AllItems *item = allItems.at(itemID);

		if (!allItems.at(itemID)->isEquiped) {
			window.draw(sprite);
			item->drawn = true;
		}
	}
	else if (isEquiped) {
		allItems.at(itemID)->isEquiped = isEquiped;
	}
}

void Item::deleteThisItem() {
	/*
	*Can't make it work properly...
	*/
	//int index = 0;
	//for (AllItems* item : allItems) {
	//	if (itemID == item->itemID) {
	//		allItems.erase(allItems.begin() + index);
	//		std::cout << "Usunieto item o itemID = "  << itemID << "\n";
	//		break;
	//	}
	//	++index;
	//}
	doesExist = false;
}

bool Item::doesItemExist() {
	return doesExist;
}