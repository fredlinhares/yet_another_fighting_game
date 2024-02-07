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

#include "walk_state.hpp"

#include "fighter.hpp"

namespace
{
  constexpr int SPEED{3};
}

namespace Entity
{

void
WalkState::init()
{
  this->animation.reset();
}

void
WalkState::tick()
{
  this->sprite_index = this->animation.tick();

  switch(this->fighter->effective_direction)
  {
  case Input::Direction::left:
    this->fighter->x -= SPEED;
    this->fighter->collide_left();
    break;
  case Input::Direction::right:
    this->fighter->x += SPEED;
    this->fighter->collide_right();
    break;
  case Input::Direction::up:
  case Input::Direction::up_left:
  case Input::Direction::up_right:
    this->fighter->set_state(JUMP_STATE);
    break;
  default:
    this->fighter->set_state(STAND_STATE);
  }
}

WalkState::WalkState(Fighter *f):
  State{f, 4},
  animation{true, {
    {15, 4},
    {15, 5},
    {15, 6},
    {15, 7},
    {15, 8}}}
{
}

}
