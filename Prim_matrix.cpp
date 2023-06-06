#include "Prim_matrix.h"
#include<iostream>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

Prim_matrix::Prim_matrix() {
	Prim_matrix::max_node = 0;
	Prim_matrix::visited = NULL;
	Prim_matrix::adjGraph = NULL;
	Prim_matrix::adjMST = NULL;
}

//destruktor usuwa ca³¹ strukture Prim_matrixy
Prim_matrix::~Prim_matrix() {
	Prim_matrix::clearGraph();
	Prim_matrix::clearMST();
}

void Prim_matrix::clearGraph() {
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


void Prim_matrix::clearMST() {
	delete[] adjMST;
	adjMST = NULL;

	//Usuwanie tablicy visited
	if (visited != NULL) {
		delete[] visited;
		visited = NULL;
	}
	// Usuwanie kolejki priorytetowej
	while (!Q.empty()) {
		Q.pop();
	}
}

void Prim_matrix::initializeMST() {
	clearMST();
	visited = new bool[max_node];		// inicjalizacja tablicy visited
	adjMST = new int* [max_node];		// inicjalizacja macierzy s¹siedztw MST

	// Wype³nianie macierzy s¹siedztw MST wartoœciami pocz¹tkowymi
	for (int i = 0; i < max_node; i++) {
		adjMST[i] = new int[max_node];

		for (int j = 0; j < max_node; j++) {
			adjMST[i][j] = 0;
		}
	}

	// Wype³nianie tablicy visited wartoœciami pocz¹tkowymi
	for (int i = 0; i < max_node; i++) {
		visited[i] = false;
	}
}

void Prim_matrix::initializeGraph(int size) {
	max_node = size;									
	
	adjGraph = new int* [size];				//inicjalizacja macierzy s¹siedztw

	for (int i = 0; i < size; i++) {
		adjGraph[i] = new int[size];

		for (int j = 0; j < size; j++) {
			adjGraph[i][j] = 0;
		}
	}
}

void Prim_matrix::addGraphNode(int v1, int v2, int w) {
	adjGraph[v1][v2] = w;
	adjGraph[v2][v1] = w;
}

void Prim_matrix::addMSTNode(int v1, int v2, int w) {
	adjMST[v1][v2] = w;
	adjMST[v2][v1] = w;
}

void Prim_matrix::createMST() {
	if (max_node < 1) {
		return;
	}

	initializeMST();

	int v = 0;

	visited[v] = true;

	for (int i = 1; i < max_node; i++) {
		for (int u = 0; u < max_node; u++) {
			if (v != u) {									// przek¹tna macierzy
				if (visited[u] == false && adjGraph[v][u] > 0) {
					pair<int, int> nodes = make_pair(v, u);
					Q.push(make_pair(adjGraph[v][u], nodes));
				}
			}
		}
		while (!Q.empty() && visited[Q.top().second.second]) {
			Q.pop();
		}
		int source = Q.top().second.first;				// wierzcho³ek Ÿród³owy
		int target = Q.top().second.second;				// wierzcho³ek docelowy
		int weight = Q.top().first;						// waga po³¹czenia miêdzy wierzcho³kami

		addMSTNode(source, target, weight);				
																		
		v = target;
		Q.pop();
		visited[v] = true;	
	}
}

void Prim_matrix::showGraph() {
	//Wyœwietlenie 1 wiersza zawieraj¹cego numery wierzcho³ków
	cout << " ";
	for (int i = 0; i < max_node; i++) {
		cout << "  " << i;
	}
	cout << '\n';

	for (int i = 0; i < max_node; i++) {
		cout << i << "  ";
		for (int j = 0; j < max_node; j++) {
			cout << adjGraph[i][j] << "  ";
		}
		cout << '\n';
	}
}

void Prim_matrix::showMST() {
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
