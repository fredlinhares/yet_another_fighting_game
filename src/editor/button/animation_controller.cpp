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

#include "animation_controller.hpp"

#include "../main.hpp"
#include "../mode/animation.hpp"

namespace Button
{

void
AnimationController::click_action(int x, int y)
{
	for(Button::Base *button: this->buttons)
		if(button->is_clicked(x, y)) break;
}

void
AnimationController::render()
{
	this->numbers.draw_fraction(
		this->animation_mode->frame_x, this->animation_mode->frame_y,
		this->animation_mode->frame_index + 1,
		this->animation_mode->current_animation->size());

	for(Button::Base *button: this->buttons) button->render();
}

AnimationController::AnimationController(
	Mode::Animation *animation_mode):
	animation_mode{animation_mode},
	previous_frame_btn{
		&editor_state->left_button, core.window_width - 200, 0,
		[animation=animation_mode->current_animation](){
			animation->previous_frame();}},
	next_frame_btn{
		&editor_state->right_button,
		core.window_width - editor_state->right_button.w, 0,
		[animation=animation_mode->current_animation](){
			animation->next_frame();}},
	play_btn{
		&editor_state->play_button,
		core.window_width - 200, editor_state->left_button.w,
		[playing=&animation_mode->playing](){*playing = true;}},
	pause_btn{
		&editor_state->pause_button,
		core.window_width - 200 + editor_state->play_button.w,
		editor_state->left_button.w,
			[playing=&animation_mode->playing](){*playing = false;}}
{
	this->location.x = core.window_width - 200;
	this->location.y = 0;
	this->location.w = 200;
	this->location.h = core.window_height;

	this->buttons.emplace_back(&this->previous_frame_btn);
	this->buttons.emplace_back(&this->next_frame_btn);
	this->buttons.emplace_back(&this->play_btn);
	this->buttons.emplace_back(&this->pause_btn);
}

}
