#pragma once

#include <vector>
#include <iostream>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include <iostream>

class animation {
private:
	void initVariables();

	int imageCount;
	int current;
	double totalTimeR;
	double totalTimeA;
	double switchTime;
	sf::Texture texture;
	sf::Vector2u currentImage;
public:
	animation();
	~animation();

	sf::IntRect uvRect;

	void updateAnimation(int& startPoint, int endPoint, double delta, bool key);
	void rollAnimation(int& startPoint, int endPoint, int whereToEndRoll, double delta, bool& unstopable, double& timeElapsed);
	void attackAnimationn(int& startPoint, int endPoint, int whereToEndRoll, double delta, bool& unstopable_r, double& timeElapsedA);
	
};