#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include"Chunk.h"
#include"Monster.h"

class BattleField
{
private:
	float a;//战场所占屏幕比例的系数

	sf::RenderWindow* window;

	sf::Vector2u size;//战场的格子数
	std::vector<std::vector<Chunk*>>* map;

	sf::Vector2f chunk_size;//每格所占像素大小

	std::vector<sf::Vector2u> ends;

	sf::Vector2u path_net_count;//每格内的路径节点数
	sf::Vector2f path_net_size;//每个路径格子的大小
	std::vector<std::vector<int>>* path_net;//路径点网格

	std::list<Monster*> monsters;//怪物链表

	float title_height;//卡牌槽的高度

	sf::Vector2f offset;//战场左上角的坐标

	void init();
	void initMap();
	void initPathNet();

	void resetPathNet();
	void updateEndstoPathNet();//刷新终点，可以放在init里跑一边就够了，但是怕后面想漏东西把init出来的覆盖掉，所以暂时用update
	void updateBarriertoPathNet();

public:

	BattleField(
		const float& title_height,
		sf::RenderWindow* window,
		const sf::Vector2u& size,
		const sf::Vector2u& path_net_count,
		const std::vector<sf::Vector2u>&ends
	);
	~BattleField();

	const sf::Vector2f& getChunkSize();//返回每格所占像素大小
	Chunk* getPressed();//获取被点击的格子的指针

	void update(const float& dt, const sf::Vector2f& mousePos);
	void render(sf::RenderTarget* target);

};

#endif