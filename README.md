# Varredura de Graham

A varredura de Graham resolve o problema da envoltória convexa mantendo uma pilha S de pontos candidatos.

O algoritmo insere cada ponto do conjunto de entrada Q na pilha uma vez e, a certa altura, retira da pilha cada ponto que não é um vértice de CH(Q). Ao término da execução, a pilha S contém exatamente os vértices de CH(Q), em
ordem anti-horária das posições que ocupam na envoltória.

- O procedimento GRAHAM-SCAN toma como entrada um conjunto Q de pontos, onde |Q| ≥ 3.
- Chama a função TOP (S), que retorna o ponto que está no topo da pilha S sem mudar S, e a função NEXT-TO-TOP (S), que retorna o ponto que está
uma entrada abaixo do topo da pilha S, sem mudar S.
- A pilha S retornada por GRAHAM-SCAN contém, de baixo para cima, exatamente os vértices de CH(Q) em ordem anti-horária.
