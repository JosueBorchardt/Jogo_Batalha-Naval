#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <time.h> 

#include "biblioteca.h"

#define TAM 8

void preencher_tabela(struct tabela *ptab1, struct tabela *ptab2){
	int i, j, k, x;
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			ptab1->posicao_atingida[i][j] = 0;
			ptab2->posicao_atingida[i][j] = 0;
			ptab1->posicao_embarcacoes[i][j] = 0;
			ptab2->posicao_embarcacoes[i][j] = 0;
		}
	}
	ptab1->vida_embarcacoes[0] = 1;
	ptab1->vida_embarcacoes[1] = 2;
	ptab1->vida_embarcacoes[2] = 3;
	ptab1->vida_embarcacoes[3] = 4;
	ptab2->vida_embarcacoes[0] = 1;
	ptab2->vida_embarcacoes[1] = 2;
	ptab2->vida_embarcacoes[2] = 3;
	ptab2->vida_embarcacoes[3] = 4;
	ptab1->pontuacao = 0;
	ptab2->pontuacao = 0;
}

void imprimir_tabela(struct tabela *tab1, struct tabela *tab2){
	int i, j;
	char x[9] = "ABCDEFGH";
	system("cls");
	printf("\n\n\t\tJogador\t\t\t\t\t\tComputador\n\n");
	printf("\t  1   2   3   4   5   6   7   8\t\t\t  1   2   3   4   5   6   7   8\n");
	for(i = 0; i < TAM; i++){
		printf("\t%c ", x[i]);
		for(j = 0; j < TAM; j++){
			if(tab1->posicao_embarcacoes[i][j] > 0){
				printf("%d   ", tab1->posicao_embarcacoes[i][j]);
			}else{
				if(tab1->posicao_embarcacoes[i][j] < 0){
					printf("X   ");
				}else{
					if(tab1->posicao_atingida[i][j] == 0){
						printf("0   ");
					}else{
						printf("~   ");
					}
				}
			}
		}
		printf("\t\t%c ", x[i]);
		for(j = 0; j < TAM; j++){
			if(tab2->posicao_atingida[i][j] == 0){
				printf("0   ");
			}else{
				if(tab2->posicao_embarcacoes[i][j] == 0){
					printf("~   ");
				}else{
					printf("X   ");
				}
			}
		}
		printf("\n");
	}
}

void posicionar_embarcacoes(struct tabela *ptab){
	int i, j, k;
	int sentido, linha, coluna, posicao_maxima, verificador;
	srand(time(NULL));
	for(i = 1; i <= 4; i++){
		posicao_maxima = 9 - i;
		do{
			verificador = 0;
			sentido = rand()%2;
			if(sentido == 0){
				linha = rand()%8;
				coluna = rand()%posicao_maxima;
				for(j = coluna; j < (coluna+i); j++){
					if(ptab->posicao_embarcacoes[linha][j] != 0){
						verificador++;
					}
				}
			}else{
				linha = rand()%posicao_maxima;
				coluna = rand()%8;
				for(j = linha; j < (linha+i); j++){
					if(ptab->posicao_embarcacoes[j][coluna] != 0){
						verificador++;
					}
				}
			}
		}while(verificador != 0);
		if(sentido == 0){
			for(k = 0; k < i; k++){
				ptab->posicao_embarcacoes[linha][coluna] = i;
				coluna++;
			}	
		}else{
			for(k = 0; k < i; k++){
				ptab->posicao_embarcacoes[linha][coluna] = i;
				linha++;
			}
		}
	}
}

int menu_principal(){
	int opcao;
	system("cls");
	printf("\n\n\t\tMenu Principal\n\n");
	printf("\tOpc�o 1) Novo jogo\n");
	printf("\tOp��o 2) Carregar jogo salvo\n");
	printf("\tOpc�o 3) Sobre o jogo\n");
	printf("\tOpc�o 4) Sair\n");
	printf("\n\tEscolha uma op��o: ");
	scanf("%d", &opcao);
	return opcao;
}

int menu_secundario(){
	int opcao;
	printf("\n\n\tOp��o 1) Disparar\n");
	printf("\tOp��o 2) Dica\n");
	printf("\tOp��o 3) Salvar\n");
	printf("\tOp��o 4) Sobre o jogo\n");
	printf("\tOp��o 5) Sair\n");
	printf("\n\tEscolha um op��o: ");
	scanf("%d", &opcao);
	return opcao;
}

