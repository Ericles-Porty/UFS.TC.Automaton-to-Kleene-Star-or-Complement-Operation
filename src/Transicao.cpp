#include "../include/Transicao.hpp"

Transicao::Transicao() {}

Transicao::Transicao(int from, int to, std::string read) {
    this->from = from;
    this->to = to;
    this->read = read;
}