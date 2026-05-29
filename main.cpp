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

    if (argc == 1) {
        /* Default */
        cout << "Impl. default\n";
    } else {
        /* Com alguma opção de linha de comando */
        string opcao = argv[1];

        if (opcao != "-a" && opcao != "-f" && opcao != "-o") {
            cerr << "[-] main(): Opção inválida, use -a, -f ou -o\n";

            return 1;
        }

        cout << "Impl. com " << opcao << "\n";
    }

    return 0;
}