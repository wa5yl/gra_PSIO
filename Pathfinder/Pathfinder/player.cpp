#include "player.h"



void player::initTexture()
{
	if (!this->texture.loadFromFile("tekstury/player.png"))
	{
		std::cout << "Klopot" << "\n";
	}
}

void player::initSprite()
{
	this->sprite.setTexture(texture);
	this->sprite.setPosition(390, 500);
	this->sprite.scale(2, 2);
}

void player::initVariables()
{
	this->score = 0;
	//this->startPoint = 0;
	this->whereToEndRoll = 6;
	this->keyIsPressed = false;
	this->direction = direction::right;
	this->unstopable_r = false;
	this->unstopable_a = false;
	this->dmg = 100;
	this->hp = 200;
	this->maxHp = 200;
	this->fireballHits = 0;
	this->timeElapsedA = 0;
	this->timeElapsedR = 0;
	this->immunityToDmg = 0;

	this->hitbox.setPosition(this->sprite.getPosition().x + 42, this->sprite.getPosition().y + 38);
	this->hitbox.setSize(sf::Vector2f(this->sprite.getGlobalBounds().width/120 - 25, this->sprite.getGlobalBounds().height/2 - 10));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);
}
player::player()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();
}

player::~player()
{
}


void player::updateMovementAndAnimation(double delta)
{
	if (this->unstopable_r == false) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			this->sprite.move(-3.f, 0.f);
			this->hitbox.move(-3.f, 0.f);
			this->startPoint = 12;
			this->endPoint = 17;
			this->keyIsPressed = true;
			direction = direction::left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			this->sprite.move(3.f, 0.f);
			this->hitbox.move(3.f, 0.f);
			this->startPoint = 0;
			this->endPoint = 5;
			this->keyIsPressed = true;
			direction = direction::right;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			this->sprite.move(0.f, -3.f);
			this->hitbox.move(0.f, -3.f);
			this->startPoint = 6;
			this->endPoint = 11;
			this->keyIsPressed = true;
			direction = direction::top;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			this->sprite.move(0.f, 3.f);
			this->hitbox.move(0.f, 3.f);
			this->startPoint = 18;
			this->endPoint = 23;
			this->keyIsPressed = true;
			direction = direction::bottom;
		}


		
		animation.updateAnimation(this->startPoint, this->endPoint, delta, this->keyIsPressed);
		this->sprite.setTextureRect(this->animation.uvRect);

		this->keyIsPressed = false;
	}
}

void player::updateRoll(double delta)
{
	this->timeElapsedR += delta;
	if (this->timeElapsedR > 0.5) {
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {

			switch (this->direction)
			{
			case direction::right: 
				this->sprite.move(14.f, 0.f);
				this->hitbox.move(14.f, 0.f);
				this->startPoint = 40;
				this->endPoint = 44;
				this->unstopable_r = true;
				this->whereToEndRoll = 0;
				break;
			case direction::bottom:
				this->sprite.move(0.f, 14.f);
				this->hitbox.move(0.f, 14.f);
				this->startPoint = 55;
				this->endPoint = 59;
				this->unstopable_r = true;
				this->whereToEndRoll = 18;
				break;
			case direction::left: 
				this->sprite.move(-14.f, 0.f);
				this->hitbox.move(-14.f, 0.f);
				this->startPoint = 50;
				this->endPoint = 54;
				this->unstopable_r = true;
				this->whereToEndRoll = 12;
				break;
			case direction::top: 
				this->sprite.move(0.f, -14.f);
				this->hitbox.move(0.f, -14.f);
				this->startPoint = 45;
				this->endPoint = 49;
				this->unstopable_r = true;
				this->whereToEndRoll = 6;
				break;
			}
		}
		this->timeElapsedR = 0;
	}
	if (this->unstopable_r == true) {
		this->animation.rollAnimation(this->startPoint, this->endPoint, this->whereToEndRoll, delta, this->unstopable_r, this->timeElapsedR);
		this->sprite.setTextureRect(this->animation.uvRect);
	}
}

void player::updateAtack(double delta)
{
	this->timeElapsedA += delta;
	if (this->timeElapsedA > 0.25) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {

			switch (this->direction)
			{
			case direction::right:
				this->startPoint = 24;
				this->endPoint = 27;
				this->unstopable_r = true;
				this->whereToEndRoll = 0;
				break;
			case direction::bottom:
				this->startPoint = 36;
				this->endPoint = 39;
				this->unstopable_r = true;
				this->whereToEndRoll = 18;
				break;
			case direction::left:
				this->startPoint = 32;
				this->endPoint = 35;
				this->unstopable_r = true;
				this->whereToEndRoll = 12;
				break;
			case direction::top:
				this->startPoint = 28;
				this->endPoint = 31;
				this->unstopable_r = true;
				this->whereToEndRoll = 6;
				break;
			}
		}
		this->timeElapsedA = 0;
	}
	/*
	if (this->unstopable_a == true) {
		this->animation.attackAnimationn(this->startPoint, this->endPoint, this->whereToEndRoll, delta, this->unstopable_a, this->timeElapsedA);
		this->sprite.setTextureRect(this->animation.uvRect);
	}
	*/
}

void player::gainPoints(float points)
{
	this->score += points;
}

void player::takeDmg(double delta)
{
	
}

void player::anotherChance()
{
	this->hp = this->maxHp/2;
	this->sprite.setPosition(390, 500);
	this->hitbox.setPosition(this->sprite.getPosition().x + 42, this->sprite.getPosition().y + 38);
	this->score /= 2;
}

void player::update(double delta)
{
	this->updateMovementAndAnimation(delta);
	this->updateRoll(delta);
	this->updateAtack(delta);
}

void player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	target.draw(this->hitbox);
	//this->hitbox.render(target);
}


