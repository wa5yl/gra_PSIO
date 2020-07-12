#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <iostream>
#include <ctime>
#include <memory>
#include <sstream>
#include "player.h"
#include "enemy.h"

class game
{

private:

	sf::RenderWindow* window;

	void initWindow();
	void initVariables();
	void initEnemies();

	player player;
	std::vector<std::unique_ptr<enemy>> enemies;

 	sf::Event event;
	sf::Sprite rescueButton;
	sf::Vector2i mousePosition;
	sf::Vector2f mousePositionView;

	sf::Font font;
	sf::Text text;
	sf::Texture texture; 

	double timeElapsed;
	int maxEnemies;

	bool end;
public:

	game();
	~game();

	void pollEvent(double delta);

	void render();
	void upadete(double delta);
	void renderPlayer();
	void updatePlayer(double delta);
	void updateEnemies(double delta);
	void renderEnemies();

	void updateText();
	void updateMouse();
	void moveToPlayer();
	void attackEnemy(double delta);
	void nextLevel();
	void collisionWithEnemy(double delta);
	void mapCollision();
	void endGame();
	void acceptRescue();

	const bool runnin() const;

};