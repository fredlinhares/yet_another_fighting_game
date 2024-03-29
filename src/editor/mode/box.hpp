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

#include "../mode.hpp"
#include "../button/pivot.hpp"
#include "../button/sprite_list.hpp"
#include "../button/sprite_box.hpp"
#include "../state/box.hpp"
#include "../state/resize.hpp"

namespace Mode
{

struct Box: public Base
{
	Graphics::Frame *frame;
	std::vector<Button::Base*> buttons;

	State::Box box_state;

	Button::SpriteList sprite_list;
	Button::SpriteBox sprite_box;
	std::vector<Button::Base*> boxes;

	void
	set_boxes();

	void
	set_limits();

	void
	render();

	Box();
	~Box();
};

}

#endif /* YAFCE_MODE_BOX_H */
