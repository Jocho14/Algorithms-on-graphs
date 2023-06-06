#include "Mst.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <chrono>
#include <string>
#include "Prim_list.h"
#include "Prim_matrix.h"
#include "Kruskal_list.h"
#include "Kruskal_matrix.h"

using namespace std;

void Mst::generate_graph(Prim_list& primList, Prim_matrix& primMatrix, Kruskal_list& kruskalList, Kruskal_matrix& kruskalMatrix, int _size, int _density) {

    srand((unsigned int)time(NULL));

    int size = _size;
    int density = _density;
    bool is99 = false;
   
    if (size < 1) {         // zako�cz generowanie je�li lb wierzcho�k�w jest < 1
        return;
    }
        
    if (density > 100) {    // je�li zostanie podana g�sto�� wi�ksza ni� 100 to ustawiamy g�sto�� na maksymaln�
        density = 100;
    }

    if (density == 99) {    // je�li g�sto�� grafu jest r�wna 99% to 
        density = 100;      // generujemy graf o g�sto�ci 100% i usuwamy 1% kraw�dzi
        is99 = true;
    }

    int numberOfEdges = (density * (size * (size - 1) / 2)) / 100;  // obliczenie ilo�ci kraw�dzi (maksymalna ilo�� kraw�dzi to n(n - 1) / 2)

    if ((numberOfEdges - 1) < size) {
        cout << "Dla podanej gestosci nie da sie utworzyc spojnego grafu\n";
        return;
    }
   

    primList.clearGraph();                               // czyszczenie struktury przed generowaniem grafu
    primMatrix.clearGraph();
    kruskalList.clearGraph();
    kruskalMatrix.clearGraph();


    primList.initializeGraph(size);                      // inicjalizacja listy s�siad�w
    primMatrix.initializeGraph(size);                    // inicjalizacja macierz sasiedztwa
    kruskalList.initializeGraph(size);
    kruskalMatrix.initializeGraph(size);

    vector<pair<int, int>>generatedGraph;

    //sprawdzic czy numberOfEdges jest wystarczajace, aby stworzyc trzewo rozpinaj�ce !!!!

    // 1. Tworzymy drzewo rozpinaj�ce
    int v1, v2, weight;
    for (int i = 0; i < size - 1; i++) {
        v1 = i;                         // wierzcho�ek v1   
        v2 = i + 1;                     // wierzcho�ek v2
        weight = 1 + rand() % 100;      // waga mi�dzy v1 i v2

        generatedGraph.push_back(make_pair(v1, v2));
        generatedGraph.push_back(make_pair(v2, v1));

        primList.addGraphNode(v1, v2, weight);
        primMatrix.addGraphNode(v1, v2, weight);
        kruskalList.addGraphNode(v1, v2, weight);
        kruskalMatrix.addGraphNode(v1, v2, weight);
    }

    if (is99) {
        numberOfEdges -= (size);
    }
    else {
        numberOfEdges -= (size - 1);        // pomniejszamy liczb� kraw�dzi do wygenerowania o liczb� kraw�dzi drzewa rozpinaj�cego
    }

    

    // 2. Uzupe�niamy pozosta�e kraw�dzie grafu
    for (int i = 0; i < numberOfEdges; i++) {
        v1 = rand() % size;             // generowanie losowego wierzcho�ka v1
        v2 = rand() % size;             // generowanie losowego wierzcho�ka v2
        weight = 1 + rand() % 100;      // generowanie losowej wagi kraw�dzi mi�dzy v1 i v2
        
        if (v1 == v2) {                 // jesli wylosowane wierzcholki s� takie same to ich nie ��czymy
            i--;
            continue;
        }

        pair<int, int> newPair = make_pair(v1, v2);             // tworzenie pary z wylosowanych wierzcho�k�w

        bool ifExist = false;
        for (int j = 0; j < generatedGraph.size(); j++) {
            if (generatedGraph[j] == newPair) {                 // je�li dana para ju� wyst�pi�a to nie ��czymy jej ponownie
                i--;
                ifExist = true;
                break;
            }
        }
        if (!ifExist) {                                         // je�li dana para nie znajduje si� w grafie to j� dodaj
            generatedGraph.push_back(make_pair(v1, v2));
            generatedGraph.push_back(make_pair(v2, v1));

            primList.addGraphNode(v1, v2, weight);
            primMatrix.addGraphNode(v1, v2, weight);
            kruskalList.addGraphNode(v1, v2, weight);
            kruskalMatrix.addGraphNode(v1, v2, weight);
        }
    }
}

