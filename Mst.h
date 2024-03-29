#pragma once
#include "Prim_list.h"
#include "Prim_matrix.h"
#include "Kruskal_list.h"
#include "Kruskal_matrix.h"

using namespace std;

class Mst {

public:
	//menu mst
	void menu_mst();

	//metoda generująca graf
	void generate_graph(Prim_list& primList, Prim_matrix& primMatrix, Kruskal_list& kruskalList, Kruskal_matrix& kruskalMatrix, int _size, int _density);

	//metoda budująca graf z pliku
	void build_graph_from_file(Prim_list& primList, Prim_matrix& primMatrix, Kruskal_list& kruskalList, Kruskal_matrix& kruskalMatrix);

	//metoda wyświetlająca graf
	void show_graph(Prim_list& primList, Prim_matrix& primMatrix);

	//metoda testująca algorytm Prima i Kruskala (dla obu reprezentacji)
	void test(int testSize);
};


