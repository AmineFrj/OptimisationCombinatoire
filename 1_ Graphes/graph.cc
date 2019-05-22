//
//  graph.cpp
//  Tp01
//
//  Created by FERDJAOUI Amine on 25/09/2018.
//  Copyright © 2018 FERDJAOUI Amine. All rights reserved.
//

#include <stdio.h>
#include "graph.h"

DirectedGraph::DirectedGraph(int num_n) : num_nodes(num_n)
{
    adj_list.resize(num_nodes,vector<int>(0));
}

int DirectedGraph::NumNodes() const
{
    return num_nodes;
}

void DirectedGraph::AddArc(int from, int to)
{
    adj_list[from].push_back(to);
}

int DirectedGraph::OutDegree(int node) const
{
    return adj_list[node].size();
}

const vector<int>& DirectedGraph::Neighbors(int node) const
{
    return adj_list[node];
}

void DirectedGraph::MakeSimple()
{
    for (int i=0; i<adj_list.size(); i++) {
        for (int j=0; j<adj_list[j].size(); j++) {
            if (adj_list[i][j]==i) {
                adj_list[i].push_back(j); i--;
            }
        }
        sort(adj_list[i].begin(), adj_list[i].end());
        adj_list[i].erase(unique(adj_list[i].begin(), adj_list[i].end()), adj_list[i].end());
    }
}
