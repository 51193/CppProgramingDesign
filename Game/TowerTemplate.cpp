#include "TowerTemplate.h"

TowerTemplate::TowerTemplate(std::string name)
	:name{ name }
{
	this->init();
}

TowerTemplate::~TowerTemplate()
{
	delete this->animation_template;
	delete this->tower_data;
}

void TowerTemplate::init()
{
	this->initAnimation();
	this->initData();
}

void TowerTemplate::initAnimation()
{
	this->animation_template = new AnimationTemplate(this->name, TowerType);
}

void TowerTemplate::initData()
{
	this->tower_data = new TowerData("Config\\Data\\Tower\\" + this->name + "\\" + this->name + ".ini");
}