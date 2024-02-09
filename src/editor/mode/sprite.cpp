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
Sprite::render_rect(const SDL_Rect &rect, uint8_t r, uint8_t g, uint8_t b)
{
  int x{(rect.x - this->src_rect.x) * this->zoom};
  int y{(rect.y - this->src_rect.y) * this->zoom};
  int w{rect.w * this->zoom};
  int h{rect.h * this->zoom};
  SDL_Rect position{x, y, w, h};

  SDL_SetRenderDrawColor(core.renderer, r, g, b, 0x33);
  SDL_RenderFillRect(core.renderer, &position);

  SDL_SetRenderDrawColor(core.renderer, r, g, b, 0xff);
  SDL_RenderDrawRect(core.renderer, &position);
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
Sprite::add_sprite()
{
  int mouse_x, mouse_y;
  SDL_GetMouseState(&mouse_x, &mouse_y);
  int x{this->src_rect.x + mouse_x / this->zoom};
  int y{this->src_rect.y + mouse_y / this->zoom};

  if(x < 10) x = 10;
  else if(x > this->tex_width - 10) x = this->tex_width - 10;

  if(y < 10) y = 10;
  else if(y > this->tex_width - 10) y = this->tex_width - 10;

  this->sprites.emplace_back(x - 10, y - 10, 20, 20);
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

  for(const ::Sprite &sprite: this->sprites)
  {
    this->render_rect(sprite.edit_box, 0x99, 0x33, 0x33);
    this->render_rect(sprite.size, 0x33, 0x99, 0x33);
    this->render_rect(sprite.resize_up_box, 0x33, 0x33, 0x99);
    this->render_rect(sprite.resize_down_box, 0x33, 0x33, 0x99);
    this->render_rect(sprite.resize_left_box, 0x33, 0x33, 0x99);
    this->render_rect(sprite.resize_righ_box, 0x33, 0x33, 0x99);
    this->render_rect(sprite.resize_up_right_box, 0x33, 0x33, 0x99);
    this->render_rect(sprite.resize_up_left_box, 0x33, 0x33, 0x99);
    this->render_rect(sprite.resize_down_right_box, 0x33, 0x33, 0x99);
    this->render_rect(sprite.resize_down_left_box, 0x33, 0x33, 0x99);
  }
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
