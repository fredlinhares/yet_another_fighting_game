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
#include "../sprite_list.hpp"
#include "../state/box.hpp"
#include "../state/resize.hpp"
#include "zoomable.hpp"

namespace Mode
{

class Box: public Base, public Zoomable
{
	int _x, _y;
	SpriteList sprite_list;

public:
	Frame *frame;

	State::Box box_state;
	State::Resize resize_state;

	inline int
	x() const {return this->_x;};
	inline int
	y() const {return this->_y;};

	inline int
	up_limit() const {return - this->frame->sprite.size.h * 2;};
	inline int
	down_limit() const {return this->frame->sprite.size.h * 2;};
	inline int
	left_limit() const {return - this->frame->sprite.size.w * 2;};
	inline int
	right_limit() const {return this->frame->sprite.size.w * 2;};

	void
	get_mouse_position(int &x, int &y);

	void
	zoom_in();
	void
	zoom_out();

	void
	default_state();

	void
	render();

	Box();
};

}

#endif /* YAFCE_MODE_BOX_H */
