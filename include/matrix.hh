#ifndef MATRIX_HH
#define MATRIX_HH
#pragma once

#include "size.hh"
#include "vector.hh"
#include <iostream>
#include <cstdlib>
#include <cmath>

/************************************************************************************
 | Klasa modelujaca w programie pojecie macierzy kwadratowej.                        |
 | Klasa posiada prywatne pole "_Matrix", stanowi zbior wartosci macierzy rotacji.  |
 |  Jest to tablica dwuwymiarowa dla warosci typu double.                           |
 | Klasa posiada publiczny interfejs pozwalajacy na wprowazdanie,                   |
 |  zmiane i odczytywanie danych z macierzy rotacji.                                |
 | Klasa zawiera publiczne przeciazenia operatorow funkcyjnych opowiedzialnych za   |
 |  wprowadzanie i odczytywanie wartosci z macierzy rotacji, oraz przeciazenie      |
 |  mnozenia macierzy razy wetkor.                                                  |
 | Klasa posiada metode inicjujaca macierz wartosciami funkcji trygonometrycznych   |
 |  dla zadanego konta obrotu.                                                      |
 */

class Matrix {
private:
    double value[SIZE][SIZE];               // Wartosci macierzy
public:
    Matrix(double [SIZE][SIZE]);            // Konstruktor klasy
    Matrix();                               // Konstruktor klasy
    Vector operator * (Vector tmp);           // Operator mnożenia przez wektor
    Matrix operator + (Matrix tmp);
    Matrix Fill_matrix(double angle);
    double & operator () (unsigned int row, unsigned int column);
    const double & operator () (unsigned int row, unsigned int column) const;
};

std::istream & operator>>(std::istream &in, Matrix &mat);
std::ostream & operator<<(std::ostream &out, Matrix const &mat);

#endif

