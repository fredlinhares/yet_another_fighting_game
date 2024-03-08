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

#ifndef YAFCE_MODE_NUMBER_H
#define YAFCE_MODE_NUMBER_H 1

#include "../common/core.hpp"

class Number
{
	struct Character
	{
		int width, height;
		SDL_Texture *texture;
	};

	int max_width, max_height;
	Character numbers[10];
	Character bar;

	void
	write_character(Character &character, const char *text);

public:

	Number();
	~Number();
};

#endif /* YAFCE_MODE_NUMBER_H */
