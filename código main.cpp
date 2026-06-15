#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool analiseLexica(string entrada) {
    string permitidos = "fori=0;()<+{}0123456789";

    for (char c : entrada) {
        if (permitidos.find(c) == string::npos) {
            return false;
        }
    }

    return true;
}

bool analiseSintatica(string entrada, int &limite) {
    string inicio = "for(i=0;i<";
    string fim = ";i++){}";

    if (entrada.size() <= inicio.size() + fim.size()) {
        return false;
    }

    if (entrada.substr(0, inicio.size()) != inicio) {
        return false;
    }

    if (entrada.substr(entrada.size() - fim.size()) != fim) {
        return false;
    }

    string numero = entrada.substr(
        inicio.size(),
        entrada.size() - inicio.size() - fim.size()
    );

    if (numero.empty()) {
        return false;
    }

    for (char c : numero) {
        if (!isdigit(c)) {
            return false;
        }
    }

    limite = stoi(numero);

    if (limite < 0 || limite > 255) {
        return false;
    }

    return true;
}

void gerarAssembly(int limite) {
    cout << "\nCodigo Assembly produzido:\n\n";

    cout << "LDI R16,0\n";
    cout << "LDI R17," << limite << "\n\n";

    cout << "LOOP:\n";
    cout << "CP R16,R17\n";
    cout << "BRGE FIM\n\n";

    cout << "INC R16\n";
    cout << "RJMP LOOP\n\n";

    cout << "FIM:\n";
    cout << "NOP\n";
}

int main() {
    string entrada;
    int limite = 0;

    cout << "Digite a estrutura:\n";
    getline(cin, entrada);

    if (!analiseLexica(entrada)) {
        cout << "Erro lexico: caractere invalido encontrado.\n";
        return 0;
    }

    cout << "Analise lexica: estrutura valida.\n";

    if (!analiseSintatica(entrada, limite)) {
        cout << "Erro sintatico: estrutura invalida.\n";
        return 0;
    }

    cout << "Analise sintatica: estrutura valida.\n";

    gerarAssembly(limite);

    return 0;
}
