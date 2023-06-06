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

	//metoda generuj¹ca graf
	void generate_graph(Prim_list& primList, Prim_matrix& primMatrix, Kruskal_list& kruskalList, Kruskal_matrix& kruskalMatrix, int _size, int _density);

	//metoda buduj¹ca graf z pliku
	void build_graph_from_file(Prim_list& primList, Prim_matrix& primMatrix, Kruskal_list& kruskalList, Kruskal_matrix& kruskalMatrix);

	//metoda wyœwietlaj¹ca graf
	void show_graph(Prim_list& primList, Prim_matrix& primMatrix);

	//metoda testuj¹ca algorytm Prima i Kruskala (dla obu reprezentacji)
	void test(int testSize);
};


