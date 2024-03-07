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

#include "box.hpp"

#include <array>

#include "../main.hpp"
#include "../mode/animation_list.hpp"
#include "../mode/box.hpp"

namespace State
{

void
Box::key_down(SDL_Keycode keycode)
{
  switch(keycode)
  {
  case SDLK_e:
    this->mode->zoom_in();
    break;
  case SDLK_d:
    this->mode->zoom_out();
    break;
  case SDLK_2:
		editor_state->next_game_mode = new Mode::Box{};
    break;
  case SDLK_3:
		editor_state->next_game_mode = new Mode::AnimationList{};
    break;
  }
}

void
Box::mouse_button_down(SDL_MouseButtonEvent& b)
{
	if(this->mode->sprite_list.is_clicked(b.x, b.y)) return;

	std::array<::Box*, 5> boxes{
		&this->mode->frame->sprite,
		&this->mode->frame->head,
		&this->mode->frame->upper_body,
		&this->mode->frame->lower_body,
		&this->mode->frame->collision};

  int x, y;
  this->mode->get_mouse_position(x, y);

	for(::Box* box: boxes)
	{
		Direction direction;

		if(box->click(&direction, x, y))
		{
			if(direction == Direction::none) continue;
			this->mode->resize_state.box = box;

			this->mode->resize_state.set_resize_move(direction);
      this->mode->current_state = &this->mode->resize_state;
      return;
		}
	}

	this->mode->current_state = &this->mode->box_state;
}

Box::Box(Mode::Box* mode):
	mode{mode}
{
}

}
