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

#ifndef YAFG_COMMAND_CHAIN_H
#define YAFG_COMMAND_CHAIN_H 1

#include <cstdint>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <vector>

class CommandChain;

struct CommandError: public std::exception
{
  CommandError(const std::string &m);
  CommandError(const char &m);

  const char* what() const noexcept;

private:
  std::string error;
};

/**
 * Stores a reversible action.
 */
struct Command
{
  void (*do_command)(void *obj);
  void (*undo_command)(void *obj);
};

/**
 * Stores a sequence of functions that must be executed and rolled back in
 * order.
 *
 * For example, if the variable _commands contain A→B→C→D→E, it will load A,
 * then B, then C, etc. If D fails, it unloads C, then B, then A.
 */
class CommandChain
{
  std::vector<Command> _commands;

  void
  partial_revert(void *obj, int32_t step) const;

public:
  CommandChain(std::initializer_list<Command> commands);

/**
 * Adds a reversible action to the command. The first action added is the first
 * to de executed the last rolled back, and so on. Those functions are stored
 * inside _commands.
 *
 * @param[unload] the undo/rollback action, if the action do not need a
 *   rollback, this pointer can be set to null.
 */
  void
  add(const Command &c);

/**
 * Execute all of the load functions in the _commands. If one of them fails,
 * roll back everything inside _commands.
 * @return true on success and false on fail.
 */
  void
  execute(void *obj) const;

/**
 * Roll back all loaded function inside commands, if there are any.
 */
  void
  revert(void *obj) const;

};

#endif /* YAFG_COMMAND_CHAIN_H */
