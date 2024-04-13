#ifndef AUTOMATO_HPP
#define AUTOMATO_HPP

#include <list>
#include <string>

#include "Estado.hpp"
#include "Transicao.hpp"

using std::list;
using std::string;

class Automato {
   public:
    list<Estado> estados;
    list<Transicao> transicoes;

    Automato();

    void importaAutomato(string caminho);
    void exportaAutomato(string caminho);

    Automato* complemento();
    Automato* estrela();
};

#endif  // AUTOMATO_HPP