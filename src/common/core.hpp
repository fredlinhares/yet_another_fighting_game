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

#ifndef YAFG_CORE_H
#define YAFG_CORE_H 1

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "command.hpp"

constexpr int WINDOW_WIDTH = 384;
constexpr int WINDOW_HEIGHT = 224;

struct Core
{
  const char *app_name;

  SDL_Window *window{nullptr};
  SDL_Surface *screen_surface{nullptr};
  SDL_Renderer *renderer{nullptr};

  void
  init();
  void
  finish();
};

extern Core core;

#endif /* YAFG_CORE_H */
