# Inicialização de subsistemas

Antes do código entrar no ciclo principal, ele precisa iniciar todos os subsistemas.
Após sair do cicloele precisa finalizar todos os subsistemas.


## CommandChain

Nesse programa eu criei uma classe chamada [CommandChain](../src/command.hpp) para facilitar o processo de alocar e liberar recursos.
O construtor dessa classe recebe uma lista de argumentos organizados em pares de ponteiros.
Cada par é responsável por alocar e liberar um recurso.
O primeiro ponteiro aponta para uma função que aloca e o segundo ponteiro para uma função que libera.
Quando um recurso não precisa ser liberado, usa-se um ponteiro nulo na segunda posição do par.

Quando o método `execute` do CommandChain é chamado,  ele executa as funções alocadoras da primeira para a ultima.
Quando o método `revert` é chamado, ele executa as funções desalocadoras da ultima para a primeira.
Isso ocorre porque alguns recursos precisam ser liberados na ordem inversa da ordem na qual eles foram alocados.


## Tratamento de erros

A classe CommandChain foi projetada para inicialização de recursos onde as etapas posteriores exigem recursos das etapas anteriores.
Por isso, cada função de alocação deve lançar (throw) um erro do tipo CommandError caso a alocação de recursos falhe.
Ao capturar esse erro, o CommandChain reverte todas a inicializações já feitas garantido que nenhum problema como vazamento de memoria ocorra.
