#include "game.h"
#include <vector>

void game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Pathfinder");
	this->window->setFramerateLimit(20);
}

void game::initVariables()
{
	this->font.loadFromFile("fonts/PixellettersFull.ttf");
	
	this->text.setFont(this->font);
	this->text.setCharacterSize(24);
	this->text.setFillColor(sf::Color::White);
	this->text.setString("NONE");

	this->texture.loadFromFile("tekstury/buttonn.jpg");
	this->rescueButton.setTexture(this->texture);
	this->rescueButton.setTextureRect(sf::IntRect(0,0,300,100));
	this->rescueButton.setPosition(400, 300);

	this->timeElapsed = 0;
	this->maxEnemies = 1;
	this->end = false;
}

void game::initEnemies()
{
	if (this->enemies.size() == 0) {
		this->nextLevel();
		for (int i = 0; i < this->maxEnemies; i++) {
			enemies.emplace_back(std::make_unique<george>());
			enemies.emplace_back(std::make_unique<bigBen>());
		}
	}
}

game::game()
{
	this->initWindow();
	this->initVariables();
}

game::~game()
{
	delete this->window;
}

void game::pollEvent(double delta)
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window->close();
		else if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}


void game::updatePlayer(double delta)
{
	this->player.update(delta);
}

void game::updateEnemies(double delta)
{
	for (auto& e : this->enemies) {
		e->update(this->player.hitbox.getPosition().x, this->player.hitbox.getPosition().y, delta, this->player.fireballHits);
	}
}

void game::updateText()
{
	std::stringstream ss;

	this->text.setPosition(5 , 0);

	ss << "Points: " << this->player.score << "\n"
		<< "Health: "  << this->player.hp <<"\n";

	this->text.setString(ss.str());

	if (this->end == true) {
		ss << "Press button to revive yourself. You' ll lose half of your points,"<<"\n"<<" and start another attempt with 50% of your max hp" << "\n"
			<< "your score::" << this->player.score;
		this->text.setPosition(30, 150);
		this->text.setFillColor(sf::Color::Red);
		this->text.setString(ss.str());
	}
}

void game::updateMouse()
{
	this->mousePosition = sf::Mouse::getPosition(*this->window);
	this->mousePositionView = this->window->mapPixelToCoords(this->mousePosition);
}

void game::moveToPlayer()
{
	for (auto& e : this->enemies) {
		if (e->canIMove == true) {
			e->moveVec.x = this->player.hitbox.getPosition().x - e->sprite.getPosition().x;
			e->moveVec.y = this->player.hitbox.getPosition().y - e->sprite.getPosition().y;

			e->vecLangth = sqrt(pow(e->moveVec.x, 2) + pow(e->moveVec.y, 2));
			e->moveVec /= e->vecLangth;

			if (e->sprite.getPosition() != this->player.hitbox.getPosition()) {
				e->sprite.move(e->moveVec.x, e->moveVec.y);
				e->hpBar.move(e->moveVec.x, e->moveVec.y);
			}
		}
	}
}

void game::attackEnemy(double delta)
{
	this->timeElapsed += delta;
	if (this->timeElapsed > 0.5) {
		this->timeElapsed = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
			switch (player.direction) {
			case player::direction::left:
				for (auto& e : this->enemies) {
					if ((this->player.sprite.getPosition().y < e->sprite.getPosition().y + e->sprite.getGlobalBounds().height / 2 &&
						this->player.sprite.getPosition().y > e->sprite.getPosition().y ||
						this->player.sprite.getPosition().y + this->player.sprite.getGlobalBounds().height >= e->sprite.getPosition().y &&
						this->player.sprite.getPosition().y < e->sprite.getPosition().y) &&
						(this->player.sprite.getPosition().x - e->sprite.getPosition().x < 70 &&
							this->player.sprite.getPosition().x - e->sprite.getPosition().x > 0)
						) {
						e->takeDmg(this->player.dmg);
					}
				}
				break;
			case player::direction::right:
				for (auto& e : this->enemies) {
					if ((this->player.sprite.getPosition().y < e->sprite.getPosition().y + e->sprite.getGlobalBounds().height / 2 &&
						this->player.sprite.getPosition().y > e->sprite.getPosition().y ||
						this->player.sprite.getPosition().y + this->player.sprite.getGlobalBounds().height >= e->sprite.getPosition().y &&
						this->player.sprite.getPosition().y < e->sprite.getPosition().y) &&
						((e->sprite.getPosition().x - this->player.sprite.getPosition().x) < 70 + this->player.sprite.getGlobalBounds().width / 2.4 &&
							this->player.sprite.getPosition().x - e->sprite.getPosition().x < 0)
						) {
						e->takeDmg(this->player.dmg);
					}
				}
				break;
			case player::direction::top:
				for (auto& e : this->enemies) {
					if ((this->player.sprite.getPosition().x < e->sprite.getPosition().x + e->sprite.getGlobalBounds().width / 6 &&
						this->player.sprite.getPosition().x > e->sprite.getPosition().x ||
						this->player.sprite.getPosition().x + this->player.sprite.getGlobalBounds().width >= e->sprite.getPosition().x &&
						this->player.sprite.getPosition().x < e->sprite.getPosition().x) &&
						(this->player.sprite.getPosition().y - e->sprite.getPosition().y < 70 &&
							this->player.sprite.getPosition().y - e->sprite.getPosition().y > 0)
						) {
						e->takeDmg(this->player.dmg);
					}
				}
				break;
			case player::direction::bottom:
				for (auto& e : this->enemies) {
					if ((this->player.sprite.getPosition().x < e->sprite.getPosition().x + e->sprite.getGlobalBounds().width / 6 &&
						this->player.sprite.getPosition().x > e->sprite.getPosition().x ||
						this->player.sprite.getPosition().x + this->player.sprite.getGlobalBounds().width >= e->sprite.getPosition().x &&
						this->player.sprite.getPosition().x < e->sprite.getPosition().x) &&
						((e->sprite.getPosition().y - this->player.sprite.getPosition().y) < 70 + this->player.sprite.getGlobalBounds().height / 2.4 &&
							this->player.sprite.getPosition().y - e->sprite.getPosition().y < 0)
						) {
						e->takeDmg(this->player.dmg);
					}
				}
				break;
			}
		}

		for (int i = 0; i < this->enemies.size(); i++) {
			if (enemies[i]->amIDead == true) {
				this->player.gainPoints(enemies[i]->points);
				enemies.erase(this->enemies.begin() + i);
			}
		}
	}
}

