#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

class Menu {
protected:
	sf::Vector2u size;
	sf::Font font;
	std::vector<sf::Text> menu;
	int selectedItem;

	//sf::SoundBuffer buffer;
	//sf::Sound selectMenuEntrySound;

	void setMenuEntrysPosition();
public:
	Menu() {}
	Menu(sf::Vector2u size);
	~Menu() {}

	void moveSelection(bool up);
	void draw(sf::RenderWindow& window);

	int getSelectedItem();
};