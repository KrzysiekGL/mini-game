#include "SaveGame.h"

void SaveGame::savePlayerItems(Equipment *equipment) {
	std::ofstream file;
	file.open("data/playerItems.sav", std::ios::out | std::ios::trunc | std::ios::binary);

	for (Item *item : equipment->items) {
		Item loacalItem = *item;
		file.write((char*)&loacalItem, sizeof(Item));
	}

	file.close();
}

bool SaveGame::loadPlayerItems(Equipment *equipment) {
	std::ifstream file;
	file.open("data/playerItems.sav", std::ios::in | std::ios::binary);

	if (file.fail()) return false;
	else {
		std::cout << "Items from save file\n";
		while (!file.eof()) {
			Item item;
			file.read((char*)&item, sizeof(Item));

			ItemsArray::addItemToArray(item);

			if(item.isThisItemEq())
				equipment->addItem(ItemsArray::getItemsArray().at(ItemsArray::getItemsArray().size() - 1)->itemID , false);
		}
	}

	file.close();
	return true;
}

void SaveGame::removeSaveFile() {
	std::remove("data/playerItems.sav");
}