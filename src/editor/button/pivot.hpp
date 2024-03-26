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

#include "../button.hpp"
#include "sprite_box.hpp"

namespace Button
{

class Pivot: public Base
{
	SpriteBox* const sprite_box;
	int* const pivot_x;
	int* const pivot_y;
	int radius;

	void
	set_position();

public:
	void
	click_action(int x, int y);

	void
	render();

	Pivot(SpriteBox *sprite_box, int *pivot_x, int *pivot_y, int radius);
};

}
