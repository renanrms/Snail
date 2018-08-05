         // Snail
        //Se quizer entender o c�digo comece pela fun��o "printsnail", depois v� para "dire��o" e depois "andar",
       //depois veja as vari�veis e seus coment�rios e o nome de cada fun��o e seus coment�rios gerais
      //(os que ficam em cima da fun��o dizendo o que ela faz)
     //Depois v� para a fun��o principal e tire as suas d�vidas lendo as fun��es por completo.
    //Nesse processo um pouco longo vc deve passar gradualmente de um n�vem macrosc�pico para um detalhado e preciso,
   //pare quando estiver satisfeito.
  //E antes de come�ar saiba que esse programa tem uma matriz bidimensional "imagem" de valores int, onde cada valor corresponde a um caracter
 //do jogo e essa vari�vel � a mem�ria do jogo, sendo modificada pela fun��o "andar" e printada pela fun��o "printsnail",
//Essa � a esrutura b�sica do jogo e o resto � frufru.


#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

static int h = 13;                //N�mero de caracteres na vertical.
static int l = 35;   		     //N�mero de caracteres na horizontal.
static int imagem[13][35];      //Este � o array que representa a imagem da tela;
static int estado;		       //Decide se o jogo termina ou se continua.
static int score;             //Pontua��o do jogador.
static int recorde;	 	     //Guarda a maior pontua��o obtida em uma sequ�ncia de partidas sem fechar a janela.
static int x, y;            //Posi��es horizontal e vertical respectivamete.
static int dx, dy;         //S�o as diferenciais de posi��o horizontal e vertical, ou seja, o quanto o caraol deve andar.
static int dt;	    	  //� a diferencial do tempo e serve como delay entre os passos do caracol.


//Essa fun��o � um delay e a eu criei e calibrei porque n�o me dou bem com as bibliotecas pra pegar ela pronta.
int sleep(unsigned long tmilis) {
	int a = 0;
	tmilis *= 1888.0442;  //Esse valor � o n�mero de vezes que � necess�rio realizar esse loop while para passar um milissegundo. 
	while (tmilis > 0) {
		tmilis--;
		for (int i = 0; i < 100; i++){  //'for' s� pra gastar um tempinho.
			a++;
			a--;
		}
	}
	return 0;
}

