#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include"AnimationTemplate.h"

class AnimationComponent {
public:
	AnimationComponent(sf::Sprite& sprite);
	AnimationComponent(sf::Sprite& sprite, AnimationComponent* animation_component);
	AnimationComponent(AnimationComponent& animation_component) = delete;
	AnimationComponent(sf::Sprite& sprite, AnimationTemplate& animation_template);

	virtual ~AnimationComponent();

	void addAnimation(const std::string& key, sf::Texture& animation_texture_sheet, const std::string& filename);
	void play(const std::string& key, const float& dt, const bool& play_once);
	void reset(const std::string& key);

	short int getPlayingFrame(const std::string& key);
	bool getHasPlayedOnce(const std::string& key);
	bool getPlayOnce();

private:
	class Animation {
	public:

		sf::Sprite& sprite;
		sf::Texture& animation_texture_sheet;
		float animation_timer;
		float timer;
		int width;
		int height;
		short int frame;

		short int current_frame;
		bool has_played_once;

		Animation(sf::Sprite& sprite,
			sf::Texture& animation_texture_sheet,
			float animation_timer,//每帧时间单位是毫秒
			int width, int height,
			short int frame)//总帧数大于等于1
			:sprite{ sprite }, animation_texture_sheet{ animation_texture_sheet },
			animation_timer{ animation_timer }, timer{ 0.f },
			width{ width }, height{ height },
			frame{ frame }, current_frame{ 1 }, has_played_once{ 0 }{
			this->sprite.setTexture(this->animation_texture_sheet);
			this->sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));
		}

		void play(const float& dt) {
			sprite.setTexture(this->animation_texture_sheet);

			this->timer += 1000.f * dt;
			if (this->timer >= this->animation_timer) {
				this->timer = 0.f;
				if (this->current_frame != frame) {
					current_frame++;
				}
				else {
					has_played_once = 1;
					current_frame = 1;
				}
			}
			this->sprite.setTextureRect(sf::IntRect(this->width* (current_frame - 1), 0, this->width, this->height));
		}

		void reset() {
			current_frame = 1;
			timer = 0.f;
			has_played_once = 0;
		}
	};

	sf::Sprite& sprite;
	std::map<std::string, Animation*>animations;

	std::string playing_animation;

	bool play_once;

};

#endif