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

#ifndef YAFCE_MODE_ANIMATION_LIST_H
#define YAFCE_MODE_ANIMATION_LIST_H 1

#include <vector>

#include "../mode.hpp"
#include "../state/name_selection.hpp"

namespace Mode
{

struct AnimationList: public Base
{

	struct AnimationName
	{
		std::string name;
		SDL_Texture *texture;
		SDL_Rect src, dst;

		AnimationName &operator=
		(const AnimationName &that) = delete;

		AnimationName(AnimationName &&that);

		AnimationName(
			const char *name, SDL_Texture *texture, SDL_Rect src, SDL_Rect dst);
		~AnimationName();
	};

	State::NameSelection name_selection_state;

	std::vector<AnimationName> names;

	void
	render();

	AnimationList();
};

}

#endif /* YAFCE_MODE_ANIMATION_LIST_H */
