#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include<cstdlib>

#include"Chunk.h"

class BattleField
{
private:
	unsigned int seed;

	float a;//ս����ռ��Ļ������ϵ��

	sf::RenderWindow* window;

	sf::Vector2u size;//ս���ĸ�����
	std::vector<std::vector<Chunk*>>* map;
	std::vector<std::vector<int>>* path_net_for_chunk;

	sf::Vector2f chunk_size;//ÿ����ռ���ش�С

	std::vector<sf::Vector2u> ends;

	sf::Vector2u path_net_count;//ÿ���ڵ�·���ڵ���
	sf::Vector2f path_net_size;//ÿ��·�����ӵĴ�С
	std::vector<std::vector<int>>* path_net;//·��������

	std::vector<Monster*> monsters;//��������

	float title_height;//���Ʋ۵ĸ߶�

	sf::Vector2f offset;//ս�����Ͻǵ�����

	float timer;
	float generate_cool_down;

	unsigned int temp_money;

	void init();
	void initMap();
	void initPathNet();
	void initPathNetforChunk();

	void resetPathNet();
	void updateBarriertoPathNet();

	void updateMonsters(const float& dt);
	void updateDeath();

	void updatePathNetforChunk();//��δ���û�ɾ������ʱ��û���ظ�update�ı�Ҫ
	void updateInnerPathNet();

	void updateTimer(const float& dt);
	void generateMonster();

public:

	BattleField(
		const float& title_height,
		sf::RenderWindow* window,
		const sf::Vector2u& size,
		const sf::Vector2u& path_net_count,
		const std::vector<sf::Vector2u>&ends
	);
	~BattleField();

	const sf::Vector2f& getChunkSize();//����ÿ����ռ���ش�С
	Chunk* getPressed();//��ȡ������ĸ��ӵ�ָ��
	const std::vector<Monster*>& getMonsterList();
	const sf::Vector2u& getPathNetCount();

	void updateWhenTowerChanging();

	unsigned int getMoney();

	bool isLose();

	void update(const float& dt, const sf::Vector2f& mousePos);
	void render(sf::RenderTarget* target);

};

#endif