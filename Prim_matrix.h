#pragma once
#include<iostream>
#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

//typ pary int oraz pair który zostaje wykorzystany do stworzenia kolejki priorytetowej para(waga, para(v1, v2))
typedef pair<int, pair<int, int> > weightNodePair;

class Prim_matrix {
public:
	//konstruktor
	Prim_matrix();

	//destruktor
	~Prim_matrix();

	/******************************Graf*******************************/

	//rozmiar grafu
	int max_node = 0;

	//macierz s¹siedztwa
	int** adjGraph;

	//metoda dodaj¹ca wierzcho³ki do grafu 
	void addGraphNode(int v1, int v2, int weight);

	//metoda inicjalizuj¹ca struktury zwi¹zane z grafem
	void initializeGraph(int s);

	//metoda czyszcz¹ca graf
	void clearGraph();

	//metoda wyœwietlaj¹ca graf 
	void showGraph();

	/*******************************MST********************************/

	//macierz s¹siedztwa MST
	int** adjMST;

	//metoda tworz¹ca MST
	void createMST();

	//tablica odwiedzonych wierzcho³ków MST
	bool* visited;

	//metoda dodaj¹ca wierzcho³ki do MST
	void addMSTNode(int v1, int v2, int weight);

	//metoda inicjalizuj¹ca struktury zwi¹zane z MST
	void initializeMST();

	//metoda czyszcz¹ca MST
	void clearMST();

	//metoda wyœwietlajaca MST
	void showMST();

	//kolejka priorytetowa zwracaj¹ca najmniejsz¹ parê (waga, wierzcho³ek)
	priority_queue<weightNodePair, vector<weightNodePair>, greater<weightNodePair>> Q;
};

