#pragma once

#include <string>
#include <vector>
#include <random>

#include "Animation.h"
#include "Object.h"
#include "Character.h"
#include "ItemsArray.h"

class NPC: public Object {
	typedef unsigned int uint;
protected:
	std::string name;
	bool isHostile;

	int hitPoints=100;
	int damage = 0;

	bool doesExist;

	//Visual representation of character
	sf::Texture texture;
	Animation animation;
	uint row;
	float switchTime;
	float speed;
	bool isMoving;
	uint xFrames;
	uint yFrames;

	//Character informations
	static std::vector<Character> characters;
	uint characterID;

	//Render Window reference
	sf::RenderWindow *window;

private:
	//directions
	sf::Vector2<bool> northSouth;
	sf::Vector2<bool> westEast;

	sf::Clock clock;

public:
	enum Texture {
		Gando = 0,
		Milo = 1,
		Momo = 2
	};

public:
	NPC() {}
	NPC(Texture textureNumber, float switchTime, float speed, std::string name, sf::Vector2u startingPosition, sf::RenderWindow *window);
	~NPC() {}

	void update(float deltaTime);
	void drawNPC();

	static std::vector<Character>& getCharacters() { return characters; }

protected:
	void setTextureAndAnimation(Texture textureNumber);
	void setCharacterInfo(Character* thisCharacter, sf::Sprite sprite, std::string name, int currentRow, uint characterID);
	void updateCharacterInfo(Character* thisCharacter, sf::Sprite sprite, uint currentRow);

	void collision(sf::Vector2f *movement);

private:
	void revive(float deltaTime);
	void dropItem();
};