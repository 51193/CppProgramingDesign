#include "Title.h"

Title::Title(sf::RenderWindow* window, sf::Font* font)
	:window{ window },
	font{ font },
	max_tower_count { 15 },
	title_height{ 0 }
{
	this->init();
}

Title::~Title()
{
	while (!this->tower_list.empty()) {
		delete* (this->tower_list.rbegin());
		this->tower_list.pop_back();
	}

	while (!this->title_background.empty()) {
		delete* (this->title_background.rbegin());
		this->title_background.pop_back();
	}

	while (!this->buttons.empty()) {
		delete* (this->buttons.rbegin());
		this->buttons.pop_back();
	}
}

void Title::updateButtons(const sf::Vector2f mousePos)
{
	for (size_t i{ 0 }; i < this->buttons.size(); i++) {
		this->buttons[i]->update(mousePos);
	}
}

void Title::setMaxTowerCount(size_t x)
{
	this->max_tower_count = x;
}

std::vector<Tower*>* Title::getTowerList()
{
	return &(this->tower_list);
}

void Title::renderButtons(sf::RenderTarget* target)
{
	for (auto& i:this->buttons) {
		i->render(*target);
	}
}

void Title::insertTower(const std::string& name)
{
	if (this->tower_list.size() < this->max_tower_count) {
		this->tower_list.push_back(new Tower(name, CardMode));
	}
	else NULL;

	for (size_t i{ 0 }; i < this->tower_list.size(); i++) {
		this->tower_list[i]->moveto(this->title_background[i]->getPosition());
		this->tower_list[i]->setScale(this->title_background[i]->getSize());
	}
	
	this->buttons[this->tower_list.size() - 1]->moveto(
		this->title_background[this->tower_list.size() - 1]->getPosition().x,
		this->title_background[this->tower_list.size() - 1]->getPosition().y);

}

void Title::init()
{
	this->initTitleBoard();
	this->initButtons();
}

void Title::initTitleBoard()
{

	float a = (float)0.6;//表示顶部宽度占窗口宽度的比例，设为变量方便调试

	float global_width = this->window->getSize().x * a;
	float width = global_width / this->max_tower_count;
	float height = width * (4.f / 3.f);

	this->title_height = height;

	float start_x{ this->window->getSize().x * ((1 - a) / 2) };

	for (size_t i{ 0 }; i < this->max_tower_count; i++) {
		this->title_background.push_back(new sf::RectangleShape(sf::Vector2f(width,height)));
		(*(this->title_background.rbegin()))->setPosition(sf::Vector2f(start_x + width * i, 1.f));
	}
	for (auto& i : this->title_background) {
		i->setFillColor(sf::Color::White);
		i->setOutlineColor(sf::Color::Black);
		i->setOutlineThickness(1.f);
	}
}

void Title::updateTowerList(const float& dt)
{
	for (auto& i : this->tower_list) {
		i->update(dt);
	}
}

void Title::renderTitleBoard(sf::RenderTarget* target)
{
	for (auto& i : this->title_background) {
		target->draw(*i);
	}
}

void Title::initButtons()
{
	for (size_t i{ 0 }; i < this->title_background.size(); i++) {
		buttons.push_back(new Button(
			(float)this->window->getSize().x, (float)this->window->getSize().y,
			this->title_background[0]->getGlobalBounds().width, this->title_background[0]->getGlobalBounds().height,
			sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
			sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,
			this->font,
			" ",
			false));
	}
}

void Title::renderTowerList(sf::RenderTarget* target)
{
	for (auto& i : this->tower_list) {
		i->render(target);
	}
}

void Title::update(const float& dt, const sf::Vector2f mousePos)
{
	this->updateTowerList(dt);
	this->updateButtons(mousePos);
}

void Title::render(sf::RenderTarget* target)
{
	this->renderTitleBoard(target);
	this->renderTowerList(target);
	this->renderButtons(target);//button没有渲染的必要，仅作鼠标检测使用
}

sf::Vector2f Title::getRectSize()
{
	return this->title_background[0]->getSize();
}

float Title::getHeight()
{
	return this->title_height;
}

Tower* Title::getPressed()
{
	for (size_t i{ 0 }; i < this->tower_list.size(); i++) {
		if (this->buttons[i]->isPressed())return this->tower_list[i];
	}
	return nullptr;
}
