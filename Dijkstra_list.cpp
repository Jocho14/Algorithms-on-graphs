#include "Dijkstra_list.h"

using namespace std;

Dijkstra_list::Dijkstra_list() {
	Dijkstra_list::max_node = 0;
	Dijkstra_list::d = nullptr;
	Dijkstra_list::p = nullptr;
}

//destruktor usuwa ca�� strukture Dijkstra_list
Dijkstra_list::~Dijkstra_list() {
	clearSP();
	clearGraph();
}

void Dijkstra_list::initializeGraph(int size) {
	max_node = size;
	adjGraph.resize(size);					// Lista s�siad�w grafu
}

void Dijkstra_list::initializeSP() {
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

void Dijkstra_list::setStartingNode(int _startingNode){
	startingNode = _startingNode;
}

void Dijkstra_list::clearGraph() {
	adjGraph.clear();
	max_node = 0;
}

void Dijkstra_list::clearSP() {
	delete[] d;
	delete[] p;

	while (!Q.empty()) {
		Q.pop();
	}
}

void Dijkstra_list::addGraphNode(int v1, int v2, int w) {
	pair<int, int> wv = make_pair(w, v2);
	adjGraph[v1].push_back(wv);
}

// algorytm wyszukiwania najkr�tszej �cie�ki
void Dijkstra_list::createSP() {
	if (max_node < 1) {
		return;
	}
	initializeSP();
	
	Q.push({ 0, startingNode });				// {waga, wierzcho�ek}

	while (!Q.empty()) {			
		int u = Q.top().second;	
		Q.pop();

		for (auto& edge : adjGraph[u]) {
			int weight = edge.first;
			int v = edge.second;
			
			if (d[u] + weight < d[v]) {			// sprawdzenie czy dotychczasowa droga jest d�u�sza
				d[v] = d[u] + weight;
				p[v] = u;						// ustawienie odpowiedniego poprzednika

				Q.push({ d[v], v });
			}
		}
	}
}

void Dijkstra_list::showGraph() {
	for (int i = 0; i < max_node; i++) {
		cout << i << " : ";
		list<Pi>::iterator j;
		for (j = adjGraph[i].begin(); j != adjGraph[i].end(); j++) {
			cout << '(' << (*j).second << "|" << "waga: " << (*j).first << ") ";
		}
		cout << '\n';
	}
}

void Dijkstra_list::showSP() {
	for (int i = 0; i < max_node; i++) {
		int tempNode = i;
		cout << tempNode <<" ";
		while (p[tempNode] != -1) {				// wypisywanie �cie�ki do wierzcho�ka id�c
			cout << " <- " << p[tempNode]; 		// od wierzcho�ka bie��cego do wierzcho�ka �r�d�owego
			tempNode = p[tempNode];
		}

		cout << " koszt sciezki: " << d[i] << '\n';
	}
}

