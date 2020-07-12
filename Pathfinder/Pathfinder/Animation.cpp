#include "Animation.h"

void animation::initVariables()
{
	this->imageCount = 60;
	this->totalTimeR = 0.0f;
	this->totalTimeA = 0.0f;
	this->currentImage.x = 0;
	this->switchTime = 0.01;
	this->current = 0;

	if (!this->texture.loadFromFile("tekstury/player.png"))
	{
		std::cout << "Klopot" << "\n";
	}

	this->uvRect.width = this->texture.getSize().x / float(imageCount);
	this->uvRect.height = this->texture.getSize().y / 1.f;
}

animation::animation()
{
	this->initVariables();
}

animation::~animation()
{
}

void animation::updateAnimation(int& startPoint, int endPoint,  double delta, bool key)
{

	if (current != startPoint) {
		currentImage.x = 0;
		std::cout << this->currentImage.x << std::endl;
		//uvRect.left = 0;
	}

	this->current = startPoint;
	this->totalTimeR += delta;

	if (key == true) {
		if (/*this->totalTimeR > this->switchTime*/ true) {
			this->totalTimeR = 0;
			this->currentImage.x++;
			std::cout <<"kolejne iteracj "<<this->currentImage.x << std::endl;
			if (this->currentImage.x >= endPoint - startPoint) {
				//std::cout << this->currentImage.x << std::endl;
				this->currentImage.x = startPoint + 1;
			}
		}
		
	}
	else {
		this->currentImage.x = startPoint;
	}
	
	this->uvRect.left = this->currentImage.x * this->uvRect.width;
	this->uvRect.top = this->currentImage.y * this->uvRect.height;

	this->currentImage.x -= startPoint;
}

void animation::rollAnimation(int& startPoint, int endPoint, int whereToEndRoll,  double delta, bool& unstopable, double& timeElapsed)
{
	if (current != startPoint) {
		currentImage.x = 0;
	}

	this->current = startPoint;
	this->totalTimeR += delta;
	
		if (this->totalTimeR > this->switchTime) {
			this->totalTimeR = 0;
			this->currentImage.x++;
			std::cout << this->currentImage.x << std::endl;
			if (this->currentImage.x >= endPoint - startPoint) {
				unstopable = false;
				//timeElapsed = 0;
				//std::cout << "roll dziala"<< std::endl;
			}
			else {
				this->currentImage.x += current;
			}
		}

		if (unstopable == false) {
			startPoint = whereToEndRoll;
			//std::cout << "roll reset" << std::endl;
		}
	
	this->uvRect.left = this->currentImage.x * this->uvRect.width;
	this->uvRect.top = this->currentImage.y * this->uvRect.height;


	this->currentImage.x -= current;
	
}
/*
void animation::attackAnimationn(int& startPoint, int endPoint, int whereToEndRoll, double delta, bool& unstopable, double& timeElapsedA)
{
	if (current != startPoint) {
		currentImage.x = 0;
	}

	this->current = startPoint;
	this->totalTimeR += delta;

	if (this->totalTimeR > this->switchTime) {
		this->totalTimeR = 0;
		this->currentImage.x ++;
		std::cout << endPoint-startPoint << std::endl;
		if (this->currentImage.x >= endPoint - startPoint) {
			unstopable = false;
			//timeElapsedA = 0;
			std::cout << "atak dziala" << std::endl;
		}
		else {
			this->currentImage.x += current;
		}
	}

	if (unstopable == false) {
		startPoint = whereToEndRoll;
		std::cout << "atak reset" << std::endl;
	}

	this->uvRect.left = this->currentImage.x * this->uvRect.width;
	this->uvRect.top = this->currentImage.y * this->uvRect.height;


	this->currentImage.x -= current;
}

*/

