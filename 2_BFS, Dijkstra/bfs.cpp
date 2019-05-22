//
//  bfs.cpp
//  Td2
//
//  Created by FERDJAOUI Amine on 27/09/2018.
//  Copyright © 2018 FERDJAOUI Amine. All rights reserved.
//
 

#include "bfs.hpp"
#include <queue>
#include <iostream>


vector<int> BFS(const UndirectedGraph& graph, int src){
    queue<int> file;
    vector<int> parents(graph.NumNodes(),-1);
    parents[src]=src;
    file.push(src);
    int nv;
    while (not file.empty()) {
        nv=file.front();
        file.pop();
        for (int i : graph.Neighbors(nv)) {
            if(parents[i]==-1) {
                file.push(i);
                parents[i]=nv;
            }
        }
    }
    return parents;
}
