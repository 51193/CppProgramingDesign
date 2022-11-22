#include "GameState.h"

void GameState::init()
{
	this->initBackground();
	this->initTowerRange();

	this->initTitle();
	this->initCards();

	this->initBattleField();

	this->initMoneyText();
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
	std::vector<sf::Vector2u>ends;
	ends.push_back(sf::Vector2u(11, 4));
	this->battle_field = new BattleField(this->title->getHeight(), this->window, sf::Vector2u(12, 9), sf::Vector2u(20, 15), ends);

	this->battle_field->updateWhenTowerChanging();
}

void GameState::initMoneyText()
{
	this->text.setFont(*this->font);
	this->text.setString(std::to_string(this->money));
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(this->window->getSize().y / 20);
	this->text.setPosition(0, 0);
	this->text.setFillColor(sf::Color::Black);
}

void GameState::updateStretchedTower()
{
	if (money >= 20) {
		if (this->title->getPressed() != nullptr && this->stretched_tower == nullptr) {
			this->stretched_tower = new Tower(this->title->getPressed()->getName(), CardMode);
			this->stretched_tower->setScale(this->title->getRectSize());
			this->tower_range->setRadius(this->stretched_tower->getRange() * (this->battle_field->getChunkSize().x / this->battle_field->getPathNetCount().x));
		}
		else if (this->title->getPressed() != nullptr && this->stretched_tower != nullptr) {
			if (this->stretched_tower->getName() != this->title->getPressed()->getName()) {
				delete this->stretched_tower;
				this->stretched_tower = new Tower(this->title->getPressed()->getName(), CardMode);
				this->stretched_tower->setScale(this->title->getRectSize());
				this->tower_range->setRadius(this->stretched_tower->getRange() * (this->battle_field->getChunkSize().x / this->battle_field->getPathNetCount().x));
			}
		}

		if (this->stretched_tower != nullptr) {
			this->stretched_tower->moveto(this->mousePosView - sf::Vector2f(this->title->getRectSize().x / 2, this->title->getRectSize().y / 2));
			this->tower_range->setPosition(this->mousePosView - sf::Vector2f(this->tower_range->getRadius(), this->tower_range->getRadius()));
		}
	}
}

void GameState::updatePlantTower()
{
	if (this->stretched_tower != nullptr &&
		this->battle_field->getPressed() != nullptr &&
		this->battle_field->getPressed()->getTower() == nullptr &&
		!this->battle_field->getPressed()->isOccupiedByMonster(this->battle_field->getMonsterList(), this->battle_field->getPathNetCount()) &&
		this->battle_field->getPressed()->getPosition().x != 0 &&
		!(this->battle_field->getPressed()->getPosition().x == 11 && this->battle_field->getPressed()->getPosition().y == 4))
	{

		this->battle_field->getPressed()->setTower(this->stretched_tower->getName());
		this->battle_field->updateWhenTowerChanging();

		delete this->stretched_tower;
		this->stretched_tower = nullptr;
		this->tower_range->setRadius(0.f);

		this->money -= 20;
	}
}

void GameState::updateMoney()
{
	this->money += this->battle_field->getMoney();

	this->text.setString(std::to_string(this->money));
}

void GameState::updateGameover()
{
	if (this->battle_field->isLose()) {
		this->states->pop();
	}
}

void GameState::renderBackground(sf::RenderTarget* target)
{
	target->draw(*(this->background));
}

GameState::GameState(sf::RenderWindow* window, sf::Font* font, std::stack<State*>* states)
	:State{ window, font, states },
	stretched_tower{ nullptr },
	money{ 20 }
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

	this->updateMoney();

	this->updateGameover();
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

	target->draw(this->text);
}
