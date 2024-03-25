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

#include "resize.hpp"
#include "../mode/sprite.hpp"

namespace State
{

void
Resize::set_resize_move(Direction direction)
{
	this->horizontal_move = nullptr;
	this->vertical_move = nullptr;

	switch(direction)
	{
	case Direction::up:
		this->vertical_move = &State::Resize::up_corner;
		break;
	case Direction::down:
		this->vertical_move = &State::Resize::down_corner;
		break;
	case Direction::left:
		this->horizontal_move = &State::Resize::left_corner;
		break;
	case Direction::right:
		this->horizontal_move = &State::Resize::right_corner;
		break;
	case Direction::up_right:
		this->vertical_move = &State::Resize::up_corner;
		this->horizontal_move = &State::Resize::right_corner;
		break;
	case Direction::up_left:
		this->vertical_move = &State::Resize::up_corner;
		this->horizontal_move = &State::Resize::left_corner;
		break;
	case Direction::down_right:
		this->vertical_move = &State::Resize::down_corner;
		this->horizontal_move = &State::Resize::right_corner;
		break;
	case Direction::down_left:
		this->vertical_move = &State::Resize::down_corner;
		this->horizontal_move = &State::Resize::left_corner;
		break;
	}
}

void
Resize::mouse_button_up(SDL_MouseButtonEvent& b)
{
	this->box->update_frame();
	this->sprite_box->mode->reset_state();
}

void
Resize::mouse_motion(int x, int y, int xrel, int yrel)
{
  if(xrel != 0 && this->horizontal_move)
	{
		int _x;
		if(this->sprite_box->x > 0)
			_x = (x - this->sprite_box->x) / this->sprite_box->zoom();
		else
			_x = x / this->sprite_box->zoom() - this->sprite_box->x;
		(this->*horizontal_move)(_x);
	}
  if(yrel != 0 && this->vertical_move)
	{
		int _y;
		if(this->sprite_box->y > 0)
			_y = (y - this->sprite_box->y) / this->sprite_box->zoom();
		else
			_y = y / this->sprite_box->zoom() - this->sprite_box->y;
		(this->*vertical_move)(_y);
	}

	this->box->update_size();
	this->box->update_frame();
}

void
Resize::up_corner(int y)
{
	int left_y{this->box->location.y};
	int right_y{this->box->location.y + this->box->location.h};
	this->box->location.y = y;
	this->box->location.h -= y - left_y;

	if(this->box->location.y < this->sprite_box->up_limit)
	{
		this->box->location.h -=
			this->sprite_box->up_limit - this->box->location.y;
		this->box->location.y = this->sprite_box->up_limit;
	}
	else if(this->box->location.h <= 0)
	{
		this->box->location.y = right_y - 1;
		this->box->location.h = 1;
	}
}

void
Resize::down_corner(int y)
{
	this->box->location.h = y - this->box->location.y;

	if(this->box->location.y + this->box->location.h >
		 this->sprite_box->down_limit)
		this->box->location.h =
			this->sprite_box->down_limit - this->box->location.y;
	else if(this->box->location.h < 1) this->box->location.h = 1;
}

void
Resize::left_corner(int x)
{
	int left_x{this->box->location.x};
	int right_x{this->box->location.x + this->box->location.w};
	this->box->location.x = x;
	this->box->location.w -= x - left_x;

	if(this->box->location.x < this->sprite_box->left_limit)
	{
		this->box->location.w -=
			this->sprite_box->left_limit - this->box->location.x;
		this->box->location.x = this->sprite_box->left_limit;
	}
	else if(this->box->location.w <= 0)
	{
		this->box->location.x = right_x - 1;
		this->box->location.w = 1;
	}
}

void
Resize::right_corner(int x)
{
	this->box->location.w = x - this->box->location.x;

	if(this->box->location.x + this->box->location.w >
		 this->sprite_box->right_limit)
		this->box->location.w =
			this->sprite_box->right_limit - this->box->location.x;
	else if(this->box->location.w < 1) this->box->location.w = 1;
}

Resize::Resize(
	Button::SpriteBox* sprite_box, Button::Box* box, Direction direction):
	sprite_box{sprite_box},
	box{box},
  vertical_move{nullptr},
  horizontal_move{nullptr}
{
	this->set_resize_move(direction);
}

}
