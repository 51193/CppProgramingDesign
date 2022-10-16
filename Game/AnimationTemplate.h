#ifndef ANIMATIONTEMPLATE_H
#define ANIMATIONTEMPLATE_H

#include<iostream>
#include<fstream>
#include<map>

#include"SFML\System.hpp"
#include"SFML\Window.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"

enum AnimationType {
	TowerType=0,
	MonsterType
};

class AnimationTemplate
{
private:
	class AnimationData {
	public:
		AnimationData(std::string texture_file, std::string config_file)
			:animation_timer{ 0 }, width{ 0 }, height{ 0 }, frame{ 0 }
		{
			if (this->texture.loadFromFile(texture_file)) {}
			else std::cout << texture_file << " open fail" << std::endl;

			std::ifstream input(config_file, std::ios::in);

			if (input.is_open()) {

				input >> this->animation_timer;
				input >> this->width;
				input >> this->height;
				input >> this->frame;

				input.close();
			}

			else
				std::cout << config_file << " open fail" << std::endl;
		}
		~AnimationData() {}

		sf::Texture texture;
		float animation_timer;
		int width;
		int height;
		short int frame;
	};

public:
	AnimationTemplate(std::string name, unsigned short int animation_type);
	~AnimationTemplate();

	std::string name;

	std::map<std::string, AnimationData*>animation_data;

	void addAnimationData(std::string key, std::string texture_file, std::string config_file);

};

#endif