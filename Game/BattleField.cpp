#include "BattleField.h"

void BattleField::init()
{
	this->initMap();
	this->initPathNet();
	this->initPathNetforChunk();

	//this->monsters.push_back(new Monster("testf", this->path_net_size, 10, 10));
	//this->monsters.push_back(new Monster("testf", this->path_net_size, 10, 20));
	//this->monsters.push_back(new Monster("testf", this->path_net_size, 10, 30));
	//this->monsters.push_back(new Monster("testf", this->path_net_size, 10, 40));
	//this->monsters.push_back(new Monster("test", this->path_net_size, 10, 50));
	//this->monsters.push_back(new Monster("test", this->path_net_size, 10, 60));
	//this->monsters.push_back(new Monster("test", this->path_net_size, 10, 70));
	//this->monsters.push_back(new Monster("test", this->path_net_size, 10, 80));
	//this->monsters.push_back(new Monster("test", this->path_net_size, 10, 90));
	//this->monsters.push_back(new Monster("tests", this->path_net_size, 10, 100));
	//this->monsters.push_back(new Monster("tests", this->path_net_size, 10, 110));
	//this->monsters.push_back(new Monster("tests", this->path_net_size, 10, 120));
	//this->monsters.push_back(new Monster("tests", this->path_net_size, 10, 130));
}

void BattleField::initMap()
{
	this->map = new std::vector<std::vector<Chunk*>>(size.x, std::vector<Chunk*>(size.y));
	
	for (size_t i{ 0 }; i < size.x; i++) {
		for (size_t j{ 0 }; j < size.y; j++) {
			(*this->map)[i][j] = new Chunk(i, j, offset.x, offset.y, this->chunk_size.x, this->chunk_size.y);
		}
	}
}

void BattleField::initPathNet()
{
	this->path_net = new std::vector<std::vector<int>>(
		this->path_net_count.x * this->size.x,
		std::vector<int>(this->path_net_count.y * this->size.y, 0));
}

void BattleField::initPathNetforChunk()
{
	this->path_net_for_chunk = new std::vector<std::vector<int>>(this->size.x, std::vector<int>(this->size.y, 0));
}

void BattleField::resetPathNet()
{
	for (auto& i : *this->path_net) {
		std::fill(i.begin(), i.end(), 0);
	}
}

void BattleField::updateBarriertoPathNet()
{
	for (auto& i : *this->map) {
		for (auto& j : i) {
			if (j->isBlocked()) {
				for (size_t k{ j->getPosition().x * this->path_net_count.x }; k < (j->getPosition().x + 1) * this->path_net_count.x; k++) {
					for (size_t l{ j->getPosition().y * this->path_net_count.y }; l < (j->getPosition().y + 1) * this->path_net_count.y; l++) {
						(*this->path_net)[k][l]--;
					}
				}
			}
		}
	}

	for (auto& i : monsters) {
		for (int j{ (int)i->getPositiononPathNet().x - (int)(i->getSize().x / 2) }; j <= (int)i->getPositiononPathNet().x + (int)(i->getSize().x / 2); j++) {
			for (int k{ (int)i->getPositiononPathNet().y - (int)(i->getSize().y / 2) }; k <= (int)i->getPositiononPathNet().y + (int)(i->getSize().y / 2); k++) {
				if (j >= 0 && j <= (int)this->path_net_count.x * (int)this->size.x - 1 &&
					k >= 0 && k <= (int)this->path_net_count.y * (int)this->size.y - 1) {
					(*this->path_net)[j][k]--;
				}
			}
		}
	}
}

