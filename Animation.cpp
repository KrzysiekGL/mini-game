#include "Animation.h"

Animation::Animation(sf::Texture& texture, sf::Vector2u imageCount, float switchTime) {
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.f;
	currentImage.x = 0;

	uvRect.width = texture.getSize().x / static_cast<float>(imageCount.x);
	uvRect.height = texture.getSize().y / static_cast<float>(imageCount.y);
}

sf::IntRect Animation::getUvRect() {
	return uvRect;
}

void Animation::update(int row, float deltaTime, bool isMoving) {
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime) {
		totalTime -= switchTime; //for smoother animation (not equal to 0 (=0) )
		currentImage.x++;

		if (currentImage.x >= imageCount.x) currentImage.x = 0;
	}

	if (!isMoving) currentImage.x = 1;

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}