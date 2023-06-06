#pragma once
#include<iostream>
#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

//typ pary int oraz pair kt�ry zostaje wykorzystany do stworzenia kolejki priorytetowej para(waga, para(v1, v2))
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

	//macierz s�siedztwa
	int** adjGraph;

	//metoda dodaj�ca wierzcho�ki do grafu 
	void addGraphNode(int v1, int v2, int weight);

	//metoda inicjalizuj�ca struktury zwi�zane z grafem
	void initializeGraph(int s);

	//metoda czyszcz�ca graf
	void clearGraph();

	//metoda wy�wietlaj�ca graf 
	void showGraph();

	/*******************************MST********************************/

	//macierz s�siedztwa MST
	int** adjMST;

	//metoda tworz�ca MST
	void createMST();

	//tablica odwiedzonych wierzcho�k�w MST
	bool* visited;

	//metoda dodaj�ca wierzcho�ki do MST
	void addMSTNode(int v1, int v2, int weight);

	//metoda inicjalizuj�ca struktury zwi�zane z MST
	void initializeMST();

	//metoda czyszcz�ca MST
	void clearMST();

	//metoda wy�wietlajaca MST
	void showMST();

	//kolejka priorytetowa zwracaj�ca najmniejsz� par� (waga, wierzcho�ek)
	priority_queue<weightNodePair, vector<weightNodePair>, greater<weightNodePair>> Q;
};

