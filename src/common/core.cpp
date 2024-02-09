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

#include "core.hpp"

#include <string>

Core core;

namespace{

void
load_sdl(void *obj)
{
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    std::string error{"SDL could not initialize! SDL Error → "};
    error += SDL_GetError();
    throw error;
  }
}

void
unload_sdl(void *obj)
{
  SDL_Quit();
}

void
load_window(void *obj)
{
  core.window = nullptr;
  core.window = SDL_CreateWindow(
    core.app_name,
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    core.window_width, core.window_height,
    SDL_WINDOW_SHOWN);
  if(core.window == NULL)
  {
    std::string error{"Window could not be created! SDL_Error → "};
    error += SDL_GetError();
    throw CommandError{error};
  }
}

void
unload_window(void *obj)
{
  SDL_DestroyWindow(core.window);
}

void
load_window_surface(void *obj)
{
  core.screen_surface = SDL_GetWindowSurface(core.window);
}

void
load_renderer(void *obj)
{
  core.renderer = SDL_CreateSoftwareRenderer(core.screen_surface);
  if(core.renderer == NULL)
  {
    std::string error{"SDL renderer could not be created! SDL Error → "};
    error += SDL_GetError();
    throw error;
  }
  SDL_SetRenderDrawBlendMode(core.renderer, SDL_BLENDMODE_BLEND);
}

void
unload_renderer(void *obj)
{
  SDL_DestroyRenderer(core.renderer);
}

void
load_sdl_img(void *obj)
{
  int img_flags{IMG_INIT_PNG};
  if(!(IMG_Init(img_flags) & img_flags))
  {
    std::string error{"SDL_image could not initialize! SDL Error → "};
    error += IMG_GetError();
    throw error;
  }
}

void
unload_sdl_img(void *obj)
{
  IMG_Quit();
}

const CommandChain loader{
  {&load_sdl, &unload_sdl},
  {&load_window, &unload_window},
  {&load_window_surface, nullptr},
  {&load_renderer, &unload_renderer},
  {&load_sdl_img, &unload_sdl_img}
};

}

void
Core::init()
{
  loader.execute(nullptr);
}

void
Core::finish()
{
  loader.revert(nullptr);
}
