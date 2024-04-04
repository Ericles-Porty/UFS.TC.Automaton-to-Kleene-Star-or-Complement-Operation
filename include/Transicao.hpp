#ifndef TRANSICAO_HPP
#define TRANSICAO_HPP

#include <string>

using std::string;

class Transicao {
   public:
    int from;
    int to;
    string read;

    Transicao();

    Transicao(int from, int to, string read);
};

#endif  // TRANSICAO_HPP