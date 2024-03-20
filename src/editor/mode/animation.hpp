/*
 * Copyright 2024 Frederico de Oliveira Linhares
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef YAFCE_MODE_ANIMATION_H
#define YAFCE_MODE_ANIMATION_H 1

#include "../../common/graphics/animation.hpp"
#include "../../common/graphics/frame.hpp"
#include "../button/animation_controller.hpp"
#include "../button/image.hpp"
#include "../button/sprite_box.hpp"
#include "../button/sprite_list.hpp"
#include "../mode.hpp"
#include "../state/animation.hpp"

namespace Mode
{

struct Animation: public Base
{
	bool playing;
	int _x, _y, frame_x, frame_y, frame_index;
	Graphics::Animation* const current_animation;

	Button::AnimationController animation_controller;
	Button::SpriteBox sprite_box;
	Button::SpriteList sprite_list;
	std::vector<Button::Base*> buttons;
	State::Animation animation_state;

	void
	default_state();

	void
	tick();

	void
	render();

	Animation(const char *animation_name);
};

}

#endif /* YAFCE_MODE_ANIMATION_H */
