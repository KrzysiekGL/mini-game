#pragma once

typedef unsigned int uint;

struct Character {
	//Character identification
	uint characterID;
	std::string characterName;

	//Animation
	uint currentRow;
	sf::Sprite sprite;
	sf::Vector2f movement;

	//Status
	int hitPoints;
	bool doesExist;
};