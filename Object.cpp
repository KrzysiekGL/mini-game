#include "Object.h"

std::vector<Prop> Object::props;
sf::Vector2u Object::borders;

Object::Object() {
	props.push_back(Prop());
	propID = props.size() - 1;
}

void Object::setBorders(sf::RenderWindow& renderWindow, sf::RectangleShape& shape) {
	borders.x = renderWindow.getSize().x;
	borders.y = renderWindow.getSize().y - shape.getSize().y;
}