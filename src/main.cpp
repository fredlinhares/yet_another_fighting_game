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

#include <iostream>

#include "core.hpp"
#include "mode/fight.hpp"

constexpr int FRAMES_PER_SECOND = 60;
constexpr int MAX_FRAME_DURATION = 1000/FRAMES_PER_SECOND;

Core core;

int
main()
{
  SDL_Event event;
  bool quit{false};

  core.init();

  Mode::Base *game_mode = new Mode::Fight{};

  auto frame_start = SDL_GetTicks();

  // Main loop
  while(!quit)
  {
    // Input processing
    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
      case SDL_QUIT:
	quit = true;
	break;
      case SDL_KEYDOWN:
	game_mode->key_down(event.key.keysym.sym);
	break;
      case SDL_KEYUP:
	game_mode->key_up(event.key.keysym.sym);
	break;
      }
    }

    // Update game
    game_mode->tick();

    { // Render
      SDL_SetRenderDrawColor(core.renderer, 0, 0, 0, 0xff);
      SDL_RenderClear(core.renderer);

      game_mode->render();

      SDL_UpdateWindowSurface(core.window);
    }

    { // Timer
      auto frame_stop = SDL_GetTicks();
      auto frame_duration = frame_stop - frame_start;

      // If frame take less time than maximum allowed.
      if(MAX_FRAME_DURATION > frame_duration)
	SDL_Delay(MAX_FRAME_DURATION - frame_duration);

      frame_start = frame_stop;
    }
  }

  delete game_mode;
  core.finish();

  return 0;
}
