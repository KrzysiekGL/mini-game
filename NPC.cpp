#include "NPC.h"

//static objects
std::vector<Character> NPC::characters;

NPC::NPC(Texture textureNumber, float switchTime, float speed, std::string name, sf::Vector2u startingPosition, sf::RenderWindow *window) {
	this->window = window;
	this->name = name;
	this->switchTime = switchTime;
	setTextureAndAnimation(textureNumber);
	this->sprite.setTexture(texture);
	
	this->speed = speed;
	this->row = 0;
	this->isMoving = false;

	this->sprite.setOrigin(0, 0);
	this->sprite.setPosition(static_cast<sf::Vector2f>(startingPosition));

	//Character Identification and Storgae
	characters.push_back(Character());
	this->characterID = characters.size() - 1;
	setCharacterInfo(&characters[characterID], sprite, this->name, row, characterID);
	doesExist = true;
}

void NPC::update(float deltaTime){
	sf::Vector2f movement(0.0f, 0.0f);

	if (clock.getElapsedTime().asSeconds() >= 1) {
		westEast.x = rand() % 2;
		westEast.y = rand() % 2;
		northSouth.x = rand() % 2;
		northSouth.y = rand() % 2;
		clock.restart();
	}


	if (westEast.x == true) {
		movement.x -= speed * deltaTime;
		row = 1;
		isMoving = true;
	}

	if (westEast.y == true) {
		movement.x += speed * deltaTime;
		row = 2;
		isMoving = true;
	}

	if (northSouth.x == true) {
		movement.y -= speed * deltaTime;
		row = 3;
		isMoving = true;
	}

	if (northSouth.y == true) {
		movement.y += speed * deltaTime;
		row = 0;
		isMoving = true;
	}

	if (movement.x == 0 && movement.y == 0) {
		row = 0;
		isMoving = false;
	}

	collision(&movement);
	characters[characterID].movement = movement;

	animation.update(row, deltaTime, isMoving);
	sprite.setTextureRect(animation.getUvRect());
	sprite.move(characters[characterID].movement);

	updateCharacterInfo(&characters[characterID], sprite, row);

	//When HP is 0 or below
	if (hitPoints <= 0) {
		if (doesExist) ItemsArray::newRandomItem(sprite.getPosition());
		doesExist = false;
	}

	if (!doesExist)
		revive(deltaTime);
}

void NPC::drawNPC() {
	if(doesExist)
		this->window->draw(sprite);
}

void NPC::setTextureAndAnimation(Texture textureNumber) {
	switch (textureNumber)
	{
	case NPC::Gando:
		this->texture.loadFromFile("images/animation/GandoWalkAni.png");
		animation = Animation(texture, sf::Vector2u(3,4), switchTime);
		this->xFrames = 3; this->yFrames = 4;
		break;
	case NPC::Milo:
		this->texture.loadFromFile("images/animation/MiloWalkAni.png");
		animation = Animation(texture, sf::Vector2u(4, 4), switchTime);
		this->xFrames = 4; this->yFrames = 4;
		break;
	case NPC::Momo:
		this->texture.loadFromFile("images/animation/MomoWalkAni.png");
		animation = Animation(texture, sf::Vector2u(3, 4), switchTime);
		this->xFrames = 3; this->yFrames = 4;
		break;
	default:
		break;
	}
}

void NPC::setCharacterInfo(Character* thisCharacter, sf::Sprite sprite, std::string name, int currentRow, uint characterID) {
	thisCharacter->characterID = characterID;
	thisCharacter->sprite = sprite;
	thisCharacter->currentRow = currentRow;
	thisCharacter->characterName = name;
	thisCharacter->hitPoints = hitPoints;
	thisCharacter->doesExist = doesExist;
}

void NPC::updateCharacterInfo(Character* thisCharacter, sf::Sprite sprite, uint currentRow) {
	//Update structure
	thisCharacter->sprite = sprite;
	thisCharacter->currentRow = currentRow;
	thisCharacter->doesExist = doesExist;
	
	//Update this character from structure
	hitPoints = thisCharacter->hitPoints;
}

void NPC::collision(sf::Vector2f *movemet) {
	sf::Vector2f thisCoord = sprite.getPosition();
	uint thisWidth = sprite.getGlobalBounds().width;
	uint thisHeight = sprite.getGlobalBounds().height;

	sf::Sprite tempSprite;
	sf::Vector2f tempCoord;

	//Collision with other NPC
	for (int i = 0; i < characters.size(); ++i) {
		if (i != characterID && characters.at(i).doesExist) {
			tempSprite = characters[i].sprite;
			tempCoord = tempSprite.getPosition();

			if (sprite.getGlobalBounds().intersects(tempSprite.getGlobalBounds())) {
				if (thisCoord.x > tempCoord.x) {
					movemet->x = 0.13f;
					characters[i].movement.x = -0.13f;
				}
				else {
					movemet->x = -0.13f;
					characters[i].movement.x = 0.13f;
				}
				if (thisCoord.y > tempCoord.y) {
					movemet->y = 0.13f;
					characters[i].movement.y = -0.13f;
				}
				else {
					movemet->y = -0.13f;
					characters[i].movement.y = 0.13f;
				}
			}
		}
	}

	//Collision with borders -> Stop
	if (thisCoord.x == 0) movemet->x = 0;
	if ((thisCoord.x + thisWidth) == borders.x) movemet->x = 0;
	if (thisCoord.y == 0) movemet->y = 0;
	if ((thisCoord.y + thisHeight) == borders.y) movemet->y = 0;

	//Transition with borders -> Push
	if (thisCoord.x < 0) movemet->x = 0.15f;
	if ((thisCoord.x + thisWidth) > borders.x) movemet->x = -0.15f;
	if (thisCoord.y < 0) movemet->y = 0.15f;
	if ((thisCoord.y + thisHeight) > borders.y) movemet->y = -0.15f;
}

void NPC::revive(float deltaTime) {
	characters.at(characterID).hitPoints += int(deltaTime * 50);
	if (characters.at(characterID).hitPoints >= 100) {
		characters.at(characterID).hitPoints = 100;
		doesExist = true;
		srand(time(NULL));
		sprite.setPosition(sf::Vector2f(rand()%window->getSize().x, rand()%476));
	}
}

void NPC::dropItem() {

}