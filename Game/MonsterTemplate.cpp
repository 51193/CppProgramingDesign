#include "MonsterTemplate.h"

MonsterTemplate::MonsterTemplate(std::string name)
	:name{ name }
{
	this->init();
}

MonsterTemplate::~MonsterTemplate()
{
	delete this->animation_template;
	delete this->monster_data;
}

void MonsterTemplate::init()
{
	this->initAnimation();
	this->initData();
}

void MonsterTemplate::initAnimation()
{
	this->animation_template = new AnimationTemplate(this->name, MonsterType);
}

void MonsterTemplate::initData()
{
	this->monster_data = new MonsterData("Config\\Data\\Monster\\" + this->name + "\\" + this->name + ".ini");
}
