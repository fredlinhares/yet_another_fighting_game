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

bool
Box::click(Direction *direction, const int x, const int y)
{
	Direction vertical_direction{Direction::none};
	Direction horizontal_direction{Direction::none};

	if(x >= this->outer_left && x <= this->outer_right &&
		 y >= this->outer_up && y <= this->outer_down)
	{
		if(x < this->center_left)
			horizontal_direction = Direction::left;
		else if(x < this->center_right)
			horizontal_direction = Direction::none;
		else
			horizontal_direction = Direction::right;

		if(y < this->center_up)
			vertical_direction = Direction::up;
		else if(y < this->center_down)
			vertical_direction = Direction::none;
		else
			vertical_direction = Direction::down;

		*direction = vertical_direction + horizontal_direction;

		return true;
	}
	else
		return false;
}

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
