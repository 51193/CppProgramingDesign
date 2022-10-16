#include "TowerData.h"

TowerData::TowerData(std::string data_file)
	:range{ 0 },
	damage{ 0 },
	cooldown{ 0 },
	isAOE{ false }
{
	std::ifstream input(data_file, std::ios::in);
	if (input.is_open()) {
		input >> this->range;
		input >> this->damage;
		input >> this->cooldown;
		input >> this->isAOE;
		input.close();
	}
	else std::cout << data_file + " open fail" << std::endl;
}

TowerData::TowerData(TowerData& tower_data)
	:range{ tower_data.range },
	damage{ tower_data.damage },
	cooldown{ tower_data.cooldown },
	isAOE{ tower_data.isAOE }{}