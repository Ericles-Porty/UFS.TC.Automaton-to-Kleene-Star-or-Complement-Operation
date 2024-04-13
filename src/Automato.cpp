#include "../include/Automato.hpp"

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "../include/Estado.hpp"
#include "../include/Transicao.hpp"

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::to_string;

Automato::Automato() {}

void Automato::importaAutomato(string caminho) {
    ifstream leitorArquivo;
    leitorArquivo.open(caminho);

    if (!leitorArquivo.is_open()) {
        cout << "Erro ao abrir arquivo" << endl;
        exit(1);
    }

    string linha;
    while (getline(leitorArquivo, linha)) {
        // if the method find not found the string, it returns string::npos
        if (linha.find("<state ") != string::npos) {
            int inicioIdIndex = linha.find("id=\"") + 4;
            int fimIdIndex = linha.find("\"");
            int tamanhoId = fimIdIndex - inicioIdIndex;
            int id = stoi(linha.substr(inicioIdIndex, tamanhoId));

            int inicioNomeIndex = linha.find("name=\"") + 6;
            int fimNomeIndex = linha.find("\"", inicioNomeIndex);
            int tamanhoNome = fimNomeIndex - inicioNomeIndex;
            string nome = linha.substr(inicioNomeIndex, tamanhoNome);

            getline(leitorArquivo, linha);

            int inicioXIndex = linha.find("<x>") + 3;
            int fimXIndex = linha.find("</x>");
            int tamanhoX = fimXIndex - inicioXIndex;
            int x = stoi(linha.substr(inicioXIndex, tamanhoX));

            getline(leitorArquivo, linha);

            int inicioYIndex = linha.find("<y>") + 3;
            int fimYIndex = linha.find("</y>");
            int tamanhoY = fimYIndex - inicioYIndex;
            int y = stoi(linha.substr(inicioYIndex, tamanhoY));

            getline(leitorArquivo, linha);

            bool isInicial = false;
            bool isFinal = false;

            while (linha.find("</state>") == string::npos) {
                if (linha.find("<initial/>") != string::npos)
                    isInicial = true;
                else if (linha.find("<final/>") != string::npos)
                    isFinal = true;

                getline(leitorArquivo, linha);
            }

            Estado novoEstado = Estado(id, nome, x, y, isInicial, isFinal);
            this->estados.push_back(novoEstado);

        } else if (linha.find("<transition>") != string::npos) {
            getline(leitorArquivo, linha);

            int inicioFromIndex = linha.find("<from>") + 6;
            int fimFromIndex = linha.find("</from>", inicioFromIndex);
            int tamanhoFrom = fimFromIndex - inicioFromIndex;
            int from = stoi(linha.substr(inicioFromIndex, tamanhoFrom));

            getline(leitorArquivo, linha);

            int inicioToIndex = linha.find("<to>") + 4;
            int fimToIndex = linha.find("</to>", inicioToIndex);
            int tamanhoTo = fimToIndex - inicioToIndex;
            int to = stoi(linha.substr(inicioToIndex, tamanhoTo));

            getline(leitorArquivo, linha);

            string read = "";

            if (linha.find("<read>") != string::npos) {
                int inicioReadIndex = linha.find("<read>") + 6;
                int fimReadIndex = linha.find("</read>", inicioReadIndex);
                int tamanhoRead = fimReadIndex - inicioReadIndex;
                read = linha.substr(inicioReadIndex, tamanhoRead);
            }

            Transicao novaTransicao = Transicao(from, to, read);
            this->transicoes.push_back(novaTransicao);
        }
    }
}

void Automato::exportaAutomato(string caminho) {
    ofstream escritorArquivo;
    escritorArquivo.open(caminho);

    if (!escritorArquivo.is_open()) {
        cout << "Erro ao abrir arquivo" << endl;
        exit(1);
    }

    escritorArquivo << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
    escritorArquivo << "<structure>\n";
    escritorArquivo << "\t<type>fa</type>\n";
    escritorArquivo << "\t<automaton>\n";

    for (Estado& e : this->estados) {
        escritorArquivo << "\t\t<state id=\"" << e.id << "\" name=\"" << e.nome << "\">\n";
        escritorArquivo << "\t\t\t<x>" << e.x << "</x>\n";
        escritorArquivo << "\t\t\t<y>" << e.y << "</y>\n";
        if (e.isInicial) {
            escritorArquivo << "\t\t\t<initial/>\n";
        }
        if (e.isFinal) {
            escritorArquivo << "\t\t\t<final/>\n";
        }
        escritorArquivo << "\t\t</state>\n";
    }

    for (Transicao& t : this->transicoes) {
        escritorArquivo << "\t\t<transition>\n";
        escritorArquivo << "\t\t\t<from>" << t.from << "</from>\n";
        escritorArquivo << "\t\t\t<to>" << t.to << "</to>\n";

        if (t.read == "")
            escritorArquivo << "\t\t\t<read/>\n";
        else
            escritorArquivo << "\t\t\t<read>" << t.read << "</read>\n";

        escritorArquivo << "\t\t</transition>\n";
    }

    escritorArquivo << "\t</automaton>\n";
    escritorArquivo << "</structure>\n";
}

Automato* Automato::complemento() {
    Automato* novoAutomato = new Automato();

    for (Estado& e : this->estados) {
        novoAutomato->estados.push_back(e);
    }

    for (Transicao& t : this->transicoes) {
        novoAutomato->transicoes.push_back(t);
    }

    for (Estado& e : novoAutomato->estados) {
        e.isFinal = !e.isFinal;
    }

    return novoAutomato;
}

Automato* Automato::estrela() {
    Automato* novoAutomato = new Automato();

    // Cria um novo estado inicial e final
    int id = this->estados.size();
    string nome = "q" + to_string(id);
    Estado novoEstadoInicial = Estado(id, nome, -100, 100, true, true);

    Estado antigoEstadoInicial;

    for (Estado e : estados) {
        if (e.isInicial) {
            antigoEstadoInicial = e;
            e.isInicial = false;
        }
        novoAutomato->estados.push_back(e);
    }

    for (Transicao t : transicoes) {
        novoAutomato->transicoes.push_back(t);
    }

    novoAutomato->estados.push_back(novoEstadoInicial);

    for (Estado e : novoAutomato->estados) {
        if (e.isFinal) {
            Transicao novaTransicao = Transicao(e.id, antigoEstadoInicial.id, "");
            novoAutomato->transicoes.push_back(novaTransicao);
        }
    }

    Transicao novaTransicao = Transicao(novoEstadoInicial.id, antigoEstadoInicial.id, "");

    novoAutomato->transicoes.push_back(novaTransicao);

    return novoAutomato;
}