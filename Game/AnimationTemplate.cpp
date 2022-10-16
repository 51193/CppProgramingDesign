#include "AnimationTemplate.h"

AnimationTemplate::AnimationTemplate(std::string name, unsigned short int animation_type)
	:name{ name }
{
	switch (animation_type) {
	case TowerType:
	{
		this->addAnimationData("idle",
			"Resources\\Images\\Sprites\\Tower\\" + this->name + "\\" + this->name + "_idle.png",
			"Config\\Sprites\\Tower\\" + this->name + "\\" + this->name + "_idle.ini");

		this->addAnimationData("active",
			"Resources\\Images\\Sprites\\Tower\\" + this->name + "\\" + this->name + "_active.png",
			"Config\\Sprites\\Tower\\" + this->name + "\\" + this->name + "_active.ini");

		this->addAnimationData("card",
			"Resources\\Images\\Sprites\\Tower\\" + this->name + "\\" + this->name + "_card.png",
			"Config\\Sprites\\Tower\\" + this->name + "\\" + this->name + "_card.ini");

		break;
	}
	case MonsterType:
	{
		this->addAnimationData("up",
			"Resources\\Images\\Sprites\\Monster\\" + this->name + "\\" + this->name + "_up.png",
			"Config\\Sprites\\Monster\\" + this->name + "\\" + this->name + "_up.ini");

		this->addAnimationData("down",
			"Resources\\Images\\Sprites\\Monster\\" + this->name + "\\" + this->name + "_down.png",
			"Config\\Sprites\\Monster\\" + this->name + "\\" + this->name + "_down.ini");

		this->addAnimationData("left",
			"Resources\\Images\\Sprites\\Monster\\" + this->name + "\\" + this->name + "_left.png",
			"Config\\Sprites\\Monster\\" + this->name + "\\" + this->name + "_left.ini");

		this->addAnimationData("right",
			"Resources\\Images\\Sprites\\Monster\\" + this->name + "\\" + this->name + "_right.png",
			"Config\\Sprites\\Monster\\" + this->name + "\\" + this->name + "_right.ini");

		break;
	}
	}
}

AnimationTemplate::~AnimationTemplate()
{
	for (auto& i : animation_data) {
		delete i.second;
	}
}

void AnimationTemplate::addAnimationData(std::string key, std::string texture_file, std::string config_file)
{
	this->animation_data[key] = new AnimationData(texture_file, config_file);
}
