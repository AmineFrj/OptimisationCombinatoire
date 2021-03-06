//
//  ugraph.h
//  Tp01
//
//  Created by FERDJAOUI Amine on 25/09/2018.
//  Copyright © 2018 FERDJAOUI Amine. All rights reserved.
//

#ifndef ugraph_h
#define ugraph_h
#include "graph.h"

// An undirected graph is just like a directed graph, but arcs are called
// "edges" and they don't have a direction: an edge (a, b) is present both
// in the adjacency list of a and the adjacency list of b.
class UndirectedGraph {
public:
    explicit UndirectedGraph(int num_nodes);
    void AddEdge(int a, int b);
    
    int NumNodes() const;
    int NumEdges() const;
    int Degree(int node) const;
    const vector<int>& Neighbors(int node) const;
    vector<int> GetNodesConnectedTo(int node);
    vector<vector<int>> ConnectedComponents();
    
private:
    // TODO
    // HINT: Use a DirectedGraph where you store each edge (a, b) as two arcs
    // a->b and b->a !
    const int num_nodes;
    DirectedGraph* graph;
    vector<int> union_find;
};


#endif /* ugraph_h */
