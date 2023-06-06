#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

//typ par do stworzenia pary po��czonych wierzcho�k�w
typedef pair<int, int> Pi;

//typ pary int i pair do stworzenia kolejki priorytetowej
typedef pair<int, pair<int, int> > weightNodePair;

//typ list par do stworzenia listy s�siedztw
typedef list<Pi> Li;


class Kruskal_list {
public:
	//konstruktor
	Kruskal_list();

	//destruktor
	~Kruskal_list();

	/***************************Graf********************************/

	//rozmiar grafu (liczba kraw�dzi w grafie)
	int max_node = 0;

	//lista s�siad�w
	vector <Li> adjGraph;

	//metoda dodaj�ca wierzcho�ki do grafu
	void addGraphNode(int v1, int v2, int weight);

	//metoda inicjalizuj�ca struktury zwi�zane z grafem
	void initializeGraph(int s);

	//metoda czyszcz�ca struktur�
	void clearGraph();

	/***************************MST********************************/

	//lista s�siad�w drzewa MST
	vector <Li> adjMST;

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

	//kolejka priorytetowa zwracaj�ca najmniejsz� par� (waga, wierzcho�ek) w li�cie kraw�dzi
	priority_queue<weightNodePair, vector<weightNodePair>, greater<weightNodePair>> Q;
};