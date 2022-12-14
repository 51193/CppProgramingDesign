#ifndef TOWER_H
#define TOWER_H

#include<list>

#include"TowerTemplate.h"
#include"Monster.h"

enum Mode {
	CardMode = 0,
	TowerMode,
};

enum Condition {
	IdleState = 0,
	ActiveState
};

class Tower
{
private:

	sf::Sprite sprite;

	std::string name;//名字，用于添加各种后缀读取图片和数据文件

	unsigned short int exist_mode;//存在形式，表示该炮塔是位于屏幕顶端的卡片还是实际的炮塔

	AnimationComponent* animation_component;//动画组件
	
	TowerData* tower_data;

	sf::Vector2f muzzle;

	Monster* target;

	sf::RectangleShape laser_beam;

	//下面是子弹附带特效的布尔值



	//下面是炮塔状态

	unsigned short int state;

	//函数

	void init();

	void initTemplate();
	void initLaser();

	void updateAiming(const sf::Vector2u& position, const sf::Vector2u& path_net_count, std::vector<Monster*> monsters);
	void updateAttack(const float& dt);
	void playingAnimation(const float& dt);//更新动画播放效果，属于一个update函数，以后可以添加一个动画播放队列，后续再精细化这个动画播放部件
	
public:
	static std::map<std::string, TowerTemplate*> tower_lib;

	Tower(std::string name, unsigned short int exist_mode);
	Tower(std::string name, unsigned short int exist_mode, const sf::Vector2f& muzzle);
	~Tower();

	void moveto(sf::Vector2f pos);//这个是移动sprite，只改变贴图位置，和逻辑判定位置无关

	void setScale(sf::Vector2f size);//把Tower大小拉伸到传进来的参数大小

	sf::Vector2f getSize();//获取大小（这个大小是缩放过的大小，不需要乘缩放比例，可以直接使用）
	sf::Vector2f getScale();//获取缩放的比例
	std::string getName();//获取名称
	float getRange();//该值表示炮塔射程，单位是寻路网格
	float getDamage();//获取伤害
	float getCooldown();//获取冷却
	bool getAOEBool();//获取是否为范围伤害的布尔值
	unsigned short int getState();//获取状态（待机，活跃等）

	void update(const float& dt, const sf::Vector2u& position, const sf::Vector2u& path_net_count, std::vector<Monster*> monsters);
	void update(const float& dt);//仅做卡片update
	void render(sf::RenderTarget* target);

};

#endif