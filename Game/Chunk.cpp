#include "Chunk.h"

void Chunk::init()
{
}

Chunk::Chunk(int x, int y, float offset_x, float offset_y, float width, float height)
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

const sf::Vector2i& Chunk::getPosition()
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

void Chunk::render(sf::RenderTarget* target)
{
    this->button->render(*target);
    if (this->tower != nullptr)this->tower->render(target);
}