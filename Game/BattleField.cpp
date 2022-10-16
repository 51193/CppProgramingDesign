#include "BattleField.h"

void BattleField::init()
{
	this->initMap();
	this->initPathNet();
}

void BattleField::initMap()
{
	this->map = new std::vector<std::vector<Chunk*>>(size.x, std::vector<Chunk*>(size.y));
	
	for (int i{ 0 }; i < size.x; i++) {
		for (int j{ 0 }; j < size.y; j++) {
			(*map)[i][j] = new Chunk(i, j, offset.x, offset.y, this->chunk_size.x, this->chunk_size.y);
		}
	}
}

void BattleField::initPathNet()
{
	this->path_net = new std::vector<std::vector<int>>(
		this->path_net_count.x * this->size.x,
		std::vector<int>(this->path_net_count.y * this->size.y, 0));
}

BattleField::BattleField(float title_height, sf::RenderWindow* window, sf::Vector2i size, sf::Vector2i path_net_count)
	:
	a{ (float)0.8 },//修改该参数可以放大或缩小战场占显示器的比例
	window{ window },
	size{ size },
	chunk_size{ (this->window->getSize().x * this->a) / this->size.x, ((this->window->getSize().x * this->a) / this->size.x) * 3.f / 4.f },
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

void BattleField::update(const float& dt, sf::Vector2f& mousePos)
{
	for (auto& i : *(this->map)) {
		for (auto& j : i) {
			j->update(dt, mousePos);
		}
	}
}

void BattleField::render(sf::RenderTarget* target)
{
	for (auto& i : *(this->map)) {
		for (auto& j : i) {
			j->render(target);
		}
	}
}
