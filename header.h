#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Towar{
    int id_towaru = NULL;
    string nazwa;
    float cena;
    int ilosc;
};

class Klient{
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

//mikolaj mozeby

class ZarzadzanieKontem{
    void zaloz_konto();
    Klient utworz_klienta();
    string zmien_haslo();

};
void ZarzadzanieKontem::zaloz_konto(){
    vector<string> login, haslo, haslo1;
    cout<<"Podaj login: ";
    cin>>login;
    if (/*nie ma w bazie danych loginu to przejdz dalej*/)
        continue;
    else (/*wyswietl error wroc do poczatku tutaj petle robimy*/)
    {/*dochodzi do sigmy sigma boy sigma boy sigma boy*/}
    for(;;){
        cout<<"podaj haslo: "<<endl;
        cin>>haslo;
        cout<<"powtorz haslo: "<<endl;
        cin>> haslo1;
        if (haslo==haslo1){//zapisz do ppliku nowego uzytkownika}
        if (haslo!=haslo1){cout<<"podales zle drugie haslo debilu";}
        else continue;
    }
}
class Platnosc{
    float kwota;
};

class Gotowka{
    float gotowka;
};

class Karta{
    long numer_karty;
    string typ_karty;
    int data_wygasniecia;
};

class IPlatnosc{
    bool autoryzacja;
};

//komentarzgdgdgdfd//komentarz