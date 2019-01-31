#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Equipment.h"
#include "Item.h"
#include "ItemsArray.h"

class SaveGame {
public:
	static void savePlayerItems(Equipment *equipment);
	static bool loadPlayerItems(Equipment *equipment);
	static void removeSaveFile();
};

