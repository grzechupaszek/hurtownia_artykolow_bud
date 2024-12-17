#include <iostream>
#include <string>


using namespace std;
//logowanie do systemu


int main(){
    string login, haslo;

    cout<<"Aplikacja hurtowni budowlanej\n";
    cout<<"Podaj login: ";
    cin>>login;
    cout<<"Podaj haslo: ";
    cin>>haslo;

    if(login == "admin" && haslo == "admin"){
        //wyjątek na logowanie dla administratora

        system("clear");

        cout<<"Aplikacja hurtowni budowlanej\n";
        cout<<"Nazwa użytkownika: "<<login<<"\n";

        int choice = -1;

        do{
            cout<<"0. Wyloguj\n1. Zaktualizuj stan magazynu\n2. Dodaj nowy produkt\n3. Złóż zamówienie\n";
            cin>>choice;
        }while(choice != 0);



    }else{
        //logowanie pozostałych użytkowaników
        //logowanie();
    }
    
    return 0;

}





