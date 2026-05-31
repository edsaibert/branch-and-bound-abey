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

    /* Inicialização com defaults */
    Otimo otimo(p);
    Atual atual(p, c);
    Flags flags;
    Monitor monitor;
    int (*bound)(const Leilao&, const int, const std::vector<bool>&) = &abey_bound_upgrade;

    if (argc == 1) {
        /* Default: Backtracking com função de bound proposta pelos alunos */
        auto start = std::chrono::high_resolution_clock::now();

        abey_bnb_max_ganho(leilao, 0, p, *bound, otimo, atual, monitor, flags);

        auto end = std::chrono::high_resolution_clock::now();
        monitor.tempo_execucao = end - start;
    } else {
        /* Com alguma opção de linha de comando */

        for (int i = 1; i < argc; i++) {
            string opcao = argv[i];

            if (opcao == "-a") {
                bound = &abey_bound_prof;
            } else if (opcao == "-f") {
                flags.flag_viabilidade = false;
            } else if (opcao == "-o") {
                flags.flag_otimalidade = false;
            } else {
                cerr << "[-] main(): Opção inválida, use uma combinação de -a, -f ou -o\n";

                return 1;
            }
        }

        auto start = std::chrono::high_resolution_clock::now();

        abey_bnb_max_ganho(leilao, 0, p, *bound, otimo, atual, monitor, flags);

        auto end = std::chrono::high_resolution_clock::now();
        monitor.tempo_execucao = end - start;
    }

    cout << "\n";

    for (int i = 0; i < p; i++)
        cout << i + 1 << " " << otimo.solucao[i] << "\n";

    cout << otimo.ganho << "\n";

    /* Relatório em stderr */
    cerr << "Duração: " << monitor.tempo_execucao.count() << "ms\n";
    cerr << "Número de nodos: " << monitor.num_nodos << "\n";
    cerr << "Número de nodos podados: " << monitor.num_nodos_podados << "\n";

    return 0;
}