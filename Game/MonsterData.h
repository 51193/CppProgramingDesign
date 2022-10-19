#ifndef MONSTERDATA_H
#define MONSTERDATA_H

#include<iostream>
#include<fstream>
#include<string>

#include<SFML/Window.hpp>

class MonsterData
{
public:
	MonsterData(std::string file_name);
	MonsterData(MonsterData& monster_data);
	~MonsterData();

	float health;
	float speed;
	sf::Vector2u size;//地图每格高15单位长20单位，size为怪物碰撞箱
	sf::Vector2u animation_size;//动画大小，单位为相对于寻路节点的大小
};

#endif