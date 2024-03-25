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

#include <iostream>

namespace Mode
{

void
Sprite::set_boxes()
{
	this->boxes.clear();
  for(int i{0}; i < editor_state->frames.size(); i++)
		this->boxes.emplace_back(
			this, &this->sprite_box, &editor_state->frames[i].sprite,
			0x33, 0x99, 0x33);
}

void
Sprite::correct_position()
{
  if(this->src_rect.x < 0) this->src_rect.x = 0;
  else if(this->src_rect.x + this->src_rect.w > this->tex_width)
    this->src_rect.x = this->tex_width - this->src_rect.w;

  if(this->src_rect.y < 0) this->src_rect.y = 0;
  else if(this->src_rect.y + this->src_rect.h > this->tex_height)
    this->src_rect.y = this->tex_height - this->src_rect.h;

	this->sprite_box.x = - this->src_rect.x;
	this->sprite_box.y = - this->src_rect.y;
}

void
Sprite::define_display_position()
{
  this->display_width = this->tex_width * this->sprite_box.zoom();
  this->display_height = this->tex_height * this->sprite_box.zoom();

  if(display_width < core.window_width)
  {
    this->src_rect.w = this->tex_width / this->sprite_box.zoom();
    this->dst_rect.w = display_width;
  }
  else
  {
    this->src_rect.w = core.window_width / this->sprite_box.zoom();
    this->dst_rect.w = core.window_width;
  }

  if(display_height < core.window_height)
  {
    this->src_rect.h = this->tex_height / this->sprite_box.zoom();
    this->dst_rect.h = display_height;
  }
  else
  {
    this->src_rect.h = core.window_height / this->sprite_box.zoom();
    this->dst_rect.h = core.window_height;
  }
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
  this->sprite_box.get_mouse_position(x, y);

  if(x < 10) x = 10;
  else if(x > this->tex_width - 10) x = this->tex_width - 10;

  if(y < 10) y = 10;
  else if(y > this->tex_height - 10) y = this->tex_height - 10;

  editor_state->frames.emplace_back(x - 10, y - 10, 20, 20);
	this->set_boxes();
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

	this->sprite_box.render();
}

Sprite::Sprite():
	sprite_box{
		this, &this->boxes,
		core.window_width, core.window_height,
		0, 0},
  sprite_state{this},
	Base{&this->sprite_state}
{
	this->buttons.emplace_back(&this->sprite_box);

  SDL_QueryTexture(
    editor_state->texture, nullptr, nullptr, &tex_width, &tex_height);

  this->src_rect.x = 0;
  this->dst_rect.x = 0;
  this->src_rect.y = 0;
  this->dst_rect.y = 0;

	this->sprite_box.up_limit = 0;
	this->sprite_box.down_limit = this->tex_height;
	this->sprite_box.left_limit = 0;
	this->sprite_box.right_limit = this->tex_width;

	this->set_boxes();
  this->define_display_position();
}

Sprite::~Sprite()
{
	this->clear_state();
}

}
