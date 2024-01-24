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
    "Yet Another Fighting Game",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    WINDOW_WIDTH, WINDOW_HEIGHT,
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
}

void
unload_renderer(void *obj)
{
  SDL_DestroyRenderer(core.renderer);
}

const CommandChain loader{
  {&load_sdl, &unload_sdl},
  {&load_window, &unload_window},
  {&load_window_surface, nullptr},
  {&load_renderer, &unload_renderer}
};

}

void
Core::init()
{
  player1_input = new InputConfig{
    {SDLK_e, DIRECTION_UP_BIT},
    {SDLK_d, DIRECTION_DOWN_BIT},
    {SDLK_s, DIRECTION_LEFT_BIT},
    {SDLK_f, DIRECTION_RIGHT_BIT},
    {SDLK_j, HEAVY_PUNCH_BIT},
    {SDLK_k, HEAVY_KICK_BIT},
    {SDLK_l, LIGHT_PUNCH_BIT},
    {SDLK_SEMICOLON, LIGHT_KICK_BIT}};

  loader.execute(nullptr);
}

void
Core::finish()
{
  delete player1_input;
  loader.revert(nullptr);
}
