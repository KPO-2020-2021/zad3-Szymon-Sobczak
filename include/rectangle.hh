#ifndef PROSTOKAT_HH
#define PROSTOKAT_HH

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "vector.hh"
#include "matrix.hh"
#include "lacze_do_gnuplota.hh"



/************************************************************************************************************************
 | Klasa modelujaca w programie pojecie prostokata, ktorego wierzcholki sa wyrazone za pomoca wektorow.                  |
 | Klasa posiada prywatne pole bedace tablica wektoror, opisujace wektorowo pozycje wierzcholkow prosotkata.             |
 | Klasa posiada publiczny konstrukotr domyśly oraz konstruktor pozwalajacy na inicjowanie prostokata za pomoca wektorow.|
 | Klasa posiada publiczne metody pozwalajace na:                                                                        |
 |   - sprawdzenie czy prostokat posiada rowne przeciwlegle boki i wyswietlajacy informacje o tym na standarowe wyjscie, |
 |   - translacje prostokata o zadany wektor,                                                                            |
 |   - obrot prostokata wokol srodka ukladu wspolrzednych o zadany kat, wybrana ilosc razy.                              |
*/

class Rectangle {
    friend std::ostream & operator << (std::ostream & Strm, const Rectangle & Rc);
    friend std::istream & operator >> (std::istream & Strm, Rectangle & Rc);
    private:  
        Vector Corners[4];
    public:   
        Rectangle() = default;// {Vector Vec; Corners[0]=Corners[1]=Corners[2]=Corners[3]=Vec;};
        Rectangle(Vector CornerA, Vector CornerB, Vector CornerC, Vector CornerD);
        Rectangle Translate_rec(Vector const vector);
        Rectangle Rotate_rec(int const multiplier, double const angle);
        bool Collision_detection(Rectangle Rec2);
        void Is_it_rec();
        void Write_rec_to_file(const char *sNazwaPliku) const;
};

std::ostream & operator << (std::ostream & Strm, const Rectangle & Rc);
std::istream & operator >> (std::ostream & Strm, Rectangle & Rc);

#endif