void atualizar_pontuacao(struct tabela *tab_atacada, struct tabela *tab_atacante, int linha, int coluna){
	if(tab_atacada->posicao_embarcacoes[linha][coluna] == 4){
		tab_atacada->posicao_embarcacoes[linha][coluna] = -4;
		tab_atacada->vida_embarcacoes[3]--;
		tab_atacante->pontuacao = tab_atacante->pontuacao + 1;
	}else{
		if(tab_atacada->posicao_embarcacoes[linha][coluna] == 3){
			tab_atacada->posicao_embarcacoes[linha][coluna] = -3;
			tab_atacada->vida_embarcacoes[2]--;
			tab_atacante->pontuacao = tab_atacante->pontuacao + 1;
		}else{
			if(tab_atacada->posicao_embarcacoes[linha][coluna] == 2){
				tab_atacada->posicao_embarcacoes[linha][coluna] = -2;
				tab_atacada->vida_embarcacoes[1]--;
				tab_atacante->pontuacao = tab_atacante->pontuacao + 1;
			}else{
				if(tab_atacada->posicao_embarcacoes[linha][coluna] == 1){
					tab_atacada->posicao_embarcacoes[linha][coluna] = -1;
					tab_atacada->vida_embarcacoes[0]--;
					tab_atacante->pontuacao = tab_atacante->pontuacao + 1;
				}
			}
		}
	}
}

void disparar(struct tabela *ptabela, struct tabela *ptabela1){
	int i, j, verificador;
	int embarcacao, posicao_linha, posicao_coluna;
	int aux_linha, aux_coluna, aux_embarcacao;
	char linha;
	int coluna;
	imprimir_tabela(ptabela1, ptabela);
	printf("\n\n\tOp��o 1) Ca�a\n\tOp��o 2) Submarino\n\tOp��o 3) Navio de escolta\n\tOp��o 4) Porta-avi�es\n");
	printf("\n\tEscolha com qual embarca��o atacar: ");
	scanf("%d", &embarcacao);
	while(embarcacao < 1 || embarcacao > 4){
		imprimir_tabela(ptabela1, ptabela);
		printf("\n\n\tOp��o 1) Ca�a\n\tOp��o 2) Submarino\n\tOp��o 3) Navio de escolta\n\tOp��o 4) Porta-avi�es\n");
		fflush(stdin);
		printf("\n\n\tEmbarca��o inv�lida, escolha novamente: ");
		scanf("%d", &embarcacao);
	}
	aux_embarcacao = embarcacao - 1;
	while(ptabela1->vida_embarcacoes[aux_embarcacao] <= 0){
		imprimir_tabela(ptabela1, ptabela);
		printf("\n\n\tEst� embarca��o j� foi destruida, escolha novamente: ");
		scanf("%d", &embarcacao);
		aux_embarcacao = embarcacao - 1;
	}
	printf("\n\tDigite a posi��o a ser atacada: ");
	fflush(stdin);
	scanf("%c", &linha);
	scanf("%d", &coluna);
	while(linha != 'A' && linha != 'B' && linha != 'C' && linha != 'D' && linha != 'E' && linha != 'F' && linha != 'G' && linha != 'H' || coluna > 8 || coluna < 1){
		imprimir_tabela(ptabela1, ptabela);
		printf("\n\n\tPosi��o inv�lida digite novamente: ");
		fflush(stdin);
		scanf("%c", &linha);
		scanf("%d", &coluna);
	}
	switch(linha){
		case 'A':
			posicao_linha = 0;
			break;
		case 'B':
			posicao_linha = 1;
			break;
		case 'C':
			posicao_linha = 2;
			break;	
		case 'D':
			posicao_linha = 3;
			break;
		case 'E':
			posicao_linha = 4;
			break;		
		case 'F':
			posicao_linha = 5;
			break;	
		case 'G':
			posicao_linha = 6;
			break;	
		case 'H':
			posicao_linha = 7;
			break;	
	}
	posicao_coluna = coluna - 1;
	switch(embarcacao){
		case 1:
			ptabela->posicao_atingida[posicao_linha][posicao_coluna] = 1;
			atualizar_pontuacao(ptabela, ptabela1, posicao_linha, posicao_coluna);
			aux_linha = posicao_linha + 1;
			aux_coluna = posicao_coluna + 1;
			for(i = 0; i < 2; i++){
				if(aux_linha >= 0 && aux_linha <= 7){
					ptabela->posicao_atingida[aux_linha][posicao_coluna] = 1;
					atualizar_pontuacao(ptabela, ptabela1, aux_linha, posicao_coluna);
				}
				aux_linha = aux_linha - 2;
				if(aux_coluna >= 0 && aux_coluna <= 7){
					ptabela->posicao_atingida[posicao_linha][aux_coluna] = 1;
					atualizar_pontuacao(ptabela, ptabela1, posicao_linha, aux_coluna);
				}
				aux_coluna = aux_coluna - 2;
			}	
			break;
		case 2:
			ptabela->posicao_atingida[posicao_linha][posicao_coluna] = 1;
			atualizar_pontuacao(ptabela, ptabela1, posicao_linha, posicao_coluna);
			break;
		case 3:
			for(i = 0; i < 2; i++){
				if(posicao_coluna >= 0 && posicao_coluna <= 7){
					ptabela->posicao_atingida[posicao_linha][posicao_coluna] = 1;
					atualizar_pontuacao(ptabela, ptabela1, posicao_linha, posicao_coluna);
					posicao_coluna++;					
				}
			}
			break;
		case 4:
			for(i = 0; i < 2; i++){
				if(posicao_linha >= 0 && posicao_linha <= 7){
					ptabela->posicao_atingida[posicao_linha][posicao_coluna] = 1;
					atualizar_pontuacao(ptabela, ptabela1, posicao_linha, posicao_coluna);
					posicao_linha++;					
				}
			}
			break;			
	}
}

