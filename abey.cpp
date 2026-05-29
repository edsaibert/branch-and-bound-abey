#include <iostream>
#include <iterator>
#include "abey.hpp"

using namespace std;

Ofertas abey_cria_ofertas(int qtd_ofertas) {
    if (qtd_ofertas <= 0) {
        cerr << "[-] abey_cria_ofertas(): Qtd. inválida de ofertas\n";

        return {};
    }

    Ofertas ofertas;

    for (int j = 0; j < qtd_ofertas; j++) {
        int oferta;
        cin >> oferta;

        ofertas.insert(oferta);
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
        Ofertas ofertas = abey_cria_ofertas(c);

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

    for (const Ofertas& ofertas : arremts) {
        for (const int& oferta : ofertas)
            soma_arremts += oferta;
    }

    for (const Ofertas& ofertas : prods_pend) {
        for (const int& oferta : ofertas) {
            if (oferta > max_prods_pend)
                max_prods_pend = oferta;
        }
    }

    return soma_arremts + tam_prods_pend * max_prods_pend;
}

int abey_bound_upgrade(const Leilao& arremts, const Leilao& prods_pend) {
    int soma_arremts = 0;
    int soma_otimos = 0;

    for (const Ofertas& ofertas : arremts) {
        for (const int& oferta : ofertas)
            soma_arremts += oferta;
    }

    for (const Ofertas& ofertas : prods_pend)
        /* Pega o último de cada conj. de ofertas (maior oferta) e acumula */
        /* GULOSO?!?! */
        soma_otimos += *ofertas.rbegin();

    return soma_arremts + soma_otimos;
}