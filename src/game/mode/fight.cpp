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

#include "../../common/core.hpp"
#include "../input.hpp"

namespace
{

inline void
change_key_state(Entity::Fighter &player1, SDL_Keycode keycode, bool state)
{
  if(input_config->player_keyboard.contains(keycode))
  {
    uint8_t input_type = input_config->player_keyboard.at(keycode)[0];
    uint8_t input_bit = input_config->player_keyboard.at(keycode)[1];

    switch(input_type)
    {
    case Input::TYPE_INDEX_DIRECTION:
      player1.current_direction[input_bit] = state;
      break;
    case Input::TYPE_INDEX_ATTACK:
      player1.current_attack[input_bit] = state;
      break;
    }
  }
}

inline void
change_button_state(Entity::Fighter &player1, Uint8 keycode, bool state)
{
  if(input_config->player_joystick[0].contains(keycode))
  {
    uint8_t input_type = input_config->player_joystick[0].at(keycode)[0];
    uint8_t input_bit = input_config->player_joystick[0].at(keycode)[1];

    switch(input_type)
    {
    case Input::TYPE_INDEX_DIRECTION:
      player1.current_direction[input_bit] = state;
      break;
    case Input::TYPE_INDEX_ATTACK:
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
Fight::joybutton_down(Uint8 player, Uint8 button)
{
  change_button_state(this->player1, button, true);
}

void
Fight::joybutton_up(Uint8 player, Uint8 button)
{
  change_button_state(this->player1, button, false);
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
