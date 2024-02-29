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
Box::render()
{
	SDL_Rect *position{&this->frame->sprite.size};

  SDL_Rect destination{
    this->_x + frame->x,
    this->_y + frame->y,
    position->w * this->zoom,
    position->h * this->zoom
  };

	SDL_RenderCopy(
		core.renderer, editor_state->texture, position, &destination);

	this->render_rect(this->frame->head.size, 0x55, 0x55, 0x99);
	this->render_rect(this->frame->upper_body.size, 0x33, 0x33, 0x99);
	this->render_rect(this->frame->lower_body.size, 0x44, 0x44, 0x99);
	this->render_rect(this->frame->collision.size, 0x33, 0x99, 0x33);
}

Box::Box():
	_x{core.window_width/2},
	_y{core.window_height/2},
	frame{&editor_state->frames[0]},
	box_state{this}
{
	this->zoom = 1;
	this->current_state = &this->box_state;
}

}
