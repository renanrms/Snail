         // Snail
        //Se quizer entender o código comece pela função "printsnail", depois vá para "direção" e depois "andar",
       //depois veja as variáveis e seus comentários e o nome de cada função e seus comentários gerais
      //(os que ficam em cima da função dizendo o que ela faz)
     //Depois vá para a função principal e tire as suas dúvidas lendo as funções por completo.
    //Nesse processo um pouco longo vc deve passar gradualmente de um nívem macroscópico para um detalhado e preciso,
   //pare quando estiver satisfeito.
  //E antes de começar saiba que esse programa tem uma matriz bidimensional "imagem" de valores int, onde cada valor corresponde a um caracter
 //do jogo e essa variável é a memória do jogo, sendo modificada pela função "andar" e printada pela função "printsnail",
//Essa é a esrutura básica do jogo e o resto é frufru.


#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

static int h = 13;                //Número de caracteres na vertical.
static int l = 35;   		     //Número de caracteres na horizontal.
static int imagem[13][35];      //Este é o array que representa a imagem da tela;
static int estado;		       //Decide se o jogo termina ou se continua.
static int score;             //Pontuação do jogador.
static int recorde;	 	     //Guarda a maior pontuação obtida em uma sequência de partidas sem fechar a janela.
static int x, y;            //Posições horizontal e vertical respectivamete.
static int dx, dy;         //São as diferenciais de posição horizontal e vertical, ou seja, o quanto o caraol deve andar.
static int dt;	    	  //É a diferencial do tempo e serve como delay entre os passos do caracol.


//Essa função é um delay e a eu criei e calibrei porque não me dou bem com as bibliotecas pra pegar ela pronta.
int sleep(unsigned long tmilis) {
	int a = 0;
	tmilis *= 1888.0442;  //Esse valor é o número de vezes que é necessário realizar esse loop while para passar um milissegundo. 
	while (tmilis > 0) {
		tmilis--;
		for (int i = 0; i < 100; i++){  //'for' só pra gastar um tempinho.
			a++;
			a--;
		}
	}
	return 0;
}

//Essa função dá a opção de continuar o programa ('j') ou encerrar o jogo ('k').
int encerrar() {
	int a = 0;                             //Variável para armazenar dentro dessa função a pecla pressionada.
	while (!((a == 106) || (a == 107))){  //Enquanto o úsuário não pressionar 'j' (106) ou 'k' (107) continua nesse while redefinindo "a".
		a = _getch();
	}
	if (a == 106){  //Se o usuário apertar 'j' redefine a variável "estado" como 1, o que faz o jogo não terminar.
		estado = 1;
	}
	return 0;
}

//Preeche o array "imagem" com zeros.
int clear(){
	for (int i = 0; i < h; i++){          //Percorre o array na vertical.
		for (int j = 0; j < l; j++){     //Percorreo array na horizontal.
			imagem[i][j] = 0;           //Iguala a zero.
		}
	}
	return 0;
}

//Printa a pontuação o recorde e o jogo.
int printsnail(){
	printf("PONTOS: %d       RECORDE: %d\n", score, recorde);
	//Percorre todo o array de variáveis int e printa na tela;
	printf("=====================================\n");
	for (int i = 0; i < h; i++){
		printf("|");
		for (int j = 0; j < l; j++){
			//Para cada valor guardado naquela posição printa um caracter diferente.
			if (imagem[i][j] == 0){
				printf(" ");  //Espaço vazio.
			}
			else if ((imagem[i][j] > 0) && (imagem[i][j] != score + 1)) {
				printf("+");  //Calda do caracol.
			}
			else if (imagem[i][j] == score + 1){
				printf("@");  //Cabeça do caracol.
			}
			else {
				printf("*");  //Alimento.
			}
		}
		printf("|\n");
	}
	printf("=====================================");
	return 0;
}

