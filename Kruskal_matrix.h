#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

//typ pary int i pair do stworzenia kolejki priorytetowej
typedef pair<int, pair<int, int> > weightNodePair;


class Kruskal_matrix {
public:
	//konstruktor
	Kruskal_matrix();

	//destruktor
	~Kruskal_matrix();

	/***************************Graf********************************/

	//rozmiar grafu (liczba krawêdzi w grafie)
	int max_node = 0;

	//macierz s¹siedztw
	int** adjGraph;

	//metoda dodaj¹ca wierzcho³ki do grafu
	void addGraphNode(int v1, int v2, int weight);

	//metoda inicjalizuj¹ca struktury zwi¹zane z grafem
	void initializeGraph(int s);

	//metoda czyszcz¹ca strukturê
	void clearGraph();

	/***************************MST********************************/

	//macierz s¹siedztw drzewa MST
	int** adjMST;

	//lista krawêdzi
	list <weightNodePair> edges;

	//metoda dodaj¹ca wierzcho³ki do MST
	void addMSTNode(int v1, int v2, int weight);

	//metoda inicjalizuj¹ca struktury zwi¹zane z MST
	void initializeMST();

	//metoda czyszcz¹ca drzewo MST
	void clearMST();

	//metoda wyœwietlaj¹ca minimalne drzewo rozpinaj¹ce
	void showMST();

	//metoda wywo³uj¹ca algorytm Kruskala
	void createMST();

	//kolejka priorytetowa zwracaj¹ca najmniejsz¹ parê (waga, wierzcho³ek)
	priority_queue<weightNodePair, vector<weightNodePair>, greater<weightNodePair>> Q;
};