#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include"Chunk.h"
#include"Monster.h"

class BattleField
{
private:
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

	std::list<Monster*> monsters;//��������

	float title_height;//���Ʋ۵ĸ߶�

	sf::Vector2f offset;//ս�����Ͻǵ�����

	void init();
	void initMap();
	void initPathNet();
	void initPathNetforChunk();

	void resetPathNet();
	void updateBarriertoPathNet();

	void updateMonsters(const float& dt);

	void updatePathNetforChunk();//��δ���û�ɾ������ʱ��û���ظ�update�ı�Ҫ
	void updateInnerPathNet();
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

	void updateWhenTowerChanging();

	void update(const float& dt, const sf::Vector2f& mousePos);
	void render(sf::RenderTarget* target);

};

#endif