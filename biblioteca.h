

struct tabela{
	int posicao_atingida[8][8];
	int posicao_embarcacoes[8][8];
	int vida_embarcacoes[4];
	int pontuacao;
};

void preencher_tabela(struct tabela *ptab1, struct tabela *ptab2);

void imprimir_tabela(struct tabela *tab1, struct tabela *tab2);

void posicionar_embarcacoes(struct tabela *ptab);

int menu_principal();

int menu_secundario();

void atualizar_pontuacao(struct tabela *tab_atacada, struct tabela *tab_atacante, int linha, int coluna);

void disparar(struct tabela *ptabela, struct tabela *ptabela1);

void dica(struct tabela *tab, struct tabela *tab2);

void disparar_computador(struct tabela *ptabela, struct tabela *ptab);

void salvar(struct tabela *tab_jog, struct tabela *tab_comp, int *dicas);

int jogo_salvo(struct tabela *tab_jog, struct tabela *tab_comp, int *dicas);

void informacoes();
