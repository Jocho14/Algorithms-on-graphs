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

	//rozmiar grafu (liczba kraw�dzi w grafie)
	int max_node = 0;

	//macierz s�siedztw
	int** adjGraph;

	//metoda dodaj�ca wierzcho�ki do grafu
	void addGraphNode(int v1, int v2, int weight);

	//metoda inicjalizuj�ca struktury zwi�zane z grafem
	void initializeGraph(int s);

	//metoda czyszcz�ca struktur�
	void clearGraph();

	/***************************MST********************************/

	//macierz s�siedztw drzewa MST
	int** adjMST;

	//lista kraw�dzi
	list <weightNodePair> edges;

	//metoda dodaj�ca wierzcho�ki do MST
	void addMSTNode(int v1, int v2, int weight);

	//metoda inicjalizuj�ca struktury zwi�zane z MST
	void initializeMST();

	//metoda czyszcz�ca drzewo MST
	void clearMST();

	//metoda wy�wietlaj�ca minimalne drzewo rozpinaj�ce
	void showMST();

	//metoda wywo�uj�ca algorytm Kruskala
	void createMST();

	//kolejka priorytetowa zwracaj�ca najmniejsz� par� (waga, wierzcho�ek)
	priority_queue<weightNodePair, vector<weightNodePair>, greater<weightNodePair>> Q;
};