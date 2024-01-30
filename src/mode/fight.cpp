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

namespace
{

inline void
change_key_state(Entity::Fighter &player1, SDL_Keycode keycode, bool state)
{
  if(core.player1_input->contains(keycode))
  {
    uint8_t input_type = core.player1_input->at(keycode)[0];
    uint8_t input_bit = core.player1_input->at(keycode)[1];

    switch(input_type)
    {
    case Input::TYPE_BIT_DIRECTION:
      player1.current_direction[input_bit] = state;
      break;
    case Input::TYPE_BIT_ATTACK:
      player1.current_attack[input_bit] = state;
      break;
    }
  }
}

}

namespace Mode
{

void
Fight::key_down(SDL_Keycode keycode)
{
  change_key_state(this->player1, keycode, true);
}

void
Fight::key_up(SDL_Keycode keycode)
{
  change_key_state(this->player1, keycode, false);
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
