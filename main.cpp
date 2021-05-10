#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

const string arquivoComplemento = "automatoComplementado.jff";
const string arquivo = "automato.jff";
const string isFinal = "\t\t\t<final/>";
const string isInicial = "\t\t\t<initial/>";
const string compStringId = "\t\t<state id=\"";
const string fecha = "\t\t</state>&#";
int quantLinhasClone;

ifstream entrada;
ofstream saida;

typedef struct estados
{
    int idEstado;
    string nomeEstado;
    bool acceptFinal = false;
} Estados[20];

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
    cout << "Ocorreu um erro ao abrir o arquivo, perdao pela inconveniencia." << endl;
    exit(1);
}

int contaFinais()
{
    string linha;
    string subStringTempId;
    int quantFinais = 0;
    entrada.open(arquivo);
    if (entrada.is_open())
    {
        while (getline(entrada, linha))
        {
            subStringTempId = linha.substr(0, 11);
            if (isFinal == subStringTempId)
            {
                quantFinais++;
            }
        }
        entrada.close();
        return quantFinais;
    }
    return 0;
    cout << "Ocorreu um erro ao abrir o arquivo, perdao pela inconveniencia." << endl;
    exit(1);
}

int contaElementos()
{
    string subStringTempId;
    string linha;
    int quantElementos = 0;
    entrada.open(arquivo);
    if (entrada.is_open())
    {
        while (getline(entrada, linha))
        {
            subStringTempId = linha.substr(0, 13);
            if (subStringTempId == compStringId)
            {
                quantElementos++;
            }
        }
        entrada.close();
        return quantElementos;
    }
    cout << "Ocorreu um erro ao abrir o arquivo, perdao pela inconveniencia." << endl;
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
    cout << "Ocorreu um erro ao abrir o arquivo, perdao pela inconveniencia." << endl;
    exit(1);
}

int guardaFinais(int *finais, Estados *elem)
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
            subStringTempId = linha.substr(0, 13);
            if (compStringId == subStringTempId)
            {
                while (getline(entrada, linha))
                {
                    subStringTempId = linha.substr(0, 13);
                    if (subStringTempId == fecha)
                        break;
                    subStringTempId = linha.substr(0, 11);
                    if (subStringTempId == isFinal)
                    {
                        finais[contador] = posicaoElemento;
                        elem[posicaoElemento]->acceptFinal = true;
                        contador++;
                    }
                    subStringTempId = linha.substr(0, 13);
                    if (subStringTempId == compStringId)
                        posicaoElemento++;
                }
            }
        }
        entrada.close();
        return *finais;
    }
    cout << "Ocorreu um erro ao abrir o arquivo, perdao pela inconveniencia." << endl;
    exit(1);
}

void mineraElementos(Estados *elem)
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
                elem[indice]->idEstado = indice;
                elem[indice]->nomeEstado = linha.substr(posicao1, posicaoDiff);
                indice++;
            }
        }
        entrada.close();
        return;
    }
    cout << "Ocorreu um erro ao abrir o arquivo, perdao pela inconveniencia." << endl;
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
    cout << "Ocorreu um erro ao abrir o arquivo, perdao pela inconveniencia." << endl;
    exit(1);
}

void complemento(string *clone)
{
    int linha = 0;
    int indice = 0;
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
                    int x = quantLinhasClone ;
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
                    while (quantLinhasClone > x )
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
                    int x = quantLinhasClone ;
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
                    while (quantLinhasClone > x )
                    {
                        clone[x + 3] = clone[x + 4];
                        x++;
                    }
                    quantLinhasClone--;
                }
            }

            indice++;
        }
        linha++;
    }
    return;
}

void caseMenu(string *clone, int quantLinhas, int quantElementos, int quantFinais, int posicaoDoInicial,Estados *elem){
    int op;
    do
    {
        op = printaMenu();
        switch (op)
        {
        case 0:
            break;
        case 1:
            saida.open(arquivoComplemento);
            if(saida.is_open()){
                for (int i = 0; i < quantLinhasClone; i++){
                    saida << clone[i]<<endl;
                }
            }
            saida.close();
            break;
        case 2:
            cout << "Opcao ainda sera implementada" << endl;
            break;
        case 3:
        {
            for (int i = 0; i < quantElementos; i++)
            {
                string aceita = (elem[i]->acceptFinal == true) ? "Sim" : "Nao";
                cout << " ----------------" << i << "----------------" << endl
                     << "Id do elemento: " << elem[i]->idEstado << endl
                     << "Nome do elemento: " << elem[i]->nomeEstado << endl
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
    cout << "Selecione uma operacao: " << endl
         << "1 - Complemento" << endl
         << "2 - Estrela " << endl
         << "3 - Informacoes do automato" << endl
         << "0 - Encerrar o programa" << endl;
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
    Estados elem[20]; //tamanho do automato pra ser alocado dinamicamente no futuro
    mineraElementos(elem);
    *elementosFinais = guardaFinais(elementosFinais, elem);
    string clone[500];
    *clone = clonandoArquivo(clone);
    quantLinhasClone = contaLinhas();
    complemento(clone);
    caseMenu(clone,quantLinhas,quantElementos,quantFinais,posicaoDoInicial, elem);

    return 0;
}

//-Implementar função estrela no automato
//-Opcao 3 - abrir o arquivo automato.jflap para apresentar ao usuário

// Comportamento do lambda é um read vazio:
//          <from>posicaoInicial</from>&#13;
//			<to>posicaoFinal</to>&#13;
//			<read/>&#13;

//Estrela
//- Criar um struct auxiliar com as mesmas definições do typedef Elementos e por ele como posicao incial e tirar posicao final do antigo
//- O Auxiliar vai apontar para o antigo
//- Descobrir a posição dos finais
//-Criar um auxiliar que vai apontar para o incial usando epslon
//-Fazer os finais apontarem para o inicial anterior usando  epslon
//-Guardar o valor da posição do inicial, e quando criar o auxiliar alterar apenas o valor de x, colocando a formula x = posicaoInicial-150
