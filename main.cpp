#include <iostream>
#include <string>
#include "abey.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        /* Default */
        cout << "Impl. default" << endl;
    } else {
        /* Com alguma opção de linha de comando */
        string opcao = argv[1];

        if (opcao != "-a" && opcao != "-f" && opcao != "-o") {
            cerr << "[-] main(): Opção inválida, use -a, -f ou -o" << endl;

            return 1;
        }

        cout << "Impl. com " << opcao << endl;
    }

    return 0;
}