#include "Dijkstra_matrix.h"

using namespace std;

Dijkstra_matrix::Dijkstra_matrix() {
	Dijkstra_matrix::max_node = 0;
	Dijkstra_matrix::adjGraph = NULL;
	Dijkstra_matrix::d = nullptr;
	Dijkstra_matrix::p = nullptr;
}

//destruktor usuwa ca�� strukture Dijkstra_matrix
Dijkstra_matrix::~Dijkstra_matrix() {
	clearSP();
	clearGraph();
}

void Dijkstra_matrix::initializeGraph(int size) {
	max_node = size;
	adjGraph = new int* [size];				//inicjalizacja macierzy s�siedztw

	for (int i = 0; i < size; i++) {
		adjGraph[i] = new int[size];

		for (int j = 0; j < size; j++) {
			adjGraph[i][j] = 0;
		}
	}
}

void Dijkstra_matrix::initializeSP() {
	clearSP();

	d = new int[max_node];
	p = new int[max_node];

	d[startingNode] = 0;						// ustawienie drogi do wierzcho�ka startowego na 0
	p[startingNode] = -1;						// ustwienie poprzednika wierzcho�ka startowego na -1 (brak poprzednika)

	// inicjalizacja tablicy d i p, INT_MAX reprezentuje niesko�czono��
	for (int i = 0; i < max_node; i++) {
		if (!(i == startingNode)) {
			d[i] = INT_MAX;						// ustawianie pocz�tkowych warto�ci dr�g do pozosta�ych wierzcho�k�w na niesko�czono��
			p[i] = -1;							// ustawienie poprzednik�w na -1
		}
	}
}

void Dijkstra_matrix::setStartingNode(int _startingNode) {
	startingNode = _startingNode;
}

void Dijkstra_matrix::clearGraph() {
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

void Dijkstra_matrix::clearSP() {
	delete[] d;
	delete[] p;

	while (!Q.empty()) {
		Q.pop();
	}
}

void Dijkstra_matrix::addGraphNode(int v1, int v2, int w) {
	adjGraph[v1][v2] = w;
}

// algorytm wyszukiwania najkr�tszej �cie�ki
void Dijkstra_matrix::createSP() {
	if (max_node < 1) {
		return;
	}
	initializeSP();

	Q.push({ 0, startingNode });				// {waga, wierzcho�ek}

	while (!Q.empty()) {
		int u = Q.top().second;
		Q.pop();

		for (int i = 0; i < max_node; i++) {
			int weight = adjGraph[u][i];
			if (weight > 0) {
				int v = i;
				if (d[u] + weight < d[v]) {			// sprawdzenie czy dotychczasowa droga jest d�u�sza
					d[v] = d[u] + weight;
					p[v] = u;						// ustawienie odpowiedniego poprzednika

					Q.push({ d[v], v });
				}
			}
		}
	}
}

void Dijkstra_matrix::showGraph() {
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

void Dijkstra_matrix::showSP() {
	for (int i = 0; i < max_node; i++) {
		int tempNode = i;
		cout << tempNode << " ";
		while (p[tempNode] != -1) {				// wypisywanie �cie�ki do wierzcho�ka id�c
			cout << " <- " << p[tempNode]; 		// od wierzcho�ka bie��cego do wierzcho�ka �r�d�owego
			tempNode = p[tempNode];
		}

		cout << " koszt sciezki: " << d[i] << '\n';
	}
}

