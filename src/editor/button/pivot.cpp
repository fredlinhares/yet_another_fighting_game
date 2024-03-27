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

#include "pivot.hpp"

#include "../state/move_pivot.hpp"

namespace Button
{

void
Pivot::set_position()
{
	this->location.x = - this->radius;
	this->location.y = - this->radius;
	this->location.w = this->radius * 2;
	this->location.h = this->radius * 2;
}

void
Pivot::click_action(int x, int y)
{
	State::Base *state = new State::MovePivot(
		this->sprite_box, this->pivot_x, this->pivot_y);
	this->sprite_box->mode->change_state(state);
}

void
Pivot::render()
{
	int vertical_x = this->sprite_box->x;
	int vertical_top_y = 0;
	int vertical_botton_y = this->sprite_box->location.h;

	int horizontal_left_x = 0;
	int horizontal_right_x = this->sprite_box->location.w;
	int horizontal_y = this->sprite_box->y;

	SDL_SetRenderDrawColor(core.renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderDrawLine(
		core.renderer, horizontal_left_x, horizontal_y,
		horizontal_right_x, horizontal_y);
	SDL_RenderDrawLine(
		core.renderer, vertical_x, vertical_top_y, vertical_x, vertical_botton_y);
}

Pivot::Pivot(SpriteBox *sprite_box, int *pivot_x, int *pivot_y, int radius):
	sprite_box{sprite_box},
	pivot_x{pivot_x},
	pivot_y{pivot_y},
	radius{radius}
{
	this->set_position();
}

}
