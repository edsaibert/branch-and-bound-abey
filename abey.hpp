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

Ofertas abey_cria_ofertas(int qtd_ofertas);

void abey_bnb_max_ganho(Leilao leilao, int l, int (*bound)(Leilao, Leilao), vector<int>& res);

int abey_bound_prof(Leilao arremts, Leilao prods_pend);

/* Sugestão: \sum_{(i, j) \in A} o_{i, j} + \sum_{i = 1}^{p} o_{i, c} (soma dos arrematados com a soma dos maiores lances por linha) */
int abey_bound_upgrade(Leilao arremts, Leilao prods_pend);

#endif // __LEILAO__