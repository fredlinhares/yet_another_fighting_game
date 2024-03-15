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

#ifndef YAFCE_BUTTON_ZOOMABLE_H
#define YAFCE_BUTTON_ZOOMABLE_H 1

#include "../button.hpp"
#include "../frame.hpp"
#include "../mode.hpp"
#include "../../common/core.hpp"

namespace Button
{

class Zoomable: public Base
{
protected:
	int _zoom;
	std::vector<::Box*> const *boxes;

public:
	Mode::Base* const mode;
	int x, y, up_limit, down_limit, left_limit, right_limit;

	void
	get_mouse_position(int &x, int &y);

	void
	zoom_in();
	void
	zoom_out();

	int
	zoom(){return this->_zoom;};

	void
	render_sprite(const Frame &frame);

	void
	render_rect(const SDL_Rect &rect, uint8_t r, uint8_t g, uint8_t b);

	void
	click_action(int x, int y);

	void
	render(){};

	Zoomable(
		Mode::Base *mode,
		std::vector<::Box*> *boxes,
		int width, int height,
		int center_x, int center_y);
};

}

#endif /* YAFCE_BUTTON_ZOOMABLE_H */
