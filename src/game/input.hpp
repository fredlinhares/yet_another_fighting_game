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

#ifndef YAFG_INPUT_H
#define YAFG_INPUT_H 1

#include "input/config.hpp"

struct InputConfig
{
  Input::ConfigKeyboard player_keyboard;

  std::array<Input::ConfigJoystick, 2> player_joystick;

  InputConfig(
    Input::ConfigKeyboard player_keyboard,
    std::array<Input::ConfigJoystick, 2> player_joystick);
};

extern InputConfig *input_config;

#endif /* YAFG_INPUT_H */
