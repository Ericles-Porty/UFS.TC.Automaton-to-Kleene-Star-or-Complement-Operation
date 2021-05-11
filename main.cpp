#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

const string arquivo = "automato.jff";
const string arquivoComplemento = "automatoComplementado.jff";
const string isFinal = "\t\t\t<final/>";
const string isInicial = "\t\t\t<initial/>";
const string compStringId = "\t\t<state id=\"";
const string fecha = "\t\t</state>&#";
int quantLinhasClone;

ifstream entrada;
ofstream saida;

typedef struct 
{
    int idEstado;
    string nomeEstado;
    bool acceptFinal = false;
} estados;
typedef estados* Estados;

int contaLinhas();
int contaFinais();
int contaElementos();
int achaInicial();
int guardaFinais();
void mineraElementos();
string clonandoArquivo();
void complemento();
void caseMenu();
int printaMenu();

void error()
{
    cout << "Ocorreu um erro ao abrir o arquivo, perdao pela inconveniencia." << endl;
}

int contaLinhas()
{
    string linha;
    int quantLinhas = 0;
    entrada.open(arquivo);
    if (entrada.is_open())
    {
        while (getline(entrada, linha))
        {
            quantLinhas++;
        }
        entrada.close();
        return quantLinhas;
    }
    error();
    exit(1);
}

int contaFinais()
{
    string linha;
    int quantFinais = 0;
    entrada.open(arquivo);
    if (entrada.is_open())
    {
        while (getline(entrada, linha))
        {
            if (isFinal == linha.substr(0, 11))
            {
                quantFinais++;
            }
        }
        entrada.close();
        return quantFinais;
    }
    return 0;
    error();
    exit(1);
}

int contaElementos()
{
    string linha;
    int quantElementos = 0;
    entrada.open(arquivo);
    if (entrada.is_open())
    {
        while (getline(entrada, linha))
        {
            if (linha.substr(0, 13) == compStringId)
            {
                quantElementos++;
            }
        }
        entrada.close();
        return quantElementos;
    }
    error();
    exit(1);
}

int achaInicial()
{

    string linha;
    string subStringTempId;
    int posicaoElemento = 0;
    entrada.open(arquivo);
    if (entrada.is_open())
    {
        while (getline(entrada, linha))
        {
            subStringTempId = linha.substr(0, 13);
            if (compStringId == subStringTempId)
            {
                while (getline(entrada, linha))
                {
                    subStringTempId = linha.substr(0, 13);
                    if (subStringTempId == fecha)
                        break;
                    if (subStringTempId == isInicial)
                    {
                        entrada.close();
                        return posicaoElemento;
                    }
                    if (subStringTempId == compStringId)
                        posicaoElemento++;
                }
            }
        }
        entrada.close();
        return -1;
    }
    error();
    exit(1);
}

int guardaFinais(int *finais, estados *elem)
{

    string linha;
    string subStringTempId;
    int contador = 0;
    int posicaoElemento = 0;
    entrada.open(arquivo);
    if (entrada.is_open())
    {
        while (getline(entrada, linha))
        {
            if (compStringId == linha.substr(0, 13))
            {
                while (getline(entrada, linha))
                {
                    if (linha.substr(0, 13) == fecha)
                        break;
                    if (linha.substr(0, 11) == isFinal)
                    {
                        finais[contador] = posicaoElemento;
                        elem[posicaoElemento].acceptFinal = true;
                        contador++;
                    }
                    if (linha.substr(0, 13) == compStringId)
                        posicaoElemento++;
                }
            }
        }
        entrada.close();
        return *finais;
    }
    error();
    exit(1);
}

void mineraElementos(estados *elem)
{
    string subStringTempId;
    string linha;
    int indice = 0;
    entrada.open(arquivo);
    if (entrada.is_open())
    {
        while (getline(entrada, linha))
        {
            subStringTempId = linha.substr(0, 13);
            if (subStringTempId == compStringId)
            {
                int posicao1 = linha.find("name=\"") + 6;
                int posicao2 = linha.find("\">");
                int posicaoDiff = posicao2 - posicao1;
                elem[indice].idEstado = indice;
                elem[indice].nomeEstado = linha.substr(posicao1, posicaoDiff);
                indice++;
            }
        }
        entrada.close();
        return;
    }
    error();
    exit(1);
}

