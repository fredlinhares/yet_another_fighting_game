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

#include "zoomable.hpp"

#include "../main.hpp"

namespace Mode
{

void
Zoomable::render_sprite(const Frame &frame)
{
	const SDL_Rect *position{&frame.sprite.size};

  SDL_Rect destination{
    this->x() + frame.x * this->zoom,
    this->y() + frame.y * this->zoom,
    position->w * this->zoom,
    position->h * this->zoom
  };

	SDL_RenderCopy(
		core.renderer, editor_state->texture, position, &destination);
}

void
Zoomable::render_rect(const SDL_Rect &rect, uint8_t r, uint8_t g, uint8_t b)
{
	int x, y;
	if(this->x() > 0)
		x = this->x() + rect.x * this->zoom;
	else
		x = (this->x() + rect.x) * this->zoom;

	if(this->y() > 0)
		y = this->y() + rect.y * this->zoom;
	else
		y = (this->y() + rect.y) * this->zoom;

  int w{rect.w * this->zoom};
  int h{rect.h * this->zoom};
  SDL_Rect position{x, y, w, h};

  SDL_SetRenderDrawColor(core.renderer, r, g, b, 0x33);
  SDL_RenderFillRect(core.renderer, &position);

  SDL_SetRenderDrawColor(core.renderer, r, g, b, 0xff);
  SDL_RenderDrawRect(core.renderer, &position);
}

}
