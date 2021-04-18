#include "rectangle.hh"

/****************************************************************************************************************
 | Domyślny konstruktor obiektu typu Rectangle.                                                                 |
 | Konstruktor pozwala na inicjalizacje prostokata z uzyciem wektorow.                                          | 
 | Argumenty:                                                                                                   |
 |  brak.                                                                                                       | 
 | Zwraca:                                                                                                      |
 |  Prostokat o wierzcholakach zainicjowanych wartosciami werkotrow zerowych.                                   |
 */

Rectangle::Rectangle(){
    for (int i=0;i<4;i++)
        Corners[i] = Vector();    
}

/****************************************************************************************************************
 | Alternatywny konstruktor obiektu typu Rectangle.                                                             |
 | Konstruktor pozwala na inicjalizacje prostokata z uzyciem wektorow.                                          |
 | Warunki wstepne:                                                                                             |
 |  CornerA - do poprawnego dzialania wektor musi byc poprawnie zainicjowany wartosciami wspolrzednych wektora. |
 |  CornerB - do poprawnego dzialania wektor musi byc poprawnie zainicjowany wartosciami wspolrzednych wektora. |
 |  CornerC - do poprawnego dzialania wektor musi byc poprawnie zainicjowany wartosciami wspolrzednych wektora. |
 |  CornerD - do poprawnego dzialania wektor musi byc poprawnie zainicjowany wartosciami wspolrzednych wektora. |
 | Warunki koncowe:                                                                                             |
 |   brak.                                                                                                      |   
 | Argumenty:                                                                                                   |
 |  CornerA - wektor opisujacy polozenie wierzcholka A.                                                         | 
 |  CornerB - wektor opisujacy polozenie wierzcholka B.                                                         |
 |  CornerC - wektor opisujacy polozenie wierzcholka C.                                                         |
 |  CornerD - wektor opisujacy polozenie wierzcholka D.                                                         |
 | Zwraca:                                                                                                      |
 |   Prostokat o wierzcholakach zainicjowanych wartosciami werkotrow.                                           |
 */

Rectangle::Rectangle(Vector CornerA, Vector CornerB, Vector CornerC, Vector CornerD){
    Corners[0] = CornerA; 
    Corners[1] = CornerB;
    Corners[2] = CornerC; 
    Corners[3] = CornerD;
}

/******************************************************************************
 |  Funktor prostokata.                                                       |
 |  Warunki wstepne:                                                          |
 |      index - wartosc musi zawierac sie w przedziale od 0 do CORNERS.       |               
 |  Warunki koncowe:                                                          |
 |      brak.                                                                 |
 |  Argumenty:                                                                |
 |      index - index prostokata.                                             |
 |  Zwraca:                                                                   |
 |      Wartosc prostokata w danym miejscu tablicy jako stala.                |
 */
const Vector & Rectangle::operator [] (int index) const {
    if (index < 0 || index >= CORNERS) {
        throw std::runtime_error("Bledna wartosc indeksu prostokata");
    } 
    return Corners[index];
}

/******************************************************************************
 |  Funktor prostokata.                                                       |
 |  Argumenty:                                                                |
 |      index - index prostokata.                                             |
 |  Zwraca:                                                                   |
 |      Wartosc prostokata w danym miejscu tablicy.                           |
 */
Vector & Rectangle::operator[](int index) {
    return const_cast <Vector &> (const_cast <const Rectangle *> (this)->operator[](index));
}

/*****************************************************************************************************************
 | Metoda klasy Rectangle realizaujca dzialanie translacji prostokata o wybrany wektor.                          |
 | Warunki wstepne:                                                                                              |
 |   vector - do poprawnego dzialania wektor musi byc poprawnie zainicjowany wartosciami wspolrzednych wektora.  |
 | Warunki koncowe:                                                                                              |
 |   brak.                                                                                                       |
 | Argumenty:                                                                                                    |
 |   vector - wektor translacji.                                                                                 |
 | Zwraca:                                                                                                       |
 |   Prostokat o zmienionym polozeniu za sprawa operacji translacji o wektor.                                    |
 */
Rectangle Rectangle::Translate_rec(Vector const vector){
    for (int i=0; i<4; i++){
        this->Corners[i] =this->Corners[i] + vector;
    }
   return *this;
}

/*****************************************************************************************************
 | Metoda klasy Rectangle realizaujca dzialanie obrotu prostokata o wybrany kat, wybrana ilosc razy. |   
 | Warunki wstepne:                                                                                  |
 |   multiplier - wartosc musi miesicic sie w zakresie wlasciwym int.                                |
 |   angle - wartosc musi byc typu double                                                            |
 | Warunki koncowe:                                                                                  |
 |   brak.                                                                                           |
 | Argumenty:                                                                                        |
 |   multiplier - ile razy ma zostac wykonany obrot                                                  |
 |   angle - kat o jaki ma zostac obrocony prostokat                                                 |
 | Zwraca:                                                                                           |
 |  Prostokat o zmienionym polozeniu za sprawa operacji obrotu.                                      |
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

/*********************************************************************************************************************
 | Funkcja wykonujaca operacje przeciazenia operatora <<.                                                            |
 | Funkcja sluzy do wypisywania na wskazany strumien wyjsciowy, wartosci wspolrzednych wierzcholka prostokata.       |
 | Warunki wstepne:                                                                                                  |
 |  & Strm- wybrany strumien musi byc typu ostream.                                                                  |
 |  & Rc - do poprawnego dzialania prostokat musi byc poprawnie zainicjowany wartosciami wspolrzednych wierzcholkow. |
 | Warunki koncowe:                                                                                                  |
 |   brak.                                                                                                           |
 | Argumenty:                                                                                                        |
 |   & Strm - Referencja do strumienia typu ostream, na ktory maja zostac wypisane wspolrzedne wektora.              |
 |   & Rc - Referencja do prostokata, ktorego wspolrzedne wierzcholkow maja zostac wpisane na wskazany strumien.     |
 | Zwraca:                                                                                                           |
 |   Wypisane wspolrzende wksazanego prostokata, w odpowiedniej formie na wskazane wyjscie.                          |
 */
