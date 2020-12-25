#ifndef OPTIMIZEDMATRIX.H
#define OPTIMIZEDMATRIX.H
#include "lista.h"
#include <utility>


template <typename tip>
using matrix = Lista<std::pair<int, Lista<std::pair<int, tip>>>>;

template <typename tip>
class Matrix {
    matrix<tip> m;
};




#endif //OPTIMIZEDMATRIX.H
