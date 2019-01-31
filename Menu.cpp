#include "Menu.h"

Menu::Menu(sf::Vector2u size) {
	this->size = size;
	if (!font.loadFromFile("fonts/8bitOperatorPlus8-Bold.ttf")) return;

	menu.push_back(sf::Text("Start Game", font));
	menu.push_back(sf::Text("Load Game", font));
	menu.push_back(sf::Text("Save Game", font));
	menu.push_back(sf::Text("Game Settings", font));
	menu.push_back(sf::Text("Exit Game", font));

	menu[0].setFillColor(sf::Color::Cyan);
	menu[1].setFillColor(sf::Color::White);

	selectedItem = 0;

	setMenuEntrysPosition();

	//buffer.loadFromFile("sounds/select1.ogg");
	//selectMenuEntrySound.setBuffer(buffer);
}

void Menu::setMenuEntrysPosition() {
	for (int i = 0; i < menu.size(); ++i) {
		menu[i].setOrigin(sf::Vector2f(menu[i].getLocalBounds().width / 2, menu[i].getLocalBounds().height / 2));
		menu[i].setPosition(sf::Vector2f(size.x / 2, size.y / menu.size() + size.y / (menu.size() + 1) * i));
	}
}

void Menu::draw(sf::RenderWindow& window) {
	for (auto _menu : menu)
		window.draw(_menu);
}

void Menu::moveSelection(bool up) {
	if (selectedItem >= 0 && selectedItem < menu.size()) {
		menu[selectedItem].setFillColor(sf::Color::White);

		if (up) {
			--selectedItem;
			if (selectedItem < 0) selectedItem = menu.size() - 1;
		}
		else if (!up) {
			++selectedItem;
			if (selectedItem >= menu.size()) selectedItem = 0;
		}

		menu[selectedItem].setFillColor(sf::Color::Cyan);
	}
	//selectMenuEntrySound.play();
}

int Menu::getSelectedItem() {
	return selectedItem;
}