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

#ifndef YAFG_INPUT_RING_H
#define YAFG_INPUT_RING_H 1

#include "state.hpp"

namespace Input
{

struct Ring
{
  static constexpr int SIZE{16};

  int state_index;
  State states[SIZE];

  Ring();

  inline State*
  current_state(){return &this->states[this->state_index];};

  void
  change_state(Input::Direction direction, Input::AttackState attack);
};

}

#endif /* YAFG_INPUT_RING_H */
