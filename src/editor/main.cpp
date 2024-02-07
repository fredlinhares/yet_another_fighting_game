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

#include "../common/graphics/texture.hpp"
#include "../common/main.hpp"
#include "mode/sprite.hpp"

int
main(int argc, char *argv[])
{
  core.app_name = "Yet Another Fighting Character Editor";
  core.window_width = 1280;
  core.window_height = 720;
  core.init();

  SDL_Texture* sprites;
  { // Parse args
    if(argc < 2)
    {
      std::cout << "insufficient arguments." << std::endl;
      core.finish();
      return 1;
    }

    sprites = Graphics::Texture::load(argv[1]);
  }

  Mode::Base *game_mode = new Mode::Sprite{sprites};

  { // main loop
    SDL_Event event;
    bool quit{false};
    auto frame_start = SDL_GetTicks();

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
	case SDL_MOUSEBUTTONDOWN:
	  game_mode->mouse_button_down(event.button);
	  break;
	case SDL_MOUSEBUTTONUP:
	  game_mode->mouse_button_up(event.button);
	  break;
	case SDL_MOUSEMOTION:
	  int x{event.motion.x};
	  int y{event.motion.y};
	  game_mode->mouse_motion(x, y);
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

      timer(frame_start);
    }
  }

  delete game_mode;
  SDL_DestroyTexture(sprites);
  core.finish();

  return 0;
}
