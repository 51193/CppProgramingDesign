#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite) :sprite{ sprite }, playing_animation{ "NULL" }, play_once{ 0 } {}

AnimationComponent::AnimationComponent(sf::Sprite& sprite, AnimationComponent* animation_component)
	: sprite{ sprite }, animations{ animation_component->animations }, playing_animation{ animation_component->playing_animation }, play_once{ animation_component->play_once }{}

AnimationComponent::AnimationComponent(sf::Sprite& sprite, AnimationTemplate& animation_template)
	: sprite{ sprite },
	playing_animation{ "NULL" },
	play_once{ 0 }
{
	for (auto& i : animation_template.animation_data) {
		animations[i.first] = new Animation(
			this->sprite,
			i.second->texture,
			i.second->animation_timer,
			i.second->width,
			i.second->height,
			i.second->frame);
	}
	
}

AnimationComponent::~AnimationComponent() {
	for (auto& i : this->animations) {
		delete i.second;
	}
}

void AnimationComponent::addAnimation(const std::string& key, sf::Texture& animation_texture_sheet, const std::string& filename) {

	float animation_timer;
	int width;
	int height;
	short int frame;

	std::ifstream input(filename, std::ios::in);

	if (input.is_open()) {

		input >> animation_timer;
		input >> width;
		input >> height;
		input >> frame;
		animations[key] = new Animation(this->sprite, animation_texture_sheet, animation_timer, width, height, frame);

		input.close();
	}

	else
		std::cout << filename << " open fail" << std::endl;

	this->play(key, 0.f, true);

}

void AnimationComponent::play(const std::string& key, const float& dt, const bool& play_once) {

	if (!(this->play_once == 1 && play_once == 0) && this->playing_animation != key) {
		if (this->playing_animation != "NULL") {
			this->animations.at(playing_animation)->reset();
		}
		this->playing_animation = key;
	}

	if (this->play_once == 0 && play_once == 1) {
		if (this->playing_animation != "NULL") {
			this->animations.at(playing_animation)->reset();
		}
		this->play_once = 1;
		this->playing_animation = key;
	}

	if (this->getHasPlayedOnce(this->playing_animation)) {
		this->play_once = 0;
	}
	if (this->playing_animation != "NULL") {
		this->animations.at(this->playing_animation)->play(dt);
	}
}

void AnimationComponent::reset(const std::string& key) {
	this->animations[key]->reset();
}

short int AnimationComponent::getPlayingFrame(const std::string& key) {

	return this->animations[key]->current_frame;

}

bool AnimationComponent::getHasPlayedOnce(const std::string& key) {
	return this->animations.at(this->playing_animation)->has_played_once;
}

bool AnimationComponent::getPlayOnce() {
	return play_once;
}
