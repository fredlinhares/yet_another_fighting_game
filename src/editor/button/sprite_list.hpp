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

#ifndef YAFCE_SPRITE_LIST_H
#define YAFCE_SPRITE_LIST_H 1

#include <functional>

#include "../../common/main.hpp"
#include "../button.hpp"
#include "../frame.hpp"

namespace Button
{

class SpriteList: public Base
{
	struct Sprite
	{
		int index;
		SDL_Rect position;
		Sprite(int index, int x, int y, int w, int h);
	};

	std::function<void(int)> callback;

	int current_set, sprites_height;
	SDL_Rect up_button, down_button;
	std::vector<int> set_indexes;
	std::vector<Sprite> positions;

	void
	set_positions();

public:
	void
	next_set();

	void
	previous_set();

	void
	click_action(int x, int y);

	void
	render();

	SpriteList(std::function<void(int)> callback);
};

}

#endif /* YAFCE_SPRITE_LIST_H */
