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

}