//Define a posição da comida do caracol no array "imagem".
int foodefine() {
	int a, b;
	srand(time(NULL));             //Define a semente para gerar números aleatórios.
	a = rand() %h;                //Armazena um número aleatório entre 0 e h.
	b = rand() %l;               //Armazena um número aleatório entre 0 e l.
	while (imagem[a][b] != 0){  //Enquanto não conseguir que a posição (b,a) no array seja um espaço vazio, repete o processo. 
		a = rand() %h;
		b = rand() %l;
	}
	imagem[a][b] = -1;  //Quando achar uma posição vazia põe -1, definindo como um alimento. 
	return 0;
}

//Reposiciona o caracol no array "imagem".
int andar(){
	x += dx;   //Define a nova posição horizontal do caracol.
	y += dy;  //Define a nova posição vertical do caracol.
	//Se a nova posição do caracol estiver fora de algum dos limites do campo ela é redefinida do outro lado, fazendo o caracol dar a volta.
	if (x == -1){
		x = l - 1;
	}
	if (x == l){
		x = 0;
	}
	if (y == -1){
		y = h - 1;
	}
	if (y == h){
		y = 0;
	}
	//Se a nova posição for um espaço vazio (caracol não come), então subtrai 1 de cada caracter que compõe o caracol,
	//fazendo sumir a ponta traseira do caracol, transformando o '@' em um '+' e
	//mantendo todo o resto preparado para sumir gradualmente nos próximos passos.
	if (imagem[y][x] == 0){
		for (int i = 0; i < h; i++){
			for (int j = 0; j < l; j++){
				if (imagem[i][j] > 0){
					imagem[i][j]--;
				}
			}
		}
	}
	//Se a nova posição for um alimento, então define-se o novo score, fazendo o '@' se tornar um '+', sem sumir nada do caracol.
	else if (imagem[y][x] == -1) {
		score++;
		foodefine();
	}
	//Se o caracol for para qualquer outra coisa (como a própria calda ou algum obstáculo que possa ser inserido no jogo),
	//então o "estado" é definido como 2, o que faz ir para a pergunta se o usuário que jogar novamente ou terminar.
	else {
		estado = 2;
		return 0;
	}
	//Depois de subtrair-se 1 de todo o caracol ou de acrescentar-se 1 ao score define-se a nova cabeça no caracol.
	imagem[y][x] = score + 1;
	return 0;
}

//Define a direção para a qual a cobra vai andar baseado na tecla pressionada.
int direcao(){
	if (_kbhit()){
		switch (_getch()){
			// Movimentação com os números '4', '5' (ou '2'), '6' e '8'.
		case 52:
			dx = -1;
			dy = 0;
			break;
		case 54:
			dx = 1;
			dy = 0;
			break;
		case 56:
			dx = 0;
			dy = -1;
			break;
		case 50:
			dx = 0;
			dy = 1;
			break;
		case 53:
			dx = 0;
			dy = 1;
			break;
			//Movimentação com as letras 'a', 's', 'd' e 'w'.
		case 97:
			dx = -1;
			dy = 0;
			break;
		case 100:
			dx = 1;
			dy = 0;
			break;
		case 119:
			dx = 0;
			dy = -1;
			break;
		case 115:
			dx = 0;
			dy = 1;
			break;
			//Pausa o jogo caso o jogador aperte a tecla 'Esc'.
		case 27:          //27 é o valor do 'Esc' na tabela ASCII.
			estado = 3;  //3 é valor dessa variável definido, na função principal, que pausa o jogo.
		}
	}
	return 0;
}

//Printa aquela apresentação aviadada que o Perovani põe em todo programa.
int apresentacao() {
	printf("================================================================================");
	printf("||                                                                            ||");
	printf("||                                   FEITO POR:                               ||");
	printf("||                        LUCAS PEROVANI E RENAN VIEIRA                       ||");
	printf("||                                     5AELT                                  ||");
	printf("||                                                                            ||");
	printf("================================================================================\n");
	printf(" -> COMO JOGAR:\n\n");
	printf(" USE AS TECLAS 2 (OU 5), 4, 6 E 8 PARA MOVIMENTAR O CARACOL.\n\n");
	printf("   8 ou W  -> SUBIR\n");
	printf(" 2, 5 ou S -> DESCER\n");
	printf("   6 ou D  -> DIREITA\n");
	printf("   4 ou A  -> ESQUERDA\n");
	printf("    ESC    -> PARA PAUSAR OU SAIR DO JOGO A QUALQUER HORA\n\n\n\n\n\n\n\n");
	system("pause");
	printf("CARREGANDO...");
	return 0;
}

