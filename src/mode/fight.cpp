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

#include "fight.hpp"

#include "../core.hpp"

namespace Mode
{

void
Fight::key_down(SDL_Keycode keycode)
{
  if(core.player1_input->contains(keycode))
    player1.input_status[core.player1_input->at(keycode)] = true;
}

void
Fight::key_up(SDL_Keycode keycode)
{
  if(core.player1_input->contains(keycode))
    player1.input_status[core.player1_input->at(keycode)] = false;
}

void
Fight::tick()
{
  player1.tick();
}

void
Fight::render()
{
  player1.render();
}

Fight::Fight()
{
}

}