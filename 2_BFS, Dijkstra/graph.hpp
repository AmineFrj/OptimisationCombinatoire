//
//  graph.hpp
//  Td2
//
//  Created by FERDJAOUI Amine on 27/09/2018.
//  Copyright © 2018 FERDJAOUI Amine. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <stdio.h>
#include <vector>
using namespace std;
// A directed graph is a set of nodes, linked by arcs. Arcs are directed: they
// go from a node to another node.
// In this implementation, each node is an integer in [0, num_nodes-1].
//
// For example, the following graph:
//
//  0 <--- 1 <--> 3 ---> 4
//  ^      |       \     ^
//  |      v        `----'
//  '----- 2
//
// Can be obtained by:
//   DirectedGraph g(5);
//   g.AddArc(1, 0);
//   g.AddArc(1, 3);
//   g.AddArc(3, 1);
//   g.AddArc(2, 0);
//   g.AddArc(1, 2);
//   g.AddArc(3, 4);
//   g.AddArc(3, 4);
//
class DirectedGraph {
public:
    // At construction, the graph has no arcs.
    explicit DirectedGraph(int num_nodes);
    
    int NumNodes() const;
    int NumArcs() const;
    
    void AddArc(int from, int to);
    
    // Returns the number of arcs originating from "node".
    // In the example above, OutDegree(1) = 3, OutDegree(4) = 0.
    int OutDegree(int node) const;
    
    // Returns all the destination nodes that were added with arcs
    // originating from "node".
    // In the example above, Neighbors(1) is {0, 2, 3} and Neighbors(2) is {0}.
    const std::vector<int>& Neighbors(int node) const;
    
    void MakeSimple();
    
private:
    std::vector<std::vector<int>> neighbors_;
    int num_arcs_;
};
#endif /* graph_hpp */
