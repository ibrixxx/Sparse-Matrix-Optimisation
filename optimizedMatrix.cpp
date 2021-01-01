#ifndef OPTIMIZEDMATRIX_CPP
#define OPTIMIZEDMATRIX_CPP

#include "optimizedMatrix.h"

template <typename Tip>
Matrix<Tip>::Matrix(int redovi, int kolone, vektor<Tip> elementi): broj_redova(redovi), broj_kolona(kolone) {

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


template <typename Tip>
Matrix<Tip>::Matrix(const Matrix<Tip> &kopija):
    mat(kopija.mat), broj_redova(kopija.broj_redova), broj_kolona(kopija.broj_kolona) {
        indeksi_redova = kopija.indeksi_redova;
}


template <typename Tip>
Matrix<Tip>::Matrix(Matrix<Tip> &&kopija):
    mat(kopija.mat), broj_redova(kopija.broj_redova), broj_kolona(kopija.broj_kolona) {
        indeksi_redova = kopija.indeksi_redova;
        kopija.broj_kolona = 0;
        kopija.broj_redova = 0;
}


template <typename Tip>
Matrix<Tip>& Matrix<Tip>::operator=(const Matrix<Tip> &rhs) {
        if(this == &rhs)
            return *this;
        mat = rhs.mat;
        indeksi_redova = rhs.indeksi_redova;
        broj_kolona = rhs.broj_kolona;
        broj_redova = rhs.broj_redova;
        return *this;
}


template <typename Tip>
Matrix<Tip>& Matrix<Tip>::operator=(Matrix<Tip> &&rhs) {
        mat = rhs.mat;
        broj_kolona = rhs.broj_kolona;
        broj_redova = rhs.broj_redova;
        indeksi_redova = rhs.indeksi_redova;
        return *this;
}


template <typename Tip>
void Matrix<Tip>::ispisi() {
        typename matrix<Tip>::Iterator it;
        for(it = mat.Begin(); it != mat.End(); it++){
            std::cout<<(*it).first<<',';
            for(auto jt = (*it).second.Begin(); jt != (*it).second.End(); jt++){
                std::cout<<(*jt).first<<'-'<<(*jt).second<<' ';
            }
            std::cout<<std::endl;
        }

}


#endif //OPTIMIZEDMATRIX_CPP
