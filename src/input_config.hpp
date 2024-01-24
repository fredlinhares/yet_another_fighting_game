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

#ifndef YAFG_INPUT_CONFIG_H
#define YAFG_INPUT_CONFIG_H 1

#include <cstdint>
#include <unordered_map>

#include "entity.hpp"

constexpr uint8_t DIRECTION_UP_BIT = 0;
constexpr uint8_t DIRECTION_DOWN_BIT = 1;
constexpr uint8_t DIRECTION_LEFT_BIT = 2;
constexpr uint8_t DIRECTION_RIGHT_BIT = 3;
constexpr uint8_t HEAVY_PUNCH_BIT = 4;
constexpr uint8_t HEAVY_KICK_BIT = 5;
constexpr uint8_t LIGHT_PUNCH_BIT = 6;
constexpr uint8_t LIGHT_KICK_BIT = 7;

typedef std::unordered_map<uint32_t, uint8_t> InputConfig;

#endif /* YAFG_INPUT_CONFIG_H */
