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
Resize::mouse_button_up(SDL_MouseButtonEvent& b)
{
  this->mode->current_state = &this->mode->sprite_state;
}

void
Resize::mouse_motion(int x, int y, int xrel, int yrel)
{
  if(xrel != 0 && this->horizontal_move)
    (this->*horizontal_move)(x / this->mode->zoom_level() + this->mode->x());
  if(yrel != 0 && this->vertical_move)
    (this->*vertical_move)(y / this->mode->zoom_level() + this->mode->y());

	this->box->update_size();
}

void
Resize::up_corner(int y)
{
	int left_y{this->box->size.y};
	int right_y{this->box->size.y + this->box->size.h};
	this->box->size.y = y;
	this->box->size.h -= y - left_y;

	if(this->box->size.y < 0) this->box->size.y = 0;
	else if(this->box->size.h <= 0)
	{
		this->box->size.y = right_y - 1;
		this->box->size.h = 1;
	}
}

void
Resize::down_corner(int y)
{
	this->box->size.h = y - this->box->size.y;

	if(this->box->size.y + this->box->size.h >
		 this->mode->texture_height())
		this->box->size.h =
			this->mode->texture_height() - this->box->size.y;
	else if(this->box->size.h < 1) this->box->size.h = 1;
}

void
Resize::left_corner(int x)
{
	int left_x{this->box->size.x};
	int right_x{this->box->size.x + this->box->size.w};
	this->box->size.x = x;
	this->box->size.w -= x - left_x;

	if(this->box->size.x < 0) this->box->size.x = 0;
	else if(this->box->size.w <= 0)
	{
		this->box->size.x = right_x - 1;
		this->box->size.w = 1;
	}
}

void
Resize::right_corner(int x)
{
	this->box->size.w = x - this->box->size.x;

	if(this->box->size.y + this->box->size.w >
		 this->mode->texture_height())
		this->box->size.w =
			this->mode->texture_height() - this->box->size.y;
	else if(this->box->size.w < 1) this->box->size.w = 1;
}

Resize::Resize(Mode::Sprite* mode):
  mode{mode},
  vertical_move{nullptr},
  horizontal_move{nullptr}
{
}

}
