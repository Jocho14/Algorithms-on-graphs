#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

//typ par do stworzenia listy s¹siedztw
typedef pair<int, int> Pi;

//typ pary int i pair do stworzenia kolejki priorytetowej
typedef pair<int, pair<int, int> > weightNodePair;

//typ list par do stworzenia listy s¹siedztw
typedef list<Pi> Li;

class Prim_list {
public:
	//konstruktor
	Prim_list();

	//destruktor
	~Prim_list();

	/***************************Graf********************************/

	//rozmiar grafu (liczba krawêdzi w grafie)
	int max_node = 0;

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

	/***************************MST********************************/

	//lista s¹siadów drzewa MST
	vector <Li> adjMST;

	//metoda dodaj¹ca wierzcho³ki do MST
	void addMSTNode(int v1, int v2, int weight);
	
	//metoda inicjalizuj¹ca struktury zwi¹zane z MST
	void initializeMST();

	//metoda czyszcz¹ca drzewo MST
	void clearMST();

	//metoda wyœwietlaj¹ca minimalne drzewo rozpinaj¹ce
	void showMST();

	//tablica odwiedzonych wierzcho³ków
	bool* visited;

	//metoda wywo³uj¹ca algorytm Prima
	void createMST();

	//kolejka priorytetowa zwracaj¹ca najmniejsz¹ parê (waga, wierzcho³ek)
	priority_queue<weightNodePair, vector<weightNodePair>, greater<weightNodePair>> Q;
};