string clonandoArquivo(string *clone)
{
    string subStringTempId;
    string linha;
    int i = 0;
    entrada.open(arquivo);
    if (entrada.is_open())
    {
        while (getline(entrada, linha))
        {
            clone[i] = linha;
            i++;
        }
        entrada.close();
        return *clone;
    }
    error();
    exit(1);
}

void complemento(string *clone)
{
    int linha = 0;
    int trava = 0;
    string aux;
    string subStringTempId;
    while (linha < quantLinhasClone)
    {
        if (clone[linha].substr(0, 13) == compStringId)
        {
            if (clone[linha + 3].substr(0, 13) == isInicial && trava == 0)
            {
                if (clone[linha + 4].substr(0, 12) == fecha)
                {
                    int x = quantLinhasClone;
                    while (x > linha + 4)
                    {
                        clone[x] = clone[x - 1];
                        x--;
                    }
                    clone[linha + 4] = "\t\t\t<final/>&#13;";
                    quantLinhasClone++;
                }
                else if (clone[linha + 4].substr(0, 11) == isFinal)
                {
                    int x = linha;
                    while (quantLinhasClone > x)
                    {
                        clone[x + 4] = clone[x + 5];
                        x++;
                    }
                    quantLinhasClone--;
                }
                trava++;
            }
            else
            {
                if (clone[linha + 3].substr(0, 11) != isFinal)
                {
                    int x = quantLinhasClone;
                    while (x > linha + 3)
                    {
                        clone[x] = clone[x - 1];
                        x--;
                    }
                    clone[linha + 3] = "\t\t\t<final/>&#13;";
                    quantLinhasClone++;
                }
                else
                {
                    int x = linha;
                    while (quantLinhasClone > x)
                    {
                        clone[x + 3] = clone[x + 4];
                        x++;
                    }
                    quantLinhasClone--;
                }
            }
        }
        linha++;
    }
    return;
}

void estrela(string *clone, int posicaoDoInicial, int *elementosFinais, int quantFinais)
{
    int linha = 0;
    while (linha < quantLinhasClone)
    {

        if (clone[linha].substr(0, 18) == "\t\t\t<initial/>&#13;") //apaga antigo inicial
        {
            int x = linha;
            while (quantLinhasClone > x)
            {
                clone[x] = clone[x + 1];
                x++;
            }
            quantLinhasClone--;
        }
        if (clone[linha].substr(0, 38) == "\t\t<!--The list of transitions.-->&#13;") //insere o novo elemento no final da lista de elementos
        {
            int x = quantLinhasClone;
            while (x > linha + 2)
            {
                clone[x] = clone[x - 1];
                x--;
            }
            clone[linha] = "\t\t<state id=\"666\" name=\"AUX\">&#13;\n\t\t\t<x>-100.0</x>&#13;\n\t\t\t<y>100.0</y>&#13;\n\t\t\t<initial/>&#13;\n\t\t\t<final/>&#13;\n\t\t</state>&#13;\n\t\t<!--The list of transitions.-->&#13;";
            quantLinhasClone += 6;
        }
        if (clone[linha].substr(0, 18) == "\t</automaton>&#13;") //faz o novo elemento apontar pro antigo inicial
        {
            int x = quantLinhasClone;
            quantLinhasClone++;
            while (x > linha + 3)
            {
                clone[x] = clone[x - 1];
                x--;
            }
            clone[linha] = "\t\t<transition>&#13;\n\t\t\t<from>666</from>&#13;\n\t\t\t<to>";
            clone[linha] += to_string(posicaoDoInicial);
            clone[linha] += "</to>&#13;\n\t\t\t<read/>&#13;\n\t\t</transition>&#13;\n\t</automaton>&#13;";
            quantLinhasClone += 6;
        }
        if (clone[linha + 1].substr(0, 19) == "\t\t<transition>&#13;") //faz os finais apontarem pro inicial
        {
            for (int i = 0; i < quantFinais; i++)
            {
                clone[linha] += "\n\t\t<transition>&#13;\n\t\t\t<from>";
                clone[linha] += to_string(elementosFinais[i]);
                clone[linha] += "</from>&#13;\n\t\t\t<to>";
                clone[linha] += to_string(posicaoDoInicial);
                clone[linha] += "</to>&#13;\n\t\t\t<read/>&#13;\n\t\t</transition>&#13;";
            }
            quantLinhasClone += 5 * quantFinais;
        }
        linha++;
    }
    return;
}

