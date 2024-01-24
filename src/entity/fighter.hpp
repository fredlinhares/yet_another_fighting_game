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

#ifndef YAFG_ENTITY_FIGHTER_H
#define YAFG_ENTITY_FIGHTER_H 1

#include <bitset>
#include <cstdint>

#include "../core.hpp"
#include "../entity.hpp"

namespace Entity
{

struct Fighter
{
  SDL_Rect sprite;

  std::bitset<8> input_status{};

  Direction current_direction;

  void
  tick();

  void
  render();

  Fighter();
};

}

#endif /* YAFG_ENTITY_FIGHTER_H */