void dica(struct tabela *tab, struct tabela *tab2){
	int i, j;
	int linha, coluna, verificador_linha = 0, verificador_coluna = 0;
	char aux_linha;
	int caca = 0, submarino = 0, navio_escolta = 0, porta_avioes = 0; 
	imprimir_tabela(tab2, tab);
	printf("\n\n\tInforme a posi��o: ");
	fflush(stdin);
	scanf("%c", &aux_linha);
	scanf("%d", &coluna);
	while(aux_linha != 'A' && aux_linha != 'B' && aux_linha != 'C' && aux_linha != 'D' && aux_linha != 'E' && aux_linha != 'F' && aux_linha != 'G' && aux_linha != 'H' || coluna > 8 || coluna < 1){
		imprimir_tabela(tab2, tab);
		printf("\n\nPosi��o inv�lida digite novamente: ");
		fflush(stdin);
		scanf("%c", &aux_linha);
		scanf("%d", &coluna);
	}
	switch(aux_linha){
		case 'A':
			linha = 0;
			break;
		case 'B':
			linha = 1;
			break;
		case 'C':
			linha = 2;
			break;	
		case 'D':
			linha = 3;
			break;
		case 'E':
			linha = 4;
			break;		
		case 'F':
			linha = 5;
			break;	
		case 'G':
			linha = 6;
			break;	
		case 'H':
			linha = 7;
			break;	
	}
	coluna = coluna - 1;
	for(i = 0; i < 8; i++){
		if(tab->posicao_embarcacoes[linha][i] == 1){
			caca++;
		}else{
			if(tab->posicao_embarcacoes[linha][i] == 2){
				submarino++;
			}else{
				if(tab->posicao_embarcacoes[linha][i] == 3){
					navio_escolta++;
				}else{
					if(tab->posicao_embarcacoes[linha][i] == 4){
						porta_avioes++;
					}
				}
			}
		}
	}
	if(caca > 0){
		verificador_linha++;
	}
	if(submarino > 0){
		verificador_linha++;
	}
	if(navio_escolta > 0){
		verificador_linha++;
	}
	if(porta_avioes > 0){
		verificador_linha++;
	}
	caca = 0;
	submarino = 0;
	navio_escolta = 0;
	porta_avioes = 0;
	for(i = 0; i < 8; i++){
		if(tab->posicao_embarcacoes[i][coluna] == 1){
			caca++;
		}else{
			if(tab->posicao_embarcacoes[i][coluna] == 2){
				submarino++;
			}else{
				if(tab->posicao_embarcacoes[i][coluna] == 3){
					navio_escolta++;
				}else{
					if(tab->posicao_embarcacoes[i][coluna] == 4){
						porta_avioes++;
					}	
				}
			}
		}
	}
	if(caca > 0){
		verificador_coluna++;
	}
	if(submarino > 0){
		verificador_coluna++;
	}
	if(navio_escolta > 0){
		verificador_coluna++;
	}
	if(porta_avioes > 0){
		verificador_coluna++;
	}
	printf("\n\n\tN�mero de embarca��es na linha %c: %d\n", aux_linha, verificador_linha);
	printf("\tN�mero de embarca��es na coluna %d: %d\n\n\n", coluna + 1, verificador_coluna);
}