void BattleField::updatePathNetforChunk()
{
	unsigned int max_count{ this->size.x * this->size.y + 1 };

	for (auto& i : *this->path_net_for_chunk) {
		std::fill(i.begin(), i.end(), max_count);
	}

	std::queue<sf::Vector2u> BFS_queue;

	for (auto& i : this->ends) {
		(*this->path_net_for_chunk)[i.x][i.y] = 0;
		BFS_queue.push(i);
	}

	while (!BFS_queue.empty()) {
		sf::Vector2u cur{ BFS_queue.front() };
		BFS_queue.pop();

		if (cur.x > 0) {
			if ((*path_net_for_chunk)[cur.x][cur.y] + 1 < (*path_net_for_chunk)[cur.x - 1][cur.y] && (!(*map)[cur.x - 1][cur.y]->isBlocked())) {
				(*path_net_for_chunk)[cur.x - 1][cur.y] = (*path_net_for_chunk)[cur.x][cur.y] + 1;
				BFS_queue.push(sf::Vector2u(cur.x - 1, cur.y));
			}
		}
		if (cur.x < this->size.x - 1) {
			if ((*path_net_for_chunk)[cur.x][cur.y] + 1 < (*path_net_for_chunk)[cur.x + 1][cur.y] && (!(*map)[cur.x + 1][cur.y]->isBlocked())) {
				(*path_net_for_chunk)[cur.x + 1][cur.y] = (*path_net_for_chunk)[cur.x][cur.y] + 1;
				BFS_queue.push(sf::Vector2u(cur.x + 1, cur.y));
			}
		}
		if (cur.y > 0) {
			if ((*path_net_for_chunk)[cur.x][cur.y] + 1 < (*path_net_for_chunk)[cur.x][cur.y - 1] && (!(*map)[cur.x][cur.y - 1]->isBlocked())) {
				(*path_net_for_chunk)[cur.x][cur.y - 1] = (*path_net_for_chunk)[cur.x][cur.y] + 1;
				BFS_queue.push(sf::Vector2u(cur.x, cur.y - 1));
			}
		}
		if (cur.y < this->size.y - 1) {
			if ((*path_net_for_chunk)[cur.x][cur.y] + 1 < (*path_net_for_chunk)[cur.x][cur.y + 1] && (!(*map)[cur.x][cur.y + 1]->isBlocked())) {
				(*path_net_for_chunk)[cur.x][cur.y + 1] = (*path_net_for_chunk)[cur.x][cur.y] + 1;
				BFS_queue.push(sf::Vector2u(cur.x, cur.y + 1));
			}
		}
	}
}

void BattleField::updateInnerPathNet()
{
	for (auto& i : *this->map) {
		for (auto& j : i) {
			j->updateStepMapandPathingQueue(this->path_net_count, *this->path_net_for_chunk);
		}
	}
}

void BattleField::updateTimer(const float& dt)
{
	this->timer += dt;
	this->generate_cool_down -= dt;
}

void BattleField::generateMonster()
{
	if (this->generate_cool_down < 0.f) {

		unsigned int n{ 1 };

		this->generate_cool_down = 5.f - timer / 5.f;

		if (this->generate_cool_down < (float)0.5) {
			this->generate_cool_down = (float)0.5;
		}

		for (size_t i{ 0 }; i < n; i++) {

			bool key{ true };

			int cur{ rand() };
			int x{ cur - (cur / (int)(*this->path_net)[0].size()) * ((int)(*this->path_net)[0].size()) };

			cur = rand();
			int y{ cur - (cur / 3) * 3 };

			while (key) {

				key = false;

				if ((*this->path_net)[0][x] < 0) {
					cur = rand();
					x = cur - (cur / (int)this->path_net_count.y) * (int)this->path_net_count.y;
					key = true;
				}
			}


			if (y == 0)
				this->monsters.push_back(new Monster("test", this->path_net_size, 0, x));
			else if (y == 1)
				this->monsters.push_back(new Monster("testf", this->path_net_size, 0, x));
			else
				this->monsters.push_back(new Monster("tests", this->path_net_size, 0, x));
		}

	}
}

bool BattleField::isLose()
{
	for (auto& j : this->monsters) {
		if (j->getPositiononPathNet().x == this->path_net->size() - 1) {
			return true;
		}
	}
	return false;
}

