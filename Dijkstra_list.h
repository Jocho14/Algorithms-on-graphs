#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

//typ par do stworzenia listy kraw�dzi (waga, wierzcho�ek)
typedef pair<int, int> Pi;

//typ list par do stworzenia listy s�siedztwa
typedef list<Pi> Li;


class Dijkstra_list {
public:
	//konstruktor
	Dijkstra_list();

	//destruktor
	~Dijkstra_list();

	/***************************Graf********************************/

	//rozmiar grafu (liczba kraw�dzi w grafie)
	int max_node = 0;

	//wierzcho�ek pocz�tkowy (domy�lnie ustawiony na 0)
	int startingNode = 0;

	//lista s�siad�w
	vector <Li> adjGraph;

	//metoda dodaj�ca wierzcho�ki do grafu
	void addGraphNode(int v1, int v2, int weight);

	//metoda inicjalizuj�ca struktury zwi�zane z grafem
	void initializeGraph(int s);

	//metoda czyszcz�ca struktur�
	void clearGraph();

	//metoda wy�wietlaj�ca graf
	void showGraph();

	/***************************Shortest path********************************/

	//tablica z kosztami doj�cia od wierzcho�ka v  do wierzcho�ka i-tego wzd�u� najkr�tszej �cie�ki
	int* d;

	//tablica z poprzednikami wierzcho�k�w na wyznaczonej najkr�tszej �cie�ce
	int* p;

	//metoda inicjalizuj�ca struktury zwi�zane z SP
	void initializeSP();

	//metoda czyszcz�ca strukture najkr�tszej �cie�ki
	void clearSP();

	//metoda wy�wietlaj�ca najkr�tsz� �cie�k�
	void showSP();

	//metoda wywo�uj�ca algorytm Dijkstry
	void createSP();

	//metoda ustawiaj�ca wierzcho�ek pocz�tkowy
	void setStartingNode(int _startingNode);

	//kolejka priorytetowa zwracaj�ca najmniejsz� par� (waga, wierzcho�ek)
	priority_queue<Pi, vector<Pi>, greater<Pi>> Q;
};