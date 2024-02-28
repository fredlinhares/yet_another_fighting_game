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

#include "animation.hpp"

#include "../main.hpp"
#include "../mode/animation.hpp"
#include "../mode/animation_list.hpp"

namespace State
{

void
Animation::key_down(SDL_Keycode keycode)
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
		editor_state->next_game_mode = new Mode::AnimationList{};
    break;
  }
}

void
Animation::mouse_button_down(SDL_MouseButtonEvent& b)
{
}

Animation::Animation(Mode::Animation* mode):
	mode{mode}
{
}

}
