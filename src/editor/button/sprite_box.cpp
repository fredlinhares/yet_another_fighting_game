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

#include "sprite_box.hpp"

#include "../main.hpp"

namespace Button
{

void
SpriteBox::get_mouse_position(int &x, int &y)
{
	if(this->x <= 0 || this->y <= 0)
	{
		x = - this->x + x / this->_zoom;
		y = - this->y + y / this->_zoom;
	}
	else
	{
		x = (x - this->x) / this->_zoom;
		y = (y - this->y) / this->_zoom;
	}
}

void
SpriteBox::zoom_in()
{
	if(this->_zoom >= 8) return;
	this->_zoom *= 2;
}

void
SpriteBox::zoom_out()
{
	if(this->_zoom <= 1) return;
	this->_zoom /= 2;
}

void
SpriteBox::render_sprite(const Graphics::Frame &frame)
{
	const SDL_Rect *position{&frame.sprite};

  SDL_Rect destination{
		this->x + frame.x * this->_zoom,
		this->y + frame.y * this->_zoom,
		position->w * this->_zoom,
		position->h * this->_zoom
  };

	SDL_RenderCopy(
		core.renderer, editor_state->texture, position, &destination);
}

void
SpriteBox::render_rect(const SDL_Rect &rect, uint8_t r, uint8_t g, uint8_t b)
{
	int x, y;
	if(this->x > 0)
		x = this->x + rect.x * this->_zoom;
	else
		x = (this->x + rect.x) * this->_zoom;

	if(this->y > 0)
		y = this->y + rect.y * this->_zoom;
	else
		y = (this->y + rect.y) * this->_zoom;

	int w{rect.w * this->_zoom};
	int h{rect.h * this->_zoom};
  SDL_Rect position{x, y, w, h};

  SDL_SetRenderDrawColor(core.renderer, r, g, b, 0x33);
  SDL_RenderFillRect(core.renderer, &position);

  SDL_SetRenderDrawColor(core.renderer, r, g, b, 0xff);
  SDL_RenderDrawRect(core.renderer, &position);
}

void
SpriteBox::click_action(int x, int y)
{
	this->get_mouse_position(x, y);

	for(Button::Base *box: *this->boxes) if(box->is_clicked(x, y)) return;
}

void
SpriteBox::render()
{
	for(Button::Base *box: *this->boxes) box->render();
}

SpriteBox::SpriteBox(
	Mode::Base *mode,
	std::vector<Button::Base*> *boxes,
	int width, int height,
	int center_x, int center_y):
	_zoom{1},
	mode{mode},
	boxes{boxes},
	x{center_x},
	y{center_y}
{
	this->location.x = 0;
	this->location.y = 0;
	this->location.w = width;
	this->location.h = height;
}

}
