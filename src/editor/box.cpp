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

#include "box.hpp"

void
Box::update_size()
{
  this->outer_left = this->size.x - 2;
  this->center_left = this->size.x + 2;
  this->outer_right = this->size.x + this->size.w + 2;
  this->center_right = this->size.x + this->size.w - 2;
  this->outer_up = this->size.y - 2;
  this->center_up = this->size.y + 2;
  this->outer_down = this->size.y + this->size.h + 2;
  this->center_down = this->size.y + this->size.h - 2;
}

Box::Box(int x, int y, int w, int h):
  size{x, y, w, h}
{
  this->update_size();
}
