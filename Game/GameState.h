#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Title.h"
#include "BattleField.h"

class GameState :
    public State
{
protected:

	sf::RectangleShape* background;//����ǽ�������Ǹ����飬���Ը��Ӳ�����ȥ

	Title* title;
	BattleField* battle_field;

	Tower* stretched_tower;//��ʾ����ϸ��ŵ���̨����ʱΪnullptr
	sf::CircleShape* tower_range;//������ʾ��̨������Χ��ԲȦ������ʱ�����޸ģ�ʹ��ʱֱ������λ�úʹ�С������ʹ��ʱ�Ѱ뾶�ĳ�0�Ϳ���

	sf::Text text;

	unsigned int money;

	void init();//��ʼ��������Ӧ���ӽ����������

	void initBackground();//��ʼ������ǽ������animation_component���
	void initTowerRange();
	void initTitle();//��ʼ���Ϸ���Ƭ��
	void initCards();//�������Ҫ�ģ�������ֱ��д������ӵ���������
	void initBattleField();//��ʼ��ս��
	void initMoneyText();

	void updateStretchedTower();//update�϶�����̨��Ƭ
	void updatePlantTower();//update�Ƿ�ѿ�Ƭ������ս����

	void updateMoney();

	void updateGameover();

	void renderBackground(sf::RenderTarget* target);

public:
	GameState(sf::RenderWindow* window, sf::Font* font, std::stack<State*>* states);
	~GameState();

	void update(const float& dt);
	void render(sf::RenderTarget* target);

};

#endif