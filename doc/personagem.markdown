# Personagem

Cada instância da classe [Fighter](../src/entity.hpp) contém as informações sobre um personagem controlado pelo jogador ou computador.


## Posição

Durante as animações do personagem, vários sprites com larguras e alturas diferentes serão usados.
Além dos sprites, os personagens também tem caixas de colisão (collision boxes), caixas de ferimento (hurt boxes) e caixas de ataque (hit boxes) que variam junto com as animações.
Essas caixas são usadas para saber se o personagem encostou, foi atingido ou atingiu o oponente.
Por causa das variações nos sprites e caixas de colisão, a posição do personagem é definida por apenas duas variáveis: `x` e `y` e todas as outras posições são relativas a essa duas coordenadas.
Esses `x` e `y` definem a posição central inferior do personagem.
O `y` também define quando o personagem colide com o chão.


## Máquina de Estados

Cada personagem funciona como uma máquina de estados.
As animações e as caixas dos personagens são definidas pelos estados do personagem.
Os estados de um personagem podem incluir, por exemplo:

- Soco fraco
- Soco forte
- Soco fraco agachado
- Pulando
- Gancho

Cada instância da classe Fighter tem um ponteiro para o [estado](../src/entity/state.hpp) atual.
