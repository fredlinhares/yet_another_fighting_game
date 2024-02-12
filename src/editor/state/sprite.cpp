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

#include "../mode/sprite.hpp"

namespace
{

inline bool
rect_clicked(const SDL_Rect &rect, int x, int y)
{
  return (x >= rect.x) && (x <= (rect.x + rect.w)) &&
    (y >= rect.y) && (y <= (rect.y + rect.h));
}

}

namespace State
{

void
Sprite::key_down(SDL_Keycode keycode)
{
  switch(keycode)
  {
  case SDLK_e:
    this->mode->zoom_in();
    break;
  case SDLK_d:
    this->mode->zoom_out();
    break;
  case SDLK_n:
    this->mode->add_sprite();
    break;
  }
}

void
Sprite::mouse_button_down(SDL_MouseButtonEvent& b)
{
  int x, y;
  this->mode->get_mouse_position(x, y);

  for(int i{0}; i < this->mode->sprites.size(); i++)
  {
    ::Sprite *sprite{&this->mode->sprites[0]};
    if(rect_clicked(sprite->edit_box, x, y))
    {
      this->mode->resize_state.sprite = sprite;

      this->mode->resize_state.horizontal_move = nullptr;
      this->mode->resize_state.vertical_move = nullptr;

      if(rect_clicked(sprite->resize_up_box, x, y))
      {
	this->mode->resize_state.vertical_move =
	  &State::Resize::up_corner;
      }
      else if(rect_clicked(sprite->resize_down_box, x, y))
      {
	this->mode->resize_state.vertical_move =
	  &State::Resize::down_corner;
      }
      else if(rect_clicked(sprite->resize_left_box, x, y))
      {
	this->mode->resize_state.horizontal_move =
	  &State::Resize::left_corner;
      }
      else if(rect_clicked(sprite->resize_right_box, x, y))
      {
	this->mode->resize_state.horizontal_move =
	  &State::Resize::right_corner;
      }
      else if(rect_clicked(sprite->resize_up_right_box, x, y))
      {
	this->mode->resize_state.vertical_move =
	  &State::Resize::up_corner;
	this->mode->resize_state.horizontal_move =
	  &State::Resize::right_corner;
      }
      else if(rect_clicked(sprite->resize_up_left_box, x, y))
      {
	this->mode->resize_state.vertical_move =
	  &State::Resize::up_corner;
	this->mode->resize_state.horizontal_move =
	  &State::Resize::left_corner;
      }
      else if(rect_clicked(sprite->resize_down_right_box, x, y))
      {
	this->mode->resize_state.vertical_move =
	  &State::Resize::down_corner;
	this->mode->resize_state.horizontal_move =
	  &State::Resize::right_corner;
      }
      else if(rect_clicked(sprite->resize_down_left_box, x, y))
      {
	this->mode->resize_state.vertical_move =
	  &State::Resize::down_corner;
	this->mode->resize_state.horizontal_move =
	  &State::Resize::left_corner;
      }

      this->mode->current_state = &this->mode->resize_state;
      return;
    }
  }

  this->mode->current_state = &this->mode->scroll_state;
}

Sprite::Sprite(Mode::Sprite* mode):
  mode{mode}
{
}

}
