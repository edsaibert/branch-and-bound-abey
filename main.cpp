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

    /* Inicialização com defaults*/
    Otimo otimo(p);
    Atual atual(p, c);
    Flags flags;

    /* abey_bound_upgrade() por padrão */
    int (*bound)(const Leilao&, const Leilao&) = &abey_bound_upgrade;

    if (argc == 1) {
        /* Branch-and-Bound com função de bound feita pelos alunos */
        abey_bnb_max_ganho(leilao, 0, p, *bound, otimo, atual, flags);
    } else {
        /* Passa pelas opções de linha de comando e ativa as flags necessárias */
        for (int i = 1; i < argc; i++) {
            string opcao = argv[i];

            if (opcao == "-a") {
                bound = &abey_bound_prof;
            } else if (opcao == "-f") {
                flags.flag_viabilidade = false;
            } else if (opcao == "-o") {
                flags.flag_otimalidade = false;
            } else {
                cerr << "[-] main(): Opção inválida\n";

                return 1;
            }
        }

        abey_bnb_max_ganho(leilao, 0, p, *bound, otimo, atual, flags);
    }

    cout << "\n";

    for (int i = 0; i < p; i++)
        cout << i + 1 << " " << otimo.solucao[i] << "\n";

    cout << otimo.ganho << "\n";

    return 0;
}