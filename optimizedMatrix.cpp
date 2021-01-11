#ifndef OPTIMIZEDMATRIX_CPP
#define OPTIMIZEDMATRIX_CPP

#include "optimizedMatrix.h"

template <typename Tip>
Matrix<Tip>::Matrix(int redovi, int kolone, vektor<Tip> elementi): broj_redova(redovi), broj_kolona(kolone) {
    try{
        if(redovi < 0 || kolone < 0)
            throw "pogrešne dimenzije matrice!";
        if((redovi < 1 || kolone < 1) && !elementi.empty())
            throw "pogrešne dimenzije matrice!";

        std::sort(elementi.begin(), elementi.end(), [](podaci<Tip> a, podaci<Tip> b) {return a.first.first < b.first.first;});

        auto it1 = elementi.begin();
        auto koordinate = it1->first;

        std::pair<int, Tip> unos;
        if(koordinate.second < 0 || koordinate.second >= kolone)
            throw "pogrešno unesena kolona!";
        unos.first = koordinate.second;
        unos.second = it1->second;

        std::pair<int, Lista<std::pair<int,Tip>>> clan;
        if(koordinate.first < 0 || koordinate.first >= redovi)
            throw "pogrešno unesen red!";
        clan.first = koordinate.first;
        clan.second.Push_Back(unos);

        std::stack<int> indeksi_redova;
        indeksi_redova.push(clan.first);

        it1++;
        bool isti(false);
        bool razlicit(false);
        for(it1 ; it1 !=elementi.end(); it1++){

            koordinate = it1->first;

            if(koordinate.first < 0 || koordinate.first >= redovi)
                throw "pogrešno unesen red!";
            if(koordinate.second < 0 || koordinate.second >= kolone)
                throw "pogrešno unesena kolona!";

            int pomRed = koordinate.first;
            unos.first = koordinate.second;
            unos.second = it1->second;

            if(pomRed != indeksi_redova.top()){
                indeksi_redova.push(pomRed);
                razlicit = true;

                if(isti){
                    mat.Push_Back(clan);
                    isti = false;
                    razlicit = false;
                    clan.second.Clear();
                    clan.first = pomRed;
                    clan.second.Push_Back(unos);
                }
            }
            else{
                bool flag(true);
                clan.first = pomRed;
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
            if(razlicit){
                mat.Push_Back(clan);
                clan.second.Clear();
                clan.first = pomRed;
                clan.second.Push_Back(unos);
                razlicit = false;
            }
        }
        mat.Push_Back(clan);
    }
    catch(const char* poruka){
        std::cout<<poruka<<std::endl;
    }
}


template <typename Tip>
Matrix<Tip>::Matrix(const Matrix<Tip> &kopija):
    mat(kopija.mat), broj_redova(kopija.broj_redova), broj_kolona(kopija.broj_kolona) {}


template <typename Tip>
Matrix<Tip>::Matrix(Matrix<Tip> &&kopija):
    mat(kopija.mat), broj_redova(kopija.broj_redova), broj_kolona(kopija.broj_kolona) {}


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
    std::cout<<'('<<broj_redova<<','<<broj_kolona<<')'<<std::endl;
    typename matrix<Tip>::Iterator it;
    for(it = mat.Begin(); it != mat.End(); it++){
        for(auto jt = (*it).second.Begin(); jt != (*it).second.End(); jt++){
            std::cout<<'['<<(*it).first<<']'<<'['<<(*jt).first<<']'<<'='<<(*jt).second<<' ';
        }
        std::cout<<std::endl;
    }
}



