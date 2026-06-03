#include <iostream>
#include <iterator>
#include "abey.hpp"

/* Cria um conjunto de ofertas (devolve conjunto vazio caso ocorra erro) */
ConjuntoOfertas abey_cria_ofertas(const int qtd_ofertas) {
    if (qtd_ofertas <= 0) {
        std::cerr << "[-] abey_cria_ofertas(): Qtd. inválida de ofertas\n";

        return {};
    }

    ConjuntoOfertas ofertas;

    for (int i = 0; i < qtd_ofertas; i++) {
        int valor;
        std::cin >> valor;

        ofertas.insert({valor, i + 1});
    }

    return ofertas;
}

Leilao abey_cria_leilao(const int p, const int c) {
    if (p <= 0 || c <= 0) {
        std::cerr << "[-] abey_cria_leilao(): Dimensões de leilão inválidas\n";

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

int abey_bound_prof(const Leilao& prods_pend, const int ganho_acumulado, const std::vector<bool>& selecionados) {
    int max_prods_pend = 0;
    int tam_prods_pend = prods_pend.size();

    /* 
    *   Soma de produtos arrematados + oferta máxima para produtos pendentes para cliente disponível * qtd. de produtos pendentes 
    *
    *   LaTeX => B(A, P, C) = \sum_{(i, j) \in A} o_{i, j} + |P| \max\{o_{i, j} : i \in P, j \in C\}
    */
    for (const ConjuntoOfertas& ofertas : prods_pend) {
        for (const Oferta& oferta : ofertas) {
            if (!selecionados[oferta.second])
                max_prods_pend = std::max(max_prods_pend, oferta.first);
        }
    }

    return ganho_acumulado + (max_prods_pend * tam_prods_pend);
}

int abey_bound_upgrade(const Leilao& prods_pend, const int ganho_acumulado, const std::vector<bool>& selecionados) {
    int soma_maximos = 0;
        
    /* 
    *   Para cada produto pendente com oferta máxima de cliente que não foi selecionado,
    *   acumula com a soma das ofertas para produtos já arrematados
    *   
    *   LaTeX => B(A, P, C) = \sum_{(i, j) \in A} o_{i, j} + \sum_{i = k}^{p} o_{i, c}, c = \max\{x : x \in C\}, k \in P}
    */
    for (const ConjuntoOfertas& ofertas : prods_pend) {
        int max_disponivel = 0;

        for (const Oferta& oferta : ofertas) {
            if (!selecionados[oferta.second])
                max_disponivel = std::max(max_disponivel, oferta.first);
        }

        soma_maximos += max_disponivel;
    }

    return ganho_acumulado + soma_maximos;
}

void abey_bnb_max_ganho(
    const Leilao &leilao,
    const int l,
    const int p,
    int (&bound)(const Leilao&, const int, const std::vector<bool>&),
    Otimo& otimo,
    Atual& atual,
    Monitor& monitor,
    Flags flags
) {
    monitor.num_nodos++;

    if (l == p) {
        if (atual.ganho_acumulado > otimo.ganho) {
            otimo.ganho = atual.ganho_acumulado;
            otimo.solucao = atual.solucao;
        }

        /* Fim da árvore */
        return;
    }
    
    /* Pega leilões de produtos pendentes para função de bound */
    Leilao pends(leilao.begin() + l, leilao.end());

    int B = bound(pends, atual.ganho_acumulado, atual.selecionados);
    
    /* Para cada oferta para o l-ésimo produto, em ordem decrescente (ótimo cresce mais rápido e cortes acontecem mais cedo) */
    for (auto iter = leilao[l].rbegin(); iter != leilao[l].rend(); iter++) {
        Oferta oferta = *iter;

        /* Corte p/ otimalidade */
        if (flags.flag_otimalidade && B <= otimo.ganho){
            monitor.num_nodos_podados++;

            return;
        }

        /* Corte p/ viabilidade */
        if (
            flags.flag_viabilidade 
            && 
            (atual.selecionados[oferta.second] || oferta.first == 0)
        )
            continue;

        atual.solucao[l] = oferta.second;
        atual.selecionados[oferta.second] = true;
        atual.ganho_acumulado += oferta.first;

        abey_bnb_max_ganho(leilao, l + 1, p, bound, otimo, atual, monitor, flags);
        
        /* Backtracking desfazendo decisão atual */
        atual.ganho_acumulado -= oferta.first;
        atual.selecionados[oferta.second] = false;
    }

    /* Produto s/ cliente associado (índice de cliente -1) */
    atual.solucao[l] = -1;  
    abey_bnb_max_ganho(leilao, l + 1, p, bound, otimo, atual, monitor, flags);
}