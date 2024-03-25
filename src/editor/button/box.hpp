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

#ifndef YAFCE_BOX_H
#define YAFCE_BOX_H 1

#include "../../common/core.hpp"
#include "../../common/direction.hpp"
#include "../../common/graphics/frame.hpp"
#include "../button.hpp"
#include "../mode.hpp"

namespace Button
{

class SpriteBox;

class Box: public Base
{
	Mode::Base* const mode;
	SpriteBox* const sprite_box;
	SDL_Rect* const rect;
	Uint8 red, green, blue;
  int outer_left, center_left, outer_right, center_right, outer_up,
    center_up, outer_down, center_down;

public:
	void
	update_frame();

	void
	click_action(const int x, const int y);

	void
	render();

  void
  update_size();

Box(Mode::Base* mode, SpriteBox *sprite_box,
		SDL_Rect *rect, Uint8 red, Uint8 green, Uint8 blue);
};

}

#endif /* YAFCE_BOX_H */
