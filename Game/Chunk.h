#ifndef CHUNK_H
#define CHUNK_H

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

	sf::Vector2u position;//����ս���ĸ���λ��
	sf::Vector2f offset;//ս�����Ͻǵ�����λ��
	sf::Vector2f size;//ÿ����ӵ����ش�С

	std::queue<sf::Vector2u> start_BFS_queue;
	std::vector<std::vector<int>>* start_step_map;

	bool is_blocked;

	void init();
public:
	Chunk(unsigned int x, unsigned int y, float offset_x, float offset_y, float width, float height);
	~Chunk();
	
	void setTower(std::string name);//������Ϊname����̨���������������
	void removeTower();//�Ƴ�Ŀǰ���������̨
	Tower* getTower();//��ȡ��ǰ��������̨��ָ�룬���Ҫ������������̨�����������̨��getname()����ʵ����һ����̨�����жϸ�ָ���Ƿ�Ϊnullptr�ж��������Ƿ�����̨

	const sf::Vector2u& getPosition();

	const std::queue<sf::Vector2u>& getStartBFSQueue();
	const std::vector<std::vector<int>>& getStartStepMap();

	bool isPressed();//�жϵ�ǰ�����Ƿ񱻵��
	bool isBlocked();//�жϵ�ǰ�������Ƿ��ж���
	bool isOccupiedByMonster(const std::list<Monster*>& monsters, const sf::Vector2u& path_net_count);

	void updateStepMapandPathingQueue(
		const sf::Vector2u& path_net_count,
		const std::vector<std::vector<int>>& path_net_for_chunk
	);//�������ֻ���������������û��Ƴ�ʱ����

	void update(const float& dt, const sf::Vector2f& mousePos, const sf::Vector2u& path_net_count, std::list<Monster*> monsters);
	void render(sf::RenderTarget* target);
};

#endif