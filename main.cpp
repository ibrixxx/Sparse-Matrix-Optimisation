#include <iostream>
#include "optimizedMatrix.h"



int main() {
    vektor<double> v{{{2,3}, 4.2}, {{4,5}, 8.5}, {{7,8}, 3.3}, {{2,8}, 1.20}};
    vektor<double> v1{{{0,0}, 1}, {{0,2}, 2}, {{1,0}, -1}, {{1,1}, 3}, {{1,2}, 1}};
    vektor<double> v2{{{0,0}, 3}, {{0,1}, 1}, {{1,0}, 2}, {{1,1}, 1}, {{2,0}, 1}};
    Matrix<double> p(100,100,{ {{8,3}, 15}, {{9,6}, 5}, {{9,3}, 25} });
    Matrix<double> p2(100,100, { {{9,7},1}, {{9,6},2}, {{10,3},7}, {{8,5},2}, {{8,3},-15} });
    //p2.ispisi();

    std::cout<<"Sabiranje: "<<std::endl;

    Matrix<double> sab(p+p2);
    sab.ispisi();

    std::cout<<std::endl<<"Oduzimanje: "<<std::endl;

    Matrix<double> m(100,100, v);
    Matrix<double> m3 = p-m;
    m3.ispisi();

    std::cout<<std::endl<<"Transponovanje: "<<std::endl;

    Matrix<double> b1(2,3,v1);
    Matrix<double> b2(3,2,v2);
    b1.ispisi();
    b1.transponovano().ispisi();

    std::cout<<std::endl<<"Množenje skalarom: "<<std::endl;

    b2 = 3%b2;
    b2.ispisi();

    std::cout<<std::endl<<"Množenje: "<<std::endl;

    Matrix<double> m1(2,3, { {{0,0}, 1}, {{1,0}, -1}, {{1,2}, 3} });
    Matrix<double> m2(3,3, { {{0,0}, 7}, {{2,2}, 1} });
    //Matrix<double> b(b1%b2);
    (m1%m2).ispisi();

    std::cout<<std::endl<<"Stepenovanje: "<<std::endl;

    //m2.powerOf(0).ispisi();
    //m1.powerOf(2).ispisi();
    m2.powerOf(4).ispisi();
    m2.ispisi();

    return 0;
}
