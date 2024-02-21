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

#include "texture.hpp"

#include <stdexcept>

namespace
{

void
throw_image_error(const char *file_path, const char *message)
{
  std::string error{message};
  error += " Image → ";
  error += file_path;
  error += ", IMG_Error → ";
  error += IMG_GetError();
  throw std::runtime_error{error};
}

void
throw_text_error(const char *message, const char *text, const char *sdl_error)
{
  std::string error{message};
  error += " Text → ";
  error += text;
  error += ", TTF_Error → ";
  error += sdl_error;
  throw std::runtime_error{error};
}

}

namespace Graphics::Texture
{

SDL_Texture*
load(const char *file_path)
{
  SDL_Texture *texture{nullptr};
  SDL_Surface *image{IMG_Load(file_path)};

  if(image == NULL)
    throw_image_error(file_path, "Image could no be loaded!");
  else
  {
    texture = SDL_CreateTextureFromSurface(core.renderer, image);
    SDL_FreeSurface(image);

    if(texture == NULL)
      throw_image_error(file_path, "Image could no be converted to texture!");
  }

  return texture;
}

SDL_Texture*
create_image_from_text(TTF_Font *font, const char *text, SDL_Color color)
{
	SDL_Texture *texture{nullptr};
	SDL_Surface *image{TTF_RenderText_Solid(font, text, color)};

	if(image == NULL)
		throw_text_error("Text could no be rendered!", text, TTF_GetError());
	else
	{
		texture = SDL_CreateTextureFromSurface(core.renderer, image);
		SDL_FreeSurface(image);

		if(texture == NULL)
			throw_text_error(
				"Text could no be converted to texture!", text, SDL_GetError());
	}

	return texture;
}

}

