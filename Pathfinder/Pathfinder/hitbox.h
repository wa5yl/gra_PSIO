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

class hitboxComponent
{
private:
	sf::RectangleShape hitbox;
	sf::Sprite& sprite;

	float off_X;
	float off_Y;
public:

	hitboxComponent(sf::Sprite& sprite, float off_x, float off_y, float width, float height);
	~hitboxComponent();

	void update();
	void render(sf::RenderTarget& target);
};

