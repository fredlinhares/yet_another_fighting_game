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

namespace
{

inline int
y_letter_position(int y, int max_height, int height)
{
	return y + max_height - height;
}

inline int
char_to_int(const char c)
{
	switch(c)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	}

	return 0;
}

}

int
Number::draw_bar(const int x, const int y)
{
	SDL_Rect src{0, 0, bar.width, bar.height};
	SDL_Rect dst{
		x, y_letter_position(y, this->max_height, bar.height),
		bar.width, bar.height};

	SDL_RenderCopy(core.renderer, bar.texture, &src, &dst);
	return x + bar.width;
}

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

int
Number::draw_number(const int x, const int y, const int number)
{
	auto current_x{x};
	std::string text{std::to_string(number)};

	for(auto c: text)
	{
		Character *character = &this->numbers[char_to_int(c)];
		SDL_Rect src{0, 0, character->width, character->height};
		SDL_Rect dst{
			current_x, y_letter_position(y, this->max_height, character->height),
			character->width, character->height};

		SDL_RenderCopy(core.renderer, character->texture, &src, &dst);
		current_x += character->width;
	}

	return current_x;
}

int
Number::draw_fraction(
	const int x, const int y, const int numerator, const int denominator)
{
	int current_x{x};
	current_x = this->draw_number(current_x, y, numerator);
	current_x = this->draw_bar(current_x, y);
	current_x = this->draw_number(current_x, y, denominator);

	return current_x;
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
