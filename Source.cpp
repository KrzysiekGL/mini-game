#include <iostream>
#include <random>
#include <ctime>
#include <unordered_map>
#include <thread>
#include <string>
#include <vector>

#include "TileMap.h"
#include "Menu.h"
#include "NPC.h"
#include "Player.h"
#include "Prop.h"
#include "Character.h"
#include "SaveGame.h"
#include "ItemsArray.h"

#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>

void prepareTextForHelpWindow(sf::RenderWindow &window, sf::Font &font, sf::Text &text, std::vector<std::string> &textArray);

int main(){
	float xWindow = 800, yWindow = 600;
	//Main window
	sf::RenderWindow renderWindow(sf::VideoMode(xWindow, yWindow), "mSGWC");
	renderWindow.setFramerateLimit(60);
	renderWindow.setVerticalSyncEnabled(true);
	int frames = 0;

	//Help window
	sf::RenderWindow helpWindow(sf::VideoMode(xWindow, yWindow), "help", sf::Style::None);
	helpWindow.setFramerateLimit(60);
	helpWindow.setVerticalSyncEnabled(true);
	bool showHelp = false;
	helpWindow.setVisible(showHelp);

	//Music
	//sf::Music gameMusic;
	//gameMusic.openFromFile("music/RaceToMars.ogg");
	//gameMusic.setLoop(true);
	//gameMusic.setVolume(70);
	//gameMusic.play();

	//For events handling
	sf::Event event;

	//For time handling
	sf::Clock clock;
	sf::Time internalTime;
	float deltaTime;

	//Menus
	enum Menus {
		Exit,
		MainMenu,
		Game,
		Load,
		Save,
		Settings,
		GameOver,
		TESTING
	};

	Menus menuChosen = MainMenu;
	Menus menuBuffer = MainMenu;
	bool isGameRunning = false;
	bool wantToQuit = false;
	bool isSaved = false;
	bool isLoaded = false;

	//Menu
	Menu menu(renderWindow.getSize());

	//Font
	sf::Font font;
	font.loadFromFile("fonts/Inconsolata-Bold.ttf");

	//Help
	std::string helpText1 = "Esc \t\texit game\nF1 \t\tShow this help\nBackspace \tduring the game show main menu\n";
	std::string helpText2 = "\nGame Controlls:\nArrows \tmovement\n'Z' \t\tpick up item\n'S' \t\tattack\n'E' \t\teat from inventory\n'C' \tcraft axe (1 stick & 1 rock required)";
	std::string helpText3 = "\nDuring the game press [Backspace] to return to Main Menu";
	std::string helpText4 = "\n\nHealth will decresse if you won't eat for too long.\nKill Monsters to obtain new items from them.";
	std::string helpText5 = "\nYou can craft axe if you have at least\none stick and one rock in your inventory.\n";
	std::vector<std::string> helpTextArray = { helpText1, helpText2, helpText3 , helpText4, helpText5};
	sf::Text helpText;
	prepareTextForHelpWindow(helpWindow, font, helpText, helpTextArray);

	//Exit
	std::string exitText1 = "Do you want to exit?\n";
	std::string exitText2 = "[Y]es\t\t[N]o\n";
	std::vector<std::string> exitTextArray = { exitText1, exitText2 };
	sf::Text exitText;
	prepareTextForHelpWindow(helpWindow, font, exitText, exitTextArray);

	std::string saveExitText1 = "Do you want to save progress befor exit?\n";
	std::string saveExitText2 = "[Y]es\t\t[N]o\n";
	std::vector<std::string> saveExitTextArray = { saveExitText1, saveExitText2 };
	sf::Text saveExitText;
	prepareTextForHelpWindow(helpWindow, font, saveExitText, saveExitTextArray);

	//Game saved
	std::string gameSavedText1 = "Game saved\n\n";
	std::string gameSavedText2 = "[C]ontinue\n";
	std::vector<std::string> gameSavedTextArray = { gameSavedText1, gameSavedText2 };
	sf::Text gameSavedText;
	prepareTextForHelpWindow(helpWindow, font, gameSavedText, gameSavedTextArray);

	//Load game
	std::string gameLoadeSuccessText1 = "Game loaded successfully\n\n";
	std::string gameLoadeSuccessText2 = "[C]ontinue\n";
	std::vector<std::string> gameLoadeSuccessArray = { gameLoadeSuccessText1, gameLoadeSuccessText2 };
	sf::Text gameLoadeSuccessText;
	prepareTextForHelpWindow(helpWindow, font, gameLoadeSuccessText, gameLoadeSuccessArray);

	std::string gameLoadeFailText1 = "Couldn't load game from file\n\n";
	std::string gameLoadeFailText2 = "[C]ontiniue\n";
	std::vector<std::string> gameLoadeFailArray = { gameLoadeFailText1, gameLoadeFailText2 };
	sf::Text gameLoadFailText;
	prepareTextForHelpWindow(helpWindow, font, gameLoadFailText, gameLoadeFailArray);

	sf::Text gameLoadTextBuffer;

	//Game Over
	std::string gameOverText1 = "Game Over\n\n";
	std::string gameOverText2 = "[C]ontinue to main menu";
	std::vector<std::string> gameOverTextArray = { gameOverText1, gameOverText2 };
	sf::Text gameOverText;
	prepareTextForHelpWindow(helpWindow, font, gameOverText, gameOverTextArray);

	//Settings
	std::string settingsText1 = "Choose game difficulty\n";
	std::string settingsText2 = "[E]asy \t[M]edium \t[H]ard";
	std::vector<std::string> settingsArray = { settingsText1, settingsText2 };
	sf::Text settingsText;
	prepareTextForHelpWindow(helpWindow, font, settingsText, settingsArray);

	//Objects created initially 
	srand(time(NULL));
	std::vector<NPC*> npcs;

	npcs.push_back(new NPC(NPC::Milo, 0.2f, 10.f, "Milo", sf::Vector2u(rand() % 100, rand() % 100), &renderWindow));
	npcs.push_back(new NPC(NPC::Momo, 0.2f, 10.f, "Momo", sf::Vector2u(600, 400), &renderWindow));
	npcs.push_back(new NPC(NPC::Milo, 0.2f, 10.f, "Milo2", sf::Vector2u(300, 350), &renderWindow));
	npcs.push_back(new NPC(NPC::Texture::Momo, 0.2f, 10.f, "Momo", sf::Vector2u(rand() % 500, rand() % 400), &renderWindow));

	ItemsArray::beginItemsArray();

	//Player
	Player player(NPC::Gando, 0.2f, 100.f, "Gando", sf::Vector2u(650, 200), &renderWindow);
	std::vector<Item> savedItems;

	enum Difficulty {
		EASY,
		MEDIUM,
		HARD
	};

	Difficulty difficulty = MEDIUM;

	//Map
	const int level[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 3, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 2, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 2, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 2, 3, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 3, 2, 3, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};

	TileMap map;
	if(!map.load("images/tilesets/tf_jungle_tileset.png", sf::Vector2u(32, 32), level, 32, 16)) return -1;

	sf::RectangleShape playerMsgBox(sf::Vector2f(renderWindow.getSize().x, 124));
	playerMsgBox.setFillColor(sf::Color::Black);
	playerMsgBox.setPosition(sf::Vector2f(0, renderWindow.getSize().y - playerMsgBox.getSize().y));

	Object::setBorders(renderWindow, playerMsgBox);

	//--------------------------------------Game Loop---------------------------------------------
	while (renderWindow.isOpen()) {
		deltaTime = static_cast<float>(clock.restart().asSeconds());
		internalTime += sf::seconds(deltaTime);

		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed) {
				renderWindow.close();
				helpWindow.close();
			}
		}

			//Exit
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && internalTime.asMilliseconds() >= 200) {
			internalTime = sf::seconds(0);
			menuChosen = Exit;
		}
			//Help
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && internalTime.asMilliseconds() >= 200) {
			internalTime = sf::seconds(0);
			showHelp = !showHelp;

			while (showHelp) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && internalTime.asMilliseconds() >= 200) {
					internalTime = sf::seconds(0);
					showHelp = !showHelp;
				}
					
				helpWindow.setVisible(showHelp);
				renderWindow.setVisible(!showHelp);

				helpWindow.clear(sf::Color::Black);
				helpWindow.draw(helpText);
				helpWindow.display();

				internalTime += clock.restart();
			}
			renderWindow.setVisible(true);
		}
		//Main Menu
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && internalTime.asMilliseconds() >= 200) {
			internalTime = sf::seconds(0);
			if (isGameRunning && menuChosen == Game) menuChosen = MainMenu;
			else if (isGameRunning && menuChosen != Game) menuChosen = Game;
			else if (menuChosen == TESTING) menuChosen = MainMenu;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && internalTime.asMilliseconds() >= 200) {
			internalTime = sf::seconds(0);
			menuChosen = TESTING;
		}

		switch (menuChosen) {
		case Exit:
			renderWindow.setVisible(false);
			helpWindow.setVisible(true);
			while (true) {
				helpWindow.clear();
				if(!wantToQuit) helpWindow.draw(exitText);
				if (wantToQuit) helpWindow.draw(saveExitText);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && internalTime.asMilliseconds() >= 200) {
					internalTime = sf::seconds(0);
					if (!wantToQuit) {
						wantToQuit = true;
					}
					else if (wantToQuit) {
						SaveGame::savePlayerItems(player.getEquipment());
						renderWindow.close();
						helpWindow.close();
						break;
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
					if (!wantToQuit) break;
					if (wantToQuit) {
						renderWindow.close();
						helpWindow.close();
						break;
					}
				}
				helpWindow.display();
				internalTime += clock.restart();
			}
			helpWindow.setVisible(false);
			renderWindow.setVisible(true);
			menuChosen = MainMenu;
			break;

		case MainMenu:
			renderWindow.clear(sf::Color(30.f, 20.f, 10.f, 255.f));
			menu.draw(renderWindow);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && internalTime.asMilliseconds() >= 200) {
				internalTime = sf::seconds(0);
				menu.moveSelection(true);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && internalTime.asMilliseconds() >= 200) {
				internalTime = sf::seconds(0);
				menu.moveSelection(false);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				switch (menu.getSelectedItem())
				{
				case 0:
					menuChosen = Game;
					break;
				case 1:
					menuChosen = Load;
					break;
				case 2:
					menuChosen = Save;
					break;
				case 3:
					menuChosen = Settings;
					break;
				case 4:
					menuChosen = Exit;
					break;
				default:
					menuChosen = MainMenu;
				}
			}
			break;

		case Game:
			isGameRunning = true;

			renderWindow.clear(sf::Color(24.f, 24.f, 190.f, 255.f));

			//  update NPC and Player
			for (NPC* npc : npcs)
				npc->update(deltaTime);

			player.update(deltaTime);

			//  draw map
			renderWindow.draw(map);

			// draw items on the ground
			ItemsArray::drawItems(renderWindow);

			//  draw NPC
			for (NPC* npc : npcs)
				npc->drawNPC();

			// ... player
			player.drawNPC();
			renderWindow.draw(playerMsgBox);
			player.showPlayerInfo();

			if (player.getHealthStatus() <= 0)
				menuChosen = GameOver;

			switch (difficulty) {
			case EASY:
				player.decreaseHelth(sf::seconds(deltaTime * 0.5));
				break;
			case MEDIUM:
				player.decreaseHelth(sf::seconds(deltaTime * 1));
				break;
			case HARD:
				player.decreaseHelth(sf::seconds(deltaTime * 2));
				break;
			default:
				player.decreaseHelth(sf::seconds(deltaTime * 1));
				break;
			}


			break;

		case Save:
			renderWindow.setVisible(false);
			helpWindow.setVisible(true);
			isSaved = false;
			while (true) {
				helpWindow.clear();
				if (!isSaved) {
					isSaved = true;
					SaveGame::savePlayerItems(player.getEquipment());
				}
				helpWindow.draw(gameSavedText);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) break;
				helpWindow.display();
				internalTime += clock.restart();
			}
			helpWindow.setVisible(false);
			renderWindow.setVisible(true);
			menuChosen = MainMenu;
			break;

		case Load:
			renderWindow.setVisible(false);
			helpWindow.setVisible(true);
			isLoaded = false;
			while (true) {
				helpWindow.clear();
				if (!isLoaded) {
					isLoaded = true;
					if (SaveGame::loadPlayerItems(player.getEquipment()))
						gameLoadTextBuffer = gameLoadeSuccessText;
					else gameLoadTextBuffer = gameLoadFailText;
				}
				helpWindow.draw(gameLoadTextBuffer);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) break;
				helpWindow.display();
				internalTime += clock.restart();
			}
			helpWindow.setVisible(false);
			renderWindow.setVisible(true);
			menuChosen = MainMenu;
			break;

		case Settings:
			renderWindow.setVisible(false);
			helpWindow.setVisible(true);
			while (true) {
				helpWindow.clear();
				helpWindow.draw(settingsText);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
					difficulty = EASY;
					break;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
					difficulty = MEDIUM;
					break;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
					difficulty = HARD;
					break;
				}

				helpWindow.display();
				internalTime += clock.restart();
			}
			helpWindow.setVisible(false);
			renderWindow.setVisible(true);
			menuChosen = MainMenu;
			break;

		case GameOver:
			//restart Game
			SaveGame::removeSaveFile();
			player.restartPlayer();

			renderWindow.setVisible(false);
			helpWindow.setVisible(true);
			isLoaded = false;
			while (true) {
				helpWindow.clear();
	
				helpWindow.draw(gameOverText);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) break;

				helpWindow.display();
				internalTime += clock.restart();
			}
			helpWindow.setVisible(false);
			renderWindow.setVisible(true);
			menuChosen = MainMenu;
			break;

		//TESTING mode
		case TESTING:
			renderWindow.clear(sf::Color(100.f, 100.f, 100.f, 255.f));
			renderWindow.draw(map);
			menuChosen = MainMenu;
			break;

		default:
			menuChosen = MainMenu;
			break;
		}

		renderWindow.display();
	}
	
	return 0;
}

void prepareTextForHelpWindow(sf::RenderWindow &window, sf::Font &font, sf::Text &text, std::vector<std::string> &textArray) {
	std::string summary;
	for (std::string& text : textArray)
		summary += text;

	text.setString(summary);
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);
	text.setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));
}