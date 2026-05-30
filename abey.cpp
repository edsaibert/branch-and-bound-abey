#include <iostream>
#include <iterator>
#include "abey.hpp"

using namespace std;

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

    /* Teste */
    for (const ConjuntoOfertas& conj_ofertas : leilao) {
        for (const Oferta& oferta : conj_ofertas)
            cout << "valor: " << oferta.first << "; índice: " << oferta.second << "\n";

        cout << "\n";
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

bool abey_busca_cliente(vector<int>& solucao, int l, int idx_cliente) {
    for (int i = 0; i < l; i++) {
        if (solucao[i] == idx_cliente)
            return true;
    }

    return false;
}

void abey_bnb_max_ganho(
    const Leilao &leilao,
    int l,
    int p,
    int (&bound)(const Leilao&, const Leilao&),
    vector<int>& solucao,
    int& ganho_otimo
) {
    if (l == p) {
        int ganho_atual = 0;

        /* Calcula ganho total até então */
        for (int i = 0 ; i < p; i++) {
            for (const Oferta& oferta : leilao[i]) {
                if (oferta.second == solucao[i]) {
                    ganho_atual += oferta.first;

                    break;
                }
            }
        }

        ganho_otimo = max(ganho_otimo, ganho_atual);

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
        if (abey_busca_cliente(solucao, l, oferta.second))
            continue;

        /* Cliente arrematou e faz parte da solução atual */
        solucao[l] = oferta.second;
        abey_bnb_max_ganho(leilao, l + 1, p, bound, solucao, ganho_otimo);
        solucao[l] = -1;
    }
}