#include "Monster.h"

std::map<std::string, MonsterTemplate*> Monster::monster_lib;

void Monster::init()
{
	if (!monster_lib.count(this->name)) {
		this->initTemplate();
	}
	this->monster_data = new MonsterData(*monster_lib[this->name]->monster_data);
	this->animation_component = new AnimationComponent(this->sprite, *monster_lib[this->name]->animation_template);
}

void Monster::initTemplate()
{
	monster_lib[this->name] = new MonsterTemplate(this->name);
}

void Monster::updatePosition(sf::Vector2f offset, sf::Vector2f path_net_size)
{
	this->exact_pos = offset + sf::Vector2f(this->position.x * path_net_size.x, this->position.y * path_net_size.y);
}

void Monster::updateExactPos()
{
	this->sprite.setPosition(
		this->exact_pos -
		sf::Vector2f(this->sprite.getGlobalBounds().width / 2,
			this->sprite.getGlobalBounds().height / 2));
}

Monster::Monster(std::string name, unsigned int x, unsigned int y)
	:name{ name },
	position_on_pathnet{x, y},
	position{ (float)x, (float)y }
{
	this->init();
}

Monster::~Monster()
{
	delete this->animation_component;
	delete this->monster_data;
}

sf::Vector2f Monster::getPosition()
{
	return this->position;
}

void Monster::setPostion(sf::Vector2f position)
{
	this->position = position;
}

sf::Vector2f Monster::getExactPos()
{
	return this->exact_pos;
}

void Monster::setExactPos(sf::Vector2f exact_pos)
{
	this->exact_pos = exact_pos;
}

void Monster::update(const float& dt, sf::Vector2f offset, sf::Vector2f path_net_size)
{
	this->updatePosition(offset, path_net_size);
	this->updateExactPos();
}

void Monster::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
