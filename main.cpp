#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;
using std::to_string;

ifstream entrada;
ofstream saida;

const string arquivo = "automato.jff";
const string arquivoComplemento = "automatoComplementado.jff";
const string arquivoEstrela = "automatoEstrelado.jff";
const string isFinal = "\t\t\t<final/>";
const string isInicial = "\t\t\t<initial/>";
const string openState = "\t\t<state id=\"";
const string closeState = "\t\t</state>&#";
int quantLinhasClone;



typedef struct
{
    int idEstado;
    string nomeEstado;
    bool acceptFinal = false;
} estados;
typedef estados *Estados;

void error();
int contaLinhas();
int contaFinais();
int contaElementos();
int achaInicial();
int guardaFinais();
void mineraElementos();
string clonandoArquivo();
void caseMenu();
int printaMenu();


void error()
{
    cout << "Ocorreu um erro ao abrir ou fechar o arquivo, perdao pela inconveniencia." << endl;
    exit(1);
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
            if (linha.substr(0, 13) == openState)
            {
                quantElementos++;
            }
        }
        entrada.close();
        return quantElementos;
    }
    error();
}

int achaInicial()
{

    string linha;
    int posicaoElemento = 0;
    entrada.open(arquivo);
    if (entrada.is_open())
    {
        while (getline(entrada, linha))
        {
            if (openState == linha.substr(0, 13))
            {
                while (getline(entrada, linha))
                {
                    if (linha.substr(0, 12) == closeState)
                        break;
                    if (linha.substr(0, 13) == isInicial)
                    {
                        entrada.close();
                        return posicaoElemento;
                    }
                    posicaoElemento++;
                }
            }
        }
        entrada.close();
        return -1;
    }
    error();
    
}

int guardaFinais(int *finais, estados *elem)
{

    string linha;
    int contador = 0;
    int posicaoElemento = 0;
    entrada.open(arquivo);
    if (entrada.is_open())
    {
        while (getline(entrada, linha))
        {
            if (openState == linha.substr(0, 13))
            {
                while (getline(entrada, linha))
                {
                    if (linha.substr(0, 13) == closeState)
                        break;
                    if (linha.substr(0, 11) == isFinal)
                    {
                        finais[contador] = posicaoElemento;
                        elem[posicaoElemento].acceptFinal = true;
                        contador++;
                    }
                    if (linha.substr(0, 13) == openState)
                        posicaoElemento++;
                }
            }
        }
        entrada.close();
        return *finais;
    }
    error();
}

void mineraElementos(estados *elem)
{
    string linha;
    int indice = 0;
    entrada.open(arquivo);
    if (entrada.is_open())
    {
        while (getline(entrada, linha))
        {
            if (linha.substr(0, 13) == openState)
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
}

string clonandoArquivo(string *clone)
{
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
}


void caseMenu(string *clone, int quantLinhas, int quantElementos, int quantFinais, int posicaoDoInicial, int *elementosFinais, estados *elem)
{
    int op;
    int travaC = 0;
    int travaE = 0;
    system("CLS");
    do
    {

        op = printaMenu();
        switch (op)
        {
        case 3:
            system("CLS");
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
       
        default:
            system("CLS");
            cout << "Voce nao digitou uma opcao valida" << endl;
            break;
        }

    } while (op != 0);
}

int printaMenu()
{
    int op;
    cout << endl
        << "---------------------------------" << endl
        << "Selecione uma operacao: " << endl
        << "3 - Informacoes do automato original " << endl
        << "---------------------------------" << endl
         << endl;
    cin >> op;
    return op;
}

int main()
{
    system("color 2"); //Deixa a cor das linhas verde
    int quantLinhas = contaLinhas();
    int quantElementos = contaElementos();
    int posicaoDoInicial = achaInicial();
    int quantFinais = contaFinais();
    int *elementosFinais = (int *)malloc(quantFinais * sizeof(int));
    Estados elem;
    elem = new estados[quantElementos];
    mineraElementos(elem);
    *elementosFinais = guardaFinais(elementosFinais, elem);
    string clone[2000];
    quantLinhasClone = contaLinhas();
    caseMenu(clone, quantLinhas, quantElementos, quantFinais, posicaoDoInicial, elementosFinais, elem);

    return 0;
}
