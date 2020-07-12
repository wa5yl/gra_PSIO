#pragma once

#include<iostream>
#include <ctime>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include <vector>
#include <stdlib.h>
#include "fireball.h"


class inventory
{
public:
	sf::Sprite sprite;
	sf::Texture texture;

	float modyfier;
	virtual void update() = 0;
};

class hpMax : public inventory {
public:
	void initTexture();
	void initSprite();
	void initVariables();

	hpMax();
	~hpMax();

	virtual void update() override;
};