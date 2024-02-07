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

#include "jump_state.hpp"

#include "fighter.hpp"

namespace
{
  constexpr int HORIZONTAL_SPEED{3};
  constexpr int INITIAL_VERTICAL_SPEED{4};
  constexpr int GRAVIT_UPDATE_DELAY{8};
}

namespace Entity
{

void
JumpState::init()
{
  this->vertical_speed = - INITIAL_VERTICAL_SPEED;
  this->gravit_update_delay = GRAVIT_UPDATE_DELAY;

  switch(this->fighter->effective_direction)
  {
  case Input::Direction::up_left:
    this->horizontal_speed = - HORIZONTAL_SPEED;
    break;
  case Input::Direction::up_right:
    this->horizontal_speed = HORIZONTAL_SPEED;
    break;
  default:
    this->horizontal_speed = 0;
  }
}

void
JumpState::tick()
{
  this->fighter->y += this->vertical_speed;
  this->fighter->x += this->horizontal_speed;

  if(this->horizontal_speed > 0)
    this->fighter->collide_right();
  else if(this->horizontal_speed < 0)
    this->fighter->collide_left();

  if(this->gravit_update_delay-- <= 0)
  {
    this->gravit_update_delay = GRAVIT_UPDATE_DELAY;
    this->vertical_speed += 1;
  }

  if(this->fighter->collide_floor())
    this->fighter->set_state(STAND_STATE);
}

JumpState::JumpState(Fighter *f):
  State{f, 9}
{
}

}
