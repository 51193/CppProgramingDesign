#include "Monster.h"

std::map<std::string, MonsterTemplate*> Monster::monster_lib;

void Monster::init(const sf::Vector2f& path_net_size)
{
	this->initTemplate();
	this->initSpirteScale(path_net_size);
}

void Monster::initTemplate()
{
	if (!monster_lib.count(this->name)) {
		monster_lib[this->name] = new MonsterTemplate(this->name);
	}

	this->monster_data = new MonsterData(*monster_lib[this->name]->monster_data);
	this->animation_component = new AnimationComponent(this->sprite, *monster_lib[this->name]->animation_template);

}

void Monster::initSpirteScale(const sf::Vector2f& path_net_size)
{
	this->sprite.setScale(
		this->monster_data->animation_size.x * path_net_size.x / this->sprite.getGlobalBounds().width,
		this->monster_data->animation_size.y * path_net_size.y / this->sprite.getGlobalBounds().height
	);
}

void Monster::updatePathing(std::vector<std::vector<int>>& path_net, sf::Vector2u path_net_count, sf::Vector2u battlefield_size)
{
	for (int j{ (int)this->position_on_pathnet.x - (int)(this->monster_data->size.x / 2) }; j <= (int)this->position_on_pathnet.x + (int)(this->monster_data->size.x / 2); j++) {
		for (int k{ (int)this->position_on_pathnet.y - (int)(this->monster_data->size.y / 2) }; k <= (int)this->position_on_pathnet.y + (int)(this->monster_data->size.y / 2); k++) {
			if (j > 0 && j < (int)path_net_count.x * (int)battlefield_size.x - 1 &&
				k > 0 && k < (int)path_net_count.y * (int)battlefield_size.y - 1) {
				path_net[j][k]++;
			}
		}
	}

	this->step_map = path_net;
	unsigned int max_count = this->step_map.size() * this->step_map[0].size() + 1;
	for (auto& i : this->step_map) {
		for (auto& j : i) {
			j = max_count;
		}
	}

	std::queue<sf::Vector2u> BFS_queue;

	for (size_t i{ 0 }; i < path_net.size(); i++) {
		for (size_t j{ 0 }; j < path_net[0].size(); j++) {
			if (path_net[i][j] == 0x5fffffff) {
				BFS_queue.push(sf::Vector2u(i, j));
				this->step_map[i][j] = 0;
			}
		}
	}
	
	while (!BFS_queue.empty()) {
		sf::Vector2u cur = BFS_queue.front();
		BFS_queue.pop();

		if (cur.x > 0) {//向左
			if (step_map[cur.x][cur.y] + 1 < step_map[cur.x - 1][cur.y] && path_net[cur.x - 1][cur.y] > -1) {
				BFS_queue.push(sf::Vector2u(cur.x - 1, cur.y));
				step_map[cur.x - 1][cur.y] = step_map[cur.x][cur.y] + 1;
			}
		}
		if (cur.x < path_net_count.x * battlefield_size.x - 1) {//向右
			if (step_map[cur.x][cur.y] + 1 < step_map[cur.x + 1][cur.y] && path_net[cur.x + 1][cur.y] > -1) {
				BFS_queue.push(sf::Vector2u(cur.x + 1, cur.y));
				step_map[cur.x + 1][cur.y] = step_map[cur.x][cur.y] + 1;
			}
		}
		if (cur.y > 0) {//向上
			if (step_map[cur.x][cur.y] + 1 < step_map[cur.x][cur.y - 1] && path_net[cur.x][cur.y - 1] > -1) {
				BFS_queue.push(sf::Vector2u(cur.x, cur.y - 1));
				step_map[cur.x][cur.y - 1] = step_map[cur.x][cur.y] + 1;
			}
		}
		if (cur.y < path_net_count.y * battlefield_size.y - 1) {//向下
			if (step_map[cur.x][cur.y] + 1 < step_map[cur.x][cur.y + 1] && path_net[cur.x][cur.y + 1] > -1) {
				BFS_queue.push(sf::Vector2u(cur.x, cur.y + 1));
				step_map[cur.x][cur.y + 1] = step_map[cur.x][cur.y] + 1;
			}
		}
	}
	while (!this->path.empty())this->path.pop();

	sf::Vector2u cur{ this->position_on_pathnet };
	while (path_net[cur.x][cur.y] != 0x5fffffff) {
		enum direction {
			null=0,
			up,
			down,
			left,
			right
		};
		unsigned int x{ max_count };
		unsigned int dir{ null };
		if (cur.y > 0) {//向上
			if (step_map[cur.x][cur.y - 1] < (int)x) {
				x = step_map[cur.x][cur.y - 1];
				dir = up;
			}
		}
		if (cur.y < path_net_count.y * battlefield_size.y + 1) {//向下
			if (step_map[cur.x][cur.y + 1] < (int)x) {
				x = step_map[cur.x][cur.y + 1];
				dir = down;
			}
		}
		if (cur.x > 0) {//向左
			if (step_map[cur.x - 1][cur.y] < (int)x) {
				x = step_map[cur.x - 1][cur.y];
				dir = left;
			}
		}
		if (cur.x < path_net_count.x * battlefield_size.x - 1) {//向右
			if (step_map[cur.x + 1][cur.y] < (int)x) {
				x = step_map[cur.x + 1][cur.y];
				dir = right;
			}
		}
		bool is_stuck{ false };
		switch (dir) {
		case up: {
			cur = sf::Vector2u{ cur.x, cur.y - 1 };
			path.push(cur);
			break;
		}
		case down: {
			cur = sf::Vector2u{ cur.x, cur.y + 1 };
			path.push(cur);
			break;
		}
		case left: {
			cur = sf::Vector2u{ cur.x - 1, cur.y};
			path.push(cur);
			break;
		}
		case right: {
			cur = sf::Vector2u{ cur.x + 1, cur.y };
			path.push(cur);
			break;
		}
		default: {
			is_stuck = true;
			break;
		}
		}
		if (is_stuck)break;
	}

	for (int j{ (int)this->position_on_pathnet.x - (int)(this->monster_data->size.x / 2) }; j <= (int)this->position_on_pathnet.x + (int)(this->monster_data->size.x / 2); j++) {
		for (int k{ (int)this->position_on_pathnet.y - (int)(this->monster_data->size.y / 2) }; k <= (int)this->position_on_pathnet.y + (int)(this->monster_data->size.y / 2); k++) {
			if (j > 0 && j < (int)path_net_count.x * (int)battlefield_size.x - 1 &&
				k > 0 && k < (int)path_net_count.y * (int)battlefield_size.y - 1) {
				path_net[j][k] --;
			}
		}
	}
}

