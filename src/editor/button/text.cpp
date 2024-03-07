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

#include "text.hpp"

#include "../../common/graphics/texture.hpp"

namespace Button
{

void
Text::click_action(int x, int y)
{
	this->callback();
}

void
Text::render()
{
	SDL_RenderCopy(core.renderer, this->texture, &this->src, &this->location);
}

Text::Text(Text &&that)
{
	this->callback = that.callback;
	this->texture = that.texture;
	this->src = that.src;
	this->location = that.location;

	that.texture = nullptr;
}

Text::Text(const char *name, int x, int y, std::function<void(void)> callback):
	callback{callback}
{
	int width, height;
	SDL_Color color{0xff, 0xff, 0xff, 0xff};

	this->texture = Graphics::Texture::create_image_from_text(
		editor_state->font, name, color);
	SDL_QueryTexture(this->texture, nullptr, nullptr, &width, &height);

	SDL_Rect src{0, 0, width, height};
	SDL_Rect dst{x, y, width, height};

	this->src = src;
	this->location = dst;
}

Text::~Text()
{
	SDL_DestroyTexture(this->texture);
}

}
