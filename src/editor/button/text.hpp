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

#ifndef YAFCE_BUTTON_TEXT_H
#define YAFCE_BUTTON_TEXT_H 1

#include <functional>

#include "../button.hpp"
#include "../main.hpp"

namespace Button
{

struct Text: public Base
{
	std::function<void(void)> callback;
	SDL_Texture *texture;
	SDL_Rect src;

	void
	click_action(int x, int y);

	void
	render();

	Text &operator=
	(const Text &that) = delete;

	Text(Text &&that);

	Text(const char *name, int x, int y, std::function<void(void)> callback);
	~Text();
};

}

#endif /* YAFCE_BUTTON_TEXT_H */
