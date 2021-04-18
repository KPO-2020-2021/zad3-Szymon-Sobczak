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
 | Klasa posiada prywatne pole bedace tablica- zbiorem wspolrzednych wekotra "size".    |
 | Klasa posiada publiczny interfejs pozwalajacy na wprowazdanie, zmiane i odczytywanie |
 |   danych o wspolrzednych wektora.                                                    |
 | Klasa zawiera publiczne przeciazenia operatorow indeksujacych opowiedzialnych za     |
 |   wprowadzanie i odczytywanie wspolrzendych wektora oraz przeciazenie operatora      |
 |   dodawania, odejmowania, mnozenia, dzielenia dwoch wektorow.                        |
 */

class Vector {
private:
    double size[SIZE];   /* Tablica wektora */
public:
    Vector(); /* Bezparametryczny konstruktor klasy */
    Vector(double [SIZE]); /* Konstruktor klasy z parametrem */
    Vector operator + (const Vector &v);    /* operator dodawania dwoch wektorow */
    Vector operator - (const Vector &v);    /* operator odejmowania dwoch wektorow */
    Vector operator * (const double &tmp);  /* operator mnozenia wektora i liczby typu double */
    Vector operator / (const double &tmp);  /* operator dzielenia wektora i liczby typu double */
    const double & operator [] (int index) const; /* Przeciazenia operatora indeksujacego */
    double & operator [] (int index);
};

std::ostream & operator << (std::ostream &out, Vector const &tmp); /* Przeciazenie operatora >> sluzace wyswietlaniu wektora */ 
std::istream & operator >> (std::istream &in, Vector &tmp); /* Przeciazenie operatora << sluzace wczytywaniu wartosci do wektora */

#endif
