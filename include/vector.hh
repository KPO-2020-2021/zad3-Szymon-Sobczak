#ifndef VECTOR_HH
#define VECTOR_HH
#pragma once

#include "size.hh"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>

/****************************************************************************************
 | Klasa modelujaca w programie pojecie wektora.                                        |
 | Klasa posiada prywatne pole bedace tablica- zbiorem wspolrzednych wekotra "_Coord".  |
 | Klasa posiada publiczny interfejs pozwalajacy na wprowazdanie, zmiane i odczytywanie |
 |   danych o wspolrzednych wektora.                                                    |
 | Klasa zawiera publiczne przeciazenia operatorow indeksujacych opowiedzialnych za     |
 |   wprowadzanie i odczytywanie wspolrzendych wektora.                                 |
 | oraz przeciazenie operatora dodawania dwoch wektorow.                                |
 */

class Vector {
private:
    double size[SIZE];     //Tablica wektora
public:
    Vector();
    Vector(double [SIZE]);
    Vector operator + (const Vector &v);
    Vector operator - (const Vector &v);
    Vector operator * (const double &tmp);
    Vector operator / (const double &tmp);
    const double & operator [] (int index) const;
    double & operator [] (int index);
};

std::ostream & operator << (std::ostream &out, Vector const &tmp);
std::istream & operator >> (std::istream &in, Vector &tmp);

#endif
