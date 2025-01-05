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

namespace
{

inline void
decrement_ring_rindex(int &ring_rindex)
{
  ring_rindex--;
  if(ring_rindex < 0) ring_rindex = Input::Ring::SIZE - 1;
}

}

namespace Input
{

Ring::Ring():
  start_index{0},
  num_inputs{0}
{
  this->reset();
}

void
Ring::reset()
{
  this->start_index = 0;
  this->num_inputs = 0;
}

void
Ring::change_state(
  Input::RelativeDirection direction, Input::AttackState attack)
{
  if(this->num_inputs < SIZE)
    this->num_inputs++;
  else
  {
    this->start_index++;
    if(this->start_index >= Ring::SIZE) this->start_index = 0;
  }

  auto current_input{&this->inputs[this->current_index()]};
  current_input->direction = direction;
  current_input->attack = attack;

  int index{this->start_index};
  for(int i{0}; i < this->num_inputs; i++)
  {
    if(index >= Ring::SIZE) index = 0;

    switch(this->inputs[index].direction)
    {
    case Input::RelativeDirection::none:
      std::cout << "_";
      break;
    case Input::RelativeDirection::up:
      std::cout << "↑";
      break;
    case Input::RelativeDirection::down:
      std::cout << "↓";
      break;
    case Input::RelativeDirection::back:
      std::cout << "←";
      break;
    case Input::RelativeDirection::front:
      std::cout << "→";
      break;
    case Input::RelativeDirection::up_back:
      std::cout << "↖";
      break;
    case Input::RelativeDirection::up_front:
      std::cout << "↗";
      break;
    case Input::RelativeDirection::down_back:
      std::cout << "↙";
      break;
    case Input::RelativeDirection::down_front:
      std::cout << "↘";
      break;
    }
    std::cout << " ";

    if(this->inputs[index].attack[Input::ATTACK_INDEX_HEAVY_PUNCH])
      std::cout << "HP ";
    if(this->inputs[index].attack[Input::ATTACK_INDEX_HEAVY_KICK])
      std::cout << "HK ";
    if(this->inputs[index].attack[Input::ATTACK_INDEX_LIGHT_PUNCH])
      std::cout << "LP ";
    if(this->inputs[index].attack[Input::ATTACK_INDEX_LIGHT_KICK])
      std::cout << "LK ";
    std::cout << "-";

    index++;
  }
  std::cout << std::endl;
}

const char*
Ring::find_move(const std::vector<Move> &moves)
{
  int ring_end{this->start_index + this->num_inputs};
  if(ring_end >= Ring::SIZE) ring_end -= Ring::SIZE;
  ring_end -= 1;

  for(int i{0}; i < moves.size(); i++)
  {
    const Move *current_move{&moves.at(i)};
    if(current_move->nodes.size() > this->num_inputs) continue;

    int node_rindex = current_move->nodes.size() - 1;
    int ring_rindex{ring_end};

    for(int ii{0}; ii < Ring::SIZE; ii++)
    {
      bool valid_node{false};
      if(current_move->nodes[node_rindex].is_attack)
      {
				if(current_move->nodes[node_rindex].entry.attack ==
					 this->inputs[ring_rindex].attack)
					valid_node = true;
      }
      else
      {
				if(current_move->nodes[node_rindex].entry.direction ==
					 this->inputs[ring_rindex].direction)
					valid_node = true;
				// If is empty movement, maybe the player slipped for a single frame,
				// so we read the previous one. Or, if current direction is the same as
				// the next one.
				else if(this->inputs[ring_rindex].direction == RelativeDirection::none
								|| current_move->nodes[node_rindex + 1].entry.direction ==
								this->inputs[ring_rindex].direction)
				{
					decrement_ring_rindex(ring_rindex);
					continue;
				}
      }

      if(valid_node)
      {
				if(node_rindex == 0)
				{
					this->reset();
					return current_move->move_name;
				}

				node_rindex--;
				decrement_ring_rindex(ring_rindex);
      }
      else
				break;
    }
  }

  return nullptr;
}

}
