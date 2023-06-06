#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

//typ par do stworzenia listy krawêdzi (waga, wierzcho³ek)
typedef pair<int, int> Pi;

//typ list par do stworzenia listy s¹siedztwa
typedef list<Pi> Li;


class Dijkstra_list {
public:
	//konstruktor
	Dijkstra_list();

	//destruktor
	~Dijkstra_list();

	/***************************Graf********************************/

	//rozmiar grafu (liczba krawêdzi w grafie)
	int max_node = 0;

	//wierzcho³ek pocz¹tkowy (domyœlnie ustawiony na 0)
	int startingNode = 0;

	//lista s¹siadów
	vector <Li> adjGraph;

	//metoda dodaj¹ca wierzcho³ki do grafu
	void addGraphNode(int v1, int v2, int weight);

	//metoda inicjalizuj¹ca struktury zwi¹zane z grafem
	void initializeGraph(int s);

	//metoda czyszcz¹ca strukturê
	void clearGraph();

	//metoda wyœwietlaj¹ca graf
	void showGraph();

	/***************************Shortest path********************************/

	//tablica z kosztami dojœcia od wierzcho³ka v  do wierzcho³ka i-tego wzd³u¿ najkrótszej œcie¿ki
	int* d;

	//tablica z poprzednikami wierzcho³ków na wyznaczonej najkrótszej œcie¿ce
	int* p;

	//metoda inicjalizuj¹ca struktury zwi¹zane z SP
	void initializeSP();

	//metoda czyszcz¹ca strukture najkrótszej œcie¿ki
	void clearSP();

	//metoda wyœwietlaj¹ca najkrótsz¹ œcie¿kê
	void showSP();

	//metoda wywo³uj¹ca algorytm Dijkstry
	void createSP();

	//metoda ustawiaj¹ca wierzcho³ek pocz¹tkowy
	void setStartingNode(int _startingNode);

	//kolejka priorytetowa zwracaj¹ca najmniejsz¹ parê (waga, wierzcho³ek)
	priority_queue<Pi, vector<Pi>, greater<Pi>> Q;
};