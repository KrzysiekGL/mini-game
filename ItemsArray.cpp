#include "ItemsArray.h"

std::vector<Item*> ItemsArray::itemsArray;

void ItemsArray::beginItemsArray() {
	srand(time(NULL));
	itemsArray.push_back(new Item(Item::ItemName::APPLE, sf::Vector2f(rand() % 700 + 50, rand() % 470 + 20)));
	itemsArray.push_back(new Item(Item::ItemName::MEAT, sf::Vector2f(rand() % 700 + 50, rand() % 470 + 20)));
	itemsArray.push_back(new Item(Item::ItemName::ROCK, sf::Vector2f(rand() % 700 + 50, rand() % 470 + 20)));
	itemsArray.push_back(new Item(Item::ItemName::STICK, sf::Vector2f(rand() % 700 + 50, rand() % 470 + 20)));
	itemsArray.push_back(new Item(Item::ItemName::ROCK, sf::Vector2f(rand() % 700 + 50, rand() % 470 + 20)));
}

void ItemsArray::drawItems(sf::RenderWindow &renderWindow) {
	for (Item* item : itemsArray) {
		if (item != NULL && item->doesItemExist() && !item->isThisItemEq())
			item->drawOnGround(renderWindow);
	}
}

void ItemsArray::newRandomItem(sf::Vector2f atPosition) {
	srand(time(NULL));
	int randomItemInt = rand() % 5;
	Item::ItemName itemName;
	switch (randomItemInt) {
	case 0:
		itemName = Item::ItemName::STICK;
		break;
	case 1:
		itemName = Item::ItemName::ROCK;
		break;
	case 3:
		itemName = Item::ItemName::MEAT;
		break;
	case 4:
		itemName = Item::ItemName::APPLE;
	default:
		itemName = Item::ItemName::APPLE;
		break;
	}
	itemsArray.push_back(new Item(itemName, atPosition));
}

void ItemsArray::addAxeForPlayer(sf::Vector2f atPosition) {
	itemsArray.push_back(new Item(Item::ItemName::AXE, atPosition));
}

void ItemsArray::addItemToArray(Item item) {
	itemsArray.push_back(new Item(item.name, item.sprite.getPosition(), item.isThisItemEq()));
}

std::vector<Item*> ItemsArray::getItemsArray() {
	return itemsArray;
}