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

#include "state.hpp"

#include "main.hpp"
#include "mode/animation_list.hpp"
#include "mode/box.hpp"
#include "mode/sprite.hpp"

namespace State
{

void
Base::key_down(SDL_Keycode keycode)
{
	if(this->key_map.contains(keycode)) this->key_map[keycode]();
}

void
Base::key_up(SDL_Keycode keycode)
{
}

Base::Base():
	key_map{
		{SDLK_1, [](){editor_state->next_game_mode = new Mode::Sprite{};}},
		{SDLK_2, [](){editor_state->next_game_mode = new Mode::Box{};}},
		{SDLK_3, [](){editor_state->next_game_mode = new Mode::AnimationList{};}}}
{
}

}
