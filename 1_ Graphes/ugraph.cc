//
//  ugraph.cpp
//  Tp01
//
//  Created by FERDJAOUI Amine on 25/09/2018.
//  Copyright © 2018 FERDJAOUI Amine. All rights reserved.
//

#include <stdio.h>
#include <set>
#include "ugraph.h"

UndirectedGraph::UndirectedGraph(int num_n) : num_nodes(num_n)
{
    graph = new DirectedGraph(num_nodes);
    union_find.resize(num_n);
    for (int i=0; i<num_n; i++) union_find[i]=i;
}

void UndirectedGraph::AddEdge(int a, int b)
{
    graph->AddArc(a, b);
    graph->AddArc(b, a);
    int x=union_find[a];
    for (int i=0; i<num_nodes; i++) if (union_find[i]==x) union_find[i]=b;
}

int UndirectedGraph::NumNodes() const
{
    return num_nodes;
}

int UndirectedGraph::NumEdges() const
{
    return graph->NumNodes();
}

int UndirectedGraph::Degree(int node) const
{
    return graph->OutDegree(node);
}

const vector<int>& UndirectedGraph::Neighbors(int node) const
{
    return graph->Neighbors(node);
}

vector<int> UndirectedGraph::GetNodesConnectedTo(int node)
{
    vector<int> to_return;
    for (int i=0; i<num_nodes; i++) 
        if (union_find[i]==union_find[node]) to_return.push_back(i);
    
    return to_return;
}

vector<vector<int>> UndirectedGraph::ConnectedComponents()
{
    set<int> set;
    vector<vector<int>> to_return;
    std::set<int>::iterator it;
    
    for (int i=0; i<num_nodes; i++) {
        set.insert(union_find[i]);
    }
    it=set.begin();
    for (int i=0; i<set.size(); i++) {
        for (int j=0; j<num_nodes; j++) {
            std::advance(it, 1);
            if(union_find[j]==*it) to_return[i].push_back(j);
        }
    }
    return to_return;
}
