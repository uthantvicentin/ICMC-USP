/* 
 * ICMC-USP
 * Trabalho em Grupo 1
 * SCC-5832
 *
 * Objetivo
 *  Desenvolver o entendimento de Linguagens Formais e seu potencial de 
 *  representação através da implementação de simuladores de autômatos finitos.
 *
 * Nome: Marina Ariane Dulcini di Marzo
 * ID USP: 3371320
 *
 * Nome: Uthant Vicentin Leite
 * ID USP: 10780024
 */

#include <bits/stdc++.h>

using namespace std;

//Variaveis de controle para critério de aceitação da linguagem
int flag = 0;
int counter = 0;

//Estrutura da aresta
struct Edge {
  int src, dest;
  string symbolTransition;
};

//Definição da estrutura do nó
typedef pair<int, pair<string, pair<bool, bool>>> Pair;

//Classe para instaciação dos nós
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
        
        //identificação de nós iniciais
        it = find (init.begin(), init.end(), src);
        if (it != init.end()) initial = true;

        //identificação de nós de aceitação
        it = find(accept.begin(), accept.end(), src);
        if (it != accept.end()) acceptance = true;

        //criação do nó
        adjList[src].push_back(make_pair(dest, 
              make_pair(symbolTransition,make_pair(initial,acceptance))));
      }
    }
};

//Método recursivo para resolução do problema
int solve(Graph const &graph, int i, string chain, int pos){

  for (Pair v: graph.adjList[i]){
    if(flag < 1 and counter < 1){
      if(pos >= chain.size()){
        counter++;
        if(v.second.second.second == 1) flag = 1;
      }
      else if(v.second.first[0] == chain[pos]) solve(graph, v.first, chain, pos+1);
    }
  }

  return 0;
}

//Método para chamar a recursão 'solve' para todos os nós iniciais
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
  
  //Variaveis de leitura do input
  int qtStates, qtSymbolsTerminals, qtStatesInitials,qtStatesAcceptance,
      qtTransitions, src, dest, qtCadeias, acceptance;
  
  string symbolsTerminals, symbol;

  Edge insert;
  vector <Edge> edges;
  vector <string> chainProcessing;
  vector <int> statesInitials;
  vector <int> statesAcceptance;
  
  //Inicio da leitura do input
  cin >> qtStates;
  cin >> qtSymbolsTerminals;
  getline(cin, symbolsTerminals);	


  //Atribuição dos nós iniciais
  cin >> qtStatesInitials;
  for(int i = 0 ; i < qtStatesInitials ; ++i) statesInitials.push_back(i);

  //Atribuição dos nós de aceitação
  cin >> qtStatesAcceptance;
  for(int i = 0 ; i < qtStatesAcceptance ; ++i){
    cin >> acceptance;
    statesAcceptance.push_back(acceptance);
  }

  //Atribuição das transições
  cin >> qtTransitions;
  for(int i = 0 ; i < qtTransitions ; ++i){
    cin >> src >> symbol >> dest;
    insert = {src, dest, symbol};	
    edges.push_back(insert);
  }

  //Construção da estrutura de grafos
  Graph graph(edges, qtStates, statesInitials, statesAcceptance);

  //Leitura das cadeias
  cin >> qtCadeias;	
  for(int i = 0 ; i < qtCadeias ; ++i){
    flag = 0;
    cin >> symbol;
    walkGraph(graph, qtStates, symbol);
  }

  return 0;
}
