//
//  vgraph.cpp
//  Td2
//
//  Created by FERDJAOUI Amine on 28/09/2018.
//  Copyright © 2018 FERDJAOUI Amine. All rights reserved.
//

#include "vgraph.hpp"

VGraph::VGraph(int num_nodes) : neighbors_(num_nodes), num_arcs_(0) {}

void VGraph::AddArc(int from, int to, double length) {
    pair<int, double> tmp;
    tmp.first = to;
    tmp.second = length;
    neighbors_[from].push_back(tmp);
    ++num_arcs_;
}

int VGraph::NumNodes() const {
    return neighbors_.size();
}

int VGraph::NumArcs() const {
    return num_arcs_;
}

int VGraph::OutDegree(int node) const {
    return neighbors_[node].size();
}

const vector<pair<int, double>>& VGraph::Neighbors(int node) const {
    return neighbors_[node];
}

//void VGraph::MakeSimple() {
//    vector<bool> visited(NumNodes(), false);
//    for (int i = 0; i < NumNodes(); ++i) {
//        vector<int>& adj = neighbors_[i];
//        int kept = 0;
//        for (int& x : adj) {
//            if (x != i && !visited[x]) {
//                visited[x] = true;
//                adj[kept++] = x;
//            }
//        }
//        adj.resize(kept);
//        for (int x : adj) visited[x] = false;
//    }
//}

