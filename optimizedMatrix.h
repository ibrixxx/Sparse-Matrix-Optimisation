#ifndef OPTIMIZEDMATRIX_H
#define OPTIMIZEDMATRIX_H

#include "lista.h"
#include <utility>
#include <vector>
#include <algorithm>
#include <stack>
//#include <initializer_list>
//using namespace std;


//Korištenje aliasa "matrix" kako bi se izbjeglo pisanje velike konstrukcije koja čuva matricu
//matrica se čuva u listi parova gdje je prvi član para index reda, a drugi član para je lista
//parova čiji je prvi član para kolona elementa, a drugi generička vrijednost elementa matrice
template <typename Tip>
using matrix = Lista<std::pair<int, Lista<std::pair<int, Tip>>>>;

template <typename Tip>
using vektor = std::vector<std::pair<std::pair<int, int>, Tip>>;

template <typename Tip>
using podaci = std::pair<std::pair<int, int>, Tip>;


template <typename Tip>
class Matrix {
    matrix<Tip> mat;
    int broj_redova;
    int broj_kolona;
    std::stack<int> indeksi_redova;
    public:
    typename Lista<Tip>::Const_Iterator Begin() const { return mat.Begin(); }
    typename Lista<Tip>::Const_Iterator End() const { return mat.End(); }
    typename Lista<Tip>::Iterator Begin() { return mat.Begin(); }
    typename Lista<Tip>::Iterator End() { return mat.End(); }

    //konstruktor bez parametara
    Matrix() {}

    //konstruktor sa dva parametra koji daju broj redova i kolona matrice
    //pošto su svi elementi jednaki nuli, ne pamtimo ih u privatni atrubut mat
    //nego samo u pomocne varijable broj_redova i broj_kolona
    Matrix(int redovi, int kolone): broj_redova(redovi), broj_kolona(kolone) {}

    Matrix(int redovi, int kolone, vektor<Tip> elementi);

    Matrix(const Matrix<Tip> &kopija);

    Matrix(Matrix<Tip> &&kopija);

    Matrix<Tip>& operator=(const Matrix<Tip> &rhs);

    Matrix<Tip>& operator=(Matrix<Tip> &&rhs);

    void ispisi();

    template <typename tip>
    friend Matrix<tip>& f(Matrix<tip> &v);
};


#include "optimizedMatrix.cpp"


#endif //OPTIMIZEDMATRIX_H
