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

#include "../frame.hpp"
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
	Frame *frame{&editor_state->frames[this->frame_index]};
	this->zoomable.render_sprite(*frame);

	this->numbers.draw_fraction(
		this->frame_x, this->frame_y,
		this->frame_index + 1, this->current_animation->size());

	for(Button::Base *button: this->buttons) button->render();
}

Animation::Animation(const char *animation_name):
	animation_state{this},
	Base{&this->animation_state},
	playing{true},
	frame_x{core.window_width - 200 + editor_state->left_button.w},
	frame_y{0},
	current_animation{editor_state->animations[animation_name]},
	zoomable{
		0, 0,
		core.window_width - 200, core.window_height,
		(core.window_width - 200)/2, (core.window_height/6)*5}
{
	this->zoomable.up_limit = -250;
	this->zoomable.down_limit = 250;
	this->zoomable.left_limit = -250;
	this->zoomable.right_limit = 250;

	this->previous_frame_btn = new Button::Image{
		&editor_state->left_button, core.window_width - 200, 0,
		[animation=this->current_animation](){animation->previous_frame();}};

	this->next_frame_btn = new Button::Image{
		&editor_state->right_button,
		core.window_width - editor_state->right_button.w, 0,
		[animation=this->current_animation](){animation->next_frame();}};

	int y{editor_state->left_button.w};
	this->play_btn = new Button::Image{
		&editor_state->play_button,
		core.window_width - 200, y, [playing=&this->playing](){
			*playing = true;}};

	this->pause_btn = new Button::Image{
		&editor_state->pause_button,
		core.window_width - 200 + editor_state->play_button.w, y,
		[playing=&this->playing](){
			*playing =false;}};

	this->buttons.emplace_back(this->previous_frame_btn);
	this->buttons.emplace_back(this->next_frame_btn);
	this->buttons.emplace_back(this->play_btn);
	this->buttons.emplace_back(this->pause_btn);
}

Animation::~Animation()
{
	delete this->previous_frame_btn;
	delete this->next_frame_btn;
	delete this->play_btn;
	delete this->pause_btn;
}


}