template <typename tip>
Matrix<tip>& operator+(Matrix<tip> &m1, Matrix<tip> &m2) {
    try{
        if(m1.broj_redova != m2.broj_redova && m1.broj_kolona != m2.broj_kolona)
            throw "matrice se ne mogu sabrati!";
        Matrix<tip>* rez = new Matrix<tip>(m1.broj_redova, m2.broj_kolona);
        rez->broj_redova = m1.broj_redova;
        rez->broj_kolona = m1.broj_kolona;
        auto it1 = m1.mat.Begin();
        auto it2 = m2.mat.Begin();
        while(it1 != m1.mat.End() && it2 != m2.mat.End()){

            std::pair<int, Lista<std::pair<int, tip>>> unos;
            if((*it1).first == (*it2).first){
                auto jt1 = (*it1).second.Begin();
                auto jt2 = (*it2).second.Begin();
                //bool nijeNula(false);
                Lista<std::pair<int, tip>> red;
                std::pair<int, tip> sadrzaj;
                while(jt1 != (*it1).second.End() && jt2 != (*it2).second.End()){

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
                    if(sadrzaj.second){
                        red.Push_Back(sadrzaj);
                        //nijeNula = true;
                    }
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
                if(!red.Empty()){
                    unos.first = (*it1).first;
                    unos.second = red;
                    rez->mat.Push_Back(unos);
                }
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
                rez->mat.Push_Back(unos);
            }
        }
        if(it1 == m1.mat.End()){
            while(it2 != m2.mat.End()){
                rez->mat.Push_Back(*it2);
                it2++;
            }
        }
        if(it2 == m2.mat.End()){
            while(it1 != m1.mat.End()){
                rez->mat.Push_Back(*it1);
                it1++;
            }
        }
        return *rez;
    }
    catch(const char* poruka){
        std::cout<<poruka<<std::endl;
    }
}



template <typename tip>
Matrix<tip>& operator-(Matrix<tip> &m1, Matrix<tip> &m2) {
    try{
        if(m1.broj_redova != m2.broj_redova && m1.broj_kolona != m2.broj_kolona)
            throw "matrice se ne mogu oduzeti!";
        Matrix<tip>* rez = new Matrix<tip>(m1.broj_redova, m2.broj_kolona);
        rez->broj_redova = m1.broj_redova;
        rez->broj_kolona = m1.broj_kolona;
        auto it1 = m1.mat.Begin();
        auto it2 = m2.mat.Begin();
        while(it1 != m1.mat.End() && it2 != m2.mat.End()){

            std::pair<int, Lista<std::pair<int, tip>>> unos;
            if((*it1).first == (*it2).first){
                auto jt1 = (*it1).second.Begin();
                auto jt2 = (*it2).second.Begin();
                //bool nijeNula(false);
                Lista<std::pair<int, tip>> red;
                std::pair<int, tip> sadrzaj;
                while(jt1 != (*it1).second.End() && jt2 != (*it2).second.End()){

                    if((*jt1).first == (*jt2).first) {
                        sadrzaj.first = (*jt1).first;
                        sadrzaj.second = (*jt1).second - (*jt2).second;
                        jt1++; jt2++;
                    }
                    else if((*jt1).first < (*jt2).first){
                        sadrzaj.first = (*jt1).first;
                        sadrzaj.second = (*jt1).second;
                        jt1++;
                    }
                    else{
                        sadrzaj.first = (*jt2).first;
                        sadrzaj.second = -(*jt2).second;
                        jt2++;
                    }
                    if(sadrzaj.second){
                        red.Push_Back(sadrzaj);
                        //nijeNula = true;
                    }
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
                if(!red.Empty()){
                    unos.first = (*it1).first;
                    unos.second = red;
                    rez->mat.Push_Back(unos);
                }
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
                rez->mat.Push_Back(unos);
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
                rez->mat.Push_Back(pom);
                it2++;
            }
        }
        if(it2 == m2.mat.End()){
            while(it1 != m1.mat.End()){
                rez->mat.Push_Back(*it1);
                it1++;
            }
        }
        return *rez;
    }
    catch(const char* poruka){
        std::cout<<poruka<<std::endl;
    }
}


template <typename Tip>
Matrix<Tip>& Matrix<Tip>::transponovano() {
    try{
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
        Matrix<Tip>* rezultat = new Matrix<Tip>(broj_kolona, broj_redova, za_ubacit);
        return *rezultat;
    }
    catch(...){
        std::cout<<"nema memorije!"<<std::endl;
    }
}


template <typename tip>
Matrix<tip>& operator%(Matrix<tip> &m1, Matrix<tip> &m2) {
    try{
        if(m1.broj_kolona != m2.broj_redova)
            throw "broj kolona prve matrice mora bit jednak broju redova druge matrice da bi se pomnožile!";
        Matrix<tip> pom = m2.transponovano();

        vektor<tip> proizvodi;
        podaci<tip> produkt;

        for(auto it = pom.mat.Begin(); it != pom.mat.End(); it++){

            for(auto jt = m1.mat.Begin(); jt != m1.mat.End(); jt++){

                produkt.first.first = (*jt).first;
                produkt.first.second = (*it).first;
                auto it1 = (*it).second.Begin();
                auto jt1 = (*jt).second.Begin();
                int zbir(0);
                while(it1 != (*it).second.End() && jt1 != (*jt).second.End()){
                    if((*jt1).first > (*it1).first)
                        it1++;
                    else if((*jt1).first < (*it1).first)
                        jt1++;
                    else{
                        zbir += (*jt1).second * (*it1).second;
                        it1++; jt1++;
                    }
                }
                produkt.second = zbir;
                if(zbir)
                    proizvodi.push_back(produkt);
            }
        }
        Matrix<tip>* rez = new Matrix<tip>(m1.broj_redova, m2.broj_kolona, proizvodi);
        return *rez;
    }
    catch(const char* poruka){
        std::cout<<poruka<<std::endl;
    }
}


template <typename tip, typename tip2>
Matrix<tip>& operator%(Matrix<tip> &m1, tip2 skalar) {
    auto it = m1.mat.Begin();
    for(it; it != m1.mat.End(); it++)
        for(auto jt = (*it).second.Begin(); jt != (*it).second.End(); jt++)
            (*jt).second *= skalar;
    return m1;
}

template <typename tip, typename tip2>
Matrix<tip>& operator%(tip2 skalar, Matrix<tip> &m1) {
    return m1%skalar;
}


template <typename Tip>
Matrix<Tip>& Matrix<Tip>::jedinicna() {
    this->mat.Clear();
    std::pair<int, Lista<std::pair<int, Tip>>> unos;
    for(int i(0); i<this->broj_redova; i++){
        Lista<std::pair<int, Tip>> red;
        std::pair<int, Tip> element;
        element.first = i;
        element.second = 1;
        red.Push_Back(element);
        unos.first = i;
        unos.second = red;
        this->mat.Push_Back(unos);
    }
    return *this;
}


template <typename Tip>
Matrix<Tip>& Matrix<Tip>::powerOf(unsigned int n) {
    try{
        if(this->broj_redova != this->broj_kolona){
            throw "stepenovanje nije definisano za nekvadratnu matricu!";
        }
        if(n == 0)
            return this->jedinicna();
        if(n == 1)
            return *this;
        if(n % 2 == 0)
            return (*this).powerOf(n/2) % (*this).powerOf(n/2);
        else
            return (*this) % (*this).powerOf(n/2) % (*this).powerOf(n/2);

    }
    catch(const char* poruka){
        std::cout<<poruka<<std::endl;
    }
    return *this;
}

#endif //OPTIMIZEDMATRIX_CPP
