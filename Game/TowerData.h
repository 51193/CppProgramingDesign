#ifndef TOWERDATA_H
#define TOWERDATA_H

#include<string>
#include<fstream>
#include<iostream>

class TowerData {
public:
	TowerData(std::string data_file);
	TowerData(TowerData& tower_data);
	~TowerData() {}

	float range;//������Χ
	float damage;//�˺�
	float cooldown;//��ȴ

	bool isAOE;//�Ƿ���AOE
};

#endif