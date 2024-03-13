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

#include "../main.hpp"
#include "sprite.hpp"

namespace Mode
{

void
Sprite::correct_position()
{
  if(this->src_rect.x < 0) this->src_rect.x = 0;
  else if(this->src_rect.x + this->src_rect.w > this->tex_width)
    this->src_rect.x = this->tex_width - this->src_rect.w;

  if(this->src_rect.y < 0) this->src_rect.y = 0;
  else if(this->src_rect.y + this->src_rect.h > this->tex_height)
    this->src_rect.y = this->tex_height - this->src_rect.h;

	this->zoomable.x = - this->src_rect.x;
	this->zoomable.y = - this->src_rect.y;
}

void
Sprite::define_display_position()
{
  this->display_width = this->tex_width * this->zoomable.zoom();
  this->display_height = this->tex_height * this->zoomable.zoom();

  if(display_width < core.window_width)
  {
    this->src_rect.w = this->tex_width / this->zoomable.zoom();
    this->dst_rect.w = display_width;
  }
  else
  {
    this->src_rect.w = core.window_width / this->zoomable.zoom();
    this->dst_rect.w = core.window_width;
  }

  if(display_height < core.window_height)
  {
    this->src_rect.h = this->tex_height / this->zoomable.zoom();
    this->dst_rect.h = display_height;
  }
  else
  {
    this->src_rect.h = core.window_height / this->zoomable.zoom();
    this->dst_rect.h = core.window_height;
  }
}

void
Sprite::get_mouse_position(int &x, int &y)
{
  int mouse_x, mouse_y;
  SDL_GetMouseState(&mouse_x, &mouse_y);
  x = this->src_rect.x + mouse_x / this->zoomable.zoom();
  y = this->src_rect.y + mouse_y / this->zoomable.zoom();
}

void
Sprite::zoom_in()
{
  this->define_display_position();

  this->src_rect.x += this->src_rect.w / 2;
  this->src_rect.y += this->src_rect.h / 2;

	this->correct_position();
}

void
Sprite::zoom_out()
{
  this->define_display_position();

  this->src_rect.x -= this->src_rect.w / 4;
  this->src_rect.y -= this->src_rect.h / 4;

	this->correct_position();
}

void
Sprite::default_state()
{
	this->current_state = &this->sprite_state;
}

void
Sprite::scroll(int x, int y)
{
  if(core.window_width < this->display_width)
    this->src_rect.x -= x;

  if(core.window_height < this->display_height)
    this->src_rect.y -= y;

	this->correct_position();
}

void
Sprite::add_sprite()
{
  int x, y;
  this->get_mouse_position(x, y);

  if(x < 10) x = 10;
  else if(x > this->tex_width - 10) x = this->tex_width - 10;

  if(y < 10) y = 10;
  else if(y > this->tex_height - 10) y = this->tex_height - 10;

  editor_state->frames.emplace_back(x - 10, y - 10, 20, 20);
}

void
Sprite::tick()
{
}

void
Sprite::render()
{
  SDL_RenderCopy(
    core.renderer, editor_state->texture, &this->src_rect, &dst_rect);

  for(const Frame &frame: editor_state->frames)
    this->zoomable.render_rect(frame.sprite.size, 0x33, 0x99, 0x33);
}

Sprite::Sprite():
	zoomable{
		0, 0,
		core.window_width, core.window_height,
		0, 0},
  resize_state{this, &this->zoomable},
  scroll_state{this},
  sprite_state{this}
{
  this->current_state = &this->sprite_state;

  SDL_QueryTexture(
    editor_state->texture, nullptr, nullptr, &tex_width, &tex_height);

  this->src_rect.x = 0;
  this->dst_rect.x = 0;
  this->src_rect.y = 0;
  this->dst_rect.y = 0;

	this->zoomable.up_limit = 0;
	this->zoomable.down_limit = this->tex_height;
	this->zoomable.left_limit = 0;
	this->zoomable.right_limit = this->tex_width;

  this->define_display_position();
}

}