void disparar_computador(struct tabela *ptabela, struct tabela *ptab){
	int i, j;
	int tiro, linha, coluna, aux_linha, aux_coluna;
	int verificador;
	srand(time(NULL));
	if(ptab->vida_embarcacoes[0] > 0){
		tiro = 1;
	}else{
		if(ptab->vida_embarcacoes[2] > 0 || ptab->vida_embarcacoes[3] > 0){
			tiro = rand()%2 + 3;
		}else{
			tiro = 2;
		}
	}	
	do{
		verificador = 0;
		linha = rand()%8;
		coluna = rand()%8;
		if(ptabela->posicao_atingida[linha][coluna] != 0){
			verificador++;
		}
	}while(verificador != 0);
	switch(tiro){
		case 1:
			ptabela->posicao_atingida[linha][coluna] = 1;
			atualizar_pontuacao(ptabela, ptab, linha, coluna);
			aux_linha = linha + 1;
			aux_coluna = coluna + 1;
			for(i = 0; i < 2; i++){
				if(aux_linha >= 0 && aux_linha <= 7){
					ptabela->posicao_atingida[aux_linha][coluna] = 1;
					atualizar_pontuacao(ptabela, ptab, aux_linha, coluna);
				}
				aux_linha = aux_linha - 2;
				if(aux_coluna >= 0 && aux_coluna <= 7){
					ptabela->posicao_atingida[linha][aux_coluna] = 1;
					atualizar_pontuacao(ptabela, ptab, linha, aux_coluna);
				}
				aux_coluna = aux_coluna - 2;
			}	
			break;
		case 2:
			ptabela->posicao_atingida[linha][coluna] = 1;
			atualizar_pontuacao(ptabela, ptab, linha, coluna);
			break;
		case 3:
			for(i = 0; i < 2; i++){
				if(coluna >= 0 && coluna <= 7){
					ptabela->posicao_atingida[linha][coluna] = 1;
					atualizar_pontuacao(ptabela, ptab, linha, coluna);
					coluna++;					
				}
			}
			break;
		case 4:
			for(i = 0; i < 2; i++){
				if(linha >= 0 && linha <= 7){
					ptabela->posicao_atingida[linha][coluna] = 1;
					atualizar_pontuacao(ptabela, ptab, linha, coluna);
					linha++;					
				}
			}
			break;			
	}
}

void salvar(struct tabela *tab_jog, struct tabela *tab_comp, int *dicas){
	int i, j;
	FILE *salvar;
	salvar = fopen("salvar.txt", "w");
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			fprintf(salvar, "%d", tab_jog->posicao_atingida[i][j]);
		}
	}
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			fprintf(salvar, "%d", tab_jog->posicao_embarcacoes[i][j]);
		}
	}
	for(i = 0; i < 4; i++){
		fprintf(salvar, "%d", tab_jog->vida_embarcacoes[i]);
	}
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			fprintf(salvar, "%d", tab_comp->posicao_atingida[i][j]);
		}
	}
	for(i = 0; i < TAM; i++){
		for(j = 0; j < TAM; j++){
			fprintf(salvar, "%d", tab_comp->posicao_embarcacoes[i][j]);
		}
	}
	for(i = 0; i < 4; i++){
		fprintf(salvar, "%d", tab_comp->vida_embarcacoes[i]);
	}
	fprintf(salvar,"%d", tab_jog->pontuacao);
	fprintf(salvar,"%d", tab_comp->pontuacao);
	fprintf(salvar, "%d", dicas);
	fclose(salvar);
}

