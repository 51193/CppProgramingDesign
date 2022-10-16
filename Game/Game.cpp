#include "Game.h"

void Game::init()
{
	this->initWindow();
	this->initFont();
	this->initStates();
}

void Game::initWindow()
{
	std::string title;
	sf::VideoMode window_bounds;
	unsigned int framerate_limit;
	bool vertical_sync_enabled;
	unsigned int antialiasing_level;
	bool isfullscreen;

	sf::ContextSettings window_settings;

	std::ifstream input("Config/WindowSetting.ini", std::ios::in);

	if (input.is_open()) {

		std::getline(input, title);
		input >> window_bounds.width >> window_bounds.height;
		input >> isfullscreen;
		input >> framerate_limit;
		input >> vertical_sync_enabled;
		input >> antialiasing_level;

		window_settings.antialiasingLevel = antialiasing_level;
		
		if (isfullscreen) {
			this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, window_settings);
		}
		else {
			this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, window_settings);
		}

		this->window->setFramerateLimit(framerate_limit);
		this->window->setVerticalSyncEnabled(vertical_sync_enabled);
	}
	else {
		std::ofstream output("Config/WindowSetting.ini", std::ios::out);
		output << "Game" << std::endl;
		output << sf::VideoMode::getDesktopMode().width << std::endl;
		output << sf::VideoMode::getDesktopMode().height << std::endl;
		output << false << std::endl;
		output << 120 << std::endl;
		output << false << std::endl;
		output << 0 << std::endl;
		output.close();

		initWindow();
	}

	input.close();
}

void Game::initFont()
{
	this->font = new sf::Font;

	std::ifstream input("Fonts/Font.ini", std::ios::in);
	std::string font_path;
	char buffer;

	if (input.is_open()) {

		buffer = input.get();
		while (buffer != EOF && buffer != '\n') {
			font_path += buffer;
			buffer = input.get();
		}

		if (this->font->loadFromFile(font_path)) {
			std::cout << "font loaded" << std::endl;
		}
	}
	else {
		std::cout << "fail open Fonts/font.ini" << std::endl;
	}

	input.close();
}

void Game::initStates()
{
	states.push(new MainMenu(window, font, &states));
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvent()
{
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->window->close();
		}
	}
}

Game::Game()
{
	this->init();
}

Game::~Game()
{
	delete this->window;
	delete this->font;
	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

void Game::update()
{
	this->updateDt();
	this->updateSFMLEvent();

	this->states.top()->update(this->dt);
}

void Game::render()
{
	this->window->clear();

	this->states.top()->render(this->window);

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}
}
