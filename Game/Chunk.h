#ifndef CHUNK_H
#define CHUNK_H

#include<list>
#include<queue>

#include"Button.h"
#include"Tower.h"

enum EndSide {
	Null=0,
	Up,
	Left,
	Right,
	Down,
};

class Chunk
{
private:
	Tower* tower;
	Button* button;

	sf::Vector2u position;//处于战场的格子位置
	sf::Vector2f offset;//战场左上角的像素位置
	sf::Vector2f size;//每格格子的像素大小

	std::queue<sf::Vector2u> start_BFS_queue;
	std::vector<std::vector<int>>* start_step_map;

	bool is_blocked;

	void init();
public:
	Chunk(unsigned int x, unsigned int y, float offset_x, float offset_y, float width, float height);
	~Chunk();
	
	void setTower(std::string name);//把名字为name的炮台设置在这个格子里
	void removeTower();//移除目前格子里的炮台
	Tower* getTower();//获取当前格子里炮台的指针，如果要依此生成新炮台，建议调用炮台的getname()并再实例化一个炮台，可判断该指针是否为nullptr判定格子里是否有炮台

	const sf::Vector2u& getPosition();

	const std::queue<sf::Vector2u>& getStartBFSQueue();
	const std::vector<std::vector<int>>& getStartStepMap();

	bool isPressed();//判断当前格子是否被点击
	bool isBlocked();//判断当前格子上是否有东西

	void updateStepMapandPathingQueue(
		const sf::Vector2u& path_net_count,
		const std::vector<std::vector<int>>& path_net_for_chunk
	);//这个函数只有在有炮塔被放置或移除时调用

	void update(const float& dt, const sf::Vector2f& mousePos);
	void render(sf::RenderTarget* target);
};

#endif