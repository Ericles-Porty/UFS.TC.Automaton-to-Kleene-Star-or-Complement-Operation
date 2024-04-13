#include "../include/Estado.hpp"

Estado::Estado() {}

Estado::Estado(int id, std::string nome, float x, float y, bool isInicial, bool isFinal) {
    this->id = id;
    this->nome = nome;
    this->x = x;
    this->y = y;
    this->isInicial = isInicial;
    this->isFinal = isFinal;
}