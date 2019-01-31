#pragma once
#include <SFML/System.hpp>
#include "NPC.h"
#include "Equipment.h"
#include "AllItems.h"
#include "ItemsArray.h"

class Player: public NPC {
private:
	//Time (actions) handling
	sf::Clock clock;
	sf::Time generalTime;
	sf::Time internalTime;

protected:
	Equipment equipment;

	sf::Time healthTimer;
	
public:
	Player(Texture textureNumber, float switchTime, float speed, std::string name, sf::Vector2u startingPosition, sf::RenderWindow *window);
	~Player() {}

	void update(float deltaTime);

	//Actions
	void attack();
	void eat();
	void pickUpItem();
	void craftAxe();

	void decreaseHelth(sf::Time deltaTime);

	//UI
	void showEquipment(sf::Text& text);
	void showPlayerInfo();
	void showActions(sf::Text& text);

	//Player managment
	Equipment *getEquipment();
	int getHealthStatus();
	void restartPlayer();
};