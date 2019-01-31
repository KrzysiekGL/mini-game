#include "Player.h"

Player::Player(Texture textureNumber, float switchTime, float speed, std::string name, sf::Vector2u startingPosition, sf::RenderWindow *window) {
	this->window = window;
	//NPC(textureNumber, switchTime, speed, name,startingPosition);
	this->name = name;
	this->switchTime = switchTime;
	setTextureAndAnimation(textureNumber);
	this->sprite.setTexture(texture);

	this->speed = speed;
	row = 0;
	isMoving = false;

	this->sprite.setOrigin(0, 0);
	this->sprite.setPosition(static_cast<sf::Vector2f>(startingPosition));

	//Character Identification and Storgae
	characters.push_back(Character());
	this->characterID = characters.size() - 1;
	setCharacterInfo(&characters[characterID], sprite, this->name, row, characterID);
	doesExist = true;

	healthTimer = sf::seconds(0);

	//Time handling
	internalTime = sf::seconds(0);
	generalTime = sf::seconds(0);
}

void Player::update(float deltaTime) {
	//Internal time handling
	internalTime += clock.restart();
	generalTime += internalTime;

	//Restart movement
	sf::Vector2f movement(0.0f, 0.0f);

	//Player Movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		movement.x -= speed * deltaTime;
		row = 1;
		isMoving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		movement.x += speed * deltaTime;
		row = 2;
		isMoving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		movement.y -= speed * deltaTime;
		row = 3;
		isMoving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		movement.y += speed * deltaTime;
		row = 0;
		isMoving = true;
	}

	if (movement.x == 0 && movement.y == 0) {
		row = 0;
		isMoving = false;
	}

	//Player Actions
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && internalTime.asMilliseconds() >= 200) {
		internalTime = sf::seconds(0);
		pickUpItem();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && internalTime.asMilliseconds() >= 200) {
		internalTime = sf::seconds(0);
		eat();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && internalTime.asMilliseconds() >= 100) {
		internalTime = sf::seconds(0);
		attack();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && internalTime.asMilliseconds() >= 200) {
		internalTime = sf::seconds(0);
		craftAxe();
	}

	collision(&movement);

	animation.update(row, deltaTime, isMoving);
	sprite.setTextureRect(animation.getUvRect());
	sprite.move(movement);
	updateCharacterInfo(&characters[characterID], sprite, row);
}