void game::nextLevel()
{
	this->maxEnemies *= 2;
}

void game::collisionWithEnemy(double delta)
{
	this->player.immunityToDmg += delta;
	if (this->player.immunityToDmg > 1) {
		this->player.immunityToDmg = 0;
		for (int i = 0; i < this->enemies.size(); i++) {
			if (this->player.hitbox.getGlobalBounds().intersects(this->enemies[i]->sprite.getGlobalBounds())) {
				this->player.hp -= 20;
			}
			if (this->enemies[i]->mageId == true) {
				for (int j = 0; j < this->enemies[i]->fireballs.size(); j++) {
					if (this->player.hitbox.getGlobalBounds().intersects(this->enemies[i]->fireballs[j]->sprite.getGlobalBounds())) {
						this->player.hp -= 11;
						this->enemies[i]->fireballs.erase(this->enemies[i]->fireballs.begin() + j);
					}
				}
			}
		/*
			for (int j = 0; j < this->enemies[i]->fireballs.size(); j++) {
				if (this->player.hitbox.getGlobalBounds().intersects(this->enemies[i]->fireballs[j]->sprite.getGlobalBounds())) {
					this->player.hp -= 11;
					this->enemies[i]->fireballs.erase(this->enemies[i]->fireballs.begin() + j);
				}
			}
			*/
		}
	}
}

void game::mapCollision()
{
	if (this->player.hitbox.getPosition().y <= 0 ||
		this->player.hitbox.getPosition().y + this->player.hitbox.getGlobalBounds().height >= 600 ||
		this->player.hitbox.getPosition().x <= 0 ||
		this->player.hitbox.getPosition().x + this->player.hitbox.getGlobalBounds().width >= 800
		) {
		this->player.hp--;
	}

}

void game::endGame()
{
	if (this->player.hp <= 0) {
		this->end = true;
	}
}

void game::acceptRescue()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->rescueButton.getGlobalBounds().contains(this->mousePositionView)) {
			this->end = false;
			this->player.anotherChance();
		}
	}
}

void game::upadete(double delta)
{
	if (this->end == false) {

		this->initEnemies();
		this->pollEvent(delta);
		this->updatePlayer(delta);
		this->updateEnemies(delta);

		this->updateText();
		this->moveToPlayer();
		this->attackEnemy(delta);
		this->collisionWithEnemy(delta);
		this->mapCollision();
		this->endGame();
	}
	else {
		this->updateText();
		this->pollEvent(delta);
		this->updateMouse();
		this->acceptRescue();
	}
}


void game::renderPlayer()
{
	this->player.render(*window);
}


void game::renderEnemies()
{
	for (auto& e : this->enemies) {
		e->render(*window);
	}
}


void game::render()
{
	this->window->clear();

	if (this->end == false) {
		this->renderPlayer();
		this->renderEnemies();
	}
	else {
		this->window->draw(this->rescueButton);
	}

	this->window->draw(this->text);

	this->window->display();
}

const bool game::runnin() const
{
	return this->window->isOpen();
}
