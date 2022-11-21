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

void Monster::updatePathing(
	const sf::Vector2u& path_net_count,
	std::vector<std::vector<int>>& path_net,
	const std::vector<std::vector<int>>& start_step_map,
	const std::queue<sf::Vector2u>& start_BFS_queue
)
{
	for (int i{ (int)this->position_on_pathnet.x - (int)(this->monster_data->size.x / 2) }; i <= (int)this->position_on_pathnet.x + (int)(this->monster_data->size.x / 2); i++) {
		for (int j{ (int)this->position_on_pathnet.y - (int)(this->monster_data->size.y / 2) }; j <= (int)this->position_on_pathnet.y + (int)(this->monster_data->size.y / 2); j++) {
			if (i >= 0 && i <= (int)path_net.size() - 1 &&
				j >= 0 && j <= (int)path_net[0].size() - 1) {
				path_net[i][j]++;
			}
		}
	}

	while (!this->path.empty())this->path.pop();

	constexpr int a = 1;//寻路单元的各边长比标准格子大1/a，如果需要修改，Chunk::updateStepMapandPathingQueue()里的也得改
	unsigned int extra_x = path_net_count.x / a;
	unsigned int extra_y = path_net_count.y / a;

	unsigned int pos_on_battlefield_x{ this->position_on_pathnet.x / path_net_count.x };
	unsigned int pos_on_battlefield_y{ this->position_on_pathnet.y / path_net_count.y };

	int offset_x{ (int)pos_on_battlefield_x * (int)path_net_count.x - (int)extra_x };
	int offset_y{ (int)pos_on_battlefield_y * (int)path_net_count.y - (int)extra_y };

	this->step_map = start_step_map;
	
	std::queue<sf::Vector2u> BFS_queue = start_BFS_queue;

	while (!BFS_queue.empty()) {
		sf::Vector2i cur = sf::Vector2i{ (int)BFS_queue.front().x,(int)BFS_queue.front().y };
		BFS_queue.pop();

		if (cur.y + offset_y >= 0 && cur.y + offset_y < (int)path_net[0].size()) {
			if (cur.x > 0) {
				if (cur.x - 1 + offset_x > 0) {
					if (this->step_map[cur.x][cur.y] + 1 < this->step_map[cur.x - 1][cur.y] && (int)path_net[cur.x + offset_x - 1][cur.y + offset_y] >= 0) {
						this->step_map[cur.x - 1][cur.y] = this->step_map[cur.x][cur.y] + 1;
						BFS_queue.push(sf::Vector2u(cur.x - 1, cur.y));
					}
				}
			}
			if (cur.x < (int)this->step_map.size() - 1) {
				if (cur.x + 1 + offset_x < (int)path_net.size()) {
					if (this->step_map[cur.x][cur.y] + 1 < this->step_map[cur.x + 1][cur.y] && (int)path_net[cur.x + offset_x + 1][cur.y + offset_y] >= 0) {
						this->step_map[cur.x + 1][cur.y] = this->step_map[cur.x][cur.y] + 1;
						BFS_queue.push(sf::Vector2u(cur.x + 1, cur.y));
					}
				}
			}
		}
		if (cur.x + offset_x >= 0 && cur.x + offset_x < (int)path_net.size()) {
			if (cur.y > 0) {
				if (cur.y - 1 + offset_y > 0) {
					if (this->step_map[cur.x][cur.y] + 1 < this->step_map[cur.x][cur.y - 1] && (int)path_net[cur.x + offset_x][cur.y + offset_y - 1] >= 0) {
						this->step_map[cur.x][cur.y - 1] = this->step_map[cur.x][cur.y] + 1;
						BFS_queue.push(sf::Vector2u(cur.x, cur.y - 1));
					}
				}
			}
			if (cur.y < (int)this->step_map[0].size() - 1) {
				if (cur.y + 1 + offset_y < (int)path_net[0].size()) {
					if (this->step_map[cur.x][cur.y] + 1 < this->step_map[cur.x][cur.y + 1] && (int)path_net[cur.x + offset_x][cur.y + offset_y + 1] >= 0) {
						this->step_map[cur.x][cur.y + 1] = this->step_map[cur.x][cur.y] + 1;
						BFS_queue.push(sf::Vector2u(cur.x, cur.y + 1));
					}
				}
			}
		}
	}

	sf::Vector2i cur{ (int)this->position_on_pathnet.x - offset_x, (int)this->position_on_pathnet.y - offset_y };

	unsigned int max_step = this->step_map.size() * this->step_map[0].size() + 1;
	unsigned int arr[4];

	while (this->step_map[cur.x][cur.y] != 0) {
		for (auto& i : arr) {
			i = max_step;
		}
		if (cur.y > 0) {
			arr[0] = this->step_map[cur.x][cur.y - 1];
		}
		if (cur.y < (int)this->step_map[0].size() - 1) {
			arr[1] = this->step_map[cur.x][cur.y + 1];
		}
		if (cur.x > 0) {
			arr[2] = this->step_map[cur.x - 1][cur.y];
		}
		if (cur.x < (int)this->step_map.size() - 1) {
			arr[3] = this->step_map[cur.x + 1][cur.y];
		}
		unsigned int min = max_step;
		for (auto i : arr) {
			if (min > i)min = i;
		}
		if (min < max_step) {
			if (arr[0] == min) cur = sf::Vector2i(cur.x, cur.y - 1);
			else if (arr[1] == min) cur = sf::Vector2i(cur.x, cur.y + 1);
			else if (arr[2] == min) cur = sf::Vector2i(cur.x - 1, cur.y);
			else if (arr[3] == min) cur = sf::Vector2i(cur.x + 1, cur.y);

			this->path.push(sf::Vector2u(cur.x + offset_x, cur.y + offset_y));
		}
		else break;
	}

	for (int i{ (int)this->position_on_pathnet.x - (int)(this->monster_data->size.x / 2) }; i <= (int)this->position_on_pathnet.x + (int)(this->monster_data->size.x / 2); i++) {
		for (int j{ (int)this->position_on_pathnet.y - (int)(this->monster_data->size.y / 2) }; j <= (int)this->position_on_pathnet.y + (int)(this->monster_data->size.y / 2); j++) {
			if (i >= 0 && i <= (int)path_net.size() - 1 &&
				j >= 0 && j <= (int)path_net[0].size() - 1) {
				path_net[i][j]--;
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
	if (!this->path.empty()) {
		float x{ this->path.front().x - this->position.x };
		float y{ this->path.front().y - this->position.y };
		if (abs(x) > abs(y)) {
			if (x > 0)this->animation_component->play("right", dt, false);
			else this->animation_component->play("left", dt, false);
		}
		else {
			if (y > 0)this->animation_component->play("down", dt, false);
			else this->animation_component->play("up", dt, false);
		}
	}
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

void Monster::update(
	const float& dt,
	const sf::Vector2f& offset,
	const sf::Vector2f& path_net_size,
	const sf::Vector2u& battlefield_size,
	const sf::Vector2u& path_net_count,
	std::vector<std::vector<int>>& path_net,
	const std::vector<std::vector<int>>& path_net_for_chunk,
	const std::vector<std::vector<int>>& start_step_map,
	const std::queue<sf::Vector2u>& start_BFS_queue
)
{
	this->updatePathing(path_net_count, path_net, start_step_map, start_BFS_queue);

	this->updateMoving(dt);

	this->updatePosition(offset, path_net_size);
	this->updateExactPos();
	this->playingAnimation(dt);
}

void Monster::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