void caseMenu(string *clone, int quantLinhas, int quantElementos, int quantFinais, int posicaoDoInicial, int *elementosFinais, estados *elem)
{
    int op;
    int trava = 0;
    do
    {
        op = printaMenu();
        switch (op)
        {
        case 0:
        delete [] elem;
            break;
        case 1:
            if (trava != 0)
                cout << "Voce ja realizou uma operacao, va ver o resultado." << endl;
            if (trava != 0)
                break;
            complemento(clone);
            saida.open(arquivoComplemento);
            if (saida.is_open())
            {
                for (int i = 0; i < quantLinhasClone; i++)
                {
                    saida << clone[i] << endl;
                }
                cout <<"Foi criado um automato com a operacao desejada."<<endl;
            }
            saida.close();
            trava++;
            break;
        case 2:
            if (trava != 0)
                cout << "Voce ja realizou uma operacao, va ver o resultado." << endl;
            if (trava != 0)
                break;
            estrela(clone, posicaoDoInicial, elementosFinais, quantFinais);
            saida.open(arquivoComplemento);
            if (saida.is_open())
            {
                for (int i = 0; i < quantLinhasClone; i++)
                {
                    saida << clone[i] << endl;
                }
                cout <<"Foi criado um automato com a operacao desejada."<<endl;
            }
            saida.close();
            trava++;
            break;
        case 3:
        {
            for (int i = 0; i < quantElementos; i++)
            {
                string aceita = (elem[i].acceptFinal == true) ? "Sim" : "Nao";
                cout << " ----------------" << i << "----------------" << endl
                     << "Id do elemento: " << elem[i].idEstado << endl
                     << "Nome do elemento: " << elem[i].nomeEstado << endl
                     << "Final? " << aceita << endl;
            }
            cout << "---------------------------------" << endl;
            if (posicaoDoInicial != -1)
                cout << "ID do elemento que esta o inicial: " << posicaoDoInicial << endl;
            cout << "Quantidade de finais: " << quantFinais << endl;
            cout << "Quantidade de linhas: " << quantLinhas << endl;
            cout << "Quantidade de elementos: " << quantElementos << endl;
            break;
        }

        default:
            cout << "Voce nao digitou uma opcao valida" << endl;
            break;
        }

    } while (op != 0);
}

int printaMenu()
{
    int op;
    cout << "---------------------------------" << endl;
    cout << "Selecione uma operacao: " << endl
         << "1 - Complemento" << endl
         << "2 - Estrela " << endl
         << "3 - Informacoes do automato original " << endl
         << "0 - Encerrar o programa" << endl;
    cout << "---------------------------------" << endl;
    cin >> op;
    return op;
}

int main()
{
    int quantLinhas = contaLinhas();
    int quantElementos = contaElementos();
    int posicaoDoInicial = achaInicial();
    int quantFinais = contaFinais();
    int *elementosFinais = (int *)malloc(quantFinais * sizeof(int));
    Estados elem; 
    elem = new estados[quantElementos];
    mineraElementos(elem);
    *elementosFinais = guardaFinais(elementosFinais, elem);
    string clone[1000];
    *clone = clonandoArquivo(clone);
    quantLinhasClone = contaLinhas();
    caseMenu(clone, quantLinhas, quantElementos, quantFinais, posicaoDoInicial, elementosFinais, elem);

    return 0;
}
