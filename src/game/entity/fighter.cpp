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

#include "../../common/parser.hpp"
#include "../mode/fight.hpp"
#include "jump_state.hpp"
#include "stand_state.hpp"
#include "walk_state.hpp"
#include <iostream>

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
  if(this->x + this->half_width > core.window_width)
  {
    this->x = core.window_width -this->half_width;
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

    if(this->current_direction[Input::DIRECTION_INDEX_UP])
      vertical_direction = Direction::up;
    else if(this->current_direction[Input::DIRECTION_INDEX_DOWN])
      vertical_direction = Direction::down;

    if(this->current_direction[Input::DIRECTION_INDEX_LEFT])
      horizontal_direction = Direction::left;
    else if(this->current_direction[Input::DIRECTION_INDEX_RIGHT])
      horizontal_direction = Direction::right;

    this->effective_direction = vertical_direction + horizontal_direction;
  }

  Input::AttackState effective_attack{0};
  if(this->current_attack != this->last_attack)
  {
    effective_attack = this->current_attack;
    this->last_attack = this->current_attack;
  }

  if((effective_attack != this->input_ring.current_input()->attack) ||
     (this->effective_direction !=
      this->input_ring.current_input()->direction))
  {
    this->input_ring.change_state(this->effective_direction, effective_attack);
    auto move{input_ring.find_move(this->moves)};
    if(move != nullptr) std::cout << move << std::endl;
  }

  this->current_state->tick();
}

void
Fighter::render()
{
  Graphics::Frame *frame{&this->frames[this->current_state->frame_index]};
  SDL_Rect destination{
    this->x + frame->x,
    this->y + frame->y,
    frame->sprite.w,
    frame->sprite.h
  };

  SDL_RenderCopy(core.renderer, this->texture, &frame->sprite, &destination);
}

void
Fighter::set_state(int state)
{
  this->current_state = this->states[state];
  this->current_state->init();
}

Fighter::Fighter():
  texture{Graphics::Texture::load("fighters/default/sprites.png")},
  states{
    new StandState{this},
    new WalkState{this},
    new JumpState{this}},
  half_width{31},
  x{192},
  y{Mode::Fight::FLOOR_POSITION},
  last_attack{},
  current_attack{},
  current_direction{},
  moves{
    {"Fireball",
     {Input::MoveNode(false, Direction::down),
      Input::MoveNode(false, Direction::down_right),
      Input::MoveNode(false, Direction::right),
      Input::MoveNode(true, Input::AttackState{Input::ATTACK_BIT_HEAVY_PUNCH})}},
    {"Uppercut",
     {Input::MoveNode(false, Direction::right),
      Input::MoveNode(false, Direction::down),
      Input::MoveNode(false, Direction::down_right),
      Input::MoveNode(true, Input::AttackState{Input::ATTACK_BIT_HEAVY_PUNCH})}}}
{
  Parse::frames(&this->frames, "fighters/default/frames.conf");
  this->set_state(STAND_STATE);
}

Fighter::~Fighter()
{
  SDL_DestroyTexture(this->texture);
  std::for_each(this->states.begin(), this->states.begin(), [](State *s)
    {delete s;});
}

}
