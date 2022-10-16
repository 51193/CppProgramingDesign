#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include"Chunk.h"
#include"Monster.h"

class BattleField
{
private:
	float a;//战场所占屏幕比例的系数

	sf::RenderWindow* window;

	sf::Vector2i size;//战场的格子数
	std::vector<std::vector<Chunk*>>* map;

	sf::Vector2f chunk_size;//每格所占像素大小

	sf::Vector2i path_net_count;//每格内的路径节点数
	sf::Vector2f path_net_size;//每个路径格子的大小
	std::vector<std::vector<int>>* path_net;//路径点网格

	std::list<Monster*> monsters;

	float title_height;//卡牌槽的高度

	sf::Vector2f offset;//战场左上角的坐标

	void init();
	void initMap();
	void initPathNet();

public:

	BattleField(float title_height, sf::RenderWindow* window, sf::Vector2i size, sf::Vector2i path_net_count);
	~BattleField();

	const sf::Vector2f& getChunkSize();//返回每格所占像素大小
	Chunk* getPressed();//获取被点击的格子的指针

	void update(const float& dt, sf::Vector2f& mousePos);
	void render(sf::RenderTarget* target);

};

#endif