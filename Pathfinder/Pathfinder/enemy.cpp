#include "enemy.h"

void george::initTexture()
{
	if (!this->texture.loadFromFile("tekstury/georgee.png"))
	{
		std::cout << "Klopot" << "\n";
	}
}

void george::initSprite()
{
	this->sprite.setTexture(texture);
	this->sprite.setPosition(rand() % static_cast<int>(800 - 60),
		200);
	this->sprite.scale(0.1, 0.1);
}

void george::initVariables()
{
	this->points = 100;
	this->hp = 150.f;
	this->maxHp = this->hp;
	this->maxHp = this->sprite.getGlobalBounds().width;
	this->amIDead = false;
	this->canIMove = true;
	this->mageId = false;
	this->hpBar.setSize(sf::Vector2f(this->sprite.getGlobalBounds().width,10));
	this->hpBar.setFillColor(sf::Color::Blue);
	this->hpBar.setPosition(this->sprite.getPosition().x , this->sprite.getPosition().y - 15);
}

george::george()
{
	this->initTexture();
	this->initSprite();
	this->initVariables();
}

george::~george()
{
}

void george::update(float pos_x, float pos_y, double delta, int& hit)
{
}


void enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	target.draw(this->hpBar);
	
}


void enemy::changeHpBar(float dmg)
{
	float percentage;
	percentage = ((dmg * 100) / this->maxHp) / 100;
	this->hpBar.setSize(sf::Vector2f(this->sprite.getGlobalBounds().width * (1 - percentage), 10));

}

void enemy::takeDmg(float dmg)
{
	this->changeHpBar(dmg);	
	//float modyfier = (rand() % 4) + 1;
	this->hp -= dmg;
	std::cout << this->hp << std::endl;
	this->stillAlive();
}

void enemy::stillAlive()
{
	if (this->hp <= 0)
		this->amIDead = true;
}



void bigBen::initTexture()
{
	if (!this->texture.loadFromFile("tekstury/bigBen.png"))
	{
		std::cout << "Klopot" << "\n";
	}
}

void bigBen::initSprite()
{
	this->sprite.setTexture(texture);
	this->sprite.setPosition(rand() % static_cast<int>(800 - 60),
		200);
	this->sprite.scale(0.1, 0.1);
}

void bigBen::initVariables()
{
	this->maxFireballs = 2.f;
	this->hp = 300.f;
	this->maxHp = this->hp;
	this->points = 300;
	this->amIDead = false;
	this->canIMove = false;
	this->elapsedTime = 0;
	this->mageId = true;
	this->hpBar.setSize(sf::Vector2f(this->sprite.getGlobalBounds().width, 10));
	this->hpBar.setFillColor(sf::Color::Blue);
	this->hpBar.setPosition(this->sprite.getPosition().x, this->sprite.getPosition().y - 15);
	
}

bigBen::bigBen() {
	this->initTexture();
	this->initSprite();
	this->initVariables();
}

bigBen::~bigBen()
{
}


void bigBen::update(float pos_x, float pos_y, double delta, int& hit)
{
	this->addFireball(delta);

	for (auto& e : this->fireballs) {
		e->moveVec.x = pos_x - e->sprite.getPosition().x;
		e->moveVec.y = pos_y - e->sprite.getPosition().y;

		e->vecLangth = sqrt(pow(e->moveVec.x, 2) + pow(e->moveVec.y, 2));
		e->moveVec /= e->vecLangth;

		if (e->sprite.getPosition().x != pos_x && e->sprite.getPosition().x != pos_y) {
			e->sprite.move(e->moveVec.x, e->moveVec.y);
		}
	}
}

void bigBen::addFireball(double delta)
{
	this->elapsedTime += delta;
	if (this->elapsedTime > 4) {
		this->elapsedTime = 0;
		if (this->fireballs.size() < this->maxFireballs) {
			this->fireballs.emplace_back(std::make_unique<fireball>(this->sprite.getPosition().x, this->sprite.getPosition().y));
		}
	}
}

void bigBen::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	target.draw(this->hpBar);
	for (auto& f : this->fireballs) {
		f->render(target);
	}
}


