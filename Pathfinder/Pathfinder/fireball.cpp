#include "fireball.h"



fireball::~fireball()
{
}

void fireball::initTexture()
{
	if (!this->texture.loadFromFile("tekstury/fireball.png"))
	{
		std::cout << "Klopot" << "\n";
	}
}

void fireball::initSprite(float pos_x, float pos_y)
{
	this->sprite.setTexture(texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->sprite.scale(0.1, 0.1);
}

void fireball::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	//std::cout << "rednderuje" << std::endl;
}



fireball::fireball(float pos_x, float pos_y)
{
	this->initTexture();
	this->initSprite(pos_x, pos_y);
}