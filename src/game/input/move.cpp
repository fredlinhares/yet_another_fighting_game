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

#include "move.hpp"

namespace Input
{

MoveEntry::MoveEntry(AttackState attack):
  attack{attack}
{
}

MoveEntry::MoveEntry(RelativeDirection direction):
  direction{direction}
{
}

MoveNode::MoveNode(bool is_attack, bool is_required, MoveEntry entry):
  is_attack{is_attack},
	is_required{is_required},
  entry{entry}
{
}

Move::Move(const char *move_name, std::initializer_list<MoveNode> nodes):
  move_name{move_name},
  nodes{nodes}
{
}

}
