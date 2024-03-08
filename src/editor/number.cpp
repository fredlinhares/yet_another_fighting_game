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

#include "number.hpp"

#include "../common/graphics/texture.hpp"
#include "main.hpp"

void
Number::write_character(Character &character, const char *text)
{
	SDL_Color color{0xff, 0xff, 0xff, 0xff};

	character.texture = Graphics::Texture::create_image_from_text(
		editor_state->font, text, color);

	SDL_QueryTexture(
		character.texture, nullptr, nullptr,
		&character.width, &character.height);

	if(character.width > this->max_width)
		this->max_width = character.width;
	if(character.height > this->max_height)
		this->max_height = character.height;
}

Number::Number():
	max_width{0},
	max_height{0}
{
	this->write_character(this->numbers[0], "0");
	this->write_character(this->numbers[1], "1");
	this->write_character(this->numbers[2], "2");
	this->write_character(this->numbers[3], "3");
	this->write_character(this->numbers[4], "4");
	this->write_character(this->numbers[5], "5");
	this->write_character(this->numbers[6], "6");
	this->write_character(this->numbers[7], "7");
	this->write_character(this->numbers[8], "8");
	this->write_character(this->numbers[9], "9");
	this->write_character(this->bar, "/");
}

Number::~Number()
{
	for(int i{0}; i < 10; i++) SDL_DestroyTexture(this->numbers[i].texture);
	SDL_DestroyTexture(this->bar.texture);
}
