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

#include "sprite.hpp"

void
Sprite::update_box_size()
{
  this->edit_box.x = this->size.x - 1;
  this->edit_box.y = this->size.y - 1;
  this->edit_box.w = this->size.w + 2;
  this->edit_box.h = this->size.h + 2;

  this->resize_up_box.x = this->size.x + 2;
  this->resize_up_box.y = this->size.y - 1;
  this->resize_up_box.w = this->size.w - 4;

  this->resize_down_box.x = this->size.x + 2;
  this->resize_down_box.y = this->size.y + this->size.h - 2;
  this->resize_down_box.w = this->size.w - 4;

  this->resize_left_box.x = this->size.x - 1;
  this->resize_left_box.y = this->size.y + 2;
  this->resize_left_box.h = this->size.h - 4;

  this->resize_right_box.x = this->size.x + this->size.w - 2;
  this->resize_right_box.y = this->size.y + 2;
  this->resize_right_box.h = this->size.h - 4;

  this->resize_up_left_box.x = this->size.x - 1;
  this->resize_up_left_box.y = this->size.y - 1;

  this->resize_up_right_box.x = this->size.x + this->size.w - 2;
  this->resize_up_right_box.y = this->size.y - 1;

  this->resize_down_left_box.x = this->size.x - 1;
  this->resize_down_left_box.y = this->size.y + this->size.h - 2;

  this->resize_down_right_box.x = this->size.x + this->size.w - 2;
  this->resize_down_right_box.y = this->size.y + this->size.h - 2;
}

Sprite::Sprite(int x, int y, int w, int h):
  size{x, y, w, h},
  resize_up_box{0, 0, 0, 3},
  resize_down_box{0, 0, 0, 3},
  resize_left_box{0, 0, 3, 0},
  resize_right_box{0, 0, 3, 0},
  resize_up_left_box{0, 0, 3, 3},
  resize_up_right_box{0, 0, 3, 3},
  resize_down_left_box{0, 0, 3, 3},
  resize_down_right_box{0, 0, 3, 3}
{
  this->update_box_size();
}
