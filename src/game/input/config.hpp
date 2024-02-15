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

#include <array>
#include <bitset>
#include <cstdint>
#include <unordered_map>

namespace Input
{

constexpr uint8_t TYPE_INDEX_DIRECTION = 0;
constexpr uint8_t TYPE_INDEX_ATTACK = 1;

constexpr uint8_t DIRECTION_BIT_NONE = 0b0000;
constexpr uint8_t DIRECTION_BIT_UP = 0b0001;
constexpr uint8_t DIRECTION_BIT_DOWN = 0b0010;
constexpr uint8_t DIRECTION_BIT_LEFT = 0b0100;
constexpr uint8_t DIRECTION_BIT_RIGHT = 0b1000;

constexpr uint8_t DIRECTION_BIT_UP_LEFT = 0b0101;
constexpr uint8_t DIRECTION_BIT_UP_RIGHT = 0b1001;
constexpr uint8_t DIRECTION_BIT_DOWN_LEFT = 0b0110;
constexpr uint8_t DIRECTION_BIT_DOWN_RIGHT = 0b1010;

constexpr uint8_t ATTACK_BIT_HEAVY_PUNCH = 0b0001;
constexpr uint8_t ATTACK_BIT_HEAVY_KICK = 0b0010;
constexpr uint8_t ATTACK_BIT_LIGHT_PUNCH = 0b0100;
constexpr uint8_t ATTACK_BIT_LIGHT_KICK = 0b1000;

constexpr uint8_t DIRECTION_INDEX_UP = 0;
constexpr uint8_t DIRECTION_INDEX_DOWN = 1;
constexpr uint8_t DIRECTION_INDEX_LEFT = 2;
constexpr uint8_t DIRECTION_INDEX_RIGHT = 3;

constexpr uint8_t ATTACK_INDEX_HEAVY_PUNCH = 0;
constexpr uint8_t ATTACK_INDEX_HEAVY_KICK = 1;
constexpr uint8_t ATTACK_INDEX_LIGHT_PUNCH = 2;
constexpr uint8_t ATTACK_INDEX_LIGHT_KICK = 3;

typedef std::bitset<4> AttackState;
typedef std::bitset<4> DirectionState;

typedef std::unordered_map<uint32_t, std::array<uint8_t, 2>> ConfigKeyboard;
typedef std::unordered_map<uint8_t, std::array<uint8_t, 2>> ConfigJoystick;

}

#endif /* YAFG_INPUT_CONFIG_H */
