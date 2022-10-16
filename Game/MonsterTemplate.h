#ifndef MONSTERTEMPLATE_H
#define MONSTERTEMPLATE_H

#include"MonsterData.h"
#include"AnimationTemplate.h"
#include"AnimationComponent.h"

class MonsterTemplate
{
private:
public:
	MonsterTemplate(std::string name);
	~MonsterTemplate();
	
	void init();

	void initAnimation();
	AnimationTemplate* animation_template;

	void initData();
	MonsterData* monster_data;

	std::string name;
};

#endif