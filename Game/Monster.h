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

	float temp_health;//Ŀǰ��Ѫ��
	bool is_dead;

	sf::Vector2f position;//�ù��������Ѱ·�����λ��
	sf::Vector2f exact_pos;//ʵ��λ����Ļ������λ��

	sf::Vector2u position_on_pathnet;//����Ѱ·�ڵ��λ��
	std::queue<sf::Vector2u> path;//Ŀ��ڵ�

	std::vector<std::vector<int>> step_map;

	void init(const sf::Vector2f& path_net_size);
	void initTemplate();
	void initSpirteScale(const sf::Vector2f& path_net_size);

	void updatePathing(
		const sf::Vector2u& path_net_count,
		std::vector<std::vector<int>>& path_net,
		const std::vector<std::vector<int>>& start_step_map,
		const std::queue<sf::Vector2u>& start_BFS_queue
	);//Ѱ·
	void updateMoving(const float& dt);//����path���н���ʵ�ʵ��ƶ�
	void updatePosition(const sf::Vector2f& offset, const sf::Vector2f& path_net_size);//��exact_pos����positionˢ��
	void updateExactPos();//��sprite��λ������exact_pos��������Ⱦ
	void playingAnimation(const float& dt);

public:
	static std::map<std::string, MonsterTemplate*>monster_lib;

	Monster(const std::string& name, const sf::Vector2f& path_net_size, unsigned int x, unsigned int y);
	~Monster();

	sf::Vector2f getPosition();//��ȡ�����Ѱ·�����λ��
	void setPostion(sf::Vector2f position);//�޸������Ѱ·�����λ��

	const sf::Vector2u& getPositiononPathNet();//��ȡλ��Ѱ·�����ϵ�λ��

	const sf::Vector2f& getExactPos();//��ȡ��������λ��
	void setExactPos(const sf::Vector2f& exact_pos);//�޸���������λ��

	const sf::Vector2u& getSize();//��ȡ��ײ�䣬��λΪѰ·�ڵ�

	const bool& isDead();

	void getDamage(const float& damage);

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