#include "Kruskal_matrix.h"
#include<iostream>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

Kruskal_matrix::Kruskal_matrix() {
	Kruskal_matrix::max_node = 0;
	Kruskal_matrix::adjGraph = NULL;
	Kruskal_matrix::adjMST = NULL;
}

//destruktor usuwa ca³¹ strukture Kruskal_matrix
Kruskal_matrix::~Kruskal_matrix() {
	Kruskal_matrix::clearGraph();
	Kruskal_matrix::clearMST();
}

void Kruskal_matrix::clearGraph() {
	if (adjGraph != NULL) {
		for (int i = 0; i < max_node; i++) {
			if (adjGraph[i] != NULL) {
				delete[] adjGraph[i];
				adjGraph[i] = NULL;
			}
		}
		delete[] adjGraph;
		adjGraph = NULL;
	}
	max_node = 0;
}


void Kruskal_matrix::clearMST() {
	delete[] adjMST;
	adjMST = NULL;

	// Usuwanie kolejki priorytetowej
	while (!Q.empty()) {
		Q.pop();
	}
}

void Kruskal_matrix::initializeMST() {
	clearMST();
	
	adjMST = new int* [max_node];		// inicjalizacja macierzy s¹siedztw MST

	// Wype³nianie macierzy s¹siedztw MST wartoœciami pocz¹tkowymi
	for (int i = 0; i < max_node; i++) {
		adjMST[i] = new int[max_node];

		for (int j = 0; j < max_node; j++) {
			adjMST[i][j] = 0;
		}
	}
}

void Kruskal_matrix::initializeGraph(int size) {
	max_node = size;

	adjGraph = new int* [size];				//inicjalizacja macierzy s¹siedztw

	for (int i = 0; i < size; i++) {
		adjGraph[i] = new int[size];

		for (int j = 0; j < size; j++) {
			adjGraph[i][j] = 0;
		}
	}
}

void Kruskal_matrix::addGraphNode(int v1, int v2, int w) {
	adjGraph[v1][v2] = w;
	adjGraph[v2][v1] = w;
}

void Kruskal_matrix::addMSTNode(int v1, int v2, int w) {
	adjMST[v1][v2] = w;
	adjMST[v2][v1] = w;
}

struct Subset1 {
	int parent;
	int rank;
};

int find1(Subset1 subsets[], int i) {
	if (subsets[i].parent != i) {
		subsets[i].parent = find1(subsets, subsets[i].parent);
	}

	return subsets[i].parent;
}

void unionSets1(Subset1 subsets[], int x, int y) {
	int xroot = find1(subsets, x);
	int yroot = find1(subsets, y);

	if (subsets[xroot].rank < subsets[yroot].rank) {
		subsets[xroot].parent = yroot;
	}
	else if (subsets[xroot].rank > subsets[yroot].rank) {
		subsets[yroot].parent = xroot;
	}
	else {
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

void Kruskal_matrix::createMST() {
	if (max_node < 1) {
		return;
	}
	initializeMST();

	for (int i = 0; i < max_node; i++) {
		for (int j = i + 1; j < max_node; j++) {  // dodajemy krawêdzie z nad przek¹tnej, aby unikn¹æ duplikatów
			if (adjGraph[i][j] > 0) {  // zak³adamy, ¿e 0 oznacza brak krawêdzi
				Q.push({ adjGraph[i][j], {i, j} });
			}
		}
	}

	Subset1* subsets = new Subset1[max_node];

	//tworzenie osobnego zbioru dla ka¿dego wierzcho³ka
	for (int v = 0; v < max_node; v++) {
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	while (!Q.empty()) {
		auto edge = Q.top();
		Q.pop();

		int u = find1(subsets, edge.second.first);
		int v = find1(subsets, edge.second.second);

		if (u != v) {
			addMSTNode(edge.second.first, edge.second.second, edge.first);
			unionSets1(subsets, u, v);
		}
	}

	delete[] subsets;
}

void Kruskal_matrix::showMST() {
	//Wyœwietlenie 1 wiersza zawieraj¹cego numery wierzcho³ków
	cout << " ";
	for (int i = 0; i < max_node; i++) {
		cout << "  " << i;
	}
	cout << '\n';

	for (int i = 0; i < max_node; i++) {
		cout << i << "  ";
		for (int j = 0; j < max_node; j++) {
			cout << adjMST[i][j] << "  ";
		}
		cout << '\n';
	}
}