void Player::showPlayerInfo() {
	const sf::Color RED = sf::Color::Red;
	const sf::Color GREEN = sf::Color::Green;
	const sf::Color WHITE = sf::Color::White;


	//User Interface
	sf::Font font;
	font.loadFromFile("fonts/8bitOperatorPlus-Bold.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);

	sf::Vector2f position = sf::Vector2f(borders.x / 2 + 20, borders.y + 15);

	std::string hp = "HP: " + std::to_string(hitPoints);
	text.setString(hp);
	text.setPosition(position);
	if (hitPoints <= 25) text.setFillColor(RED);
	window->draw(text);
	text.setFillColor(WHITE);

	//std::string cos = "cos";
	//text.setString(cos);
	//position.y += 25;
	//text.setPosition(position);
	//window->draw(text);

	//std::string cos2 = "cos2";
	//text.setString(cos2);
	//position.y += 25;
	//text.setPosition(position);
	//window->draw(text);

	showActions(text);

	showEquipment(text);
}


void Player::showEquipment(sf::Text& text) {
	int appleInt = 0;
	int meatInt = 0;
	int stickInt = 0;
	int rockInt = 0;
	int axeInt = 0;

	Item *item;
	for (Item* item : equipment.items) {
		if (item->name == Item::ItemName::APPLE) appleInt++;
		if (item->name == Item::ItemName::MEAT) meatInt++;
		if (item->name == Item::ItemName::STICK) stickInt++;
		if (item->name == Item::ItemName::ROCK) rockInt++;
		if (item->name == Item::ItemName::AXE) axeInt++;
	}

	std::string apple = "apples: " + std::to_string(appleInt);
	std::string meat = "meat pieces: " + std::to_string(meatInt);
	std::string stick = "sticks: " + std::to_string(stickInt);
	std::string rock = "rocks: " + std::to_string(rockInt);
	std::string axe = "axes: " + std::to_string(axeInt);

	sf::Vector2f position = sf::Vector2f(20, borders.y + 15);
	
	text.setPosition(position);
	text.setString(apple);
	window->draw(text);

	text.setPosition(sf::Vector2f(position.x + 170, position.y));
	text.setString(meat);
	window->draw(text);

	position.y += 25;
	text.setPosition(position);
	text.setString(stick);
	window->draw(text);

	text.setPosition(sf::Vector2f(position.x + 170, position.y));
	text.setString(rock);
	window->draw(text);

	position.y += 25;
	text.setPosition(position);
	text.setString(axe);
	window->draw(text);
}

void Player::pickUpItem() {
	for (AllItems* item : Item::allItems) {
		if (this->sprite.getGlobalBounds().intersects(item->sprite.getGlobalBounds()) && item->drawn && !item->isEquiped) {
			if (equipment.addItem(item->itemID, true)) std::cout << "Picked up item\n";
		}
		//else std::cout << "There is no item\n";
	}
}

void Player::showActions(sf::Text& text) {
	const sf::Color RED = sf::Color::Red;
	const sf::Color GREEN = sf::Color::Green;
	const sf::Color WHITE = sf::Color::White;

	sf::Vector2f position = sf::Vector2f(borders.x / 2 + 120, borders.y + 15);

	for (Character& npc : characters) {
		if (characterID != npc.characterID) {
			if (sprite.getGlobalBounds().intersects(npc.sprite.getGlobalBounds()) && npc.doesExist) {
				//show SLAY option
				text.setPosition(position);
				text.setString("'S': Attack Monster");
				window->draw(text);
			}
		}
	}

	for (AllItems* item : Item::allItems) {
		if (sprite.getGlobalBounds().intersects(item->sprite.getGlobalBounds()) && item->drawn && !item->isEquiped) {
			text.setPosition(sf::Vector2f(position.x, position.y + 25));
			text.setString("'Z': Pick Up Item");
			window->draw(text);
		}
	}

	if (hitPoints <= 25) {
		text.setPosition(sf::Vector2f(position.x, position.y + 75));
		text.setFillColor(RED);
		text.setString("Hungry (low HP)");
		window->draw(text);
		text.setFillColor(WHITE);

		for (Item* item : equipment.items) {
			if (item->name == Item::ItemName::APPLE || item->name == Item::ItemName::MEAT) {
				text.setPosition(sf::Vector2f(position.x, position.y + 50));
				text.setString("'E': Eat");
				window->draw(text);
			}
		}
	}
}

void Player::eat() {
	int index = 0;
	for (Item* item : equipment.items) {
		if (item->name == Item::ItemName::APPLE || item->name == Item::ItemName::MEAT) {
			equipment.deleteItem(item, index);
			characters.at(characterID).hitPoints += 15;
			break;
		}
		++index;
	}
}

void Player::attack() {
	for (Character& npc : characters) {
		if (npc.characterID != characterID) {
			if (sprite.getGlobalBounds().intersects(npc.sprite.getGlobalBounds())) {
				//If there is an axe in eq, use it to instantly kill monster
				int index = 0;
				for (Item* axe : equipment.items) {
					if (axe->name == Item::ItemName::AXE) {
						equipment.deleteItem(axe, index);
						npc.hitPoints = 0;
						break;
					}
					++index;
				}
				//Else just hit him for 20 HP
				npc.hitPoints -= 20;
				break;
			}
		}
	}
}

void Player::craftAxe() {
	bool isThereAStick = false;
	int stickIndex;
	Item *stick = NULL;

	bool isThereARock = false;
	int rockIndex;
	Item *rock = NULL;

	//searching for a stick
	int index = 0;
	for (Item* item : equipment.items) {
		if (item->name == Item::ItemName::STICK) {
			isThereAStick = true;
			stickIndex = index;
			stick = item;
			break;
		}
		++index;
	}

	//searching for a rock
	index = 0;
	for (Item* item : equipment.items) {
		if (item->name == Item::ItemName::ROCK) {
			isThereARock = true;
			rockIndex = index;
			rock = item;
			break;
		}
		++index;
	}

	//if success then craft
	if (isThereARock && isThereAStick) {
		equipment.deleteItem(stick, stickIndex);
		if (rockIndex == 0) rockIndex++;
		equipment.deleteItem(rock, rockIndex-1); //nalez zmniejszyc o 1 poniewaz po usunieciu itemu powyzej wszystkie itemy z nastepnymi indexami przesuwaja sie o jeden do tylu
		
		ItemsArray::addAxeForPlayer(sprite.getPosition());
	}
}

Equipment *Player::getEquipment() {
	return &equipment;
}

void Player::decreaseHelth(sf::Time deltaTime) {
	healthTimer += deltaTime;
	if (healthTimer >= sf::seconds(4)) {
		healthTimer = sf::seconds(0);
		characters.at(characterID).hitPoints -= 7;
	}
}

int Player::getHealthStatus() {
	return characters.at(characterID).hitPoints;
}

void Player::restartPlayer() {
	sprite.setPosition(sf::Vector2f(650, 200));
	characters.at(characterID).hitPoints = 100;

	for (Item* item : equipment.items)
		equipment.deleteItem(item, 0);
}