#ifndef MONSTER_H
#define MONSTER_H

#include<queue>

#include"MonsterTemplate.h"

class Monster
{
private:

	sf::Sprite sprite;

	std::string name;

	MonsterData* monster_data;
	AnimationComponent* animation_component;

	sf::Vector2f position;//该怪物相对于寻路网格的位置
	sf::Vector2f exact_pos;//实际位于屏幕上像素位置

	sf::Vector2u position_on_pathnet;//处于寻路节点的位置
	std::queue<sf::Vector2u> path;//目标节点

	std::vector<std::vector<int>> step_map;

	void init(const sf::Vector2f& path_net_size);
	void initTemplate();
	void initSpirteScale(const sf::Vector2f& path_net_size);

	void updatePathing(
		const sf::Vector2u& path_net_count,
		std::vector<std::vector<int>>& path_net,
		const std::vector<std::vector<int>>& start_step_map,
		const std::queue<sf::Vector2u>& start_BFS_queue
	);//寻路
	void updateMoving(const float& dt);//根据path队列进行实际的移动
	void updatePosition(const sf::Vector2f& offset, const sf::Vector2f& path_net_size);//将exact_pos根据position刷新
	void updateExactPos();//将sprite的位置置于exact_pos，用于渲染
	void playingAnimation(const float& dt);

public:
	static std::map<std::string, MonsterTemplate*>monster_lib;

	Monster(const std::string& name, const sf::Vector2f& path_net_size, unsigned int x, unsigned int y);
	~Monster();

	sf::Vector2f getPosition();//获取相对于寻路网格的位置
	void setPostion(sf::Vector2f position);//修改相对于寻路网格的位置

	const sf::Vector2u& getPositiononPathNet();//获取位于寻路网格上的位置

	const sf::Vector2f& getExactPos();//获取所处像素位置
	void setExactPos(const sf::Vector2f& exact_pos);//修改所处像素位置

	const sf::Vector2u& getSize();//获取碰撞箱，单位为寻路节点

	void update(
		const float& dt,
		const sf::Vector2f& offset,
		const sf::Vector2f& path_net_size,
		const sf::Vector2u& battlefield_size,
		const sf::Vector2u& path_net_count,
		std::vector<std::vector<int>>& path_net,
		const std::vector<std::vector<int>>& path_net_for_chunk,
		const std::vector<std::vector<int>>& start_step_map,
		const std::queue<sf::Vector2u>& start_BFS_queue
	);
	void render(sf::RenderTarget* target);
};

#endif