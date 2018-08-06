# Snail

Jogo análogo ao 'Snake' para o terminal. Na verdade, o jogo pretendia ser um Snake, mas apenas com caracteres ASCII brancos em fundo preto, onde a cabeça da cobra (*snake*) é um '@' e a calda é uma sequência de '+', a cobra parece mais um caracol (*snail*) de calda grande.

Há duas versões funcionais do jogo que estão nas duas branchs: na da branch master não é possível reverter a direção do movimento do caracol, e na da branch tem-volta é possível reverter a direção do movimento.

O programa foi escrito e compilado usando o DEV-C++.

No momento o jogo está funcionando apenas no rWindows, portanto é na verdade um jogo para o CMD, mais isto ainda será resolvido um dia.

### Próximos passos

* Unificar as duas versões em uma só que dê a opção ao usuário;
* Resolver a portabilidade para Linux;
* Usar uma biblioteca para evitar a gambiarra feita na implementação da sleep;
* Implementar o controle pelas setas do teclado;
* Resolver o problema da demora para printar;
  * usar outra função no lugar do *printf*?
  * dar um jeito de escrever apenas os caracteres que forem alterados?
* Deixar mais bonito com algum controle de cores;
* Quem sabe, usar Ncurses para apresentar menus, como quando o jogo é pausado, na mesma tela, além de outras bonitices;
* Implementar fases com outros cenários diferentes do tradicional retângulo;
* Gravar estatísticas do jogo e o nome de quem jogou pra fazer um ranking.
