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

#ifndef YAFCE_MODE_ANIMATION_H
#define YAFCE_MODE_ANIMATION_H 1

#include "../../common/graphics/animation.hpp"
#include "../../common/graphics/frame.hpp"
#include "../button/image.hpp"
#include "../mode.hpp"
#include "../number.hpp"
#include "../state/animation.hpp"
#include "zoomable.hpp"

namespace Mode
{

class Animation: public Base, public Zoomable
{
	int _x, _y, frame_x, frame_y, frame_index;
	Number numbers;
	Graphics::Animation* current_animation;

	Button::Image *previous_frame_btn, *next_frame_btn;
	std::vector<Button::Base*> buttons;

public:
	State::Animation animation_state;

	inline int
	x() const {return this->_x;};
	inline int
	y() const {return this->_y;};

	inline int
	up_limit() const {return -250;};
	inline int
	down_limit() const {return 250;};
	inline int
	left_limit() const {return -250;};
	inline int
	right_limit() const {return 250;};

	void
	zoom_in();
	void
	zoom_out();

	void
	default_state();

	void
	tick();

	void
	render();

	Animation(const char *animation_name);
	~Animation();
};

}

#endif /* YAFCE_MODE_ANIMATION_H */
