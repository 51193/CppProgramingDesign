#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include"Chunk.h"
#include"Monster.h"

class BattleField
{
private:
	float a;//ս����ռ��Ļ������ϵ��

	sf::RenderWindow* window;

	sf::Vector2i size;//ս���ĸ�����
	std::vector<std::vector<Chunk*>>* map;

	sf::Vector2f chunk_size;//ÿ����ռ���ش�С

	sf::Vector2i path_net_count;//ÿ���ڵ�·���ڵ���
	sf::Vector2f path_net_size;//ÿ��·�����ӵĴ�С
	std::vector<std::vector<int>>* path_net;//·��������

	std::list<Monster*> monsters;

	float title_height;//���Ʋ۵ĸ߶�

	sf::Vector2f offset;//ս�����Ͻǵ�����

	void init();
	void initMap();
	void initPathNet();

public:

	BattleField(float title_height, sf::RenderWindow* window, sf::Vector2i size, sf::Vector2i path_net_count);
	~BattleField();

	const sf::Vector2f& getChunkSize();//����ÿ����ռ���ش�С
	Chunk* getPressed();//��ȡ������ĸ��ӵ�ָ��

	void update(const float& dt, sf::Vector2f& mousePos);
	void render(sf::RenderTarget* target);

};

#endif