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
*   Saída: Um leilão de dimensões p X c. Devolve uma exceção se alguma dimensão for inválida
*/
Leilao abey_cria_leilao(int p, int c);

int abey_func_lim_prof();

int abey_func_lim_upgrade();

#endif // __LEILAO__