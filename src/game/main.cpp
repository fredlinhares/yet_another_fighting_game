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

InputConfig *input_config;

namespace
{

// FIXME: These values are bases on the PS4 controller only.
// This code need to be tested with different controllers.
constexpr Uint8 JOYSTICK_UP{11};
constexpr Uint8 JOYSTICK_DOWN{12};
constexpr Uint8 JOYSTICK_LEFT{13};
constexpr Uint8 JOYSTICK_RIGHT{14};

constexpr Uint8 JOYSTICK_LIGHT_PUNCH{2};
constexpr Uint8 JOYSTICK_HEAVY_PUNCH{3};
constexpr Uint8 JOYSTICK_LIGHT_KICK{0};
constexpr Uint8 JOYSTICK_HEAVY_KICK{1};

}

int
main()
{
  core.app_name = "Yet Another Fighting Game";
  core.window_width = 384;
  core.window_height = 224;
  core.init();

  input_config = new InputConfig{
    Input::ConfigKeyboard{
    {SDLK_e, {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_UP}},
     {SDLK_d, {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_DOWN}},
     {SDLK_s, {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_LEFT}},
     {SDLK_f, {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_RIGHT}},
     {SDLK_j, {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_HEAVY_PUNCH}},
     {SDLK_k, {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_HEAVY_KICK}},
     {SDLK_l, {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_LIGHT_PUNCH}},
     {SDLK_SEMICOLON,
      {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_LIGHT_KICK}}},

    std::array<Input::ConfigJoystick, 2>{
      Input::ConfigJoystick{
	{JOYSTICK_UP,
	 {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_UP}},
	{JOYSTICK_DOWN,
	 {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_DOWN}},
	{JOYSTICK_LEFT,
	 {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_LEFT}},
	{JOYSTICK_RIGHT,
	 {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_RIGHT}},
	{JOYSTICK_LIGHT_PUNCH,
	 {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_LIGHT_PUNCH}},
	{JOYSTICK_HEAVY_PUNCH,
	 {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_HEAVY_PUNCH}},
	{JOYSTICK_LIGHT_KICK,
	 {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_LIGHT_KICK}},
	{JOYSTICK_HEAVY_KICK,
	 {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_HEAVY_KICK}}},

      Input::ConfigJoystick{
	{JOYSTICK_UP,
	 {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_UP}},
	{JOYSTICK_DOWN,
	 {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_DOWN}},
	{JOYSTICK_LEFT,
	 {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_LEFT}},
	{JOYSTICK_RIGHT,
	 {Input::TYPE_INDEX_DIRECTION, Input::DIRECTION_INDEX_RIGHT}},
	{JOYSTICK_LIGHT_PUNCH,
	 {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_LIGHT_PUNCH}},
	{JOYSTICK_HEAVY_PUNCH,
	 {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_HEAVY_PUNCH}},
	{JOYSTICK_LIGHT_KICK,
	 {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_LIGHT_KICK}},
	{JOYSTICK_HEAVY_KICK,
	 {Input::TYPE_INDEX_ATTACK, Input::ATTACK_INDEX_HEAVY_KICK}}}}
    };

  SDL_Joystick *joystick1{nullptr};
  SDL_Joystick *joystick2{nullptr};

  SDL_JoystickID joystick1_id;
  SDL_JoystickID joystick2_id;

  int num_joysticks = SDL_NumJoysticks();
  if(num_joysticks == 1)
  {
    joystick1 = SDL_JoystickOpen(0);
    joystick1_id = SDL_JoystickInstanceID(joystick1);
  }
  else if(num_joysticks > 1)
  {
    joystick1 = SDL_JoystickOpen(0);
    joystick2 = SDL_JoystickOpen(1);
    joystick1_id = SDL_JoystickInstanceID(joystick1);
    joystick2_id = SDL_JoystickInstanceID(joystick2);
  }

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
	case SDL_JOYBUTTONDOWN:
	  // event.jbutton.which == joystick1_id
	  game_mode->joybutton_down(0, event.jbutton.button);
	  break;
	case SDL_JOYBUTTONUP:
	  game_mode->joybutton_up(0, event.jbutton.button);
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

  SDL_JoystickClose(joystick1);
  SDL_JoystickClose(joystick2);
  delete game_mode;
  delete input_config;
  core.finish();

  return 0;
}