void Mst::build_graph_from_file(Prim_list& primList, Prim_matrix& primMatrix, Kruskal_list& kruskalList, Kruskal_matrix& kruskalMatrix) {
    primList.clearGraph();
    primMatrix.clearGraph();
    kruskalList.clearGraph();
    kruskalMatrix.clearGraph();

    ifstream file_name;
    cout << "Podaj nazwe pliku: ";
    string name;
    cin >> name;
    file_name.open(name);
    int fileNumOfEdges, fileNumOfVertex;
    int v1, v2, w, pom = 0;
    if (file_name.is_open()) {
        file_name >> fileNumOfEdges;
        file_name >> fileNumOfVertex;

        primList.initializeGraph(fileNumOfVertex);
        primMatrix.initializeGraph(fileNumOfVertex);
        kruskalList.initializeGraph(fileNumOfVertex);
        kruskalMatrix.initializeGraph(fileNumOfVertex);

        for (int i = 0; i < fileNumOfEdges; i++) {
            file_name >> v1;
            file_name >> v2;
            file_name >> w;
            primList.addGraphNode(v1, v2, w);
            primMatrix.addGraphNode(v1, v2, w);
            kruskalList.addGraphNode(v1, v2, w);
            kruskalMatrix.addGraphNode(v1, v2, w);
        }
    }
    else
    {
        cout << "Nie ma takiego pliku!";
        return;
    }
    file_name.close();
}

void Mst::show_graph(Prim_list& primList, Prim_matrix& primMatrix) {
    cout << "Graf - reprezentacja listowa:\n";
    primList.showGraph();
    cout << '\n';
    cout << "Graf - reprezentacja macierzowa:\n";
    primMatrix.showGraph();
}

void Mst::test(int testSize) {
    cout << "Test dla " << testSize << " danych\n";

    Prim_list* primList = new Prim_list();
    Prim_matrix* primMatrix = new Prim_matrix();

    Kruskal_list* kruskalList = new Kruskal_list();
    Kruskal_matrix* kruskalMatrix = new Kruskal_matrix();

    long averageTimePrimList = 0;               // �rednie czasy wykonania poszczeg�lnych algorytm�w
    long averageTimePrimMatrix = 0;
    long averageTimeKruskalList = 0;
    long averageTimeKruskalMatrix = 0;

    int testAmount = 10;                    //zmienna przechowuj�ca liczbe powt�rze� test�w
    int density[] = { 20, 60, 99 };           // tablica przechowuj�ca g�sto�ci graf�w
    //int testSamples[] = { 50, 100, 150, 200, 250, 300, 350 };

    srand((unsigned int)time(NULL));

        for (int i = 0; i < 3; i++) {
            averageTimePrimList = 0;              
            averageTimePrimMatrix = 0;
            averageTimeKruskalList = 0;
            averageTimeKruskalMatrix = 0;

            for (int j = 0; j < testAmount; j++) {
                generate_graph(*primList, *primMatrix, *kruskalList, *kruskalMatrix, testSize, density[i]);

                
                std::chrono::high_resolution_clock::time_point TimeStart;
                std::chrono::high_resolution_clock::time_point TimeEnd;
                

                /***************************************Testowanie Prim List*******************************************************/
                TimeStart = std::chrono::high_resolution_clock::now();

                primList->createMST();
                
                TimeEnd = std::chrono::high_resolution_clock::now();
                averageTimePrimList += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
                /***************************************Testowanie Prim Matrix*****************************************************/
                TimeStart = std::chrono::high_resolution_clock::now();

                primMatrix->createMST();

                TimeEnd = std::chrono::high_resolution_clock::now();
                averageTimePrimMatrix += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
                /***************************************Testowanie Kruskal List*****************************************************/
                TimeStart = std::chrono::high_resolution_clock::now();

                kruskalList->createMST();

                TimeEnd = std::chrono::high_resolution_clock::now();
                averageTimeKruskalList += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
                /***************************************Testowanie Kruskal Matrix***************************************************/
                TimeStart = std::chrono::high_resolution_clock::now();

                kruskalMatrix->createMST();

                TimeEnd = std::chrono::high_resolution_clock::now();
                averageTimeKruskalMatrix += chrono::duration_cast<chrono::nanoseconds>(TimeEnd - TimeStart).count();
            }
            averageTimePrimList /= testAmount;
            averageTimePrimMatrix /= testAmount;
            averageTimeKruskalList /= testAmount;
            averageTimeKruskalMatrix /= testAmount;

            string filePathWithResult = "./MST_czas_" + to_string(testSize) + ".txt";
            ofstream outputFile;

            outputFile.open(filePathWithResult, fstream::app);
            if (!outputFile.is_open()) {
                cout << "couldn't open the file\n";
                return;
            }

            outputFile << "�r. czas wykonania, dla g�sto�ci " + to_string(density[i]) + " algorytmu Prima (lista s�siedztw): " + to_string(averageTimePrimList) + "\n";
            outputFile << "�r. czas wykonania, dla g�sto�ci " + to_string(density[i]) + " algorytmu Prima (macierz s�siedztw): " + to_string(averageTimePrimMatrix) + "\n";
            outputFile << "�r. czas wykonania, dla g�sto�ci " + to_string(density[i]) + " algorytmu Kruskala (lista s�siedztw): " + to_string(averageTimeKruskalList) + "\n";
            outputFile << "�r. czas wykonania, dla g�sto�ci " + to_string(density[i]) + " algorytmu Kruskala (macierz s�siedztw): " + to_string(averageTimeKruskalMatrix) + "\n";
            
            outputFile.close();
        }

        delete primList;
        delete primMatrix;
        delete kruskalList;
        delete kruskalMatrix;
}



