#include "BattleField.h"

void BattleField::init()
{
	this->initMap();
	this->initPathNet();

	this->monsters.push_back(new Monster("test", this->path_net_size, 10, 10));
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

void BattleField::resetPathNet()
{
	for (auto& i : *this->path_net) {
		for (auto& j : i) {
			j = 0;
		}
	}
}

void BattleField::updateEndstoPathNet()
{
	for (auto& i : this->ends) {
		if (i.x < this->size.x && i.y < this->size.y) {
			if (i.x == this->size.x - 1) {
				for (size_t j{ 0 }; j < this->path_net_count.y; j++)
					(*this->path_net)[(this->path_net_count.x) * (this->size.x) - 1][(this->path_net_count.y) * (i.y) + j] = 0x5fffffff;
			}
			if (i.x == 0) {
				for (size_t j{ 0 }; j < this->path_net_count.y; j++)
					(*this->path_net)[0][(this->path_net_count.y) * (i.y) + j] = 0x5fffffff;
			}
			if (i.y == this->size.y - 1) {
				for (size_t j{ 0 }; j < this->path_net_count.x; j++)
					(*this->path_net)[(this->path_net_count.x) * (i.x) + j][(this->path_net_count.y) * (this->size.y) - 1] = 0x5fffffff;
			}
			if (i.y == 0) {
				for (size_t j{ 0 }; j < this->path_net_count.x; j++)
					(*this->path_net)[(this->path_net_count.x) * (i.x) + j][0] = 0x5fffffff;
			}
		}
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
				if (j > 0 && j < (int)this->path_net_count.x * (int)this->size.x - 1 &&
					k > 0 && k < (int)this->path_net_count.y * (int)this->size.y - 1) {
					(*this->path_net)[j][k]--;
				}
			}
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
	a{ (float)0.8 },//修改该参数可以放大或缩小战场占显示器的比例
	window{ window },
	size{ size },
	chunk_size{ (this->window->getSize().x * this->a) / this->size.x, ((this->window->getSize().x * this->a) / this->size.x) * 3.f / 4.f },
	ends{ends},
	path_net_count{ path_net_count },
	path_net_size{ this->chunk_size.x / this->path_net_count.x, this->chunk_size.y / this->path_net_count.y },
	title_height{ title_height },
	offset{
	this->window->getSize().x * ((1 - this->a) / 2),
	this->title_height + ((this->window->getSize().y - this->title_height) - (this->size.y * this->chunk_size.y)) / 2 }
{
	/*std::cout << "size: " << size.x << " " << size.y << std::endl;
	std::cout << "chunk_size: " << chunk_size.x << " " << chunk_size.y << std::endl;
	std::cout << "path_net_count: " << path_net_count.x << " " << path_net_count.y << std::endl;
	std::cout << "path_net_size: " << path_net_size.x << " " << path_net_size.y << std::endl;
	std::cout << "title_height: " << title_height << std::endl;
	std::cout << "offset: " << offset.x << " " << offset.y << std::endl;*/
	this->init();
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

void BattleField::update(const float& dt, const sf::Vector2f& mousePos)
{
	this->resetPathNet();

	this->updateEndstoPathNet();

	this->updateBarriertoPathNet();

	for (auto& i : *(this->map)) {
		for (auto& j : i) {
			j->update(dt, mousePos);
		}
	}
	for (auto& i : this->monsters) {
		i->update(dt, this->offset, this->path_net_size, *this->path_net, this->path_net_count, this->size);
	}
}

void BattleField::render(sf::RenderTarget* target)
{
	for (auto& i : this->monsters) {
		i->render(target);
	}

	for (auto& i : *(this->map)) {
		for (auto& j : i) {
			j->render(target);
		}
	}
}
