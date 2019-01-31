#pragma once
#include <SFML/Graphics.hpp>

class Field {
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Field();
	~Field();
};