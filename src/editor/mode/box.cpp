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

#include "../main.hpp"

namespace Mode
{

void
Box::get_mouse_position(int &x, int &y)
{
  int mouse_x, mouse_y;
  SDL_GetMouseState(&mouse_x, &mouse_y);
  x = (mouse_x - this->_x) / this->zoom;
  y = (mouse_y - this->_y) / this->zoom;
}

void
Box::zoom_in()
{
  if(this->zoom >= 8) return;
  this->zoom *= 2;
}

void
Box::zoom_out()
{
  if(this->zoom <= 1) return;
  this->zoom /= 2;
}

void
Box::default_state()
{
	this->current_state = &this->box_state;
}

void
Box::render()
{
	this->render_sprite(*this->frame);

	this->render_rect(this->frame->head.size, 0x66, 0x66, 0xbb);
	this->render_rect(this->frame->upper_body.size, 0x22, 0x22, 0x77);
	this->render_rect(this->frame->lower_body.size, 0x44, 0x44, 0x99);
	this->render_rect(this->frame->collision.size, 0x33, 0x99, 0x33);
}

Box::Box():
	_x{core.window_width/2},
	_y{(core.window_height/6)*5},
	frame{&editor_state->frames[0]},
	box_state{this},
	resize_state{this}
{
	this->zoom = 1;
	this->current_state = &this->box_state;
}

}
