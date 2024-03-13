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

#ifndef YAFCE_MODE_BOX_H
#define YAFCE_MODE_BOX_H 1

#include "../frame.hpp"
#include "../mode.hpp"
#include "../button/sprite_list.hpp"
#include "../button/zoomable.hpp"
#include "../state/box.hpp"
#include "../state/resize.hpp"

namespace Mode
{

struct Box: public Base
{
	Frame *frame;

	State::Box box_state;
	State::Resize resize_state;

	Button::SpriteList sprite_list;
	Button::Zoomable zoomable;

  void
  get_mouse_position(int &x, int &y);

	void
	set_limits();

	void
	default_state();

	void
	render();

	Box();
};

}

#endif /* YAFCE_MODE_BOX_H */
