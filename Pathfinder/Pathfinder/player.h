#pragma once

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include "Animation.h" 
//#include "hitbox.h"

#include <iostream>

class player {
private:
	void initTexture();
	void initSprite();
	void initVariables();

	animation animation;
	
public:

	sf::RectangleShape hitbox;

	sf::Sprite sprite;
	sf::Texture texture;

	enum class direction { top = 't', left = 'l', bottom = 'b', right = 'r' };
	direction direction;

	player();
	~player();

	float dmg;
	float hp;
	float maxHp;
	float score;
	int startPoint;
	int endPoint;
	int fireballHits;
	int whereToEndRoll;
	double timeElapsedA;
	double timeElapsedR;
	double immunityToDmg;
	bool keyIsPressed;
	bool unstopable_r;
	bool unstopable_a;

	void render(sf::RenderTarget& target);
	void update(double delta);
	void updateMovementAndAnimation(double delta);
	void updateRoll(double delta);
	void updateAtack(double delta);
	void gainPoints(float points);
	void takeDmg(double delta);
	void anotherChance();
};