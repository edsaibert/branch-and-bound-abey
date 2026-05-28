#include <iostream>
#include "abey.hpp"

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

    /* Teste */
    for (const auto &ofertas : leilao) {
        for (const auto &oferta : ofertas)
            cout << oferta << " ";

        cout << "\n";
    }

    return leilao; 
}