#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Prop.h"

typedef unsigned int uint;

class Object {
	typedef unsigned int uint;
protected:
	sf::Sprite sprite;

	static sf::Vector2u borders;

	static std::vector<Prop> props;
	uint propID;

	

public:
	Object();
	~Object() {};

	static std::vector<Prop>* getProps() { return &props; }
	uint getPropID() { return propID; }

	static void setBorders(sf::RenderWindow& renderWindow, sf::RectangleShape& shape);
};

