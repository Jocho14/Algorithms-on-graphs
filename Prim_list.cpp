#include "Prim_list.h"

using namespace std;

Prim_list::Prim_list() {
	Prim_list::max_node = 0;
	Prim_list::visited = NULL;
}

//destruktor usuwa ca³¹ strukture Prim_list
Prim_list::~Prim_list() {
	if (visited != NULL) {
		delete visited;
	}
}

void Prim_list::initializeGraph(int size) {
	max_node = size;
	adjGraph.resize(size);					// Lista s¹siadów grafu
}

void Prim_list::initializeMST() {
	clearMST();
	adjMST.resize(max_node);				// Lista s¹siadów drzewa MST

	visited = new bool[max_node];
	for (int i = 0; i < max_node; i++) {
		visited[i] = false;
	}
}

void Prim_list::clearGraph() {
	if (visited != NULL) {
		delete[] visited;
		visited = NULL;
	}
	adjGraph.clear();
	max_node = 0;
}

void Prim_list::clearMST() {
	adjMST.clear();

	while (!Q.empty()) {
		Q.pop();
	}
}

void Prim_list::addGraphNode(int v1, int v2, int w) {
	pair<int, int> wv = make_pair(w, v2);
	adjGraph[v1].push_back(wv);

	wv = make_pair(w, v1);
	adjGraph[v2].push_back(wv);
}

void Prim_list::addMSTNode(int v1, int v2, int w) {
	pair<int, int> wv = make_pair(w, v2);
	adjMST[v1].push_back(wv);

	wv = make_pair(w, v1);
	adjMST[v2].push_back(wv);
}

void Prim_list::createMST() {
	if (max_node < 1) {
		return;
	}

	initializeMST();
	
	int v = 0;

	visited[v] = true;

	for (int i = 1; i < max_node; i++) {
		for (auto& edge : adjGraph[v]) {  // teraz iterujemy przez s¹siaduj¹ce wierzcho³ki
			int u = edge.second;
			int w = edge.first;

			if (visited[u] == false && w > 0) {
				pair<int, int> nodes = make_pair(v, u);
				Q.push(make_pair(w, nodes));
			}
		}
		while (!Q.empty() && visited[Q.top().second.second]) {
			Q.pop();
		}
		int source = Q.top().second.first;
		int target = Q.top().second.second;
		int weight = Q.top().first;

		addMSTNode(source, target, weight);

		v = target;
		Q.pop();
		visited[v] = true;
	}
}


void Prim_list::showGraph() {
	for (int i = 0; i < max_node; i++) {
		cout << i << " : ";
		list<Pi>::iterator j;
		for (j = adjGraph[i].begin(); j != adjGraph[i].end(); j++) {
			cout << '(' << (*j).second << "|" << "waga: " << (*j).first << ") ";
		}
		cout << '\n';
	}
}

void Prim_list::showMST() {
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