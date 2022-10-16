#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Title.h"
#include "BattleField.h"

class GameState :
    public State
{
protected:

	sf::RectangleShape* background;//背景墙，现在是个方块，可以附加材质上去

	Title* title;
	BattleField* battle_field;

	Tower* stretched_tower;//表示鼠标上附着的炮台，空时为nullptr
	sf::CircleShape* tower_range;//用来表示炮台攻击范围的圆圈，可随时调用修改，使用时直接设置位置和大小，结束使用时把半径改成0就可以

	void init();//初始化函数都应该扔进这个函数里

	void initBackground();//初始化背景墙，可用animation_component替代
	void initTowerRange();
	void initTitle();//初始化上方卡片槽
	void initCards();//这里后续要改，现在是直接写死了添加的炮塔名称
	void initBattleField();//初始化战场

	void updateStretchedTower();//update拖动的炮台卡片
	void updatePlantTower();//update是否把卡片放置在战场上

	void renderBackground(sf::RenderTarget* target);

public:
	GameState(sf::RenderWindow* window, sf::Font* font, std::stack<State*>* states);
	~GameState();

	void update(const float& dt);
	void render(sf::RenderTarget* target);

};

#endif