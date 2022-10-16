#include "MainMenu.h"

void MainMenu::init()
{
	this->initButtons();
	this->initBackground();
}

void MainMenu::initButtons()
{
	this->buttons["NewGame"] = new Button(
		((float)this->window->getSize().x - (float)this->window->getSize().x / (float)5.12) / 2.f,
		(float)this->window->getSize().y / 3.f,
		(float)this->window->getSize().x / (float)5.12,
		(float)this->window->getSize().y / 8.f,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(192, 192, 192), sf::Color(255, 255, 255), sf::Color(255, 215, 0),
		font, "New Game");

	this->buttons["Settings"] = new Button(
		((float)this->window->getSize().x - (float)this->window->getSize().x / (float)5.12) / 2.f,
		(float)this->window->getSize().y / (float)2.1,
		(float)this->window->getSize().x / (float)5.12,
		(float)this->window->getSize().y / 8.f,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(192, 192, 192), sf::Color(255, 255, 255), sf::Color(255, 215, 0),
		font, "Settings");

	this->buttons["Quit"] = new Button(
		((float)this->window->getSize().x - (float)this->window->getSize().x / (float)5.12) / 2.f,
		(float)this->window->getSize().y / (float)1.6,
		(float)this->window->getSize().x / (float)5.12,
		(float)this->window->getSize().y / 8.f,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(192, 192, 192), sf::Color(255, 255, 255), sf::Color(255, 215, 0),
		font, "Quit");
}

void MainMenu::initBackground()
{
	this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setFillColor(sf::Color::White);

	this->background.setSize(
		sf::Vector2f
		(static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)));

	if (!this->bg_texture.loadFromFile("Resources\\Images\\Backgrounds\\MainMenu_bg1.png")) {
		std::cout << "Fail to load main menu background" << std::endl;
	}
	this->background.setTexture(&this->bg_texture);
}

void MainMenu::updateButtons()
{
	for (auto& it : this->buttons) {
		it.second->update(this->mousePosView);
	}

	if (buttons["NewGame"]->isPressed()) {
		states->push(new GameState(this->window, this->font, this->states));
	}
	else if (buttons["Settings"]->isPressed()) {

	}
	else if (buttons["Quit"]->isPressed()) {
		this->window->close();
	}
}

void MainMenu::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons) {
		it.second->render(*target);
	}
}

void MainMenu::renderBackground(sf::RenderTarget* target)
{
	target->draw(this->background);
}

MainMenu::MainMenu(sf::RenderWindow* window, sf::Font* font, std::stack<State*>* states) : State(window, font, states)
{
	this->init();
}

MainMenu::~MainMenu()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); it++) {
		delete it->second;
	}
}

void MainMenu::update(const float& dt)
{
	this->updateMousePosition();
	this->updateButtons();
}

void MainMenu::render(sf::RenderTarget* target)
{
	this->renderBackground(target);
	this->renderButtons(target);
}
