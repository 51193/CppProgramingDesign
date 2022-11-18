#ifndef TOWER_H
#define TOWER_H

#include"TowerTemplate.h"

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

	std::string name;//���֣�������Ӹ��ֺ�׺��ȡͼƬ�������ļ�

	unsigned short int exist_mode;//������ʽ����ʾ��������λ����Ļ���˵Ŀ�Ƭ����ʵ�ʵ�����

	AnimationComponent* animation_component;//�������
	
	TowerData* tower_data;

	//�������ӵ�������Ч�Ĳ���ֵ



	//����������״̬

	unsigned short int state;

	//����

	void init();

	void initTemplate();

	void playingAnimation(const float& dt);//���¶�������Ч��������һ��update�������Ժ�������һ���������Ŷ��У������پ�ϸ������������Ų���
	
public:
	static std::map<std::string, TowerTemplate*> tower_lib;

	Tower(std::string name, unsigned short int exist_mode);
	~Tower();

	void moveto(sf::Vector2f pos);//������ƶ�sprite��ֻ�ı���ͼλ�ã����߼��ж�λ���޹�

	void setScale(sf::Vector2f size);//��Tower��С���쵽�������Ĳ�����С

	sf::Vector2f getSize();//��ȡ��С�������С�����Ź��Ĵ�С������Ҫ�����ű���������ֱ��ʹ�ã�
	sf::Vector2f getScale();//��ȡ���ŵı���
	std::string getName();//��ȡ����
	float getRange();//��ֵ��ʾ������̣���λ��Ѱ·����
	float getDamage();//��ȡ�˺�
	float getCooldown();//��ȡ��ȴ
	bool getAOEBool();//��ȡ�Ƿ�Ϊ��Χ�˺��Ĳ���ֵ
	unsigned short int getState();//��ȡ״̬����������Ծ�ȣ�

	void update(const float& dt);
	void render(sf::RenderTarget* target);

};

#endif