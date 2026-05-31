#include <iostream>
#include <string>
#include "abey.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    int p, c;

    /* # de produtos e # de ofertas respectivamente */
    cin >> p;
    cin >> c;

    Leilao leilao = abey_cria_leilao(p, c);

    if (leilao.size() == 0)
        return 1;

    /* Default */
    int ganho_max = 0;
    vector<int> solucao(p, -1);
    vector<int> melhor_solucao(p, -1);
    vector<bool> selecionados(c + 1, false);

    if (argc == 1) {
        abey_bnb_max_ganho(leilao, 0, p, c, abey_bound_upgrade, solucao, ganho_max, melhor_solucao, 0, selecionados);

    } else {
        /* Com alguma opção de linha de comando */
        string opcao = argv[1];
        int (*bound)(const Leilao&, const Leilao&) = &abey_bound_upgrade;
        bool flag_viabilidade = 0;
        bool flag_otimalidade = 0;

        cout << "Impl. com " << opcao << "\n";
        if (opcao == "-a"){
            /* Backtracking com função de bound dada pelo professor */
            bound = &abey_bound_prof;
        }
        else if (opcao == "-f"){
            /* Desliga os cortes de viabilidade */
            flag_viabilidade = 1;
        }
        else if (opcao == "-o"){
            /* Desliga os cortes de otimalidade */
            flag_otimalidade = 1;
        }
        else {
            cerr << "[-] main(): Opção inválida, use -a, -f ou -o\n";

            return 1;
        }

        abey_bnb_max_ganho(leilao, 0, p, c, *bound, solucao, ganho_max, melhor_solucao, 0, selecionados, flag_viabilidade, flag_otimalidade);
    }

    for (int i = 0; i < p; i++)
        cout << i + 1 << " " << melhor_solucao[i] << "\n";

    cout << ganho_max << "\n";

    return 0;
}