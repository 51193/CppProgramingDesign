#ifndef GAME_H
#define GAME_H

#include"MainMenu.h"

class Game
{
private:

	//窗口相关变量

	sf::RenderWindow* window;

	//事件变量

	sf::Event event;

	//窗口刷新相关变量

	sf::Clock dtClock;
	float dt;

	//字体变量

	sf::Font* font;

	//State变量

	std::stack<State*>states;

	//初始化

	void init();

	void initWindow();
	void initFont();
	void initStates();

	//零散update函数

	void updateDt();
	void updateSFMLEvent();

public:
	//构造函数与析构函数

	Game();
	~Game();

	//功能函数

	void update();
	void render();
	void run();

};

#endif GAME_H