#include "rectangle.hh"
#include <chrono>
#include <thread>
#include <unistd.h>

/*
* Alternatywny konstruktor obiektu typu Rectangle.
* Konstruktor pozwala na inicjalizacje prostokata z uzyciem wektorow.
* Warunki wstepne:
*   CornerA - do poprawnego dzialania wektor musi byc poprawnie zainicjowany wartosciami wspolrzednych wektora.
*   CornerB - do poprawnego dzialania wektor musi byc poprawnie zainicjowany wartosciami wspolrzednych wektora.
*   CornerC - do poprawnego dzialania wektor musi byc poprawnie zainicjowany wartosciami wspolrzednych wektora.
*   CornerD - do poprawnego dzialania wektor musi byc poprawnie zainicjowany wartosciami wspolrzednych wektora.
* Warunki koncowe:
*   brak.
* Argumenty:
*   CornerA - wektor opisujacy polozenie wierzcholka A.
*   CornerB - wektor opisujacy polozenie wierzcholka B.
*   CornerC - wektor opisujacy polozenie wierzcholka C.
*   CornerD - wektor opisujacy polozenie wierzcholka D.
* Zwraca:
*   brak;
*/

Rectangle::Rectangle(Vector CornerA, Vector CornerB, Vector CornerC, Vector CornerD){
    Corners[0] = CornerA; 
    Corners[1] = CornerB;
    Corners[2] = CornerC; 
    Corners[3] = CornerD;
}

/*
* Metoda klasy Rectangle realizaujca dzialanie translacji prostokata o wybrany wektor.
* Warunki wstepne:
*   vector - do poprawnego dzialania wektor musi byc poprawnie zainicjowany wartosciami wspolrzednych wektora.
* Warunki koncowe:
*   brak.
* Argumenty:
*   vector - wektor translacji.
* Zwraca:
*   Prostokat o zmienionym polozeniu za sprawa operacji translacji o wektor.
*/

Rectangle Rectangle::Translate_rec(Vector const vector){
    for (int i=0; i<4; i++){
        this->Corners[i] =this->Corners[i] + vector;
    }
    return *this;
}

/*
* Metoda klasy Rectangle realizaujca dzialanie obrotu prostokata o wybrany kat, wybrana ilosc razy.
* Warunki wstepne:
*   multiplier - wartosc musi miesicic sie w zakresie wlasciwym int.
*   angle - wartosc musi byc typu 
* Warunki koncowe:
*   brak.
* Argumenty:
*   multiplier - wartosc musi miesicic sie w zakresie wlasciwym int.
*   angle - wartosc musi byc typu 
* Zwraca:
*   Prostokat o zmienionym polozeniu za sprawa operacji obrotu.
*/

Rectangle Rectangle::Rotate_rec(int const multiplier, double const angle){
    Matrix mtx; 
    mtx.Fill_matrix(angle);
    for (int i=0; i<multiplier; i++){
        for(int j=0; j<4; j++)
            Corners[j]=mtx * Corners[j];
    }
    return *this;
}

/*
* Funkcja wykonujaca operacje przeciazenia operatora <<.
* Funkcja sluzy do wypisywania na wskazany strumien wyjsciowy, wartosci wspolrzednych wierzcholka prostokata.
* Warunki wstepne:
*   & Strm- wybrany strumien musi byc typu ostream.
*   & Rc - do poprawnego dzialania prostokat musi byc poprawnie zainicjowany wartosciami wspolrzednych wierzcholkow.
* Warunki koncowe:
*   brak.
* Argumenty:
*   & Strm - Referencja do strumienia typu ostream, na ktory maja zostac wypisane wspolrzedne wektora.
*   & Rc - Referencja do prostokata, ktorego wspolrzedne wierzcholkow maja zostac wpisane na wskazany strumien.
* Zwraca:
*   Wypisane wspolrzende wksazanego prostokata, w odpowiedniej formie na wskazane wyjscie. 
*/

std::ostream & operator << (std::ostream & Strm, const Rectangle & Rc){
    for (int i=0; i<4;i++)
        Strm << Rc.Corners[i] << std::endl;
    return Strm;
}

