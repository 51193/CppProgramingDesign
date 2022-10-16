#include "MonsterData.h"

MonsterData::MonsterData(std::string file_name)
	:health{ 100 },
	speed{ 0 },
	size{ 0,0 },
	animation_size{ 0,0 }
{
	float x, y;
	std::ifstream input{ file_name, std::ios::in };
	if (input.is_open()) {
		input >> this->health;
		input >> this->speed;
		input >> x;
		input >> y;

		size = sf::Vector2f(x, y);

		input >> x;
		input >> y;

		animation_size = sf::Vector2f(x, y);

		input.close();
	}
	else std::cout << file_name + " open fail" << std::endl;
}

MonsterData::MonsterData(MonsterData& monster_data)
	:health{ monster_data.health },
	speed{ monster_data.speed },
	size{ monster_data.size }{}

MonsterData::~MonsterData()
{
}
