#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <time.h> 

#include "biblioteca.h"

#define TAM 8



int main(int argc[], char *argv[]){
	setlocale(LC_ALL, "portuguese");
	int i, j;
	int n_dicas, *pdicas;
	pdicas = &n_dicas;
	int opcao1, opcao2;
	struct tabela jogador, computador, *pjogador, *pcomputador;
	pjogador = &jogador;
	pcomputador = &computador;
	informacoes();
	do{
		opcao1 = menu_principal();
		while(opcao1 != 1 && opcao1 != 2 && opcao1 != 3 && opcao1 != 4){
			system("cls");
			printf("\n\n\n");
			printf("\t\t>>>>>>>>>> OPÇÂO INVÁLIDA <<<<<<<<<<");
			sleep(1);
			opcao1 = menu_principal();	
		}
		switch(opcao1){
			case 1:
				n_dicas = 0;
				preencher_tabela(pjogador, pcomputador);
				posicionar_embarcacoes(pjogador);
				sleep(1);/*solução que encontrei para o gerador de números aleatórios não usar a mesma semente e gerar duas tabela identicas*/
				posicionar_embarcacoes(pcomputador);
				do{
					imprimir_tabela(pjogador, pcomputador);
					opcao2 = menu_secundario();
					switch(opcao2){
						case 1:
							disparar(pcomputador, pjogador);
							disparar_computador(pjogador, pcomputador);
							break;
						case 2:
							n_dicas++;
							if(n_dicas <= 3){
								dica(pcomputador, pjogador);
							}else{
								printf("\n\n\t>>>>>>> Você atingiu o limite máximo de dicas <<<<<<<\n\n\n");
							}
							system("pause");
							break;
						case 3:
							salvar(pjogador, pcomputador, pdicas);
							break;
						case 4:
							informacoes();
							break;
						case 5:
							return 0;			
					}	
				}while(pjogador->pontuacao != 10 && pcomputador->pontuacao != 10 && opcao2 != 3);
				if(opcao2 != 3){
					if(pjogador->pontuacao >= pcomputador->pontuacao){
						system("cls");
						printf("\n\n\n\tParabéns, você ganhou!!!\n\n");
						system("pause");
					}else{
						system("cls");
						printf("\n\n\n\tVocê foi derrotado!\n\n");
						system("pause");
					}
				}
				break;
			case 2:
				if(jogo_salvo(pjogador, pcomputador, pdicas) == 0){
					do{
						imprimir_tabela(pjogador, pcomputador);
						opcao2 = menu_secundario();
						switch(opcao2){
							case 1:
								disparar(pcomputador, pjogador);
								disparar_computador(pjogador, pcomputador);
								break;
							case 2:
								n_dicas++;
								if(n_dicas <= 3){
									dica(pcomputador, pjogador);
								}else{
									printf("\n\n\t>>>>>>> Você atingiu o limite máximo de dicas <<<<<<<\n\n\n");
								}
								system("pause");
								break;
							case 3:
								salvar(pjogador, pcomputador, pdicas);
								break;
							case 4:
									informacoes();
								break;
							case 5:
								return 0;			
						}	
					}while(pjogador->pontuacao != 10 && pcomputador->pontuacao != 10 && opcao2 != 3);
					if(opcao2 != 3){
						if(pjogador->pontuacao >= pcomputador->pontuacao){
							system("cls");
							printf("\n\n\n\tParabéns, você ganhou!!!\n\n");
							system("pause");
						}else{
							system("cls");
							printf("\n\n\n\tVocê foi derrotado!\n\n");
							system("pause");
						}
					}
				}
				break;				
			case 3:
					informacoes();
				break;
			case 4: 
				return 0;				
		}
	}while("true");
	return 0;
}


