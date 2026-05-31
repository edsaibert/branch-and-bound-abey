#include <iostream>
#include <iterator>
#include "abey.hpp"

using namespace std;

/* Cria um conjunto de ofertas (devolve conjunto vazio caso ocorra erro) */
ConjuntoOfertas abey_cria_ofertas(int qtd_ofertas) {
    if (qtd_ofertas <= 0) {
        cerr << "[-] abey_cria_ofertas(): Qtd. inválida de ofertas\n";

        return {};
    }

    ConjuntoOfertas ofertas;

    for (int i = 0; i < qtd_ofertas; i++) {
        int valor;
        cin >> valor;

        ofertas.insert({valor, i + 1});
    }

    return ofertas;
}

Leilao abey_cria_leilao(int p, int c) {
    if (p <= 0 || c <= 0) {
        cerr << "[-] abey_cria_leilao(): Dimensões de leilão inválidas\n";

        return {};
    }

    Leilao leilao;

    for (int i = 0; i < p; i++) {
        ConjuntoOfertas ofertas = abey_cria_ofertas(c);

        if (ofertas.size() == 0)
            return {};
        
        leilao.push_back(ofertas);
    }

    return leilao; 
}

int abey_bound_prof(const Leilao& arremts, const Leilao& prods_pend) {
    int soma_arremts = 0;
    int max_prods_pend = 0;
    int tam_prods_pend = prods_pend.size();

    for (const ConjuntoOfertas& conj_ofertas : arremts) {
        for (const Oferta& oferta : conj_ofertas)
            soma_arremts += oferta.first;
    }

    for (const ConjuntoOfertas& ofertas : prods_pend) {
        for (const Oferta& oferta : ofertas)
            max_prods_pend = max(max_prods_pend, oferta.first);
    }

    return soma_arremts + tam_prods_pend * max_prods_pend;
}

int abey_bound_upgrade(const Leilao& arremts, const Leilao& prods_pend) {
    int soma_arremts = 0;
    int soma_otimos = 0;

    for (const ConjuntoOfertas& ofertas : arremts) {
        for (const Oferta& oferta : ofertas)
            soma_arremts += oferta.first;
    }

    for (const ConjuntoOfertas& ofertas : prods_pend)
        /* Pega a última oferta de cada conj. de ofertas (maior oferta) e acumula */
        /* MINDSET GULOSO?!?! */
        soma_otimos += ofertas.rbegin()->first;

    return soma_arremts + soma_otimos;
}

void abey_bnb_max_ganho(
    const Leilao &leilao,
    int l,
    int p,
    int c,
    int (&bound)(const Leilao&, const Leilao&),
    vector<int>& solucao,
    int& ganho_otimo,
    vector<int>& melhor_solucao,
    int curP,
    vector<bool>& selecionados,
    bool flag_viabilidade,
    bool flag_otimalidade
) {
    if (l == p) {
        if (curP > ganho_otimo) {
            ganho_otimo = curP;
            melhor_solucao = solucao;
        }

        /* Fim da árvore */
        return;
    }

    /* Pega leilões de arrematados e pendentes para função de bound */
    Leilao arremts(leilao.begin(), leilao.begin() + l);
    Leilao pends(leilao.begin() + l, leilao.end());

    int B = bound(arremts, pends);
    
    /* Para cada oferta para o l-ésimo produto, em ordem decrescente (como é um set, as maiores ofertas estão no final) */
    for (auto iter = leilao[l].rbegin(); iter != leilao[l].rend(); iter++) {
        Oferta oferta = *iter;

        /* Corte p/ otimalidade */
        if (B <= ganho_otimo)
            return;

        /* Corte p/ viabilidade */
        if (!flag_viabilidade && selecionados[oferta.second])
            continue;

        /* Clientes sem interesse não são viáveis */
        if (!flag_otimalidade && oferta.first == 0)
            continue;

        solucao[l] = oferta.second;
        selecionados[oferta.second] = true;

        abey_bnb_max_ganho(leilao, l + 1, p, c, bound, solucao, ganho_otimo, melhor_solucao, curP + oferta.first, selecionados, flag_viabilidade, flag_otimalidade);
        
        /* backtrack */
        selecionados[oferta.second] = false;
    }
}