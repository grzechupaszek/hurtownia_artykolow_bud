#include <iostream>
#include <string>

using namespace std;

class Towar{
    int id_towaru = NULL;
    string nazwa;
    float cena;
    int ilosc;
};

class Kient{
    int id_klienta = NULL;
    string imie;
    string nazwisko;
    string haslo;
    bool aktywny;
    int wybierz_platnosc();
    Towar wybierz_towar();
};

class Admin{
    int id_admina = NULL;
    void akt_stanu_magazynu();
};

class Magazynier{
    int id_magazyniera = NULL;
    void odebranie_towaru(Towar[]);
    Towar raport(Towar[]);
};

class Dostawca{
    int id_dostawcy = NULL;
    Towar dostawa(Towar[]);
};

class Zamowienie{
    int id_zamowienia = NULL;
    int id_klienta;
    int id_towaru;
    float wartosc;
    float wartosc_zamowienia;
};

