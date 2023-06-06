#include "Kruskal_list.h"

using namespace std;

Kruskal_list::Kruskal_list() {
	Kruskal_list::max_node = 0;
}

//destruktor usuwa ca³¹ strukture Kruskal_list
Kruskal_list::~Kruskal_list() {
	clearMST();
	clearGraph();
}

void Kruskal_list::initializeGraph(int size) {
	max_node = size;
	adjGraph.resize(size);					// Lista s¹siadów grafu
}

void Kruskal_list::initializeMST() {
	clearMST();
	adjMST.resize(max_node);				// Lista s¹siadów drzewa MST

}

void Kruskal_list::clearGraph() {
	adjGraph.clear();
	max_node = 0;
}

void Kruskal_list::clearMST() {
	adjMST.clear();

	while (!Q.empty()) {
		Q.pop();
	}
}

void Kruskal_list::addGraphNode(int v1, int v2, int w) {
	auto wv = make_pair(w, v2);
	adjGraph[v1].push_back(wv);

	wv = make_pair(w, v1);
	adjGraph[v2].push_back(wv);
}

void Kruskal_list::addMSTNode(int v1, int v2, int w) {
	auto wv = make_pair(w, v2);
	adjMST[v1].push_back(wv);

	wv = make_pair(w, v1);
	adjMST[v2].push_back(wv);
}

struct Subset {
	int parent;
	int rank;
};

int find(Subset subsets[], int i) {
	if (subsets[i].parent != i) {
		subsets[i].parent = find(subsets, subsets[i].parent);
	}

	return subsets[i].parent;
}

void unionSets(Subset subsets[], int x, int y) {
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	// jeœli ranga x jest mniejsza to rodzicem x staje siê y
	if (subsets[xroot].rank < subsets[yroot].rank) {
		subsets[xroot].parent = yroot;
	}
	else if (subsets[xroot].rank > subsets[yroot].rank) {
		subsets[yroot].parent = xroot;
	}
	//jeœli rangi s¹ równe to rodzicem y staje siê x oraz inkrementujemy range x
	else {
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

void Kruskal_list::createMST() {
	if (max_node < 1) {
		return;
	}
	initializeMST();

	for (int v = 0; v < max_node; v++) {
		for (auto& edge : adjGraph[v]) {
			if (v < edge.second) {
				Q.push({ edge.first, {v, edge.second} });
			}
		}
	}

	Subset* subsets = new Subset[max_node];

	//tworzenie osobnego zbioru dla ka¿dego wierzcho³ka
	for (int v = 0; v < max_node; v++) {
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	while (!Q.empty()) {
		auto edge = Q.top();
		Q.pop();

		int u = find(subsets, edge.second.first);
		int v = find(subsets, edge.second.second);

		// sprawdzenie czy wierzcho³ki nale¿¹ do tego samego zbioru
		if (u != v) {
			addMSTNode(edge.second.first, edge.second.second, edge.first);

			// dodawanie wierzcho³ków do jednego zbioru
			unionSets(subsets, u, v);
		}
	}

	delete[] subsets;
}

void Kruskal_list::showMST() {
	int koszt = 0;
	for (int i = 0; i < max_node; i++) {
		cout << i << " : ";
		list<Pi>::iterator j;
		for (j = adjMST[i].begin(); j != adjMST[i].end(); j++) {
			cout << '(' << (*j).second << "|" << "waga: " << (*j).first << ") ";
			koszt += (*j).first;
		}
		cout << '\n';
	}
	koszt /= 2;
	cout << "koszt drzewa: " << koszt << '\n';
}

