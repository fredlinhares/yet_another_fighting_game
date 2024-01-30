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

#include "ring.hpp"
#include <iostream>

namespace Input
{

Ring::Ring():
  state_index{0}
{
}

void
Ring::change_state(Input::Direction direction, Input::AttackState attack)
{
  this->state_index++;
  if(this->state_index >= Ring::SIZE) this->state_index = 0;

  this->current_state()->direction = direction;
  this->current_state()->attack = attack;

  int index{this->state_index + 1};
  for(int i{0}; i < Ring::SIZE; i++)
  {
    if(index >= Ring::SIZE) index = 0;

    switch(this->states[index].direction)
    {
    case Input::Direction::none:
      std::cout << "_";
      break;
    case Input::Direction::up:
      std::cout << "↑";
      break;
    case Input::Direction::down:
      std::cout << "↓";
      break;
    case Input::Direction::left:
      std::cout << "←";
      break;
    case Input::Direction::right:
      std::cout << "→";
      break;
    case Input::Direction::up_left:
      std::cout << "↖";
      break;
    case Input::Direction::up_right:
      std::cout << "↗";
      break;
    case Input::Direction::down_left:
      std::cout << "↙";
      break;
    case Input::Direction::down_right:
      std::cout << "↘";
      break;
    }
    std::cout << " ";

    // if(states[index].attack.count() > 0)
    {
      if(this->states[index].attack[Input::ATTACK_BIT_HEAVY_PUNCH])
	std::cout << "HP ";
      if(this->states[index].attack[Input::ATTACK_BIT_HEAVY_KICK])
	std::cout << "HK ";
      if(this->states[index].attack[Input::ATTACK_BIT_LIGHT_PUNCH])
	std::cout << "LP ";
      if(this->states[index].attack[Input::ATTACK_BIT_LIGHT_KICK])
	std::cout << "LK ";
    }
    std::cout << "-";

    index++;
  }
  std::cout << std::endl;
}

}
