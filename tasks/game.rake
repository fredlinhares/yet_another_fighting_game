# Copyright 2024 Frederico de Oliveira Linhares
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

module Game
  OBJ = 'yafg'

  CPP_H_FILES = FileList[
    'src/game/**/*.hpp'
  ]
  CPP_FILES = FileList[
    'src/game/**/*.cpp'
  ]

  CPP_OBJS = (::CPP_FILES + CPP_FILES).ext('.o')

end

namespace "game" do
  task build: Game::CPP_OBJS do
    libs = LIBRARIES.inject('') {_1 + "-l#{_2} "}

    system("g++ -o #{Game::OBJ} #{Game::CPP_OBJS} #{libs}")
  end
end
