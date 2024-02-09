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

#include "../common/main.hpp"
#include "input.hpp"
#include "mode/fight.hpp"

InputConfig input_config;

int
main()
{
  core.app_name = "Yet Another Fighting Game";
  core.window_width = 384;
  core.window_height = 224;
  core.init();

  input_config.player1 = new Input::Config{
    {SDLK_e, {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_UP}},
    {SDLK_d, {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_DOWN}},
    {SDLK_s, {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_LEFT}},
    {SDLK_f, {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_RIGHT}},
    {SDLK_j, {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_HEAVY_PUNCH}},
    {SDLK_k, {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_HEAVY_KICK}},
    {SDLK_l, {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_LIGHT_PUNCH}},
    {SDLK_SEMICOLON,
     {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_LIGHT_KICK}}};

  Mode::Base *game_mode = new Mode::Fight{};

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
	}
      }

      // Update game
      game_mode->tick();

      { // Render
	SDL_SetRenderDrawColor(core.renderer, 0, 0, 0, 0xff);
	SDL_RenderClear(core.renderer);

	game_mode->render();

	SDL_RenderPresent(core.renderer);
      }

      timer(frame_start);
    }
  }

  delete game_mode;
  delete input_config.player1;
  core.finish();

  return 0;
}
