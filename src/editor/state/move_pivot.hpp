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

#ifndef YAFCE_STATE_MOVE_PIVOT_H
#define YAFCE_STATE_MOVE_PIVOT_H 1

#include "../button/sprite_box.hpp"
#include "../state.hpp"

namespace State
{

class MovePivot: public State::Base
{
	Button::SpriteBox* const sprite_box;
	int* const pivot_x;
	int* const pivot_y;

public:
	void
	mouse_button_up(SDL_MouseButtonEvent& b);

	void
	mouse_motion(int x, int y, int xrel, int yrel);

	MovePivot(Button::SpriteBox* sprite_box, int *pivot_x, int *pivot_y);
};

}

#endif /* YAFCE_STATE_MOVE_PIVOT_H */
