#ifndef __LEILAO__
#define __LEILAO__

#include <vector>
#include <set>

/* Oferta da forma (i, j), onde i indexa um cliente e j representa o valor oferecido por ele */
typedef std::pair<int, int> Oferta;

/* Conjunto de ofertas */
typedef std::set<Oferta> ConjuntoOfertas;

/* Vetor de conjuntos de ofertas (leilão) */
typedef std::vector<ConjuntoOfertas> Leilao;

/* 
*   Cria um leilão com 'p' produtos e 'c' ofertas (1 p/ cliente)
*
*   Entrada: Número de produtos e número de ofertas
*
*   Saída: Um leilão de dimensões p X c ou um leilão vazio caso alguma dimensão for inválida
*/
Leilao abey_cria_leilao(int p, int c);

/*
*   Função limitante dada pelo professor: \sum_{(i, j) \in A} o_{i, j} + |P| \max\{o_{i, j} | i \in P, j \in C\}
*
*   Entrada: Leilão dos arremates já feitos e um leilão com os produtos pendentes
*
*   Saída: Limitante superior para a configuração de leilões de arrematados e pendentes atual
*/
int abey_bound_prof(const Leilao& arremts, const Leilao& prods_pend);

/*
*   Função limitante proposta pelos alunos: \sum_{(i, j) \in A} o_{i, j} + \sum_{i = k}^{p} o_{i, c}, tal que k \in P e c = \max\{x : x \in C\}
*   
*   Entrada: Leilão dos arremates já feitos e um leilão com os produtos pendentes
*
*   Saída: Limitante superior para a configuração de leilões de arrematados e pendentes atual
*/
int abey_bound_upgrade(const Leilao& arremts, const Leilao& prods_pend);

/*
*   Faz branch-and-bound no leilão para obter o ganho máximo
*
*   Entrada: Leilão, nível da recursão, número de produtos, 
*   ptr. para função de bound, vetor que guarda a solução atual e o ganho ótimo atual
*/
void abey_bnb_max_ganho(
    const Leilao &leilao,
    int l,
    int p,
    int (&bound)(const Leilao&, const Leilao&),
    std::vector<int>& solucao,
    int& ganho_otimo
);

#endif // __LEILAO__