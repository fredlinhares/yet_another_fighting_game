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

#include "../../common/direction.hpp"
#include "../main.hpp"
#include "../mode/animation_list.hpp"
#include "../mode/sprite.hpp"

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
  case SDLK_2:
		editor_state->next_game_mode = new Mode::AnimationList{};
    break;
  }
}

void
Sprite::mouse_button_down(SDL_MouseButtonEvent& b)
{
  int x, y;
  this->mode->get_mouse_position(x, y);

  for(int i{0}; i < editor_state->sprites.size(); i++)
  {
    ::Sprite *sprite{&editor_state->sprites[i]};
    Direction vertical_direction{Direction::none};
    Direction horizontal_direction{Direction::none};
    Direction direction;

    if(x >= sprite->outer_left && x <= sprite->outer_right &&
			 y >= sprite->outer_up && y <= sprite->outer_down)
    {
      if(x < sprite->center_left)
	horizontal_direction = Direction::left;
      else if(x < sprite->center_right)
	horizontal_direction = Direction::none;
      else
	horizontal_direction = Direction::right;

      if(y < sprite->center_up)
	vertical_direction = Direction::up;
      else if(y < sprite->center_down)
	vertical_direction = Direction::none;
      else
	vertical_direction = Direction::down;
    }

    direction = vertical_direction + horizontal_direction;

    if(direction != Direction::none)
    {
      this->mode->resize_state.sprite = sprite;

      this->mode->resize_state.horizontal_move = nullptr;
      this->mode->resize_state.vertical_move = nullptr;

      switch(direction)
      {
      case Direction::up:
	this->mode->resize_state.vertical_move =
	  &State::Resize::up_corner;
	break;
      case Direction::down:
	this->mode->resize_state.vertical_move =
	  &State::Resize::down_corner;
	break;
      case Direction::left:
	this->mode->resize_state.horizontal_move =
	  &State::Resize::left_corner;
	break;
      case Direction::right:
	this->mode->resize_state.horizontal_move =
	  &State::Resize::right_corner;
	break;
      case Direction::up_right:
	this->mode->resize_state.vertical_move =
	  &State::Resize::up_corner;
	this->mode->resize_state.horizontal_move =
	  &State::Resize::right_corner;
	break;
      case Direction::up_left:
	this->mode->resize_state.vertical_move =
	  &State::Resize::up_corner;
	this->mode->resize_state.horizontal_move =
	  &State::Resize::left_corner;
	break;
      case Direction::down_right:
	this->mode->resize_state.vertical_move =
	  &State::Resize::down_corner;
	this->mode->resize_state.horizontal_move =
	  &State::Resize::right_corner;
	break;
      case Direction::down_left:
	this->mode->resize_state.vertical_move =
	  &State::Resize::down_corner;
	this->mode->resize_state.horizontal_move =
	  &State::Resize::left_corner;
	break;
      }

			this->mode->resize_state.sprite = &editor_state->sprites[i];
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
