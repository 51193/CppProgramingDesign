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
	sf::Vector2f size;//地图每格高15单位长20单位，size为怪物碰撞箱
	sf::Vector2f animation_size;//动画大小，单位为相对于宽2560像素的的像素值
};

#endif