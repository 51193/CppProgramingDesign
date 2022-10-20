#include "Chunk.h"

void Chunk::init()
{
}

Chunk::Chunk(unsigned int x, unsigned int y, float offset_x, float offset_y, float width, float height)
    :tower{ nullptr },
    position{ x, y },
    offset{ offset_x, offset_y },
    size{ width, height },
    is_blocked{ false }
{
    this->button = new Button(
        offset_x + x * width,
        offset_y + y * height,
        width,
        height,
        sf::Color::Transparent,
        sf::Color::Color(255, 255, 255, 64),
        sf::Color::Color(255, 255, 255, 128),
        sf::Color::Transparent,
        sf::Color::Transparent,
        sf::Color::Transparent,
        nullptr,
        " ",
        true
    );

    this->init();
}

Chunk::~Chunk()
{
    if (this->tower != nullptr)delete this->tower;
}

void Chunk::setTower(std::string name)
{
    if (this->tower != nullptr) {
        this->removeTower();
    }
    this->tower = new Tower(name, TowerMode);
    this->tower->setScale(sf::Vector2f(this->size.x,
        (this->size.x / Tower::tower_lib[name]->animation_template->animation_data["idle"]->width) *
        Tower::tower_lib[name]->animation_template->animation_data["idle"]->height));
    this->tower->moveto(this->offset + sf::Vector2f(this->position.x * this->size.x, ((this->position.y + 1) * this->size.y) - this->tower->getSize().y));

	this->is_blocked = true;
}

void Chunk::removeTower()
{
    if (this->tower != nullptr) {
        delete this->tower;
        this->tower = nullptr;
    }
}

Tower* Chunk::getTower()
{
    return this->tower;
}

const sf::Vector2u& Chunk::getPosition()
{
    return this->position;
}

bool Chunk::isPressed()
{
    if (this->button->isPressed())return true;
    else return false;
}

bool Chunk::isBlocked()
{
    return this->is_blocked;
}

void Chunk::update(const float& dt, const sf::Vector2f& mousePos)
{
    if (this->tower != nullptr) {
        this->tower->update(dt);
        this->is_blocked = true;
    }
    else this->is_blocked = false;

    this->button->update(mousePos);

}

const std::queue<sf::Vector2u>& Chunk::getStartBFSQueue()
{
	return this->start_BFS_queue;
}

void Chunk::render(sf::RenderTarget* target)
{
    this->button->render(*target);
    if (this->tower != nullptr)this->tower->render(target);
}

const std::vector<std::vector<int>>& Chunk::getStartStepMap()
{
	return *this->start_step_map;
}

void Chunk::updateStepMapandPathingQueue(const sf::Vector2u& path_net_count, const std::vector<std::vector<int>>& path_net_for_chunk)
{
	constexpr unsigned int a = 3;//寻路单元的各边长比标准格子大1/a

	while (!this->start_BFS_queue.empty())this->start_BFS_queue.pop();

	if (this->start_step_map == nullptr) {
		this->start_step_map = new std::vector<std::vector<int>>(path_net_count.x + path_net_count.x / a * 2, std::vector<int>(path_net_count.y + path_net_count.y / a * 2, 0));
	}
	unsigned int max_step{ (*this->start_step_map).size() * (*this->start_step_map)[0].size() + 1 };
	for (auto& i : *this->start_step_map) {
		std::fill(i.begin(), i.end(), max_step);
	}

	unsigned int pos_on_battlefield_x{ this->position.x };
	unsigned int pos_on_battlefield_y{ this->position.y };

	unsigned int max_step_for_battlefield{ path_net_for_chunk.size() * path_net_for_chunk[0].size() + 1 };
	unsigned int arr[4]{ max_step_for_battlefield,max_step_for_battlefield,max_step_for_battlefield,max_step_for_battlefield };//[0]:上, [1]:下, [2]:左, [3]:右
	if (pos_on_battlefield_y > 0) {//上
		arr[0] = path_net_for_chunk[pos_on_battlefield_x][pos_on_battlefield_y - 1];
	}
	if (pos_on_battlefield_y < path_net_for_chunk[0].size() - 1) {//下
		arr[1] = path_net_for_chunk[pos_on_battlefield_x][pos_on_battlefield_y + 1];
	}
	if (pos_on_battlefield_x > 0) {//左
		arr[2] = path_net_for_chunk[pos_on_battlefield_x - 1][pos_on_battlefield_y];
	}
	if (pos_on_battlefield_x < path_net_for_chunk.size() - 1) {//右
		arr[3] = path_net_for_chunk[pos_on_battlefield_x + 1][pos_on_battlefield_y];
	}
	unsigned int min{ max_step_for_battlefield };
	for (auto i : arr) {
		if (i < min)min = i;
	}
	for (size_t i{ 0 }; i < 4; i++) {
		if (arr[i] == min) {
			if (i == 0) {
				for (auto& i : *this->start_step_map) {
					i[0] = 0;
				}
			}
			if (i == 1) {
				for (auto& i : *this->start_step_map) {
					*i.rbegin() = 0;
				}
			}
			if (i == 2) {
				std::fill((*this->start_step_map)[0].begin(), (*this->start_step_map)[0].end(), 0);
			}
			if (i == 3) {
				std::fill(this->start_step_map->rbegin()->begin(), this->start_step_map->rbegin()->end(), 0);
			}
		}
	}
	if (this->position.x == 0) {
		for (size_t i{ 0 }; i <= path_net_count.x / a; i++) {
			std::fill((*this->start_step_map)[i].begin(), (*this->start_step_map)[i].end(), max_step);
		}
	}
	if (this->position.x == path_net_for_chunk.size() - 1) {
		for (size_t i{ 0 }; i <= path_net_count.x / a; i++) {
			std::fill((this->start_step_map->rbegin() + i)->begin(), (this->start_step_map->rbegin() + i)->end(), max_step);
		}
	}
	if (this->position.y == 0) {
		for (size_t i{ 0 }; i < this->start_step_map->size(); i++) {
			std::fill((*this->start_step_map)[i].begin(), (*this->start_step_map)[i].begin() + path_net_count.y / a, max_step);
		}
	}
	if (this->position.y == path_net_for_chunk[0].size() - 1) {
		for (size_t i{ 0 }; i < this->start_step_map->size(); i++) {
			std::fill((*this->start_step_map)[i].end() - path_net_count.y / a, (*this->start_step_map)[i].end(), max_step);
		}
	}
	for (size_t i{ 0 }; i < (*this->start_step_map).size(); i++) {
		for (size_t j{ 0 }; j < (*this->start_step_map)[0].size(); j++) {
			if ((*this->start_step_map)[i][j] == 0)this->start_BFS_queue.push(sf::Vector2u(i, j));
		}
	}
}
