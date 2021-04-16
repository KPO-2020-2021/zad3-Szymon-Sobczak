#include "../tests/doctest/doctest.h"
#include "vector.hh"

TEST_CASE("Test konstrukora bezparametrowego dla klasy Vector"){
    Vector Vec;
    CHECK((Vec[0]==0 && Vec[1]==0));
}

TEST_CASE("Test konstrukora z argumentem dla klasy Vector"){
    double values[]={1,2};
    Vector Vec(values);
    CHECK((Vec[0]==1 && Vec[1]==2));
}

TEST_CASE("Test odczytywania wartosci wektora z uzyciem operatora indeksowania "){
    double values[]={1,2},a,b;
    Vector Vec(values);
    a= Vec[0];
    b= Vec[1];
    CHECK((a==1 && b==2));
}

TEST_CASE("Test wpraowadzania wartosci do wektora z uzyciem operatora indeksowania "){
    Vector Vec;
    double a=7,b=15;
    Vec[0]=a;
    Vec[1]=b;
    CHECK((Vec[0]==7 && Vec[1]==15));
}

TEST_CASE("Test operatora indeksowania - bledna wartosc indeksu "){
    double values[]={1,2};
    Vector Vec(values);
    WARN_THROWS (Vec[-8]);
}

TEST_CASE("Test wyswietlenia wartosci wektora z uzyciem przeciazenia << "){
    double values[]={1,2};
    Vector Vec(values);
    std::ostringstream out;
    out << Vec;
    CHECK ("1.0000000000\t2.0000000000\t" == out.str());  
}

TEST_CASE("Test wczytywania wartosci do wektora z uzyciem przeciazenia >> "){
    double values[]={1,2};
    Vector Vec(values);
    std::istringstream input("1 2");
    input >> Vec;
    CHECK ((Vec[0]==1 && Vec[1]==2));  
}