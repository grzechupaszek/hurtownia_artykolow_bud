#include <iostream>
#include <string>
#include <sqlite3.h>
#ifdef _WIN32
#include <windows.h>
#define CLEAR_CMD "cls"
#else
#include <unistd.h>
#define CLEAR_CMD "clear"
#endif

using namespace std;

// Funkcja inicjalizująca bazę danych i tworząca tabelę użytkowników, jeśli jej nie ma
bool initDatabase(sqlite3*& db) {
    int rc = sqlite3_open("login.db", &db);
    if (rc != SQLITE_OK) {
        cerr << "Nie można otworzyć bazy danych: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    const char* sql = "CREATE TABLE IF NOT EXISTS users ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "username TEXT NOT NULL UNIQUE, "
                      "password TEXT NOT NULL);";

    char* errMsg = nullptr;
    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Błąd tworzenia tabeli: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

// Sprawdza czy użytkownik o danej nazwie istnieje
bool userExists(sqlite3* db, const string& username) {
    const char* sql = "SELECT id FROM users WHERE username = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    bool exists = (rc == SQLITE_ROW);

    sqlite3_finalize(stmt);
    return exists;
}

// Dodaje nowego użytkownika
bool addUser(sqlite3* db, const string& username, const string& password) {
    if (userExists(db, username)) {
        cout << "Użytkownik o takiej nazwie już istnieje!" << endl;
        return false;
    }

    const char* sql = "INSERT INTO users (username, password) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Błąd przygotowania zapytania: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "Błąd dodawania użytkownika: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    cout << "Użytkownik zarejestrowany pomyślnie!" << endl;
    return true;
}

// Logowanie użytkownika
bool loginUser(sqlite3* db, const string& username, const string& password) {
    const char* sql = "SELECT id FROM users WHERE username = ? AND password = ?;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    bool success = (rc == SQLITE_ROW);

    sqlite3_finalize(stmt);
    return success;
}

int main() {
    sqlite3* db = nullptr;
    if (!initDatabase(db)) {
        return 1;
    }

    // Dodajmy domyślnego admina, jeśli go nie ma (login: admin, hasło: admin)
    if (!userExists(db, "admin")) {
        addUser(db, "admin", "admin");
    }

    cout << "Aplikacja hurtowni budowlanej\n";
    int action = 0;
    do {
        cout << "\nWybierz akcje:\n1. Zaloguj\n2. Zarejestruj\n3. Wyjdz\n";
        cin >> action;

        if (action == 3) {
            cout << "Zamykanie aplikacji..." << endl;
            break;
        }

        string login, haslo;
        cout << "Podaj login: ";
        cin >> login;
        cout << "Podaj haslo: ";
        cin >> haslo;

        if (action == 1) {
            // Logowanie
            if (loginUser(db, login, haslo)) {
                // Po udanym logowaniu
                system(CLEAR_CMD);
                cout<<"Aplikacja hurtowni budowlanej\n";
                cout<<"Nazwa użytkownika: "<<login<<"\n";

                if (login == "admin") {
                    // Menu dla admina
                    int choice = -1;
                    do {
                        cout<<"0. Wyloguj\n1. Zaktualizuj stan magazynu\n2. Dodaj nowy produkt\n3. Złóż zamówienie\n";
                        cin>>choice;
                    } while(choice != 0);
                    cout << "Wylogowano.\n";
                } else {
                    // Menu dla zwykłego użytkownika
                    int choice = -1;
                    do {
                        cout << "0. Wyloguj\n1. Przeglądaj produkty\n2. Złóż zamówienie\n";
                        cin >> choice;
                    } while(choice != 0);
                    cout << "Wylogowano.\n";
                }

            } else {
                cout << "Błąd logowania. Sprawdź login/hasło.\n";
            }

        } else if (action == 2) {
            // Rejestracja
            addUser(db, login, haslo);
        } else {
            cout << "Nieprawidłowy wybór.\n";
        }

    } while (action != 3);

    sqlite3_close(db);
    return 0;
}
