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

/* Struct para variáveis da solução ótima encontrada */
struct Otimo {
    int ganho = 0;
    std::vector<int> solucao;
    
    Otimo(int p) : solucao(p, -1) {}
};

/* Struct para variáveis da solução atual */
struct Atual {
    std::vector<int> solucao;
    std::vector<bool> selecionados;
    int ganho_acumulado = 0;
    
    Atual(int p, int c) : solucao(p, -1), selecionados(c + 1, false) {}
};

/* 
*   Struct para bandeiras de controle
*
*   Flags de viabilidade e otimalidade ligadas por padrão
*/
struct Flags {
    bool flag_viabilidade = true;
    bool flag_otimalidade = true;
};

/* 
*   Cria um leilão com 'p' produtos e 'c' ofertas (1 p/ cliente)
*
*   Entrada: Número de produtos e número de ofertas
*
*   Saída: Um leilão de dimensões p X c ou um leilão vazio caso alguma dimensão for inválida
*/
Leilao abey_cria_leilao(const int p, const int c);

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
*   Entrada: Leilão, nível da recursão, número de produtos, número de clientes,
*   ptr. para função de bound, struct com solução ótima, struct com solução atual,
*   e struct com flags de controle
*/
void abey_bnb_max_ganho(
    const Leilao &leilao,
    const int l,
    const int p,
    int (&bound)(const Leilao&, const Leilao&),
    Otimo& otimo,
    Atual& atual,
    Flags flags
);

#endif // __LEILAO__