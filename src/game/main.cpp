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

  main_loop(game_mode);

  delete game_mode;
  delete input_config.player1;
  core.finish();

  return 0;
}
