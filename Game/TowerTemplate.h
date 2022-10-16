#ifndef TOWERTEMPLATE_H
#define TOWERTEMPLATE_H

#include"TowerData.h"
#include"AnimationComponent.h"

class TowerTemplate
{
public:
	TowerTemplate(std::string name);
	~TowerTemplate();

	void init();

	void initAnimation();
	AnimationTemplate* animation_template;

	void initData();
	TowerData* tower_data;

	std::string name;
};

#endif