/*
* Funkcja wykonujaca operacje przeciazenia operatora >>.
* Funkcja sluzy do wprowadzania wartosci wspolrzednych wierzcholkow prostokata ze wskazanego strumienia wejsciowego.  
* Warunki wstepne:
*   & Strm- wybrany strumien musi byc typu istream.
*   & Rc - do poprawnego dzialania prostokat musi byc wczesniej zainicjowany.
* Warunki koncowe:
*   brak;
* Argumenty:
*   & Strm - Referencja do strumienia typu istream, z ktorego maja zostac wczytane wspolrzedne wierzcholkow prostokata.
*   & Vec - Referencja do prostokata, do ktorego maja zostac wpisane podane wspolrzedne weirzcholkow.
* Zwraca:
*   Wczytany obiekt- prostokat.
*/

std::istream & operator >> (std::istream & Strm,Rectangle & Rc){
    for (int i=0; i<CORNERS;i++){
        Strm >> Rc.Corners[i];
    }
    return Strm;
}

/*
* Funkcja wykonujaca operacje przeciazenia operatora >>.
* Funkcja sluzy do wprowadzania wartosci wspolrzednych wierzcholkow prostokata ze wskazanego strumienia wejsciowego.  
* Warunki wstepne:
*   *sNazwaPliku - do poprawnego dzialania wybrany napis stanowiacy nazwe musi być zgodny z nazwa pliku wskazanego programowi GNUplot.
* Warunki koncowe:
*   brak;
* Argumenty:
*   *sNazwaPliku - wskaznik na napis stanowiacy nazwe pliku wyjsciowego.
* Zwraca:
*   brak.
*/

void Rectangle::Write_rec_to_file(const char *sNazwaPliku) const{
  std::ofstream  StrmPlikowy;
  StrmPlikowy.open(sNazwaPliku);
  if (!StrmPlikowy.is_open()){
    throw std::runtime_error(":(  Operacja otwarcia pliku do zapisu nie powiodla sie.");
  }
  StrmPlikowy << *this;
  StrmPlikowy << Corners[0];
  StrmPlikowy.close();
}

 void Rectangle::Is_it_rec(){
    double a,b,c,d;
    a = sqrt(pow(this->Corners[1][0]-this->Corners[0][0],2)+pow(this->Corners[1][1]-this->Corners[0][1],2)); 
    b = sqrt(pow(this->Corners[2][0]-this->Corners[1][0],2)+pow(this->Corners[2][1]-this->Corners[1][1],2));
    c = sqrt(pow(this->Corners[3][0]-this->Corners[2][0],2)+pow(this->Corners[3][1]-this->Corners[2][1],2));
    d = sqrt(pow(this->Corners[0][0]-this->Corners[3][0],2)+pow(this->Corners[0][1]-this->Corners[3][1],2));
    std::cout << std::endl;
    if(a-c < LENGTH_DIFF && c-a < LENGTH_DIFF){
        if(a >= b && a >= d && c >= b && c >= d)
            std::cout << ":) Dluzsze przeciwlegle boki sa sobie rowne" << std::endl;
        else
            std::cout << ":) Krotsze przeciwlegle boki sa sobie rowne" << std::endl;
    }
    else{ 
        if(a >= b && a >= d && c >= b && c >= d)
            std::cout << ":O Dluzsze przeciwlegle boki nie sa sobie rowne" << std::endl;
        else
            std::cout << ":O Krotsze przeciwlegle boki nie sa sobie rowne" << std::endl;
    }
    std::cout << "Dlugosc pierwszego boku: " << a << std::endl;
    std::cout << "Dlugosc drugiego boku: " << c << std::endl;
    std::cout << std::endl;
    
    if(b-d < LENGTH_DIFF && d-b < LENGTH_DIFF){
        if(b >= a && b >= c && d >= a && d >= c)
            std::cout << ":) Dluzsze rzeciwlegle boki sa sobie rowne "<< std::endl;
        else
            std::cout << ":) Krotsze rzeciwlegle boki sa sobie rowne" << std::endl;
    }
    else{ 
        if(a >= b && a >= d && c >= b && c >= d)
            std::cout << ":O Dluzsze przeciwlegle boki nie sa sobie rowne " << std::endl;
        else
            std::cout << ":O  Krotsze przeciwlegle boki nie sa sobie rowne " << std::endl;
    }
    std::cout << "Dlugosc pierwszego boku: " << b << std::endl;
    std::cout << "Dlugosc drugiego boku: " << d << std::endl;
    std::cout << std::endl;
 }
