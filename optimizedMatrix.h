#ifndef OPTIMIZEDMATRIX.H
#define OPTIMIZEDMATRIX.H
#include "lista.h"
#include <utility>
#include <vector>
#include <algorithm>
#include <stack>
#include <algorithm>
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
    //konstruktor bez parametara
    Matrix() {}

    //konstruktor sa dva parametra koji daju broj redova i kolona matrice
    //pošto su svi elementi jednaki nuli, ne pamtimo ih u privatni atrubut mat
    //nego samo u pomocne varijable broj_redova i broj_kolona
    Matrix(int redovi, int kolone): broj_redova(redovi), broj_kolona(kolone) {}

    Matrix(int redovi, int kolone, vektor<Tip> elementi): broj_redova(redovi), broj_kolona(kolone) {

        sort(elementi.begin(), elementi.end(), [](podaci<Tip> a, podaci<Tip> b) {return a.first.first < b.first.first;});

        auto it1 = elementi.begin();
        auto koordinate = it1->first;


        std::pair<int, Tip> unos;
        unos.first = koordinate.second;
        auto vrijednost = it1->second;
        unos.second = vrijednost;

        std::pair<int, Lista<std::pair<int,Tip>>> clan;
        clan.first = koordinate.first;
        clan.second.Push_Back(unos);

        indeksi_redova.push(clan.first);

        it1++;
        bool isti(false);
        for(auto i(it1); i!=elementi.end(); i++){

            auto koordinate2 = i->first;
            int pomRed = koordinate2.first;
            auto vrijednost = i->second;

            std::pair<int, Tip> unos2;
            unos2.first = koordinate2.second;
            unos2.second = vrijednost;

            if(pomRed != indeksi_redova.top()){
                if(isti){
                    mat.Push_Back(clan);
                    clan.second.Clear();
                    clan.first = pomRed;
                    isti = false;
                }
                std::pair<int, Lista<std::pair<int,Tip>>> clan2;
                clan2.first = pomRed;
                clan2.second.Push_Back(unos2);
                mat.Push_Back(clan2);
                indeksi_redova.push(pomRed);
            }
            else{
                clan.second.Push_Back(unos2);
                isti = true;
            }
        }
    }
    void ispisi() {
        /*std::pair<int,int> sp = std::make_pair(10,10);
        Lista<std::pair<int,int>> s;
        s.Push_Back(sp);
        Lista<std::pair<int,int>>::Iterator it;
        it = s.Begin();
        std::cout<<(*it).first;*/
        typename matrix<Tip>::Iterator it;
        for(it = mat.Begin(); it != mat.End(); it++){
            std::cout<<(*it).first<<',';
            for(auto jt = (*it).second.Begin(); jt != (*it).second.End(); jt++){
                std::cout<<(*jt).first<<'-'<<(*jt).second<<' ';
            }
            std::cout<<std::endl;
        }

    }
};




#endif //OPTIMIZEDMATRIX.H
