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

#include "animation.hpp"

#include "../main.hpp"

namespace Mode
{

void
Animation::default_state()
{
}

void
Animation::tick()
{
	if(this->playing)
		this->frame_index = this->current_animation->tick();
	else
		this->frame_index = this->current_animation->index();
}

void
Animation::render()
{
	Graphics::Frame *frame{&editor_state->frames[this->frame_index]};
	this->sprite_box.render_sprite(*frame);

	for(Button::Base *button: this->buttons) button->render();
}

Animation::Animation(const char *animation_name):
	animation_state{this},
	Base{&this->animation_state},
	playing{true},
	frame_x{core.window_width - 200 + editor_state->left_button.w},
	frame_y{0},
	current_animation{editor_state->animations[animation_name]},
	animation_controller{this},
	sprite_box{
		0, 0,
		core.window_width - 200, core.window_height,
		(core.window_width - 200)/2, (core.window_height/6)*5},
	sprite_list{
		[&](int index){
			this->current_animation->frames.insert(
				this->current_animation->frames.begin() + this->frame_index + 1,
				Graphics::AnimationFrame{10, index});
			this->buttons.pop_back();
			this->buttons.emplace_back(&this->animation_controller);}}
{
	this->sprite_box.up_limit = -250;
	this->sprite_box.down_limit = 250;
	this->sprite_box.left_limit = -250;
	this->sprite_box.right_limit = 250;

	this->buttons.emplace_back(&this->animation_controller);
}

}
