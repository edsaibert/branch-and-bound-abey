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
    Monitor monitor;
    int (*bound)(const Leilao&, int, const std::vector<bool>&) = &abey_bound_upgrade;

    if (argc == 1) {
        /* Backtracking com função de bound proposta pelos alunos */
        auto start = std::chrono::high_resolution_clock::now();

        abey_bnb_max_ganho(leilao, 0, p, c, *bound, otimo, atual, monitor, flags);

        auto end = std::chrono::high_resolution_clock::now();
        monitor.tempo_execucao = end - start;

    } else {
        /* Com alguma opção de linha de comando */
        string opcao = argv[1];

        cout << "Impl. com " << opcao << "\n";
        if (opcao == "-a"){
            /* Backtracking com função de bound dada pelo professor */
            bound = &abey_bound_prof;
        }
        else if (opcao == "-f"){
            /* Desliga os cortes de viabilidade */
            flags.flag_viabilidade = 1;
        }
        else if (opcao == "-o"){
            /* Desliga os cortes de otimalidade */
            flags.flag_otimalidade = 1;
        }
        else {
            cerr << "[-] main(): Opção inválida, use -a, -f ou -o\n";

            return 1;
        }
        auto start = std::chrono::high_resolution_clock::now();

        abey_bnb_max_ganho(leilao, 0, p, c, *bound, otimo, atual, monitor, flags);

        auto end = std::chrono::high_resolution_clock::now();
        monitor.tempo_execucao = end - start;
    }

    /* Print */
    for (int i = 0; i < p; i++)
        cout << i + 1 << " " << otimo.solucao[i] << "\n";

    cout << otimo.ganho << "\n";

    /* Print stderr */
    cerr << "[+] Duração: " << monitor.tempo_execucao.count() << "ms\n";
    cerr << "[+] Número de nodos: " << monitor.num_nodos << "\n";
    cerr << "[+] Número de nodos podados: " << monitor.num_nodos_podados << "\n";

    return 0;
}