/* Przygotowal: Szymon Sobczak nr 259275 */

/* Executables must have the following defined if the library contains
doctest definitions. For builds with this disabled, e.g. code shipped to
users, this can be left out. */
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <unistd.h>

#include "exampleConfig.h"
#include "vector.hh"
#include "matrix.hh"
#include "rectangle.hh"
#include "../include/lacze_do_gnuplota.hh"

int main() {
    double X[]={2,2}, Y[]={50,2}, Z[]={50,35}, U[]={2,35}, Vt[]={15,30}, angle, multiplier; /* Inicjalizacja tablic wartosciami wierzcholkow prostokata oraz zmiennych potrzebnych w programie */
    Vector A(X),B(Y),C(Z),D(U),T(Vt),T_vector;    /* Inicjalizacja wektorow reprezentujacych wspolrzedne wierzcholkow prostokata i wektora translacji */
    Rectangle Rec(A,B,C,D);                       /* Inicjalizacja prostokata za pomoca wektorow */
    PzG::LaczeDoGNUPlota Link;                    /* Zmienna potrzebna do wizualizacji rysunku prostokata */
    char Option;

    /********************************************************************************
     |   Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"           |
     |  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane na dwa sposoby:|
     |  1.Rysowane jako linia ciagla o grubosci 2 piksele                           |
    */
    Link.DodajNazwePliku("../datasets/prostokat.dat",PzG::RR_Ciagly,2);

    /*******************************************************************************
     |   2. Rysowane jako zbior punktow reprezentowanych przez kwadraty,           |
     |   których połowa długości boku wynosi 2.                                    |
    */
    Link.DodajNazwePliku("../datasets/prostokat.dat",PzG::RR_Punktowy,2);

    /******************************************************************************* 
     | Ustawienie trybu rysowania 2D, tzn. rysowany zbiór punktów                  |
     |   znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj              |
     |  jako wspolrzedne punktow podajemy tylko x,y.                               |
    */
    Link.ZmienTrybRys(PzG::TR_2D);

    try{
        Rec.Write_rec_to_file("../datasets/prostokat.dat"); /* Wyswietlenie w GNUplot stanu poczatkowego prostokata */
        Link.Rysuj();
        std::cout << "Poczatkowe wspolrzedne prostokata: " << std::endl;
        Rec.Is_it_rec(); 
        std::cout << "Menu wyboru opcji:" << std::endl
                  << "\to - obrot prostokata o zadany kat " << std::endl
                  << "\tp - przesuniecie prostokata o zadany wektor " << std::endl
                  << "\tw - wyswietlenie wspolrzednych wierzcholkow " << std::endl
                  << "\tm - wyswietl menu" << std::endl
                  << "\tk - koniec dzialania programu" << std::endl;
        while (Option != 'k'){ /* Glowna petla menu, dzialajaca do czasu wybrania opcji zakonczenia - k */
            std::cout << "Twoj wybor? (m - menu) > ";
            std::cin >> Option;
            switch(Option){
                case 'o': /* Opcja obrotu prostokata */
                    std::cout << "Podaj wartosc kata obrotu w stopniach > "; /* Okreslenie parametrow obrotu prostokata- kata i ilosci obrotow */
                    std::cin >> angle;
                    if(std::cin.fail())
                        throw std::runtime_error("Podano wyrazenie nie bedace typu double");
                    std::cout << "Ile razy operacja obrotu ma byc powtorzona > ";
                    std::cin >> multiplier;
                    if(std::cin.fail())
                        throw std::runtime_error("Podano wyrazenie nie bedace typu double");
                    std::cout << "Czy obrot ma byc animowany? T/N? (Operacja wykonywana bardzo szybko dla duzej ilosci powtorzen) > ";
                    std::cin >> Option;
                    switch(Option){
                        case 'T':  /* Gdy uzytkownik zdecyduje sie na animacje obrotu */
                            for (int i=0; i< multiplier;i++){
                                for(int j=0;j < FRAMES; j++){
                                    Rec.Rotate_rec(1,angle/FRAMES); /* Wywolanie metody obracajacej prostokat raz, o ulamek wybranego kata, w celu nadania wrazenia ruchu */
                                    Rec.Write_rec_to_file("../datasets/prostokat.dat");
                                    usleep(4000);
                                    Link.Rysuj();
                                    usleep(4000);
                                }
                            }
                            Rec.Is_it_rec();
                        break;

                        case 'N': /* Gdy uzytkownik nie zdecyduje sie na animacje obrotu */
                            Rec.Rotate_rec(multiplier,angle); /* Wywolanie metody obracajacej prostokat wybrana ilosc razy o wybrany kat w stopniach */
                            Rec.Write_rec_to_file("../datasets/prostokat.dat");
                            Rec.Is_it_rec();
                            Link.Rysuj();
                        break;

                        default: /*Dzialanie,gdy opcja podmenu nie bedzie zdefiniowana */
                            std::cout << ":/ Opcja niezdefiniowana" << std::endl; 
                        break;
                    }
                break;

                case 'p': /* Opcja translacji o wektor */
                    std::cout << "Wprowadz wspolrzedne wektora translacji w postaci liczb x i y > ";
                    std::cin >> T_vector;
                    std::cout << "Czy translacja ma byc animowana? T/N? > ";
                    std::cin >> Option;
                    switch(Option){
                        case 'T':  /* Gdy uzytkownik zdecyduje sie na animacje translacji */
                            T_vector/FRAMES;
                            for(int i=0;i<FRAMES;i++){
                                Rec.Translate_rec(T_vector/FRAMES);/* Wywolanie metody przesuwajacej prostokat raz, o ulamek wybranego kata, w celu nadania wrazenia ruchu */
                                Rec.Write_rec_to_file("../datasets/prostokat.dat");
                                usleep(4000);
                                Link.Rysuj();
                                usleep(4000); 
                            }
                            Rec.Is_it_rec();
                        break;

                        case 'N': /* Gdy uzytkownik nie zdecyduje sie na animacje translacji */
                            Rec.Translate_rec(T_vector);
                            Rec.Write_rec_to_file("../datasets/prostokat.dat");
                            Rec.Is_it_rec();
                            Link.Rysuj();
                        break;

                        default: /*Dzialanie,gdy opcja podmenu nie bedzie zdefiniowana */
                            std::cout << ":/ Opcja niezdefiniowana" << std::endl; 
                        break;
                    }
                break;

                case 'w': /* Opcja wyswietlajaca wspolrzedne prsotokata */
                    std::cout << "Aktualne wspolrzedne prostokata: " << std::endl;
                    std::cout << Rec;
                break;

                case 'm': /* Opcja wyswietlajaca dostepne w menu opcje */
                    std::cout << "Menu wyboru opcji:" << std::endl
                              << "\to - obrot prostokata o zadany kat " << std::endl
                              << "\tp - przesuniecie prostokata o zadany wektor " << std::endl
                              << "\tw - wyswietlenie wspolrzednych wierzcholkow " << std::endl
                              << "\tm - wyswietl menu" << std::endl
                              << "\tk - koniec dzialania programu" << std::endl;
                break;

                case 'k': /* Opcja konczaca program */
                    std::cout << ":) Konczenie pracy programu" << std::endl;
                break;

                default: /* dzialanie, gdy podana opcja nie bedzie uprzednio zdefiniowana */
                    std::cout << ":/ Opcja niezdefiniowana" << std::endl;
            }
        }
    }
    catch (std::runtime_error & e){ /* W wyniku wyrzucenia bledu program poinformuje o tym i zakonczy swoje dzialanie */
        std::cout << ":O Wystapil blad!"<< std::endl << e.what() << std::endl;
        exit(1);
    }
    return 0;
} 
