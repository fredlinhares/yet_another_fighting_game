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

#include "../common/main.hpp"

class SpriteList
{
	struct Sprite
	{
		int index;
		SDL_Rect position;
		Sprite(int index, int x, int y, int w, int h);
	};

	int current_set, width, height;
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
	render();

	SpriteList();
};

#endif /* YAFCE_SPRITE_LIST_H */
