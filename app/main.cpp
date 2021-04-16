// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "exampleConfig.h"
#include "example.h"
#include "vector.hh"
#include "matrix.hh"
#include "rectangle.hh"
#include "../include/lacze_do_gnuplota.hh"

int main() {
    std::cout << "Project Rotation 2D based on C++ Boiler Plate v"
              << PROJECT_VERSION_MAJOR /*duże zmiany, najczęściej brak kompatybilności wstecz */
              << "."
              << PROJECT_VERSION_MINOR /* istotne zmiany */
              << "."
              << PROJECT_VERSION_PATCH /* naprawianie bugów */
              << "."
              << PROJECT_VERSION_TWEAK /* zmiany estetyczne itd. */
              << std::endl; 

    double X[]={2,2}, Y[]={50,2}, Z[]={50,35}, U[]={2,35}, Vt[]={15,30}, angle, multiplier; /* Inicjalizacja tablic z wartosciami wierzcholkow prostokata */
    Vector A(X),B(Y),C(Z),D(U),T(Vt),T_vector;
    char Option;
    Rectangle Rec(A,B,C,D); /* Inicjalizacja prostokata wspolrzednymi wierzcholkow */
    PzG::LaczeDoGNUPlota Link;  /* Ta zmienna jest potrzebna do wizualizacji rysunku prostokata */
    /* 
    *   Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat" 
    *   Ponizsze metody powoduja, ze dane z pliku beda wizualizowane na dwa sposoby:
    *   1.Rysowane jako linia ciagla o grubosci 2 piksele
    */
    Link.DodajNazwePliku("prostokat.dat",PzG::RR_Ciagly,2);
    /*
    *   2. Rysowane jako zbior punktow reprezentowanych przez kwadraty,
    *    których połowa długości boku wynosi 2.
    */
    Link.DodajNazwePliku("prostokat.dat",PzG::RR_Punktowy,2);
    /* 
    *  Ustawienie trybu rysowania 2D, tzn. rysowany zbiór punktów
    *   znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
    *   jako wspolrzedne punktow podajemy tylko x,y.
    */
    Link.ZmienTrybRys(PzG::TR_2D);

    try{
        Rec.Write_rec_to_file("prostokat.dat");
        Link.Rysuj();
        std::cout << "Poczatkowe wspolrzedne prostokata: " << std::endl;
        Rec.Is_it_rec();
        std::cout << "menu:" << std::endl
                  << "o - obrot prostokata o zadany kat " << std::endl
                  << "p - przesuniecie prostokata o zadany wektor " << std::endl
                  << "w - wyswietlenie wspolrzednych wierzcholkow " << std::endl
                  << "m - wyswietl menu" << std::endl
                  << "k - koniec dzialania programu" << std::endl;
        while (Option != 'k')
        {   
            std::cout << "Twoj wybor? (m - menu) > ";
            std::cin >> Option;
            switch(Option){
                case 'o':
                    std::cout << "Podaj wartosc kata obrotu w stopniach > ";
                    std::cin >> angle;
                    if(std::cin.fail()){
                        throw std::runtime_error("Podano wyrazenie nie bedace typu double");
                        break;
                    }    
                    std::cout << "Ile razy operacja obrotu ma byc powtorzona > ";
                    std::cin >> multiplier;
                    if(std::cin.fail()){
                        throw std::runtime_error("Podano wyrazenie nie bedace typu double");
                        break;
                    }
                    std::cout << "Czy obrot ma byc animowany? T/N? (Operacja wykonywana bardzo szybko dla duzej ilosci powtorzen) > ";
                    std::cin >> Option;
                    switch(Option){
                        case 'T':
                        for (int i=0; i< multiplier;i++){
                            for(int j=0;j < FRAMES; j++){
                                Rec.Rotate_rec(multiplier,angle/FRAMES);
                                Rec.Write_rec_to_file("prostokat.dat");
                                usleep(4000);
                                Link.Rysuj();
                                usleep(4000);
                            }
                        }
                          
                            Rec.Is_it_rec();
                        break;

                        case 'N':
                            Rec.Rotate_rec(multiplier,angle); /* Wywolanie metody obracajacej prostokat wybrana ilosc razy o wybrany kat w stopniach */
                            Rec.Write_rec_to_file("prostokat.dat");
                            Rec.Is_it_rec();
                            Link.Rysuj();
                        break;

                        default:
                            std::cout << ":/ Opcja niezdefiniowana" << std::endl; 
                        break;
                    }
                break;

                case 'p':
                    std::cout << "Wprowadz wspolrzedne wektora translacji w postaci liczb x i y > ";
                    std::cin >> T_vector;
                    if(std::cin.fail()){
                        throw std::runtime_error("Podano wyrazenie nie bedace typu double");
                        break;
                    }
                    std::cout << "Czy translacja ma byc animowana? T/N? > ";
                    std::cin >> Option;
                    switch(Option){
                        case 'T':
                            T_vector/FRAMES;
                            for(int i=0;i<FRAMES;i++){
                                Rec.Translate_rec(T_vector/FRAMES);
                                Rec.Write_rec_to_file("prostokat.dat");
                                usleep(4000);
                                Link.Rysuj();
                                usleep(4000); 
                            }
                            Rec.Is_it_rec();
                        break;

                        case 'N':
                            Rec.Translate_rec(T_vector);
                            Rec.Write_rec_to_file("prostokat.dat");
                            Rec.Is_it_rec();
                            Link.Rysuj();
                        break;

                        default:
                            std::cout << ":/ Opcja niezdefiniowana" << std::endl; 
                        break;
                    }
                break;

                case 'w':
                    std::cout << "Aktualne wspolrzedne prostokata: " << std::endl;
                    std::cout << Rec;
                break;

                case 'm':
                     std::cout << "menu:" << std::endl
                               << "o - obrot prostokata o zadany kat " << std::endl
                               << "p - przesuniecie prostokata o zadany wektor " << std::endl
                               << "w - wyswietlenie wspolrzednych wierzcholkow " << std::endl
                               << "m - wyswietl menu" << std::endl
                               << "k - koniec dzialania programu" << std::endl;
                break;

                case 'k':
                    std::cout << ":) Konczenie pracy programu" << std::endl;
                break;

                default:
                    std::cout << ":/ Opcja niezdefiniowana" << std::endl;
            }
        }
    }
    catch (std::runtime_error & e){
    std::cout << "Wystapil blad!"<< std::endl << e.what() << std::endl;
    exit(1);
    }
    return 0;
}
/*
   //-------------------------------------------------------
   //  Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"
   //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
   //  na dwa sposoby:
   //   1. Rysowane jako linia ciagl o grubosci 2 piksele
   //
  Lacze.DodajNazwePliku("../datasets/prostokat.dat",PzG::RR_Ciagly,2);
   //
   //   2. Rysowane jako zbior punktow reprezentowanych przez kwadraty,
   //      których połowa długości boku wynosi 2.
   //
  Lacze.DodajNazwePliku("../datasets/prostokat.dat",PzG::RR_Punktowy,2);
   //
   //  Ustawienie trybu rysowania 2D, tzn. rysowany zbiór punktów
   //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
   //  jako wspolrzedne punktow podajemy tylko x,y.
   //
  Lacze.ZmienTrybRys(PzG::TR_2D);

  PrzykladZapisuWspolrzednychDoStrumienia(std::cout,0);
  if (!PrzykladZapisuWspolrzednychDoPliku("../datasets/prostokat.dat",0)) return 1;
  Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
  std::cout << "Naciśnij ENTER, aby kontynuowac" << std::endl;
  std::cin.ignore(100000,'\n');
   //----------------------------------------------------------
   // Ponownie wypisuje wspolrzedne i rysuje prostokąt w innym miejscu.
   //
  PrzykladZapisuWspolrzednychDoStrumienia(std::cout,50);
  if (!PrzykladZapisuWspolrzednychDoPliku("../datasets/prostokat.dat",50)) return 1;
  Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
  std::cout << "Naciśnij ENTER, aby kontynuowac" << std::endl;
  std::cin.ignore(100000,'\n');

  // Z bazy projektu-wydmuszki Boiler Plate C++:
  // Bring in the dummy class from the example source,
  // just to show that it is accessible from main.cpp.
  Dummy d = Dummy();
  return d.doSomething() ? 0 : -1;
}*/




  // std::system("cat ../LICENSE");
  // do zadania Rotacja 2D
 /* std::cout << "Vector:" << std::endl;
  Vector tmpV1 = Vector();
  std::cout << "Vector - konstruktor bezparametryczny:\n" << tmpV1 << std::endl;
  double argumentsV[] = {1.0, 2.0};
  Vector tmpV2 = Vector(argumentsV);
  std::cout << "Vector - konstruktor parametryczny:\n" << tmpV2 << std::endl;

  std::cout << "Matrix:" << std::endl;
  Matrix tmpM1 = Matrix();
  std::cout << "Matrix - konstruktor bezparametryczny:\n" << tmpM1 << std::endl;
  double argumentsM[][SIZE] = {{1.0, 2.0},{3.0, 4.0}};
  Matrix tmpM2 = Matrix(argumentsM);
  std::cout << "Matrix - konstruktor parametryczny:\n" << tmpM2 << std::end
  */



    //    std::cout << "Wspolrzedne wejsciowe wierzcholkow prostokata to: " << std::endl;
    //    std::cout << Rec;  /* Wypisanie wartosci wspolrzednych wierzcholkow prostokata na standardowe wyjscie */
    //    Rec.Is_it_rec(); /* Wywolanie metody sprawdzajacej zgodnosc dlugosci bokow prostokatow */
    //    Rec.Write_rec_to_file("prostokat.dat"); /* Zapisanie wartosci wierzcholkow prostokata do pliku, w celu pozniejszego wyrysowania ich przez GNUplot */
    //    Link.Rysuj(); /* Inicjalizacja rysowania prostokata w programie GNUplot */
    //   std::cout << "Naciśnij ENTER, aby kontynuoac";
    //    std::cin.ignore(100000,'\n');
    //    
    //    //Rec.Rotate_rec(489000,157); /* Wywolanie metody obracajacej prostokat 489000 razy o kat 157 stopni */
    //    Rec.Animated_rotation(1,30,"prostokat.dat",Link);
    //    std::cout << Rec;
    //   Rec.Is_it_rec();
    //    Rec.Write_rec_to_file("prostokat.dat");
    //    Link.Rysuj();
    //   std::cout << "Naciśnij ENTER, aby kontynuoac";
    //    std::cin.ignore(100000,'\n');
    //    Rec.Translate_rec(T); /* Wywolanie metody translacji prostokata o wektor T */
    //    std::cout << Rec;
    //    Rec.Is_it_rec();
    //    Rec.Write_rec_to_file("prostokat.dat");
    //    Link.Rysuj();
    //  std::cout << "Naciśnij ENTER, aby kontynuoac";
    //   std::cin.ignore(100000,'\n');