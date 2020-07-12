#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>

class fireball
{
public:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f moveVec;

	float vecLangth;

	fireball(float pos_x, float pos_y);
	~fireball();

	float hp;

	void initTexture();
	void initSprite(float pos_x, float pos_y);
	void initVariables();

	void update(float pos_x, float pos_y, double delta);
	void render(sf::RenderTarget& target);
};

