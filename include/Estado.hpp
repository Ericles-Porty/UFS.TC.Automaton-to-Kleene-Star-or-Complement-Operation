#ifndef ESTADO_HPP
#define ESTADO_HPP

#include <string>
using std::string;

class Estado {
   public:
    int id;
    string nome;
    float x;
    float y;
    bool isInicial;
    bool isFinal;

    Estado();

    Estado(int id, string nome,float x, float y, bool isInicial, bool isFinal);
};

#endif  // ESTADO_HPP