int jogo_salvo(struct tabela *tab_jog, struct tabela *tab_comp, int *dicas){
	int i, j, k = 0;
	char x[400];
	char aux[2], aux2[3];
	FILE *jogo_salvo;
	jogo_salvo = fopen("salvar.txt", "r");
	if(jogo_salvo == NULL){
		printf("\n\n\t>>>>>>> N�o foi encontrado nenhum jogo salvo <<<<<<<\n\n");
		system("pause");
		return 1;
	}else{
		while(fgets(x, 400, jogo_salvo) != NULL){
			
		}
		for(i = 0; i < TAM; i++){
			for(j = 0; j < TAM; j++){
				aux[0] = x[k];
				tab_jog->posicao_atingida[i][j] = atoi(aux);
				k++;
			}	
		}
		for(i = 0; i < TAM; i++){
			for(j = 0; j < TAM; j++){
				if(x[k] == '-'){
					aux2[0] = x[k];
					k++;
					aux2[1] = x[k];
					k++;
					tab_jog->posicao_embarcacoes[i][j]= atoi(aux2);
				}else{
					aux[0] = x[k];
					k++;
					tab_jog->posicao_embarcacoes[i][j] = atoi(aux);
				}
			}	
		}
		for(i = 0; i < 4; i++){
			aux[0] = x[k];
			tab_jog->vida_embarcacoes[i] = atoi(aux);
			k++;	
		}
		for(i = 0; i < TAM; i++){
			for(j = 0; j < TAM; j++){
				aux[0] = x[k];
				tab_comp->posicao_atingida[i][j] = atoi(aux);
				k++;
			}	
		}
		for(i = 0; i < TAM; i++){
			for(j = 0; j < TAM; j++){
				if(x[k] == '-'){
					aux2[0] = x[k];
					k++;
					aux2[1] = x[k];
					k++;
					tab_comp->posicao_embarcacoes[i][j] = atoi(aux2);
				}else{
					aux[0] = x[k];
					k++;
					tab_comp->posicao_embarcacoes[i][j] = atoi(aux);
				}
			}	
		}
		for(i = 0; i < 4; i++){
			aux[0] = x[k];
			tab_comp->vida_embarcacoes[i] = atoi(aux);
			k++;	
		}
		aux[0] = x[k];
		tab_jog->pontuacao = atoi(aux);
		k++;
		aux[0] = x[k];
		tab_comp->pontuacao = atoi(aux);
		k++;
		aux[0] = x[k];
		dicas = atoi(aux);
	}
	fclose(jogo_salvo);
	return 0;
}

void informacoes(){
	system("cls");
	printf("\n\t\tDescri��o\n\n\t0 - Posi��o n�o atingida\n");
	printf("\t~ - �gua\n");
	printf("\tX - Embarca��o atingida\n");
	printf("\t1 - Ca�a\n\t2 - Submarino\n\t3 - Navio de escolta\n\t4 - Porta-avi�es\n\n\n");
	system("pause");
	system("cls");
	printf("\n\t\tCa�a\n");
	printf("\tDisparo estrela\n");
	printf("\tAtinge 5 posi��es: posi��o escolhida e as posi��es inferior, superior, a esquerda e a direita desta\n");
	printf("\n\t\tSubmarino\n");
	printf("\tDisparo comum\n");
	printf("\tAtinge 1 posi��o: posi��o escolhida\n");
	printf("\n\t\tNavio escolta\n");
	printf("\tDisparo cascata horizontal\n");
	printf("\tAtinge 2 posi��o: posi��o escolhida e a posi��o a direita desta\n");
	printf("\n\t\tPorta-avi�es\n");
	printf("\tDisparo cascata vertical\n");
	printf("\tAtinge 2 posi��o: posi��o escolhida e a posi��o inferior desta\n\n\n");
	system("pause");
	system("cls");
	printf("\n\t\tInforma��es do desenvolvedor\n\n");
	printf("\n\tNome: Josu� Borchardt Paiva\n\tIdade: 18 anos\n\tCursando o 2� semestre em Engenharia da Computa��o\n\n\n");
	system("pause");
}






