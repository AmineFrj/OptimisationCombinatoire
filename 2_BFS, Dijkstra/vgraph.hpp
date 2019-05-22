//
//  vgraph.hpp
//  Td2
//
//  Created by FERDJAOUI Amine on 28/09/2018.
//  Copyright © 2018 FERDJAOUI Amine. All rights reserved.
//

#ifndef vgraph_hpp
#define vgraph_hpp

#include <stdio.h>
#include <vector>
#include <utility>

using namespace std;

class VGraph {
public:
    // At construction, the graph has no arcs.
    explicit VGraph(int num_nodes);
    
    int NumNodes() const;
    int NumArcs() const;
    
    void AddArc(int from, int to, double length);
    
    // Returns the number of arcs originating from "node".
    // In the example above, OutDegree(1) = 3, OutDegree(4) = 0.
    int OutDegree(int node) const;
    
    // Returns all the destination nodes that were added with arcs
    // originating from "node".
    // In the example above, Neighbors(1) is {0, 2, 3} and Neighbors(2) is {0}.
    const vector<pair<int, double>>& Neighbors(int node) const;
    
//    void MakeSimple();
    
private:
    vector<vector<pair<int, double>>> neighbors_;
    int num_arcs_;
};

#endif /* vgraph_hpp */
