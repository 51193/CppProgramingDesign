#include "Tower.h"

std::map<std::string, TowerTemplate*> Tower::tower_lib;

void Tower::init()
{
	if (tower_lib.count(this->name)) {
		this->tower_data = new TowerData(*tower_lib[this->name]->tower_data);
		this->animation_component = new AnimationComponent(this->sprite, *tower_lib[this->name]->animation_template);
	}
	else {
		this->initTemplate();
	}
}

void Tower::initTemplate()
{
	tower_lib[this->name] = new TowerTemplate(this->name);
	this->init();
}

void Tower::playingAnimation(const float& dt)
{
	if (this->exist_mode == CardMode) {
		this->animation_component->play("card", dt, false);
	}
	else {
		if (this->state == IdleState) {
			this->animation_component->play("idle", dt, false);
		}
		else if (this->state == ActiveState) {
			this->animation_component->play("active", dt, false);
		}
	}
}

Tower::Tower(std::string name, unsigned short int exist_mode)
	:name{ name },
	exist_mode{ exist_mode },
	state{ IdleState }
{
	this->init();
	this->playingAnimation(0);
}

Tower::~Tower()
{
	delete this->animation_component;
	delete this->tower_data;
}

void Tower::moveto(sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Tower::setScale(sf::Vector2f size)
{
	this->sprite.scale(size.x / this->sprite.getGlobalBounds().width, size.y / this->sprite.getGlobalBounds().height);
}

sf::Vector2f Tower::getSize()
{
	return sf::Vector2f(this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().height);
}

sf::Vector2f Tower::getScale()
{
	return this->sprite.getScale();
}

std::string Tower::getName()
{
	return this->name;
}

float Tower::getRange()
{
	return this->tower_data->range;
}

float Tower::getRangeinWindow(sf::RenderWindow* window)
{
	return this->tower_data->range * ((float)window->getSize().x / 2560.f);
}

float Tower::getDamage()
{
	return this->tower_data->damage;
}

float Tower::getCooldown()
{
	return this->tower_data->cooldown;
}

bool Tower::getAOEBool()
{
	return this->tower_data->isAOE;
}

unsigned short int Tower::getState()
{
	return this->state;
}

void Tower::update(const float& dt)
{
	this->playingAnimation(dt);
}

void Tower::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
