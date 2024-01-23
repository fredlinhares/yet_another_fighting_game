# Ciclo principal

A primeira coisa que precisamos em um jogo é do [ciclo principal](../src/main.cpp) ("main loop" em Inglês).
Cada execução desse ciclo produz um frame do jogo.
O ciclo principal é responsável pelas seguintes tarefas:

- Ler a entrada de comandos do jogador
- Atualizar o jogo
- Desenhar a tela
- Cronometrar os frames do jogo


## Leitura de entrada

Aqui o código lê e processa a entrada do jogador, essa entrada pode vir do teclado, mouse, controle, etc...
Também é responsável por processar o comando de sair do jogo.
Essa comando pode vir de varias formas, a mais provável será o usuário apertando o botão de fechar a janela.
Ao recebe o sinal de saída, ele termina o ciclo principal fazendo com que o jogo seja finalizado.

## Atualizar o jogo

Nessa parte atualiza o estado de todas as entidades do jogo.


## Renderizar a tela

Aqui o SDL está usando uma técnica chamada de double buffering.
Ao invés de desenhar cada frame direto na tela, o frame é renderizado em uma imagem temporária chamada de buffer.
Depois que todo o desenho é finalizada no buffer, ele é copiada para a tela.
Desenhar diretamente na tela geraria imagens sem sentido para o jogador.

Antes de iniciar o desenho, o jogo define uma cor e em seguida sobrescreve toda a imagem no buffer com a cor definida, limpando a imagem de todos os resquícios do frame anterior.
O código que desenha a tela do jogo virá logo após essa limpeza.
Após finalizar de desenhar o frame, o código substitui a imagem que está na tela pela nova imagem.


## Cronômetro

Por último, temos o cronômetro (timer).
Ele é responsável por garantir que nenhum frame rode mais rápido que o esperado.
Isso evita que o jogo consuma toda a CPU.
Esse jogo roda a 60 frames por segundo, o que significa que cada frame pode gastar pouco mais de 16 milissegundos para ser processado.
No final de cada ciclo, o cronômetro calcula quanto tempo o frame demorou.
Se o ciclo tiver demorado menos tempo que o desejado, o código espera a quantidade de tempo necessária para evitar que o frame termine antes do esperado.
