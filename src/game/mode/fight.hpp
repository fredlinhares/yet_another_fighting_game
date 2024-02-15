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

#ifndef YAFG_MODE_FIGHT_H
#define YAFG_MODE_FIGHT_H 1

#include "../mode.hpp"
#include "../entity/fighter.hpp"
#include "../input/config.hpp"

namespace Mode
{

struct Fight : public Base
{
  static constexpr int FLOOR_POSITION{203};

  Entity::Fighter player1;

  void
  key_down(SDL_Keycode keycode);
  void
  key_up(SDL_Keycode keycode);

  void
  joybutton_down(Uint8 player, Uint8 button);
  void
  joybutton_up(Uint8 player, Uint8 button);

  void
  tick();
  void
  render();

  Fight();
};

}

#endif /* YAFG_MODE_FIGHT_H */
