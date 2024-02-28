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
Animation::zoom_in()
{
  if(this->zoom >= 8) return;
  this->zoom *= 2;
}

void
Animation::zoom_out()
{
  if(this->zoom <= 1) return;
  this->zoom /= 2;
}


void
Animation::tick()
{
	this->frame_index = this->current_animation->tick();
}

void
Animation::render()
{
	Frame *frame{&editor_state->frames[this->frame_index]};
	SDL_Rect *position{&frame->sprite.size};

  SDL_Rect destination{
    this->_x + frame->x,
    this->_y + frame->y,
    position->w * this->zoom,
    position->h * this->zoom
  };

	SDL_RenderCopy(
		core.renderer, editor_state->texture, position, &destination);
}

Animation::Animation(const char *animation_name):
	_x{core.window_width/2},
	_y{core.window_height/2},
	current_animation{editor_state->animations[animation_name]},
	animation_state{this}
{
	this->zoom = 1;
	this->current_state = &this->animation_state;
}

}
