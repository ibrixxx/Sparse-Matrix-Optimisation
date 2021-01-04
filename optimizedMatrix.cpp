#ifndef OPTIMIZEDMATRIX_CPP
#define OPTIMIZEDMATRIX_CPP

#include "optimizedMatrix.h"

template <typename Tip>
Matrix<Tip>::Matrix(int redovi, int kolone, vektor<Tip> elementi): broj_redova(redovi), broj_kolona(kolone) {

        std::sort(elementi.begin(), elementi.end(), [](podaci<Tip> a, podaci<Tip> b) {return a.first.first < b.first.first;});
        elementi.push_back({{-1,-1}, 0});

        auto it1 = elementi.begin();
        auto koordinate = it1->first;

        std::pair<int, Tip> unos;
        unos.first = koordinate.second;
        unos.second = it1->second;

        std::pair<int, Lista<std::pair<int,Tip>>> clan;
        clan.first = koordinate.first;
        clan.second.Push_Back(unos);

        std::stack<int> indeksi_redova;
        indeksi_redova.push(clan.first);

        it1++;
        bool isti(false);
        bool razlicit(false);
        for(it1; it1 !=elementi.end(); it1++){

            koordinate = it1->first;
            int pomRed = koordinate.first;

            unos.first = koordinate.second;
            unos.second = it1->second;

            if(pomRed != indeksi_redova.top()){
                if(razlicit){
                    mat.Push_Back(clan);
                    clan.second.Clear();
                    clan.first = pomRed;
                    clan.second.Push_Back(unos);
                }
                if(isti){
                    mat.Push_Back(clan);
                    isti = false;
                    clan.second.Clear();
                    clan.first = pomRed;
                    clan.second.Push_Back(unos);
                    razlicit = true;
                }
                indeksi_redova.push(pomRed);
            }
            else{
                bool flag(true);
                auto jt = clan.second.Begin();
                while(jt != clan.second.End()){
                    if((*jt).first > unos.first){
                        clan.second.Insert(jt, unos);
                        flag = false;
                        break;
                    }
                    jt++;
                }
                if(flag)
                    clan.second.Push_Back(unos);
                razlicit = false;
                isti = true;
            }
        }
}


template <typename Tip>
Matrix<Tip>::Matrix(const Matrix<Tip> &kopija):
    mat(kopija.mat), broj_redova(kopija.broj_redova), broj_kolona(kopija.broj_kolona) {

}


template <typename Tip>
Matrix<Tip>::Matrix(Matrix<Tip> &&kopija):
    mat(kopija.mat), broj_redova(kopija.broj_redova), broj_kolona(kopija.broj_kolona) {
        kopija.broj_kolona = 0;
        kopija.broj_redova = 0;
}


template <typename Tip>
Matrix<Tip>& Matrix<Tip>::operator=(const Matrix<Tip> &rhs) {
        if(this == &rhs)
            return *this;
        mat = rhs.mat;
        broj_kolona = rhs.broj_kolona;
        broj_redova = rhs.broj_redova;
        return *this;
}


template <typename Tip>
Matrix<Tip>& Matrix<Tip>::operator=(Matrix<Tip> &&rhs) {
        mat = rhs.mat;
        broj_kolona = rhs.broj_kolona;
        broj_redova = rhs.broj_redova;
        return *this;
}


