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
Sprite::scroll(int x, int y)
{
  if(core.window_width < tex_width)
  {
    if(x > 0)
    {
      this->src_rect.x -= x;
      if(this->src_rect.x < 0) this->src_rect.x = 0;
    }
    else if(x < 0)
    {
      this->src_rect.x -= x;
      if(this->src_rect.x + core.window_width > tex_width)
	this->src_rect.x = tex_width - core.window_width;
    }
  }

  if(core.window_height < tex_height)
  {
    if(y > 0)
    {
      this->src_rect.y -= y;
      if(this->src_rect.y < 0) this->src_rect.y = 0;
    }
    else if(y < 0)
    {
      this->src_rect.y -= y;
      if(this->src_rect.y + core.window_height > tex_height)
	this->src_rect.y = tex_height - core.window_height;
    }
  }
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

  if(this->tex_width < core.window_width)
  {
    this->src_rect.w = this->tex_width;
    this->dst_rect.w = this->tex_width;
  }
  else
  {
    this->src_rect.w = core.window_width;
    this->dst_rect.w = core.window_width;
  }

  if(this->tex_height < core.window_height)
  {
    this->src_rect.h = this->tex_height;
    this->dst_rect.h = this->tex_height;
  }
  else
  {
    this->src_rect.h = core.window_height;
    this->dst_rect.h = core.window_height;
  }
}

}
