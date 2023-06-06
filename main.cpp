#include "Mst.h"
#include "Sp.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    int select;
    bool exit = true;
    Mst mst;
    Sp sp;

    while (exit) {
        system("cls");
        cout << "=== Menu ===\n\n";
        cout << "1. Wyznaczanie minimalnego drzewa rozpinajacego (MST)\n";
        cout << "2. Wyznaczanie najkrotszej sciezki (SP)\n";
        cout << "0. Wyjdz\n\n";
        cout << "Wybierz: ";
        cin >> select;

        switch (select) {
        case 1:
            system("cls");
            mst.menu_mst();
            break;

        case 2:
            system("cls");
            sp.menu_sp();
            break;

        case 0:
            exit = false;
            break;
        }
    }

    return 0;
}
