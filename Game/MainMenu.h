#ifndef MAINMENU_H
#define MAINMENU

#include "GameState.h"

class MainMenu :
    public State
{
protected:

	//变量

	sf::Texture bg_texture;
	sf::RectangleShape background;
	std::map<std::string, Button*>buttons;

	//函数

	void init();

	void initButtons();
	void initBackground();

	//update函数

	void updateButtons();

	//render函数

	void renderButtons(sf::RenderTarget* target);
	void renderBackground(sf::RenderTarget* target);

public:

	MainMenu(sf::RenderWindow* window, sf::Font* font, std::stack<State*>* states);
	~MainMenu();

	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

#endif