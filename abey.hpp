#ifndef __LEILAO__
#define __LEILAO__

#include <vector>
#include <set>

using namespace std;

/* Conjunto de ofertas */
typedef set<int> Ofertas;

/* Vetor de conjuntos de ofertas (leilão) */
typedef vector<Ofertas> Leilao;

/* 
*   Cria um leilão com 'p' produtos e 'c' ofertas (1 p/ cliente)
*
*   Entrada: Número de produtos e número de ofertas
*
*   Saída: Um leilão de dimensões p X c ou um leilão vazio caso alguma dimensão for inválida
*/
Leilao abey_cria_leilao(int p, int c);

/*
*   Cria um conjunto de ofertas
*   
*   Entrada: Quantidade de ofertas a serem inseridas no conjunto
*
*   Saída: Um conjunto de ofertas
*/
Ofertas abey_cria_ofertas(int qtd_ofertas);

/*
*   Função limitante dada pelo professor: \sum_{(i, j) \in A} o_{i, j} + |P| \max\{o_{i, j} | i \in P, j \in C\}
*
*   Entrada: Leilão dos arremates já feitos e um leilão com os produtos pendentes
*
*   Saída: Limitante superior para a configuração de leilões de arrematados e pendentes atual
*/
int abey_bound_prof(Leilao arremts, Leilao prods_pend);

/*
*   Função limitante proposta pelos alunos: \sum_{(i, j) \in A} o_{i, j} + \sum_{i = 1}^{p} o_{i, c}, onde c é o tam. de cada conj. de ofertas
*   
*   Entrada: Leilão dos arremates já feitos e um leilão com os produtos pendentes
*
*   Saída: Limitante superior para a configuração de leilões de arrematados e pendentes atual
*/
int abey_bound_upgrade(Leilao arremts, Leilao prods_pend);

void abey_bnb_max_ganho(Leilao leilao, int l, int (*bound)(Leilao, Leilao), vector<int>& solucao_otima, int& ganho_otimo);

#endif // __LEILAO__