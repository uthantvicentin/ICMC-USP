#include <bits/stdc++.h>

using namespace std;

int flag = 0;
int counter = 0;

struct Edge {
	int src, dest;
	string symbolTransition;
};

typedef pair<int, pair<string, pair<bool, bool>>> Pair;

class Graph {
	public:
		vector<vector<Pair>> adjList;

		Graph(vector<Edge> const &edges, int N, vector<int> init, vector<int> accept) {

			vector<int>::iterator it;

			adjList.resize(N);

			for (auto &edge: edges) {
				bool initial = false, acceptance = false;
				int src = edge.src;
				int dest = edge.dest;
				string symbolTransition = edge.symbolTransition;

				it = find (init.begin(), init.end(), src);
				if (it != init.end()) initial = true;

				it = find(accept.begin(), accept.end(), src);
				if (it != accept.end()) acceptance = true;

				adjList[src].push_back(make_pair(dest, 
							make_pair(symbolTransition,make_pair(initial,acceptance))));
			}
		}
};

int solve(Graph const &graph, int i, string chain, int pos){

	for (Pair v: graph.adjList[i]){
		if(pos == chain.size() and counter < 1){
			counter++;
			if(v.second.second.second == 1){
				flag = 1;
			}
			return 0;
		}
		else if(v.second.first[0] == chain[pos]){ 
			solve(graph, v.first, chain, ++pos);
		}
	}

	return 0;
}

void walkGraph(Graph const &graph, int N, string chain){

	for (int i = 0; i < N; i++){
		for (Pair v: graph.adjList[i]){
			if(v.second.second.first == 1){
				counter = 0;
				solve(graph, i, chain, 0);
				if(flag) break;
			}
		}
	}

	if(flag) cout << "aceita\n";
	else cout << "rejeita\n";

}

int main(){

	int qtStates, qtSymbolsTerminals, qtStatesInitials,qtStatesAcceptance,
			qtTransitions, src, dest, qtCadeias, acceptance;

	string symbolsTerminals, symbol;

	Edge insere;
	vector <Edge> edges;
	vector <string> chainProcessing;
	vector <int> statesInitials;
	vector <int> statesAcceptance;

	cin >> qtStates;
	cin >> qtSymbolsTerminals;
	getline(cin, symbolsTerminals);	

	cin >> qtStatesInitials;
	for(int i = 0 ; i < qtStatesInitials ; ++i) statesInitials.push_back(i);

	cin >> qtStatesAcceptance;
	
	for(int i = 0 ; i < qtStatesAcceptance ; ++i){
		cin >> acceptance;
		statesAcceptance.push_back(acceptance);
	}

	cin >> qtTransitions;

	for(int i = 0 ; i < qtTransitions ; ++i){
		cin >> src >> symbol >> dest;
		insere = {src, dest, symbol};	
		edges.push_back(insere);
	}

	Graph graph(edges, qtStates, statesInitials, statesAcceptance);

	cin >> qtCadeias;	

	for(int i = 0 ; i < qtCadeias ; ++i){
		flag = 0;

		cin >> symbol;
		walkGraph(graph, qtStates, symbol);
	}

	return 0;
}
