#include <iostream>
#include "abey.hpp"

Leilao abey_cria_leilao(int p, int c) {
    if (p <= 0 || c <= 0) {
        cerr << "[-] abey_cria_leilao(): Dimensões de leilão inválidas\n";

        return {};
    }

    Leilao leilao;

    for (int i = 0; i < p; i++) {
        Ofertas ofertas;

        for (int j = 0; j < c; j++) {
            int oferta;
            cin >> oferta;

            ofertas.insert(oferta);
        }

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