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

	sf::Vector2f position;//�ù��������Ѱ·�����λ��
	sf::Vector2f exact_pos;//ʵ��λ����Ļ������λ��

	sf::Vector2u position_on_pathnet;//����Ѱ·�ڵ��λ��

	void init();
	void initTemplate();

	void updatePosition(sf::Vector2f offset, sf::Vector2f path_net_size);//��exact_pos����positionˢ��
	void updateExactPos();//��sprite��λ������exact_pos��������Ⱦ

public:
	static std::map<std::string, MonsterTemplate*>monster_lib;

	Monster(std::string name, unsigned int x, unsigned int y);
	~Monster();

	sf::Vector2f getPosition();//��ȡ�����Ѱ·�����λ��
	void setPostion(sf::Vector2f position);//�޸������Ѱ·�����λ��

	sf::Vector2f getExactPos();//��ȡ��������λ��
	void setExactPos(sf::Vector2f exact_pos);//�޸���������λ��

	void update(const float& dt, sf::Vector2f offset, sf::Vector2f path_net_size);
	void render(sf::RenderTarget* target);
};

#endif