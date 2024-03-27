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

#include "move_pivot.hpp"

namespace State
{

void
MovePivot::mouse_button_up(SDL_MouseButtonEvent& b)
{
	this->sprite_box->mode->reset_state();
}

void
MovePivot::mouse_motion(int x, int y, int xrel, int yrel)
{
	if(xrel != 0) *this->pivot_x -= xrel;
	if(yrel != 0) *this->pivot_y -= yrel;
}

MovePivot::MovePivot(Button::SpriteBox* sprite_box, int *pivot_x, int *pivot_y):
	sprite_box{sprite_box},
	pivot_x{pivot_x},
	pivot_y{pivot_y}
{
}

}
