# Yet Another Fighting Games

## Introdução

Esse é um jogo de luta simples criado com o propósito de demonstrar os princípios básicos da programação de jogos.
Portanto ele não usará nenhum motor, ao invés disso usará o mínimo de dependências possíveis.
Nesse projeto usaremos as linguagens de programação C++ e Ruby e a libSDL, nada mais.

Como esse é projeto didático, sinta-se livre para contribuir mesmo que você tenha pouca ou nenhum experiência como programador.


## Compilando

A principal plataforma de desenvolvimento desse jogo será o GNU/Linux com o compilador GCC.
Para que você consiga compilar o código no Windows ou MacOS, recomendo que use um ambiente de desenvolvimento parecido com o do Linux.
Para o Windows, você pode usar o [MSYS2 com MINGW](https://www.msys2.org/).
Para o MacOs, você pode usar o [Homebrew](https://brew.sh/).

Toda a compilação do código é automatizada com o [Rake](https://ruby.github.io/rake/).
Uma vez que você tenha o Ruby, o GCC (com suporte para C++) e o Rake instalado, pode compilar o jogo com apenas um comando no seu terminal:

```
rake
```

Após compilar o jogo, poderá executá-lo através da linha de comando:

```
./yafg
```


## Princípios de programação de jogos

Uma vez que tenha conseguido compilar e rodar o jogo com sucesso, você pode começar a ler sobre os algorítimos que são usados nesse código:

[Ciclo principal](doc/ciclo_principal.markdown)

[Inicialização de subsistemas](doc/inicializacao_de_subsistemas.markdown)
