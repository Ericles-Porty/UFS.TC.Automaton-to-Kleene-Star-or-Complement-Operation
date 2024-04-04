#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "../include/Automato.hpp"
#include "../include/Estado.hpp"
#include "../include/Transicao.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::list;
using std::ofstream;
using std::string;
using std::to_string;

void menu(Automato* automato);
int printaMenu();

void executeBatchFile() {
    system("OpenOriginalAutomaton.bat");
}

int main() {
    system("color 2");  // Deixa a cor das linhas verde
    Automato automato;
    string caminho = "./resources/automato.jff";
    automato.importaAutomato(caminho);

    menu(&automato);

    return 0;
}

void menu(Automato* automato) {
    int op;
    bool flagEstrela = false;
    bool flagComplemento = false;

    system("CLS");
    do {
        op = printaMenu();
        Automato* novoAutomatoEstrela = automato->estrela();
        Automato* novoAutomatoComplemento = automato->complemento();

        switch (op) {
            case 0:
                cout << "Programa encerrado" << endl;
                break;
            case 1:
                system("CLS");

                if (flagComplemento) {
                    cout << "Voce ja realizou essa operacao." << endl;
                    break;
                }

                novoAutomatoComplemento->exportaAutomato("./resources/automatoComplemento.jff");

                cout << "Foi criado um automato com a operacao complemento." << endl;

                flagComplemento = true;

                break;
            case 2:
                system("CLS");

                if (flagEstrela) {
                    cout << "Voce ja realizou essa operacao." << endl;
                    break;
                }

                novoAutomatoEstrela->exportaAutomato("./resources/automatoEstrela.jff");

                cout << "Foi criado um automato com a operacao estrela." << endl;

                flagEstrela = true;

                break;
            case 3:
                system("CLS");

                cout << "Informacoes do automato original: " << endl;
                cout << "Quantidade de estados: " << automato->estados.size() << endl;
                cout << "Quantidade de transicoes: " << automato->transicoes.size() << endl;
                cout << endl;

                cout << "Estados: " << endl;

                for (Estado& estado : automato->estados) {
                    cout << "ID: " << estado.id << endl;
                    cout << "Nome: " << estado.nome << endl;
                    cout << "X: " << estado.x << endl;
                    cout << "Y: " << estado.y << endl;
                    cout << "Inicial: " << estado.isInicial << endl;
                    cout << "Final: " << estado.isFinal << endl;
                    cout << endl;
                }

                cout << "Transicoes: " << endl;

                for (Transicao& transicao : automato->transicoes) {
                    cout << "From: " << transicao.from << endl;
                    cout << "To: " << transicao.to << endl;
                    cout << "Read: " << transicao.read << endl;
                    cout << endl;
                }

                cout << endl;

                break;
            case 4:
                system("CLS");
                cout << "ATENCAO, VOCE SO PODERA VOLTAR A USAR COMANDOS APOS FECHAR O JFLAP!!!" << endl;
                system("OpenOriginalAutomaton.bat");
                system("CLS");
                break;
            case 5:
                system("CLS");
                if (!flagComplemento) {
                    cout << "Voce ainda nao modificou o arquivo para complemento" << endl;
                } else {
                    cout << "ATENCAO, VOCE SO PODERA VOLTAR A USAR COMANDOS APOS FECHAR O JFLAP!!!" << endl;
                    system("OpenComplementAutomaton.bat");
                    system("CLS");
                }
                break;
            case 6:
                system("CLS");
                if (!flagEstrela) {
                    cout << "Voce ainda nao modificou o arquivo para estrela" << endl;
                } else {
                    cout << "ATENCAO, VOCE SO PODERA VOLTAR A USAR COMANDOS APOS FECHAR O JFLAP!!!" << endl;
                    system("OpenKleeneStarAutomaton.bat");
                    system("CLS");
                }
                break;
            default:
                system("CLS");
                cout << "Voce nao digitou uma opcao valida" << endl;
                break;
        }

    } while (op != 0);
}

int printaMenu() {
    int op;
    cout << endl
         << "---------------------------------" << endl
         << "Selecione uma operacao: " << endl
         << "1 - Complemento" << endl
         << "2 - Estrela " << endl
         << "3 - Informacoes do automato original " << endl
         << "4 - Abrir o arquivo jFlap original " << endl
         << "5 - Abrir o arquivo jFlap complemento " << endl
         << "6 - Abrir o arquivo jFlap estrela " << endl
         << "0 - Encerrar o programa " << endl
         << "---------------------------------" << endl
         << endl;
    cin >> op;
    return op;
}