void show_menu_mst() {
    cout << "=== Menu ===\n\n";
    cout << "1. Wygeneruj graf\n";
    cout << "2. Wczytaj graf z pliku\n";
    cout << "3. Wyswietl graf\n";
    cout << "4. Algorytm Prima\n";
    cout << "5. Algorytm Kruskala\n";
    //cout << "6. Test\n";
    cout << "0. Wyjdz\n\n";
    cout << "Wybierz: ";
}

void Mst::menu_mst() {
    int select;
    bool exit = true;

    Prim_list* primList = new Prim_list();
    
    Prim_matrix* primMatrix = new Prim_matrix();

    Kruskal_list* kruskalList = new Kruskal_list();
    Kruskal_matrix* kruskalMatrix = new Kruskal_matrix();

    int size, density;
    while (exit) {
        system("cls");
        show_menu_mst();
        cin >> select;

        switch (select) {
        case 1:
            system("cls");
            cout << "Podaj liczbe wierzcholkow: ";
            cin >> size;

            cout << "Podaj gestosc grafu: ";
            cin >> density;

            generate_graph(*primList, *primMatrix, *kruskalList, *kruskalMatrix, size, density);
            show_graph(*primList, *primMatrix);
            cout << "\n\n";
            system("pause");
            break;

        case 2:
            system("cls");
            build_graph_from_file(*primList, *primMatrix, *kruskalList, *kruskalMatrix);
            show_graph(*primList, *primMatrix);
            cout << "\n\n";
            system("pause");
            break;

        case 3:
            system("cls");
            show_graph(*primList, *primMatrix);
            cout << "\n\n";
            system("pause");
            break;

        case 4:
            system("cls");
            cout << "Prim - lista sasiadow: \n\n";
            primList->createMST();
            primList->showMST();
            cout << "\n\nPrim - macierz sasiedztwa: \n\n";
            primMatrix->createMST();
            primMatrix->showMST();
            cout << "\n\n";
            system("pause");
            break;

        case 5:
            system("cls");
            cout << "Kruskal - lista sasiadow: \n\n";
            kruskalList->createMST();
            kruskalList->showMST();
            cout << "\n\nKruskal - macierz sasiedztwa: \n\n";
            kruskalMatrix->createMST();
            kruskalMatrix->showMST();
            cout << "\n\n";
            system("pause");
            break;

        case 6:
            system("cls");
           /*  test(20);
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