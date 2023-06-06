#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

//typ par do stworzenia pary po³¹czonych wierzcho³ków
typedef pair<int, int> Pi;

//typ pary int i pair do stworzenia kolejki priorytetowej
typedef pair<int, pair<int, int> > weightNodePair;

//typ list par do stworzenia listy s¹siedztw
typedef list<Pi> Li;


class Kruskal_list {
public:
	//konstruktor
	Kruskal_list();

	//destruktor
	~Kruskal_list();

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

	//metoda wywo³uj¹ca algorytm Kruskala
	void createMST();

	//kolejka priorytetowa zwracaj¹ca najmniejsz¹ parê (waga, wierzcho³ek) w liœcie krawêdzi
	priority_queue<weightNodePair, vector<weightNodePair>, greater<weightNodePair>> Q;
};