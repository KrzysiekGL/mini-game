#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CollisionObject.h"

class CollisionMap {
protected:
	
public:
	CollisionMap(sf::RenderWindow& renderWidow);
	CollisionMap() {}
	~CollisionMap() {}
};