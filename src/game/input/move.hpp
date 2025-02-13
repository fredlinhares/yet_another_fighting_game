/*
 * Copyright 2024-2025 Frederico de Oliveira Linhares
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

#ifndef YAFG_INPUT_MOVE_H
#define YAFG_INPUT_MOVE_H 1

#include <initializer_list>
#include <vector>

#include "config.hpp"
#include "relative_direction.hpp"

namespace Input
{

union MoveEntry
{
  AttackState attack;
  RelativeDirection direction;

  MoveEntry(AttackState attack);
  MoveEntry(RelativeDirection direction);
};

struct MoveNode
{
  bool is_attack;
	bool is_required;
  MoveEntry entry;

  MoveNode(bool is_required, AttackState entry);
  MoveNode(bool is_required, RelativeDirection entry);
};

struct Move
{
  const char *move_name;
  std::vector<MoveNode> nodes;

  Move(const char *move_name, std::initializer_list<MoveNode> nodes);
};

}

#endif /* YAFG_INPUT_MOVE_H */
