#ifndef MONSTER_H
#define MONSTER_H

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

	void init();
	void initTemplate();

	void updatePosition(sf::Vector2f offset, sf::Vector2f path_net_size);//将exact_pos根据position刷新
	void updateExactPos();//将sprite的位置置于exact_pos，用于渲染

public:
	static std::map<std::string, MonsterTemplate*>monster_lib;

	Monster(std::string name, unsigned int x, unsigned int y);
	~Monster();

	sf::Vector2f getPosition();//获取相对于寻路网格的位置
	void setPostion(sf::Vector2f position);//修改相对于寻路网格的位置

	sf::Vector2f getExactPos();//获取所处像素位置
	void setExactPos(sf::Vector2f exact_pos);//修改所处像素位置

	void update(const float& dt, sf::Vector2f offset, sf::Vector2f path_net_size);
	void render(sf::RenderTarget* target);
};

#endif