void Monster::updateMoving(const float& dt)
{
	float dis = dt * this->monster_data->speed;
	while (!this->path.empty()) {
		if (dis * dis >
			(this->position.x - this->path.front().x) * (this->position.x - this->path.front().x) +
			(this->position.y - this->path.front().y) * (this->position.y - this->path.front().y)) {
			this->position_on_pathnet = path.front();
			dis -= sqrt(
				(this->position.x - this->position_on_pathnet.x) * (this->position.x - this->position_on_pathnet.x) +
				(this->position.y - this->position_on_pathnet.y) * (this->position.y - this->position_on_pathnet.y));
			this->position = sf::Vector2f((float)position_on_pathnet.x, (float)position_on_pathnet.y);
			this->path.pop();
		}
		else break;
	}
	if (!this->path.empty()) {
		float slash{ sqrt(
				(this->position.x - this->path.front().x) * (this->position.x - this->path.front().x) +
				(this->position.y - this->path.front().y) * (this->position.y - this->path.front().y)) };
		float x = this->path.front().x - this->position.x;
		float y = this->path.front().y - this->position.y;
		this->position += sf::Vector2f(dis * x / slash, dis * y / slash);
	}
	
}

void Monster::updatePosition(const sf::Vector2f& offset, const sf::Vector2f& path_net_size)
{
	this->exact_pos = offset + sf::Vector2f(this->position.x * path_net_size.x, this->position.y * path_net_size.y);
}

void Monster::updateExactPos()
{
	this->sprite.setPosition(
		this->exact_pos -
		sf::Vector2f(this->sprite.getGlobalBounds().width / 2,
			this->sprite.getGlobalBounds().height / 2));
}

void Monster::playingAnimation(const float& dt)
{
	this->animation_component->play("up", dt, false);
}

Monster::Monster(const std::string& name, const sf::Vector2f& path_net_size, unsigned int x, unsigned int y)
	:name{ name },
	position_on_pathnet{x, y},
	position{ (float)x, (float)y }
{
	this->init(path_net_size);
}

Monster::~Monster()
{
	delete this->animation_component;
	delete this->monster_data;
}

sf::Vector2f Monster::getPosition()
{
	return this->position;
}

void Monster::setPostion(sf::Vector2f position)
{
	this->position = position;
}

const sf::Vector2u& Monster::getPositiononPathNet()
{
	return this->position_on_pathnet;
}

const sf::Vector2f& Monster::getExactPos()
{
	return this->exact_pos;
}

void Monster::setExactPos(const sf::Vector2f& exact_pos)
{
	this->exact_pos = exact_pos;
}

const sf::Vector2u& Monster::getSize()
{
	return this->monster_data->animation_size;
}

void Monster::update(const float& dt, const sf::Vector2f& offset, const sf::Vector2f& path_net_size, std::vector<std::vector<int>>& path_net, sf::Vector2u path_net_count, sf::Vector2u battlefield_size)
{
	this->updatePathing(path_net, path_net_count, battlefield_size);

	this->updateMoving(dt);

	this->updatePosition(offset, path_net_size);
	this->updateExactPos();
	this->playingAnimation(dt);
}

void Monster::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
