#ifndef VECTOR_HH
#define VECTOR_HH
#pragma once

#include "size.hh"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>

class Vector {
    friend std::ostream & operator << (std::ostream &out, Vector const &tmp);
    friend std::istream & operator >> (std::istream &in, Vector &tmp);
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
