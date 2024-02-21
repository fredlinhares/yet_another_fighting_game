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

#include "animation_list.hpp"

#include "../../common/graphics/texture.hpp"
#include "../main.hpp"

namespace Mode
{

AnimationList::AnimationName::AnimationName(AnimationName &&that)
{
	this->name = that.name;
	this->texture = that.texture;
	this->src = that.src;
	this->dst = that.dst;

	that.texture = nullptr;
}


AnimationList::AnimationName::AnimationName(
	const char *name, SDL_Texture *texture, SDL_Rect src, SDL_Rect dst):
	name{name},
	texture{texture},
	src{src},
	dst{dst}
{

}

AnimationList::AnimationName::~AnimationName()
{
	if(this->texture != nullptr) SDL_DestroyTexture(this->texture);
}

void
AnimationList::render()
{
	for(const AnimationName &name: this->names)
		SDL_RenderCopy(core.renderer, name.texture, &name.src, &name.dst);
}

AnimationList::AnimationList():
	name_selection_state{this}
{
	int y{10};
	SDL_Color color{0xff, 0xff, 0xff, 0xff};

	for(const auto & [key, value]: editor_state->animations)
	{
		int width, height;
		SDL_Texture *texture{
			Graphics::Texture::create_image_from_text(
				editor_state->font, key.c_str(), color)};
		SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

		SDL_Rect src{0, 0, width, height};
		SDL_Rect dst{10, y, width, height};
		this->names.emplace_back(key.c_str(), texture, src, dst);
		y += 10 + height;
	}

	this->current_state = &this->name_selection_state;
}

}
