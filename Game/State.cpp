#include "State.h"

void State::updateMousePosition()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

State::State(sf::RenderWindow* window, sf::Font* font, std::stack<State*>* states) :window{ window }, font{ font }, states{ states }
{
}

State::~State()
{
}
