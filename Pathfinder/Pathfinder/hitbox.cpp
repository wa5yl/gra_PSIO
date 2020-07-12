#include "hitbox.h"

hitboxComponent::hitboxComponent(sf::Sprite& sprite, float off_x, float off_y, float width, float height):
	sprite(sprite), off_X(off_x), off_Y(off_y)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + off_x, this->sprite.getPosition().y + off_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);
}

hitboxComponent::~hitboxComponent()
{
}

void hitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->off_X, this->sprite.getPosition().y + this->off_Y);
}

void hitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
