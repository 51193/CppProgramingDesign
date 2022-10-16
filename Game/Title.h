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

	std::vector<sf::RectangleShape*>title_background;//����ǽ��������Ը���sf::Texture

	std::vector<Tower*>tower_list;//������ÿ�Ƭ��˳���
	size_t max_tower_count;//������Ƭ��������

	std::vector<Button*>buttons;

	float title_height;//��Title�ĸ߶ȣ������ڳ�ʼ��BattleField�ĸ߶�

	void init();
	void initTitleBoard();
	void initButtons();

	void updateTowerList(const float& dt);
	void updateButtons(const sf::Vector2f mousePos);

	void renderTitleBoard(sf::RenderTarget* target);
	void renderTowerList(sf::RenderTarget* target);
	void renderButtons(sf::RenderTarget* target);//����Ҫ�ĺ���������debug
public:
	Title(sf::RenderWindow* window, sf::Font* font);
	~Title();

	void setMaxTowerCount(size_t x);//�޸Ŀ�Ƭ�۵Ŀ�Ƭ����

	std::vector<Tower*>* getTowerList();//��ȡ��Ƭ�ۣ�����ֵ��һ��װ��Tower*��vector
	float getHeight();//��ȡ��Ƭ�۸߶�
	sf::Vector2f getRectSize();//��ȡ�������۴�С

	Tower* getPressed();//��ȡ������Ŀ��ۣ��������е�Tower*

	void insertTower(const std::string& name);//����������Ƭ��ֱ�Ӳ���У�������Ҫ�����޸Ķ������ڸú�����

	void update(const float& dt, const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};

#endif