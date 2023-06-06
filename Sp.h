#pragma once
#include "Dijkstra_list.h"
#include "Dijkstra_matrix.h"


using namespace std;

class Sp {

public:
	//menu sp
	void menu_sp();

	//metoda generuj�ca graf
	void generate_graph(Dijkstra_list& dijkstraList, Dijkstra_matrix& dijkstraMatrix, int _size, int _density);	//Dijkstra_matrix& dijkstraMatrix

	//metoda buduj�ca graf z pliku
	void build_graph_from_file(Dijkstra_list& dijkstraList, Dijkstra_matrix& dijkstraMatrix);

	//metoda wy�wietlaj�ca graf
	void show_graph(Dijkstra_list& dijkstraList, Dijkstra_matrix& dijkstraMatrix);

	//metoda do testowania algorytmu
	void test(int testSize);
};


