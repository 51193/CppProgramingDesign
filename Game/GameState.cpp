#include "GameState.h"

void GameState::init()
{
	this->initBackground();
	this->initTowerRange();

	this->initTitle();
	this->initCards();

	this->initBattleField();
}

void GameState::initBackground()
{
	this->background = new sf::RectangleShape(sf::Vector2f(0.f, 0.f));
	this->background->setSize(sf::Vector2f((float)this->window->getSize().x, (float)this->window->getSize().y));
	this->background->setFillColor(sf::Color::White);
}

void GameState::initTowerRange()
{
	this->tower_range = new sf::CircleShape(0.f, 128);
	this->tower_range->setFillColor(sf::Color::Color(200, 200, 200, 64));
	this->tower_range->setOutlineColor(sf::Color::Black);
	this->tower_range->setOutlineThickness(1.f);
}

void GameState::initTitle()
{
	this->title = new Title(this->window, this->font);
}

void GameState::initCards()
{
	this->title->insertTower("test");
}

void GameState::initBattleField()
{
	this->battle_field = new BattleField(this->title->getHeight(), this->window, sf::Vector2i(12, 9), sf::Vector2i(20, 15));
}

void GameState::updateStretchedTower()
{
	if (this->title->getPressed() != nullptr && this->stretched_tower == nullptr) {
		this->stretched_tower = new Tower(this->title->getPressed()->getName(), CardMode);
		this->stretched_tower->setScale(this->title->getRectSize());
		this->tower_range->setRadius(this->stretched_tower->getRangeinWindow(this->window));
	}
	else if (this->title->getPressed() != nullptr && this->stretched_tower != nullptr) {
		if (this->stretched_tower->getName() != this->title->getPressed()->getName()) {
			delete this->stretched_tower;
			this->stretched_tower = new Tower(this->title->getPressed()->getName(), CardMode);
			this->stretched_tower->setScale(this->title->getRectSize());
			this->tower_range->setRadius(this->stretched_tower->getRangeinWindow(this->window));
		}
	}

	if (this->stretched_tower != nullptr) {
		this->stretched_tower->moveto(this->mousePosView - sf::Vector2f(this->title->getRectSize().x / 2, this->title->getRectSize().y / 2));
		this->tower_range->setPosition(this->mousePosView - sf::Vector2f(this->tower_range->getRadius(), this->tower_range->getRadius()));
	}
}

void GameState::updatePlantTower()
{
	if (this->stretched_tower != nullptr &&
		this->battle_field->getPressed() != nullptr &&
		this->battle_field->getPressed()->getTower() == nullptr) {

		this->battle_field->getPressed()->setTower(this->stretched_tower->getName());
		delete this->stretched_tower;
		this->stretched_tower = nullptr;
		this->tower_range->setRadius(0.f);
	}
}

void GameState::renderBackground(sf::RenderTarget* target)
{
	target->draw(*(this->background));
}

GameState::GameState(sf::RenderWindow* window, sf::Font* font, std::stack<State*>* states)
	:State{ window, font, states },
	stretched_tower{ nullptr }
{
	this->init();
}

GameState::~GameState()
{
	delete this->background;
	delete this->title;
	delete this->battle_field;
	if (this->stretched_tower != nullptr)delete this->stretched_tower;
	if (this->tower_range != nullptr)delete this->tower_range;
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->title->update(dt, this->mousePosView);
	this->updateStretchedTower();
	this->updatePlantTower();
	this->battle_field->update(dt, this->mousePosView);

	if (this->stretched_tower != nullptr)this->stretched_tower->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	this->renderBackground(target);
	this->title->render(target);
	this->battle_field->render(target);

	if (this->stretched_tower != nullptr) {
		this->stretched_tower->render(target);
	}

	target->draw(*this->tower_range);
}
