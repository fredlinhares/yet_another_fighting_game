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
}

void
Sprite::define_display_position()
{
  this->display_width = this->tex_width * this->zoom;
  this->display_height = this->tex_height * this->zoom;

  if(display_width < core.window_width)
  {
    this->src_rect.w = this->tex_width / this->zoom;
    this->dst_rect.w = display_width;
  }
  else
  {
    this->src_rect.w = core.window_width / this->zoom;
    this->dst_rect.w = core.window_width;
  }

  if(display_height < core.window_height)
  {
    this->src_rect.h = this->tex_height / this->zoom;
    this->dst_rect.h = display_height;
  }
  else
  {
    this->src_rect.h = core.window_height / this->zoom;
    this->dst_rect.h = core.window_height;
  }
}

void
Sprite::zoom_in()
{
  if(this->zoom >= 8) return;
  this->zoom *= 2;
  this->define_display_position();

  this->src_rect.x += this->src_rect.w / 2;
  this->src_rect.y += this->src_rect.h / 2;

  this->correct_position();  
}

void
Sprite::zoom_out()
{
  if(this->zoom <= 1) return;
  this->zoom /= 2;
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
Sprite::tick()
{
}

void
Sprite::render()
{
  SDL_RenderCopy(
    core.renderer, this->texture, &this->src_rect, &dst_rect);
}

Sprite::Sprite(SDL_Texture* texture):
  texture{texture},
  zoom{1},
  scroll_state{this},
  sprite_state{this}
{
  this->current_state = &this->sprite_state;

  SDL_QueryTexture(
    this->texture, nullptr, nullptr, &tex_width, &tex_height);

  this->src_rect.x = 0;
  this->dst_rect.x = 0;
  this->src_rect.y = 0;
  this->dst_rect.y = 0;

  this->define_display_position();
}

}
