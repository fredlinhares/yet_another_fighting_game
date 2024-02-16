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

#ifndef YAFG_INPUT_RELATIVE_DIRECTION_H
#define YAFG_INPUT_RELATIVE_DIRECTION_H 1

#include <cstdint>

namespace Input
{

enum class RelativeDirection: uint8_t
{
  none = 0,
  up = 1,
  down = 2,
  back = 3,
  front = 6,
  up_back = 4,
  up_front = 7,
  down_back = 5,
  down_front = 8
};

RelativeDirection
operator+(const RelativeDirection &a, const RelativeDirection &b);

}

#endif /* YAFG_INPUT_RELATIVE_DIRECTION_H */
