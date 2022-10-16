#ifndef CHUNK_H
#define CHUNK_H

#include<list>

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

	sf::Vector2i position;//����ս���ĸ���λ��
	sf::Vector2f offset;//ս�����Ͻǵ�����λ��
	sf::Vector2f size;//ÿ����ӵ����ش�С

	bool is_blocked;

	void init();
public:
	Chunk(int x, int y, float offset_x, float offset_y, float width, float height);
	~Chunk();
	
	void setTower(std::string name);//������Ϊname����̨���������������
	void removeTower();//�Ƴ�Ŀǰ���������̨
	Tower* getTower();//��ȡ��ǰ��������̨��ָ�룬���Ҫ������������̨�����������̨��getname()����ʵ����һ����̨�����жϸ�ָ���Ƿ�Ϊnullptr�ж��������Ƿ�����̨

	bool isPressed();//�жϵ�ǰ�����Ƿ񱻵��
	bool isBlocked();//�жϵ�ǰ�������Ƿ��ж���

	void update(const float& dt, sf::Vector2f& mousePos);
	void render(sf::RenderTarget* target);
};

#endif