std::ostream & operator << (std::ostream & Out, const Rectangle & Rc){
    for (int i=0; i<4;i++)
        Out << Rc[i] << std::endl;
    return Out;
}

/***********************************************************************************************************************
 | Funkcja wykonujaca operacje przeciazenia operatora >>.                                                               |
 | Funkcja sluzy do wprowadzania wartosci wspolrzednych wierzcholkow prostokata ze wskazanego strumienia wejsciowego.   |
 | Warunki wstepne:                                                                                                     |
 |   & Strm- wybrany strumien musi byc typu istream.                                                                    |
 |   & Rc - do poprawnego dzialania prostokat musi byc wczesniej zainicjowany.                                          |
 | Warunki koncowe:                                                                                                     |
 |   brak;                                                                                                              |
 | Argumenty:                                                                                                           |
 |   & Strm - Referencja do strumienia typu istream, z ktorego maja zostac wczytane wspolrzedne wierzcholkow prostokata.|
 |   & Vec - Referencja do prostokata, do ktorego maja zostac wpisane podane wspolrzedne weirzcholkow.                  |
 | Zwraca:                                                                                                              |
 |   Wczytany obiekt- prostokat.                                                                                        |
 */
std::istream & operator >> (std::istream & In,Rectangle & Rc){
    for (int i=0; i<CORNERS;i++){
        In >> Rc[i];
    }
    return In;
}

/************************************************************************************************************
 | Metoda klasy Rectangle realizujaca zapis wartosci wspolrzednych wierzcholkow do pliku.                   | 
 | Warunki wstepne:                                                                                         |
 |   this - Do poprawnego dzialania prostokat musi byc zainicjowany wartosciami wzpolrzednych weirzcholkow  |
 |   *sNazwaPliku - do poprawnego dzialania wybrany napis stanowiacy nazwe musi być zgodny z nazwa          |
 |   pliku wskazanego programowi GNUplot.                                                                   |
 | Warunki koncowe:                                                                                         |
 |   brak;                                                                                                  |
 | Argumenty:                                                                                               |
 |    this - prostokat do zapisu.                                                                           |
 |   *sNazwaPliku - wskaznik na napis stanowiacy nazwe pliku wyjsciowego.                                   |
 | Zwraca:                                                                                                  |
 |   brak.                                                                                                  |
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

/***************************************************************************************************
 | Metoda klasy Rectangle wykonujaca operacje wyznaczenia dlugosic bokow prostokata i sprawdzenia, |
 |   czy przeciwlegle boki sa sobie rowne.                                                         |
 | Warunki wstepne:                                                                                |
 |   this - Do poprawnego dzialania prostokat musi byc zainicjowany wartosciami                    |
 |          reprezentujacym wzpolrzedne weirzcholkow                                               |
 | Warunki koncowe:                                                                                |
 |   brak;                                                                                         |
 | Argumenty:                                                                                      |
 |   this - prostokat, ktory ma zostac poddany sprawdzeniu.                                        |
 | Zwraca:                                                                                         |
 |   Wypisuje na standardowe wyjscie dane o bokach prostokata.                                     |
 */

void Rectangle::Is_it_rec(){
    double a,b,c,d;
    a = sqrt(pow(this->Corners[1][0]-this->Corners[0][0],2)+pow(this->Corners[1][1]-this->Corners[0][1],2)); 
    b = sqrt(pow(this->Corners[2][0]-this->Corners[1][0],2)+pow(this->Corners[2][1]-this->Corners[1][1],2));
    c = sqrt(pow(this->Corners[3][0]-this->Corners[2][0],2)+pow(this->Corners[3][1]-this->Corners[2][1],2));
    d = sqrt(pow(this->Corners[0][0]-this->Corners[3][0],2)+pow(this->Corners[0][1]-this->Corners[3][1],2));
    std::cout << std::endl;
    if(a-c < MAX_VALUE_DIFF && c-a < MAX_VALUE_DIFF){
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
    std::cout << "Dlugosc pierwszego boku: " << std::fixed << std::setprecision(10) << a << std::endl;
    std::cout << "Dlugosc drugiego boku: " << std::fixed << std::setprecision(10) << c << std::endl;
    std::cout << std::endl;
    
    if(b-d < MAX_VALUE_DIFF && d-b < MAX_VALUE_DIFF){
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
    std::cout << "Dlugosc pierwszego boku: " << std::fixed << std::setprecision(10) << b << std::endl;
    std::cout << "Dlugosc drugiego boku: " << std::fixed << std::setprecision(10) << d << std::endl;
    std::cout << std::endl;
}

