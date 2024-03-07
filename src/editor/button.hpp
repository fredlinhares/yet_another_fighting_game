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

#ifndef YAFCE_BUTTON_H
#define YAFCE_BUTTON_H 1

#include "../common/core.hpp"

namespace Button
{

struct Base
{
	SDL_Rect location;

	inline static bool
	is_point_inside_rect(const SDL_Rect &rect, int x, int y)
		{return (
				x > rect.x && x < rect.x + rect.w &&
				y > rect.y && y < rect.y + rect.h);};

	bool
	is_clicked(int x, int y);

	virtual void
	click_action(int x, int y) = 0;

	virtual void
	render() = 0;

	virtual
	~Base(){};
};

}

#endif /* YAFCE_BUTTON_H */
