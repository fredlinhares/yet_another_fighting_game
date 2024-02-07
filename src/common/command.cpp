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

#include <stdlib.h>

#include "command.hpp"

CommandError::CommandError(const std::string &m):
  error(m)
{
}

CommandError::CommandError(const char &m):
  CommandError{std::string{m}}
{
}

const char* CommandError::what() const noexcept
{
  return this->error.c_str();
}

CommandChain::CommandChain(std::initializer_list<Command> commands)
{
  for(auto c: commands) this->add(c);
}

void
CommandChain::partial_revert(void *obj, int32_t step) const
{
  // Already unloaded, nothing to do.
  if(step <= 0) return;

  for(; step > 0; step--)
  {
    auto command = this->_commands[step -1].undo_command;
    if(command != nullptr) command(obj);
  }
}

void
CommandChain::add(const Command &c)
{
  this->_commands.push_back(c);
}

void
CommandChain::execute(void *obj) const
{
  for(auto i{0}; i < this->_commands.size(); i++)
  {
    try { this->_commands[i].do_command(obj); }
    catch(const CommandError &error)
    {
      this->partial_revert(obj, i);
      throw;
    }
  }
}

void
CommandChain::revert(void *obj) const
{
  this->partial_revert(obj, this->_commands.size());
}