//Define as variáveis iniciais do programa. 
int iniciacao() {
	score = 0;
	dx = 1;
	dy = 0;
	clear();
	x = l / 2;
	y = h / 2;
	imagem[y][x] = score + 1;
	foodefine();
	return 0;
}

//Dá um delay de acordo com a pontuação do jogador e com a direção, corrigindo a diferença de velocidade entre a vertical e a horizontal. 
int velocidade() {
	//Níveis de velocidade de acordo com a pontuação.
	switch (score){
	case 0:
		dt = 100;
		break;
	case 5:
		dt = 75;
		break;
	case 10:
		dt = 50;
		break;
	case 20:
		dt = 40;
		break;
	case 30:
		dt = 30;
		break;
	case 50:
		dt = 20;
		break;
	case 100:
		dt = 10;
		break;
	case 333:
		dt = 0;
	}
	//Correção da velocidade para igualar a vertical e a horizontal.
	if (dx == 0){
		//Se o movimento é na vertical...
		sleep(1.47*dt);
	}
	else{
		//Se é na horizontal... 
		sleep(dt);
	}
	return 0;
}



int main() {
	estado = 1;
	recorde = 0;
	apresentacao();
	while (estado == 1){
		//Atualiza o recorde toda vez que começa um novo jogo sem se ter fechado a janela.
		if (score > recorde){
			recorde = score;
		}
		iniciacao();
		system("cls");
		printsnail();
		while (estado == 1){
			//Define a direção e anda o caracol na memória do jogo sem alterar a tela.
			direcao();
			//Pause. Se o jogador pressionar 'k', "estado" continua como 3 e o programa sai dos dois loops.
			if (estado == 3){
				system("cls");
				printf("\n	 =============================================================");
				printf("\n	 ||                                                         ||");
				printf("\n	 ||                     Jogo Pausado:                       ||");
				printf("\n         ||                                                         ||");
				printf("\n	 ||                                                         ||");
				printf("\n	 ||         ->  Pressione 'j' para continuar o jogo.        ||");
				printf("\n	 ||                                                         ||");
				printf("\n	 ||         ->  Pressione 'k' para encerrar o jogo.         ||");
				printf("\n	 ||                                                         ||");
				printf("\n	 =============================================================");
				encerrar();
			}
			andar();
			//Limpa a tela e printa o jogo com as novas posição, pontuação e recorde. 
			system("cls");
			printsnail();
			velocidade();
		}
		//Pergunta se o jogador quer terminar ou jogar novamente. Se o jogador pressionar 'k',
		//"estado" continua como 2 e o programa sai do loop. Se pressionar 'j' continua nesse loop mais externo
		//e começa outra partida, passando pela função iniciação que restaura a maior parte das variáveis.
		if (estado == 2){
			system("cls");
			printf("\n	 =============================================================");
			printf("\n	 ||                                                         ||");
			printf("\n	 ||             O caracol morreu na propria calda!          ||");
			printf("\n         ||                                                         ||");
			printf("\n	 ||                                                         ||");
			printf("\n	 ||         ->  Pressione 'j' para jogar novamente.         ||");
			printf("\n	 ||                                                         ||");
			printf("\n	 ||         ->  Pressione 'k' para encerrar o jogo.         ||");
			printf("\n	 ||                                                         ||");
			printf("\n	 =============================================================\n\n\n\n\n");
			encerrar();
		}
	}
	printf("\n\n\n\n\n\n\n\n");
	return 0;
}

