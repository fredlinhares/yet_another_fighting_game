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

#include "box.hpp"

#include "../state/resize.hpp"
#include "sprite_box.hpp"

namespace Button
{

void
Box::update_frame()
{
	this->rect->x = this->location.x + 2;
	this->rect->y = this->location.y + 2;
	this->rect->w = this->location.w - 4;
	this->rect->h = this->location.h - 4;
}

void
Box::click_action(const int x, const int y)
{
	Direction direction;
	Direction vertical_direction{Direction::none};
	Direction horizontal_direction{Direction::none};

	if(x >= this->outer_left && x <= this->outer_right &&
		 y >= this->outer_up && y <= this->outer_down)
	{
		if(x < this->center_left)
			horizontal_direction = Direction::left;
		else if(x < this->center_right)
			horizontal_direction = Direction::none;
		else
			horizontal_direction = Direction::right;

		if(y < this->center_up)
			vertical_direction = Direction::up;
		else if(y < this->center_down)
			vertical_direction = Direction::none;
		else
			vertical_direction = Direction::down;

		direction = vertical_direction + horizontal_direction;
		State::Base *state = new State::Resize(this->sprite_box, this, direction);
		this->mode->change_state(state);
	}
}

void
Box::render()
{
	this->sprite_box->render_rect(
		*this->rect, this->red, this->green, this->blue);
}

void
Box::update_size()
{
  this->outer_left = this->rect->x - 2;
  this->center_left = this->rect->x + 2;
  this->outer_right = this->rect->x + this->rect->w + 2;
  this->center_right = this->rect->x + this->rect->w - 2;
  this->outer_up = this->rect->y - 2;
  this->center_up = this->rect->y + 2;
  this->outer_down = this->rect->y + this->rect->h + 2;
  this->center_down = this->rect->y + this->rect->h - 2;
}

Box::Box(Mode::Base* mode, SpriteBox *sprite_box,
				 SDL_Rect *rect, Uint8 red, Uint8 green, Uint8 blue):
	mode{mode},
	sprite_box{sprite_box},
	rect{rect},
	red{red},
	green{green},
	blue{blue}
{
	this->location.x = rect->x - 2;
	this->location.y = rect->y - 2;
	this->location.w = rect->w + 4;
	this->location.h = rect->h + 4;
  this->update_size();
}

}
