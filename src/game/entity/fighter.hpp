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
#include <vector>

#include "../../common/core.hpp"
#include "../../common/direction.hpp"
#include "../../common/graphics/frame.hpp"
#include "../../common/graphics/texture.hpp"
#include "../input/config.hpp"
#include "../input/move.hpp"
#include "../input/relative_direction.hpp"
#include "../input/ring.hpp"
#include "state.hpp"

namespace Entity
{

constexpr int STAND_STATE = 0;
constexpr int WALK_STATE = 1;
constexpr int JUMP_STATE = 2;

class Fighter
{
  SDL_Texture *texture;
  std::vector<Graphics::Frame> frames;

  std::vector<State*> states;
  State* current_state;

public:
  const int half_width;

  Direction facing_direction;
  int x, y;

  Input::AttackState last_attack, current_attack;
  Input::DirectionState current_direction;
  Input::RelativeDirection effective_direction;
  Input::Ring input_ring;
  std::vector<Input::Move> moves;

  bool
  collide_floor();

  bool
  collide_left();

  bool
  collide_right();

  void
  tick();

  void
  render();

  void
  set_state(int state);

  Fighter(Direction facing_direction, int x);

  ~Fighter();
};

}

#endif /* YAFG_ENTITY_FIGHTER_H */
