#ifndef TITLE_H
#define TITLE_H

#include<iostream>

#include"Button.h"
#include"Tower.h"

class Title
{
private:

	sf::RenderWindow* window;
	sf::Font* font;

	std::vector<sf::RectangleShape*>title_background;//背景墙，后面可以改用sf::Texture

	std::vector<Tower*>tower_list;//储存可用卡片的顺序表
	size_t max_tower_count;//炮塔卡片数量上限

	std::vector<Button*>buttons;

	float title_height;//该Title的高度，可用于初始化BattleField的高度

	void init();
	void initTitleBoard();
	void initButtons();

	void updateTowerList(const float& dt);
	void updateButtons(const sf::Vector2f mousePos);

	void renderTitleBoard(sf::RenderTarget* target);
	void renderTowerList(sf::RenderTarget* target);
	void renderButtons(sf::RenderTarget* target);//不必要的函数，用来debug
public:
	Title(sf::RenderWindow* window, sf::Font* font);
	~Title();

	void setMaxTowerCount(size_t x);//修改卡片槽的卡片上限

	std::vector<Tower*>* getTowerList();//获取卡片槽，返回值是一个装满Tower*的vector
	float getHeight();//获取卡片槽高度
	sf::Vector2f getRectSize();//获取单个卡槽大小

	Tower* getPressed();//获取被点击的卡槽，返回其中的Tower*

	void insertTower(const std::string& name);//插入炮塔卡片，直接插就行，其他必要检测和修改都包含在该函数内

	void update(const float& dt, const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};

#endif