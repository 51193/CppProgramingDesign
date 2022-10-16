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
	sf::Vector2f size;//��ͼÿ���15��λ��20��λ��sizeΪ������ײ��
	sf::Vector2f animation_size;//������С����λΪ����ڿ�2560���صĵ�����ֵ
};

#endif