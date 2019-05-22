#include "kruskal.h"
#include <set>
#include <iostream>
bool operator<(const Edge& e1, const Edge& e2) { 
	return e1.weight > e2.weight;
}

double Kruskal(const vector<Edge>& graph) {
	double total = 0;
	priority_queue<Edge> pq;
  int max=0;
	for (int i = 0; i < graph.size(); ++i){
		pq.push(graph[i]);
    if (graph[i].from>max) max = graph[i].from;
    if (graph[i].to>max) max = graph[i].to;
	}
	UnionFind u(max+1);
	while(not pq.empty()){
		if (u.AddEdge(pq.top().from,pq.top().to))
			total += pq.top().weight;
		pq.pop();
	}
	return total;
}



// *** PAS BESOIN DE TROP REGARDER CE QUI EST PLUS BAS ***

// Implementation de la class UnionFind.
UnionFind::UnionFind(int num_nodes)
  : parent_(num_nodes, -1), depth_(num_nodes, 1) {
  for (int i = 0; i < parent_.size(); ++i) parent_[i] = i;
}

bool UnionFind::AddEdge(int a, int b) {
  const int ra = GetRoot(a);
  const int rb = GetRoot(b);
  if (ra == rb) return false;  // Already connected.
  if (depth_[ra] > depth_[rb]) {
    parent_[rb] = ra;
  } else {
    parent_[ra] = rb;
    if (depth_[ra] == depth_[rb]) ++depth_[rb];
  }
  return true;
}

int UnionFind::GetRoot(int a) {
  int r = a;
  while (r != parent_[r]) r = parent_[r];
  const int root = r;
  for (int r = a; r != root; ) {
    const int p = parent_[r];
    parent_[r] = root;
    r = p;
  }
  return root;
}
