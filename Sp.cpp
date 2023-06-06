#include "Sp.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <chrono>
#include <string>
#include "Dijkstra_list.h"
#include "Dijkstra_matrix.h"


using namespace std;

void Sp::generate_graph(Dijkstra_list& dijkstraList, Dijkstra_matrix& dijkstraMatrix, int _size, int _density) {

    srand((unsigned int)time(NULL));

    int size = _size;
    int density = _density;
    bool is99 = false;

    if (size < 1) {         // zakoñcz generowanie jeœli lb wierzcho³ków jest < 1
        return;
    }

    if (density > 100) {    // jeœli zostanie podana gêstoœæ wiêksza ni¿ 100 to ustawiamy gêstoœæ na maksymaln¹
        density = 100;
    }

    if (density == 99) {    // jeœli gêstoœæ grafu jest równa 99% to 
        density = 100;      // generujemy graf o gêstoœci 100% i usuwamy 1% krawêdzi
        is99 = true;
    }

    int numberOfEdges = (density * (size * (size - 1) ))/ 100;  // obliczenie iloœci krawêdzi (maksymalna iloœæ krawêdzi to n(n - 1) / 2)

    if ((numberOfEdges - 1) < size) {
        cout << "Dla podanej gestosci nie da sie utworzyc spojnego grafu\n";
        return;
    }


    dijkstraList.clearGraph();                               // czyszczenie struktury przed generowaniem grafu
    dijkstraMatrix.clearGraph();


    dijkstraList.initializeGraph(size);                      // inicjalizacja listy s¹siadów
    dijkstraMatrix.initializeGraph(size);                    // inicjalizacja macierz sasiedztwa
   

    vector<pair<int, int>>generatedGraph;


    // Tworzymy cykl, aby mieæ pewnoœæ, ¿e dojdziemy z jednego wierzcho³ka do ka¿dego innego
    int v1, v2, weight;
    for (int i = 0; i < size; i++) {
        v1 = i;                         // wierzcho³ek v1   
        v2 = (i + 1) % size;            // wierzcho³ek v2
        weight = 1 + rand() % 9;        // waga miêdzy v1 i v2

        generatedGraph.push_back(make_pair(v1, v2));

        dijkstraList.addGraphNode(v1, v2, weight);
        dijkstraMatrix.addGraphNode(v1, v2, weight);
    }

    if (is99) {
        numberOfEdges -= size;
    }
    else {
        numberOfEdges -= (size - 1);            // pomniejszamy liczbê krawêdzi do wygenerowania o liczbê krawêdzi drzewa rozpinaj¹cego
    }

            

    // 2. Uzupe³niamy pozosta³e krawêdzie grafu
    for (int i = 0; i < numberOfEdges; i++) {
        v1 = rand() % size;             // generowanie losowego wierzcho³ka v1
        v2 = rand() % size;             // generowanie losowego wierzcho³ka v2
        weight = 1 + rand() % 9;      // generowanie losowej wagi krawêdzi miêdzy v1 i v2

        if (v1 == v2) {                 // jesli wylosowane wierzcholki s¹ takie same to ich nie ³¹czymy
            i--;
            continue;
        }

        auto newPair = make_pair(v1, v2);             // tworzenie pary z wylosowanych wierzcho³ków

        bool ifExist = false;
        for (int j = 0; j < generatedGraph.size(); j++) {
            if (generatedGraph[j] == newPair) {                 // jeœli dana para ju¿ wyst¹pi³a to nie ³¹czymy jej ponownie
                i--;
                ifExist = true;
                break;
            }
        }
        if (!ifExist) {                                         // jeœli dana para nie znajduje siê w grafie to j¹ dodaj
            generatedGraph.push_back(make_pair(v1, v2));

            dijkstraList.addGraphNode(v1, v2, weight);
            dijkstraMatrix.addGraphNode(v1, v2, weight);
        }
    }
}

void Sp::build_graph_from_file(Dijkstra_list& dijkstraList, Dijkstra_matrix& dijkstraMatrix) {
    dijkstraList.clearGraph();
    dijkstraMatrix.clearGraph();

    ifstream file_name;
    cout << "Podaj nazwe pliku: ";
    string name;
    cin >> name;
    file_name.open(name);
    int fileNumOfEdges, fileNumOfVertex;
    int v1, v2, w, pom = 0;
    int startingVertex;
    if (file_name.is_open()) {
        file_name >> fileNumOfEdges;
        file_name >> fileNumOfVertex;
        file_name >> startingVertex;

        dijkstraList.initializeGraph(fileNumOfVertex);
        dijkstraList.setStartingNode(startingVertex);
        dijkstraMatrix.initializeGraph(fileNumOfVertex);
        dijkstraMatrix.setStartingNode(startingVertex);

        for (int i = 0; i < fileNumOfEdges; i++) {
            file_name >> v1;
            file_name >> v2;
            file_name >> w;
            dijkstraList.addGraphNode(v1, v2, w);
            dijkstraMatrix.addGraphNode(v1, v2, w);
        }
    }
    else
    {
        cout << "Nie ma takiego pliku!";
        return;
    }
    file_name.close();
}

