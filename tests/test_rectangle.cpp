#include "../tests/doctest/doctest.h"
#include "rectangle.hh"

TEST_CASE("Test konstrukora bezparametrowego dla klasy rectangle"){
    Rectangle Example;
    CHECK((Example[0][0]==0 && Example[0][1]==0 && Example[1][0]==0 && Example[1][1]==0 && 
          Example[2][0]==0 && Example[2][1]==0 && Example[3][0]==0 && Example[3][1]==0));
}

TEST_CASE("Test konstruktora wieloparametrowego dla klasy rectangle"){
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4};
    Vector A(X),B(Y),C(Z),D(U);
    Rectangle Example(A,B,C,D);
    CHECK((Example[0][0]==3 && Example[0][1]==1 && Example[1][0]==8 && Example[1][1]==1 && 
           Example[2][0]==8 && Example[2][1]==4 && Example[3][0]==3 && Example[3][1]==4));
}
 
TEST_CASE("Test wpraowadzania i odczytywania wartosci wierzcholkow prostokata z uzyciem operatora indeksowania "){
    Rectangle Example;
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4};
    Vector A(X),B(Y),C(Z),D(U);
    Example[0]= A;
    Example[1]= B;
    Example[2]= C;
    Example[3]= D;
    CHECK((Example[0][0]==3 && Example[0][1]==1 && Example[1][0]==8 && Example[1][1]==1 && 
           Example[2][0]==8 && Example[2][1]==4 && Example[3][0]==3 && Example[3][1]==4));
}

TEST_CASE("Test operatora indeksowania - bledna wartosc indeksu podana przy odczytywaniu wartosci z prostokata"){
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4};
    Vector A(X),B(Y),C(Z),D(U);
    Rectangle Example(A,B,C,D);
    WARN_THROWS((Example[15][0]==3 && Example[-9][1]==1));
}

TEST_CASE("Test operatora indeksowania - bledna wartosc indeksu podana przy wprowadzaniu wartosci z prostokata"){
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4};
    Vector A(X),B(Y),C(Z),D(U);
    Rectangle Example;
    WARN_THROWS((Example[-9]=A));
}

TEST_CASE("Test wyswietlania wartosci wektorow reprezentujacych polozenia wierzcholkow prostokata za pomoca przeciazenia operatora << "){
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4};
    Vector A(X),B(Y),C(Z),D(U);
    Rectangle Example(A,B,C,D);
    std::ostringstream out;
    out << Example;
    CHECK(("3.0000000000\t1.0000000000\t\n8.0000000000\t1.0000000000\t\n8.0000000000\t4.0000000000\t\n3.0000000000\t4.0000000000\t\n"==out.str()));
}


TEST_CASE("Test zapisu inforamcji o wspolrzednych wierzcholkow prostokata do wskazanego pliku wraz ze sprawdzeniem ich porpawnosci"){
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4};
    Vector A(X),B(Y),C(Z),D(U);
    Rectangle Example(A,B,C,D);
    std::string test[10],pattern[10]= {"3.0000000000","1.0000000000", "8.0000000000", "1.0000000000", "8.0000000000","4.0000000000","3.0000000000","4.0000000000","3.0000000000","1.0000000000"};
    std::ifstream  StrmPlikowy;
    Example.Write_rec_to_file("../tests/datasets/test_rec.dat");
    StrmPlikowy.open("../tests/datasets/test_rec.dat");
    for (int i=0; i<10 ; i++){
        StrmPlikowy >> test[i];
        CHECK((pattern[i]==test[i]));
    }  
}

TEST_CASE("Test wczytywania wartosci do wektora z uzyciem przeciazenia >> "){
    Vector Vec;
    std::istringstream input("1 2");
    input >> Vec;
    CHECK ((Vec[0]==1 && Vec[1]==2));  
}

TEST_CASE("Test dzialania metody przesunieca prostokata o zadany wektor"){
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4};
    Vector A(X),B(Y),C(Z),D(U);
    Rectangle Example(A,B,C,D);
    double values[]={1,2};
    Vector Vec(values);
    Example.Translate_rec(Vec);
    CHECK((Example[0][0]==4 && Example[0][1]==3 && Example[1][0]==9 && Example[1][1]==3 && 
           Example[2][0]==9 && Example[2][1]==6 && Example[3][0]==4 && Example[3][1]==6));
}

TEST_CASE("Test dzialania metody obrotu prostokata o zadany kat, wybrana ilosc razy "){
    double X[]={3,1}, Y[]={8,1}, Z[]={8,4}, U[]={3,4}, angle= 90, mulitpier = 3;
    Vector A(X),B(Y),C(Z),D(U);
    Rectangle Example(A,B,C,D);
    double values[]={1,2};
    Vector Vec(values);
    Example.Rotate_rec(mulitpier,angle);
    CHECK((Example[0][0]>1-MAX_VALUE_DIFF && Example[0][0]<1+MAX_VALUE_DIFF &&
            Example[0][1]>-3-MAX_VALUE_DIFF && Example[0][1]<-3+MAX_VALUE_DIFF &&
            Example[1][0]>1-MAX_VALUE_DIFF && Example[1][0]<1+MAX_VALUE_DIFF &&
            Example[1][1]>-8-MAX_VALUE_DIFF && Example[1][1]<-8+MAX_VALUE_DIFF &&
            Example[2][0]>4-MAX_VALUE_DIFF && Example[2][0]<4+MAX_VALUE_DIFF &&
            Example[2][1]>-8-MAX_VALUE_DIFF && Example[2][1]<-8+MAX_VALUE_DIFF &&
            Example[3][0]>4-MAX_VALUE_DIFF && Example[3][0]<4+MAX_VALUE_DIFF &&
            Example[3][1]>-3-MAX_VALUE_DIFF && Example[3][1]<-3+MAX_VALUE_DIFF));
}
