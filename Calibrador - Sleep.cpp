#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

unsigned long tempo; /*tempo em segundos que será cronometrado com um relógio e comparado a o da função sleep 
						  a fim de descobrir o número de loops necessários para gastar 1 mili-segundo.*/

int sleep(unsigned long tmilis) {
	int a = 0;
	tmilis *= 1888.0442;
	while (tmilis > 0) {
		tmilis--;
		for (int i = 0; i < 100; i++){
			a++;
			a--;
		}
	}
	return 0;
}

int main() {
	//Entrada do tempo de espera da função.
	printf("Digite o tempo, em segundos, que vc quer cronometrar para calibrar a funcao:");
	scanf_s("%d", &tempo);
	system("cls");
	//Contagem regressiva para começar a medida.
	for (int i = 50; i > 0; i--){
		printf("%d", i);
		sleep(100);
		system("cls");
	}
	//Aviso para o chinês dar a largada no cronômetro e inicia-se a contagem.
	printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	sleep((tempo-5)*1000);
	//Contagem regressiva para terminar a medida.
	for (int i = 50; i > 0; i--){
		printf("%d", i);
		sleep(100);
		system("cls");
	}
	printf("\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	printf("\nPassaran-se %ds\n\n\n", tempo);
	system("pause");
	return 0;
}