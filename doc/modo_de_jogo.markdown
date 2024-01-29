# Modo de Jogo

O [modo](../src/mode.hpp) define o que está acontecendo no jogo.
Alguns exemplos de modos de jogo incluem:

- Menu principal
- Treino
- Luta
- Créditos

Um modo de jogo pode ter algumas variações.
O modo luta, por exemplo, pode ser subdivido em:

- Luta contra maquina
- Luta contra outro jogador local
- Luta contra outro jogador on-line

O [ciclo principal](../src/main.cpp) aponta para uma instância da classe Mode.
Para mudar o modo de jogo é necessário mudar liberar o ponteiro para o modo anterior e substitui-lo pelo novo modo.
