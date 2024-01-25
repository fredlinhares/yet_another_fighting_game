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

#include "fighter.hpp"

#include <algorithm>

#include "../mode/fight.hpp"
#include "jump_state.hpp"
#include "stand_state.hpp"
#include "walk_state.hpp"

namespace Entity
{

bool
Fighter::collide_floor()
{
  if(this->y > Mode::Fight::FLOOR_POSITION)
  {
    this->y = Mode::Fight::FLOOR_POSITION;
    return true;
  }
  return false;
}

bool
Fighter::collide_left()
{
  if(this->x - this->half_width < 0)
  {
    this->x = this->half_width;
    return true;
  }
  return false;
}

bool
Fighter::collide_right()
{
  if(this->x + this->half_width > WINDOW_WIDTH)
  {
    this->x = WINDOW_WIDTH -this->half_width;
    return true;
  }
  return false;
}

void
Fighter::tick()
{
  // Set direction.
  { // Eliminate self-contradicting input like left-right movement.
    Direction vertical_direction{Direction::none};
    Direction horizontal_direction{Direction::none};

    if(input_status[DIRECTION_UP_BIT])
      vertical_direction = Direction::up;
    else if(input_status[DIRECTION_DOWN_BIT])
      vertical_direction = Direction::down;

    if(input_status[DIRECTION_LEFT_BIT])
      horizontal_direction = Direction::left;
    else if(input_status[DIRECTION_RIGHT_BIT])
      horizontal_direction = Direction::right;

    this->current_direction = vertical_direction + horizontal_direction;
  }

  this->current_state->tick();
}

void
Fighter::render()
{
  SDL_SetRenderDrawColor(core.renderer, 0x33, 0x33, 0x99, 0xff);
  this->current_state->sprite.x = this->x + this->current_state->x;
  this->current_state->sprite.y = this->y + this->current_state->y;
  SDL_RenderFillRect(core.renderer, &this->current_state->sprite);
}

void
Fighter::set_state(int state)
{
  this->current_state = this->states[state];
  this->current_state->init();
}

Fighter::Fighter():
  x{192},
  y{Mode::Fight::FLOOR_POSITION},
  half_width{31},
  states{
    new StandState{this},
    new WalkState{this},
    new JumpState{this}}
{
  this->set_state(STAND_STATE);
}

Fighter::~Fighter()
{
  std::for_each(this->states.begin(), this->states.begin(), [](State *s)
    {delete s;});
}

}
