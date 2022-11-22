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

	this->initLaser();
}

void Tower::initTemplate()
{
	tower_lib[this->name] = new TowerTemplate(this->name);
	this->init();
}

void Tower::initLaser()
{
	this->laser_beam.setFillColor(sf::Color::Color(0, 204, 204, 255));
	this->laser_beam.setOutlineColor(sf::Color::Color(0, 102, 102, 128));
	this->laser_beam.setOutlineThickness(3.f);
	this->laser_beam.setSize(sf::Vector2f(0, 0));
}

void Tower::updateAiming(const sf::Vector2u& position, const sf::Vector2u& path_net_count, std::vector<Monster*> monsters)
{
	if (this->target != nullptr) {
		this->target = nullptr;
	}

	unsigned int cur{ (unsigned int)this->tower_data->range };

	for (auto& i : monsters) {
		if ((unsigned int)sqrt(
			(i->getPositiononPathNet().x - (position.x * path_net_count.x + path_net_count.x / 2)) * (i->getPositiononPathNet().x - (position.x * path_net_count.x + path_net_count.x / 2)) +
			(i->getPositiononPathNet().y - (position.y * path_net_count.y + path_net_count.y / 2)) * (i->getPositiononPathNet().y - (position.y * path_net_count.y + path_net_count.y / 2)))
			< cur) {

			cur = (unsigned int)sqrt(
				(i->getPositiononPathNet().x - (position.x * path_net_count.x + path_net_count.x / 2)) * (i->getPositiononPathNet().x - (position.x * path_net_count.x + path_net_count.x / 2)) +
				(i->getPositiononPathNet().y - (position.y * path_net_count.y + path_net_count.y / 2)) * (i->getPositiononPathNet().y - (position.y * path_net_count.y + path_net_count.y / 2)));

			this->target = i;
		}
	}
}

void Tower::updateAttack(const float& dt)
{
	if (this->target != nullptr) {
		this->state = ActiveState;
		if (this->target->getExactPos().x <= this->muzzle.x) {
			this->laser_beam.setPosition(this->target->getExactPos());
			this->laser_beam.setSize(sf::Vector2f(
				(float)sqrt(
					(this->target->getExactPos().x - this->muzzle.x) * (this->target->getExactPos().x - this->muzzle.x) +
					(this->target->getExactPos().y - this->muzzle.y) * (this->target->getExactPos().y - this->muzzle.y)),
				3.f));
			this->laser_beam.setRotation((float)atan((this->muzzle.y - this->target->getExactPos().y) / (this->muzzle.x - this->target->getExactPos().x)) * (180.f / (float)3.14));
		}
		else {
			this->laser_beam.setPosition(this->muzzle);
			this->laser_beam.setSize(sf::Vector2f(
				(float)sqrt(
					(this->target->getExactPos().x - this->muzzle.x) * (this->target->getExactPos().x - this->muzzle.x) +
					(this->target->getExactPos().y - this->muzzle.y) * (this->target->getExactPos().y - this->muzzle.y)),
				3.f));
			this->laser_beam.setRotation((float)atan((this->target->getExactPos().y - this->muzzle.y) / (this->target->getExactPos().x - this->muzzle.x)) * (180.f / (float)3.14));
		}
		this->target->getDamage(this->tower_data->damage * dt);
	}
	else {
		this->state = IdleState;
		this->laser_beam.setSize(sf::Vector2f(0.f, 0.f));
	}
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
	state{ IdleState },
	muzzle{ 0.f, 0.f }
{
	this->init();
	this->playingAnimation(0);
}

Tower::Tower(std::string name, unsigned short int exist_mode, const sf::Vector2f& muzzle)
	:name{ name },
	exist_mode{ exist_mode },
	state{ IdleState },
	muzzle{ muzzle }
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

void Tower::update(const float& dt, const sf::Vector2u& position, const sf::Vector2u& path_net_count, std::vector<Monster*> monsters)
{
	this->updateAiming(position, path_net_count, monsters);
	this->updateAttack(dt);
	this->playingAnimation(dt);
}

void Tower::update(const float& dt)
{
	this->playingAnimation(dt);
}

void Tower::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	target->draw(this->laser_beam);
}
