#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

const string arquivo = "automato.jff";
const string isFinal = "\t\t\t<final/>";
const string isInicial = "\t\t\t<initial/>";
const string compStringId = "\t\t<state id=\"";
const string fecha = "\t\t</state>&#";

ifstream entrada;
ofstream saida;

typedef struct frases
{
    string frase;
} FraseLinhas[10];
typedef struct estados
{
    int idEstado;
    string nomeEstado;
    int acceptInicial;
    int acceptFinal;
} Estados[10];

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
    int posicaoDoInicial = -1;
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
                    //linhas[contador]->frase = linha;
                    //cout << linhas[contador]->frase << endl;
                }
            }
        }
        entrada.close();
        return posicaoDoInicial;
    }
    cout << "Ocorreu um erro ao abrir o arquivo, perdao pela inconveniencia." << endl;
    exit(1);
}

void guardaFinais(finais[])
{

    string linha;
    string subStringTempId;
    int posicaoElemento = 0;
    int posicaoDoInicial = -1;
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
                    //linhas[contador]->frase = linha;
                    //cout << linhas[contador]->frase << endl;
                }
            }
        }
        entrada.close();
        return posicaoDoInicial;
    }
    cout << "Ocorreu um erro ao abrir o arquivo, perdao pela inconveniencia." << endl;
    exit(1);
}

void mineraNomes(Estados *elem)
{
    string subStringTempId;
    string linha;
    int indice = 0;
    entrada.open(arquivo);
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
}

int main()
{
    Estados elem;
    FraseLinhas frase;
    //mineraNomes(&elem);
    int posicaoDoInicial = achaInicial();
    int quantFinais = contaFinais();
    int *elementosFinais = (int *)malloc(quantFinais * sizeof(int));
    guardaFinais(&elementosFinais);
    int quantElementos = contaElementos();
    int quantLinhas = contaLinhas();
    /*for (int i = 0; i < 5; i++)
    {
        cout << "Palavra " << i << frase[i].frase << endl;
    }*/
    if (posicaoDoInicial != -1)
        cout << "ID do elemento que esta o inicial: " << posicaoDoInicial << endl;
    cout << "Quantidade de finais: " << quantFinais << endl;
    cout << "Quantidade de linhas: " << quantLinhas << endl;
    cout << "Quantidade de elementos: " << quantElementos << endl;
    return 0;
}

//Criar um vetor de Strings com o tamanho de linhas que vamos precisar para poder escrever os epslon e o auxiliar dentro dele
//E sobrescrever o automato.jflap usando o vetor de strings no final

//Criar menu
//Opcao 1 - implementar função estrela no automato
//Opcao 2 - implementar função complemento  automato
//Opcao 3 - abrir o arquivo automato.jflap para apresentar ao usuário

// Comportamento do lambda é um read vazio:
//          <from>posicaoInicial</from>&#13;
//			<to>posicaoFinal</to>&#13;
//			<read/>&#13;

//Estrela
//- Criar um struct auxiliar com as mesmas definições do typedef Elementos e por ele como posicao incial e tirar posicao final do antigo
//- O Auxiliar vai apontar para o antigo
//- Descobrir a posição dos finais
//Criar um auxiliar que vai apontar para o incial usando epslon
//Fazer os finais apontarem para o inicial anterior usando  epslon
//Guardar o valor da posição do inicial, e quando criar o auxiliar alterar apenas o valor de x, colocando a formula x = posicaoInicial-150

//Complemento
//Fazer os finais deixarem de serem inciais
//Fazer os não finais virarem finais

//Criar 2 arquivos, antigo e alterado