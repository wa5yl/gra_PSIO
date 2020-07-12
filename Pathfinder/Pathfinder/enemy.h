#pragma once

#include<iostream>
#include <ctime>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include <vector>
#include <stdlib.h>
#include "fireball.h"

class enemy
{
protected:
	float hp;
	float maxHp;
	float maxHpBar;
	
public:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f moveVec;
	sf::RectangleShape hpBar;

	float points;
	float dmg;
	float vecLangth;
	bool amIDead;
	bool canIMove;
	bool mageId;
	std::vector<std::unique_ptr<fireball>> fireballs;

	virtual void render(sf::RenderTarget& target);
	virtual void update(float pos_x, float pos_y, double delta, int& hit) = 0;
	virtual void takeDmg(float dmg);
	virtual void stillAlive();
	virtual void changeHpBar(float dmg);
};

class george : public enemy {
private:

public:

	void initTexture();
	void initSprite();
	void initVariables();

	george();
	~george();

	void update(float pos_x, float pos_y, double delta, int& hit) override;
};

class bigBen : public enemy {
public:
	void initTexture();
	void initSprite();
	void initVariables();

	bigBen();
	~bigBen();

	float maxFireballs;
	float elapsedTime;

	//std::vector<std::unique_ptr<fireball>> fireballs;

	void update(float pos_x, float pos_y, double delta, int& hit) override;
	void addFireball(double delta);
	void render(sf::RenderTarget& target) override;
	
};