void Sp::test(int testSize) {
    cout << "Test dla " << testSize << " danych\n";

    Dijkstra_list* dijkstraList = new Dijkstra_list();
    Dijkstra_matrix* dijkstraMatrix = new Dijkstra_matrix();


    long averageTimeDijkstraList = 0;               // Œrednie czasy wykonania poszczególnych algorytmów
    long averageTimeDijkstraMatrix = 0;

    int testAmount = 10;                    //zmienna przechowuj¹ca liczbe powtórzeñ testów
    int density[] = { 20, 60, 99 };           // tablica przechowuj¹ca gêstoœci grafów

    srand((unsigned int)time(NULL));

    for (int i = 0; i < 3; i++) {
        averageTimeDijkstraList = 0;
        averageTimeDijkstraMatrix = 0;

        for (int j = 0; j < testAmount; j++) {
            generate_graph(*dijkstraList, *dijkstraMatrix, testSize, density[i]);


            std::chrono::high_resolution_clock::time_point TimeStart;
            std::chrono::high_resolution_clock::time_point TimeEnd;


            /***************************************Testowanie Dijkstra List*******************************************************/
            TimeStart = std::chrono::high_resolution_clock::now();

            dijkstraList->createSP();

            TimeEnd = std::chrono::high_resolution_clock::now();
            averageTimeDijkstraList += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
            /***************************************Testowanie Dijkstra Matrix*****************************************************/
            TimeStart = std::chrono::high_resolution_clock::now();

            dijkstraMatrix->createSP();

            TimeEnd = std::chrono::high_resolution_clock::now();
            averageTimeDijkstraMatrix += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
        }
        averageTimeDijkstraList /= testAmount;
        averageTimeDijkstraMatrix /= testAmount;

        string filePathWithResult = "./ShortPath_czas_" + to_string(testSize) + ".txt";
        ofstream outputFile;

        outputFile.open(filePathWithResult, fstream::app);
        if (!outputFile.is_open()) {
            cout << "couldn't open the file\n";
            return;
        }

        outputFile << "Œr. czas wykonania, dla gêstoœci " + to_string(density[i]) + " algorytmu Dijkstry (lista s¹siedztw): " + to_string(averageTimeDijkstraList) + "\n";
        outputFile << "Œr. czas wykonania, dla gêstoœci " + to_string(density[i]) + " algorytmu Dijkstry (macierz s¹siedztw): " + to_string(averageTimeDijkstraMatrix) + "\n";
       
        outputFile.close();
    }

    delete dijkstraList;
    delete dijkstraMatrix;
}

void Sp::show_graph(Dijkstra_list& dijkstraList, Dijkstra_matrix& dijkstraMatrix) {
    cout << "Graf - reprezentacja listowa:\n";
    dijkstraList.showGraph();
    cout << '\n';
    cout << "Graf - reprezentacja macierzowa:\n";
    dijkstraMatrix.showGraph();
}

void show_menu_sp() {
    cout << "=== Menu ===\n\n";
    cout << "1. Wygeneruj graf\n";
    cout << "2. Wczytaj graf z pliku\n";
    cout << "3. Wyswietl graf\n";
    cout << "4. Algorytm Dijkstry\n";
    //cout << "5. Test\n";
    cout << "0. Wyjdz\n\n";
    cout << "Wybierz: ";
}

void Sp::menu_sp() {
    int select;
    bool exit = true;

    Dijkstra_list* dijkstraList = new Dijkstra_list();

    Dijkstra_matrix* dijkstraMatrix = new Dijkstra_matrix();

    int size, density;

    while (exit) {
        system("cls");
        show_menu_sp();
        cin >> select;

        switch (select) {
        case 1:
            system("cls");
            cout << "Podaj liczbe wierzcholkow: ";
            cin >> size;

            cout << "Podaj gestosc grafu (w %): ";
            cin >> density;

            generate_graph(*dijkstraList, *dijkstraMatrix, size, density);
            show_graph(*dijkstraList, *dijkstraMatrix);
            cout << "\n\n";
            system("pause");
            break;

        case 2:
            system("cls");
            build_graph_from_file(*dijkstraList, *dijkstraMatrix);
            show_graph(*dijkstraList, *dijkstraMatrix);
            cout << "\n\n";
            system("pause");
            break;

        case 3:
            system("cls");
            show_graph(*dijkstraList, *dijkstraMatrix);
            cout << "\n\n";
            system("pause");
            break;

        case 4:
            system("cls");
            cout << "Dijkstra - lista sasiadow: \n\n";
            dijkstraList->createSP();
            dijkstraList->showSP();
            cout << "\n\nDijkstra - macierz sasiedztwa: \n\n";
            dijkstraMatrix->createSP();
            dijkstraMatrix->showSP();
            cout << "\n\n";
            system("pause");
            break;

        case 5:
            system("cls");
            /*test(20);
            test(30);
            test(50);
            test(75);
            test(90);
            test(100);
            test(125);*/
            system("pause");
            break;

        case 0:
            return;
            break;

        default:
            system("cls");
            cout << "podaj prawidlowa wartosc\n";
            system("pause");
            break;
        }
    }
}