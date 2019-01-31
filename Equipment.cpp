#include "Equipment.h"

Equipment::Equipment() {
}

Equipment::Equipment(int items){
	Equipment();
	while ( items > 0 ) {
		this->items.push_back(new Item());
		--items;
	}
}

bool Equipment::addItem(int itemID, bool fromGround) {
	void *item = Item::getItem(itemID, fromGround);
	if (item != NULL) {
		items.push_back(static_cast<Item *>(item));
		static_cast<Item *>(item)->setThisItemEq(true);
		return true;
	}
	else return false;
}

void Equipment::deleteItem(Item *item, int index) {
	if (item != NULL) {
		item->deleteThisItem();
		items.erase(items.begin() + index);
	}
}