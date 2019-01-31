#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

class Animation {
protected:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;

	sf::IntRect uvRect;

public:
	Animation() {}
	Animation(sf::Texture& texture, sf::Vector2u imageCount, float switchTime);
	~Animation() {}

	sf::IntRect getUvRect();

	void update(int row, float deltaTime, bool isMoving);
};