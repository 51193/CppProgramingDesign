#ifndef STATE_H
#define STATE_H

#include<stack>

#include"Button.h"
#include"BattleField.h"

class State
{
protected:

	sf::RenderWindow* window;
	sf::Font* font;

	std::stack<State*>* states;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	void updateMousePosition();//更新鼠标位置

	virtual void init() = 0;
	
public:

	State(sf::RenderWindow* window, sf::Font* font, std::stack<State*>* states);
	virtual ~State();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
};

#endif