template <typename Tip>
void Matrix<Tip>::ispisi() {
        typename matrix<Tip>::Iterator it;
        for(it = mat.Begin(); it != mat.End(); it++){
            for(auto jt = (*it).second.Begin(); jt != (*it).second.End(); jt++){
                std::cout<<'['<<(*it).first<<']'<<'['<<(*jt).first<<']'<<'='<<(*jt).second<<' ';
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
                std::pair<int, tip> sadrzaj;
                while(jt1 != (*it1).second.End() && jt2 != (*it2).second.End()){

                    if((*jt1).first == (*jt2).first) {
                        sadrzaj.first = (*jt1).first;
                        sadrzaj.second = (*jt1).second + (*jt2).second;
                        jt1++; jt2++;
                    }
                    if((*jt1).first < (*jt2).first){
                        sadrzaj.first = (*jt1).first;
                        sadrzaj.second = (*jt1).second;
                        jt1++;
                    }
                    if((*jt1).first > (*jt2).first){
                        sadrzaj.first = (*jt2).first;
                        sadrzaj.second = (*jt2).second;
                        jt2++;
                    }
                    red.Push_Back(sadrzaj);
                }
                if(jt1 == (*it1).second.End()){
                    while(jt2 != (*it2).second.End()){
                        sadrzaj.first = (*jt2).first;
                        sadrzaj.second = (*jt2).second;
                        red.Push_Back(sadrzaj);
                        jt2++;
                    }
                }
                if(jt2 == (*it2).second.End()){
                    while(jt1 != (*it1).second.End()){
                        sadrzaj.first = (*jt1).first;
                        sadrzaj.second = (*jt1).second;
                        red.Push_Back(sadrzaj);
                        jt1++;
                    }
                }
                unos.first = (*it1).first;
                unos.second = red;
                rez.mat.Push_Back(unos);
                it1++; it2++;
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
                    it1++;
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
                    it2++;
                }
                unos.second = red;
                rez.mat.Push_Back(unos);
            }
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



template <typename tip>
Matrix<tip> operator-(Matrix<tip> m1, Matrix<tip> m2) {
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
                std::pair<int, tip> sadrzaj;
                while(jt1 != (*it1).second.End() && jt2 != (*it2).second.End()){

                    if((*jt1).first == (*jt2).first) {
                        sadrzaj.first = (*jt1).first;
                        sadrzaj.second = (*jt1).second - (*jt2).second;
                        jt1++; jt2++;
                    }
                    if((*jt1).first < (*jt2).first){
                        sadrzaj.first = (*jt1).first;
                        sadrzaj.second = (*jt1).second;
                        jt1++;
                    }
                    if((*jt1).first > (*jt2).first){
                        sadrzaj.first = (*jt2).first;
                        sadrzaj.second = -(*jt2).second;
                        jt2++;
                    }
                    red.Push_Back(sadrzaj);
                }
                if(jt1 == (*it1).second.End()){
                    while(jt2 != (*it2).second.End()){
                        sadrzaj.first = (*jt2).first;
                        sadrzaj.second = -(*jt2).second;
                        red.Push_Back(sadrzaj);
                        jt2++;
                    }
                }
                if(jt2 == (*it2).second.End()){
                    while(jt1 != (*it1).second.End()){
                        sadrzaj.first = (*jt1).first;
                        sadrzaj.second = (*jt1).second;
                        red.Push_Back(sadrzaj);
                        jt1++;
                    }
                }
                unos.first = (*it1).first;
                unos.second = red;
                rez.mat.Push_Back(unos);
                it1++; it2++;
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
                    it1++;
                }
                else{
                    unos.first = (*it2).first;
                    auto jt2 = (*it2).second.Begin();
                     while(jt2 != (*it2).second.End()){
                        std::pair<int, tip> sadrzaj;
                        sadrzaj.first = (*jt2).first;
                        sadrzaj.second = -(*jt2).second;
                        red.Push_Back(sadrzaj);
                        jt2++;
                    }
                    it2++;
                }
                unos.second = red;
                rez.mat.Push_Back(unos);
            }
        }
        if(it1 == m1.mat.End()){
            std::pair<int, Lista<std::pair<int, tip>>> pom;
            while(it2 != m2.mat.End()){
                pom = (*it2);
                auto i = pom.second.Begin();
                while(i != pom.second.End()){
                    (*i).second *= -1;
                    i++;
                }
                rez.mat.Push_Back(pom);
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


template <typename Tip>
Matrix<Tip> Matrix<Tip>::transponovano() {
    vektor<Tip> za_ubacit;
    typename matrix<Tip>::Iterator it;
    for(it = mat.Begin(); it != mat.End(); it++){
        std::pair<std::pair<int, int>, Tip> pom;
        pom.first.second = (*it).first;
        for(auto jt = (*it).second.Begin(); jt != (*it).second.End(); jt++){
            pom.first.first = (*jt).first;
            pom.second = (*jt).second;
            za_ubacit.push_back(pom);
        }
    }
    Matrix<Tip> rezultat(broj_kolona, broj_redova, za_ubacit);
    return rezultat;
}

#endif //OPTIMIZEDMATRIX_CPP