void BattleField::updateMonsters(const float& dt)
{
	for (auto& i : monsters) {
		i->update(
			dt,
			this->offset,
			this->path_net_size,
			this->size,
			this->path_net_count,
			*this->path_net,
			*this->path_net_for_chunk,
			(*this->map)[i->getPositiononPathNet().x / this->path_net_count.x][i->getPositiononPathNet().y / this->path_net_count.y]->getStartStepMap(),
			(*this->map)[i->getPositiononPathNet().x / this->path_net_count.x][i->getPositiononPathNet().y / this->path_net_count.y]->getStartBFSQueue()
		);
	}
}

void BattleField::updateDeath()
{
	for (size_t i{ 0 }; i < this->monsters.size(); i++) {
		if (this->monsters[i]->isDead()) {
			delete this->monsters[i];
			this->monsters.erase(this->monsters.begin() + i);
			i--;
			this->temp_money += 5;
		}
	}
}

BattleField::BattleField(
	const float& title_height,
	sf::RenderWindow* window,
	const sf::Vector2u& size,
	const sf::Vector2u& path_net_count,
	const std::vector<sf::Vector2u>& ends
	)
	:
	seed{ 0 },
	a{ (float)0.8 },//�޸ĸò������ԷŴ����Сս��ռ��ʾ���ı���
	window{ window },
	size{ size },
	chunk_size{ (this->window->getSize().x * this->a) / this->size.x, ((this->window->getSize().x * this->a) / this->size.x) * 3.f / 4.f },
	ends{ends},
	path_net_count{ path_net_count },
	path_net_size{ this->chunk_size.x / this->path_net_count.x, this->chunk_size.y / this->path_net_count.y },
	title_height{ title_height },
	offset{
	this->window->getSize().x * ((1 - this->a) / 2),
	this->title_height + ((this->window->getSize().y - this->title_height) - (this->size.y * this->chunk_size.y)) / 2 },
	timer{ 0.f },
	generate_cool_down{ 0.f },
	temp_money{ 0 }
{
	/*std::cout << "size: " << size.x << " " << size.y << std::endl;
	std::cout << "chunk_size: " << chunk_size.x << " " << chunk_size.y << std::endl;
	std::cout << "path_net_count: " << path_net_count.x << " " << path_net_count.y << std::endl;
	std::cout << "path_net_size: " << path_net_size.x << " " << path_net_size.y << std::endl;
	std::cout << "title_height: " << title_height << std::endl;
	std::cout << "offset: " << offset.x << " " << offset.y << std::endl;*/
	this->init();
	srand(seed);
}

BattleField::~BattleField()
{
	for (auto& i : *(this->map)) {
		for (auto& j : i) {
			delete j;
		}
	}
	delete this->map;
	delete this->path_net;
	for (auto& i : this->monsters) {
		delete i;
	}
}

const sf::Vector2f& BattleField::getChunkSize()
{
	return this->chunk_size;
}

Chunk* BattleField::getPressed()
{
	for (auto& i : *(this->map)) {
		for (auto& j : i) {
			if (j->isPressed())return j;
		}
	}
	return nullptr;
}

const std::vector<Monster*>& BattleField::getMonsterList()
{
	return this->monsters;
}

const sf::Vector2u& BattleField::getPathNetCount()
{
	return this->path_net_count;
}

void BattleField::updateWhenTowerChanging()
{
	this->updatePathNetforChunk();
	this->updateInnerPathNet();
}

unsigned int BattleField::getMoney()
{
	unsigned int temp{ this->temp_money };
	this->temp_money = 0;
	return temp;
}

void BattleField::update(const float& dt, const sf::Vector2f& mousePos)
{
	this->resetPathNet();

	this->updateBarriertoPathNet();

	for (auto& i : *(this->map)) {
		for (auto& j : i) {
			j->update(dt, mousePos, this->path_net_count, this->monsters);
		}
	}

	this->updateMonsters(dt);

	this->updateDeath();

	this->updateTimer(dt);
	this->generateMonster();
}

void BattleField::render(sf::RenderTarget* target)
{
	for (auto& i : *(this->map)) {
		for (auto& j : i) {
			j->render(target);
		}
	}

	for (auto& i : this->monsters) {
		i->render(target);
	}
}
