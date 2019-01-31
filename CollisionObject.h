#pragma once
#include <SFML/Graphics.hpp>

struct CollisionObject {
	sf::Vector2u upperLeftCorner;
	sf::Vector2u widthAndHeight;
};