//Essa fun��o d� a op��o de continuar o programa ('j') ou encerrar o jogo ('k').
int encerrar() {
	int a = 0;                             //Vari�vel para armazenar dentro dessa fun��o a pecla pressionada.
	while (!((a == 106) || (a == 107))){  //Enquanto o �su�rio n�o pressionar 'j' (106) ou 'k' (107) continua nesse while redefinindo "a".
		a = _getch();
	}
	if (a == 106){  //Se o usu�rio apertar 'j' redefine a vari�vel "estado" como 1, o que faz o jogo n�o terminar.
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

//Printa a pontua��o o recorde e o jogo.
int printsnail(){
	printf("PONTOS: %d       RECORDE: %d\n", score, recorde);
	//Percorre todo o array de vari�veis int e printa na tela;
	printf("=====================================\n");
	for (int i = 0; i < h; i++){
		printf("|");
		for (int j = 0; j < l; j++){
			//Para cada valor guardado naquela posi��o printa um caracter diferente.
			if (imagem[i][j] == 0){
				printf(" ");  //Espa�o vazio.
			}
			else if ((imagem[i][j] > 0) && (imagem[i][j] != score + 1)) {
				printf("+");  //Calda do caracol.
			}
			else if (imagem[i][j] == score + 1){
				printf("@");  //Cabe�a do caracol.
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

//Define a posi��o da comida do caracol no array "imagem".
int foodefine() {
	int a, b;
	srand(time(NULL));             //Define a semente para gerar n�meros aleat�rios.
	a = rand() %h;                //Armazena um n�mero aleat�rio entre 0 e h.
	b = rand() %l;               //Armazena um n�mero aleat�rio entre 0 e l.
	while (imagem[a][b] != 0){  //Enquanto n�o conseguir que a posi��o (b,a) no array seja um espa�o vazio, repete o processo. 
		a = rand() %h;
		b = rand() %l;
	}
	imagem[a][b] = -1;  //Quando achar uma posi��o vazia p�e -1, definindo como um alimento. 
	return 0;
}

//Reposiciona o caracol no array "imagem".
int andar(){
	x += dx;   //Define a nova posi��o horizontal do caracol.
	y += dy;  //Define a nova posi��o vertical do caracol.
	//Se a nova posi��o do caracol estiver fora de algum dos limites do campo ela � redefinida do outro lado, fazendo o caracol dar a volta.
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
	//Se a nova posi��o for um espa�o vazio (caracol n�o come), ent�o subtrai 1 de cada caracter que comp�e o caracol,
	//fazendo sumir a ponta traseira do caracol, transformando o '@' em um '+' e
	//mantendo todo o resto preparado para sumir gradualmente nos pr�ximos passos.
	if (imagem[y][x] == 0){
		for (int i = 0; i < h; i++){
			for (int j = 0; j < l; j++){
				if (imagem[i][j] > 0){
					imagem[i][j]--;
				}
			}
		}
	}
	//Se a nova posi��o for um alimento, ent�o define-se o novo score, fazendo o '@' se tornar um '+', sem sumir nada do caracol.
	else if (imagem[y][x] == -1) {
		score++;
		foodefine();
	}
	//Se o caracol for para qualquer outra coisa (como a pr�pria calda ou algum obst�culo que possa ser inserido no jogo),
	//ent�o o "estado" � definido como 2, o que faz ir para a pergunta se o usu�rio que jogar novamente ou terminar.
	else {
		estado = 2;
		return 0;
	}
	//Depois de subtrair-se 1 de todo o caracol ou de acrescentar-se 1 ao score define-se a nova cabe�a no caracol.
	imagem[y][x] = score + 1;
	return 0;
}

//Define a dire��o para a qual a cobra vai andar baseado na tecla pressionada.
int direcao(){
	if (_kbhit()){
		switch (_getch()){
			// Movimenta��o com os n�meros '4', '5' (ou '2'), '6' e '8'.
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
			//Movimenta��o com as letras 'a', 's', 'd' e 'w'.
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
		case 27:          //27 � o valor do 'Esc' na tabela ASCII.
			estado = 3;  //3 � valor dessa vari�vel definido, na fun��o principal, que pausa o jogo.
		}
	}
	return 0;
}

//Printa aquela apresenta��o aviadada que o Perovani p�e em todo programa.
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

//Define as vari�veis iniciais do programa. 
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

//D� um delay de acordo com a pontua��o do jogador e com a dire��o, corrigindo a diferen�a de velocidade entre a vertical e a horizontal. 
int velocidade() {
	//N�veis de velocidade de acordo com a pontua��o.
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
	//Corre��o da velocidade para igualar a vertical e a horizontal.
	if (dx == 0){
		//Se o movimento � na vertical...
		sleep(1.47*dt);
	}
	else{
		//Se � na horizontal... 
		sleep(dt);
	}
	return 0;
}



int main() {
	estado = 1;
	recorde = 0;
	apresentacao();
	while (estado == 1){
		//Atualiza o recorde toda vez que come�a um novo jogo sem se ter fechado a janela.
		if (score > recorde){
			recorde = score;
		}
		iniciacao();
		system("cls");
		printsnail();
		while (estado == 1){
			//Define a dire��o e anda o caracol na mem�ria do jogo sem alterar a tela.
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
			//Limpa a tela e printa o jogo com as novas posi��o, pontua��o e recorde. 
			system("cls");
			printsnail();
			velocidade();
		}
		//Pergunta se o jogador quer terminar ou jogar novamente. Se o jogador pressionar 'k',
		//"estado" continua como 2 e o programa sai do loop. Se pressionar 'j' continua nesse loop mais externo
		//e come�a outra partida, passando pela fun��o inicia��o que restaura a maior parte das vari�veis.
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

