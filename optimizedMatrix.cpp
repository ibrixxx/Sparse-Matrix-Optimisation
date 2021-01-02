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


template <typename tip>
Matrix<tip> operator+(Matrix<tip> m1, Matrix<tip> m2) {
        if(m1.broj_redova != m2.broj_redova && m1.broj_kolona != m2.broj_kolona)
            throw "matrice se ne mogu sabrati!";
        Matrix<tip> rez;
        rez.broj_redova = m1.broj_redova;
        rez.broj_kolona = m1.broj_kolona;
        auto it1 = m1.mat.Begin();
        auto it2 = m2.mat.Begin();
        while(it1 != m1.mat.End() && it2 != m2.mat.End()){

            std::pair<int, Lista<std::pair<int, tip>>> unos;
            if((*it1).first == (*it2).first){
                auto jt1 = (*it1).second.Begin();
                auto jt2 = (*it2).second.Begin();

                Lista<std::pair<int, tip>> red;
                while(jt1 != (*it1).second.End() && jt2 != (*it2).second.End()){
                    std::pair<int, tip> sadrzaj;
                    if((*jt1).first == (*jt2).first) {
                        sadrzaj.first = (*jt1).first;
                        sadrzaj.second = (*jt1).second + (*jt2).second;
                        jt1++; jt2++;
                    }
                    else if((*jt1).first < (*jt2).first){
                        sadrzaj.first = (*jt1).first;
                        sadrzaj.second = (*jt1).second;
                        jt1++;
                    }
                    else{
                        sadrzaj.first = (*jt2).first;
                        sadrzaj.second = (*jt2).second;
                        jt2++;
                    }
                    red.Push_Back(sadrzaj);
                }
                if(jt1 == (*it1).second.End()){
                    while(jt2 != (*it2).second.End()){
                        std::pair<int, tip> sadrzaj;
                        sadrzaj.first = (*jt2).first;
                        sadrzaj.second = (*jt2).second;
                        red.Push_Back(sadrzaj);
                        jt2++;
                    }
                }
                if(jt2 == (*it2).second.End()){
                    while(jt1 != (*it1).second.End()){
                        std::pair<int, tip> sadrzaj;
                        sadrzaj.first = (*jt1).first;
                        sadrzaj.second = (*jt1).second;
                        red.Push_Back(sadrzaj);
                        jt1++;
                    }
                }
                unos.first = (*it1).first;
                unos.second = red;
                rez.mat.Push_Back(unos);
            }
            else{
                Lista<std::pair<int, tip>> red;
                if((*it1).first < (*it2).first){
                    unos.first = (*it1).first;
                    auto jt1 = (*it1).second.Begin();
                    while(jt1 != (*it1).second.End()){
                        std::pair<int, tip> sadrzaj;
                        sadrzaj.first = (*jt1).first;
                        sadrzaj.second = (*jt1).second;
                        red.Push_Back(sadrzaj);
                        jt1++;
                    }
                }
                else{
                    unos.first = (*it2).first;
                    auto jt2 = (*it2).second.Begin();
                     while(jt2 != (*it2).second.End()){
                        std::pair<int, tip> sadrzaj;
                        sadrzaj.first = (*jt2).first;
                        sadrzaj.second = (*jt2).second;
                        red.Push_Back(sadrzaj);
                        jt2++;
                    }
                }
                unos.second = red;
                rez.mat.Push_Back(unos);
            }
        it1++; it2++;
        }
        if(it1 == m1.mat.End()){
            while(it2 != m2.mat.End()){
                rez.mat.Push_Back(*it2);
                it2++;
            }
        }
        if(it2 == m2.mat.End()){
            while(it1 != m1.mat.End()){
                rez.mat.Push_Back(*it1);
                it1++;
            }
        }
        return rez;
}


#endif //OPTIMIZEDMATRIX_CPP
