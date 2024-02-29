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

#include "frame.hpp"

namespace Graphics
{

void
Frame::set_sprite(int pivot_x, int pivot_y, int x, int y, int w, int h)
{
  this->x = pivot_x;
  this->y = pivot_y;
  this->sprite.x = x;
  this->sprite.y = y;
  this->sprite.w = w;
  this->sprite.h = h;
}

void
Frame::set_head(int x, int y, int w, int h)
{
  this->head.x = x;
  this->head.y = y;
  this->head.w = w;
  this->head.h = h;
}

void
Frame::set_upper_body(int x, int y, int w, int h)
{
  this->upper_body.x = x;
  this->upper_body.y = y;
  this->upper_body.w = w;
  this->upper_body.h = h;
}

void
Frame::set_lower_body(int x, int y, int w, int h)
{
  this->lower_body.x = x;
  this->lower_body.y = y;
  this->lower_body.w = w;
  this->lower_body.h = h;
}

void
Frame::set_collision(int x, int y, int w, int h)
{
  this->collision.x = x;
  this->collision.y = y;
  this->collision.w = w;
  this->collision.h = h;
}

Frame::Frame():
	x{-20},
	y{-60},
	sprite{0, 0, 40, 60},
	head{-10, -60, 20, 20},
	upper_body{-15, -40, 30, 20},
	lower_body{-15, -20, 30, 20},
	collision{-10, -30, 20, 20}
{
}

}
