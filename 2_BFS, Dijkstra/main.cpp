//
//  main.cpp
//  Td2
//
//  Created by FERDJAOUI Amine on 27/09/2018.
//  Copyright © 2018 FERDJAOUI Amine. All rights reserved.
//

#include <iostream>
#include "graph.hpp"
#include "bfs.hpp"
#include "bfs2.hpp"
#include "bfs3.hpp"
#include "vgraph.hpp"


using namespace std;

int main(int argc, const char * argv[]) {
    
    VGraph vg(4);
    vg.AddArc(1, 2, 2.);
    vg.AddArc(1, 3, 4.);

        for (pair<int, double> i : vg.Neighbors(1)) {
            cout<<i.first<<i.second<<endl;
        }
    
    UndirectedGraph dg(6);
    dg.AddEdge(4, 3);
    dg.AddEdge(1, 3);
    dg.AddEdge(3, 2);
    dg.AddEdge(5, 0);
    dg.AddEdge(0, 2);

    for (int i : BFS(dg, 2)) {
        cout<<i;
    }
    cout<<"---------------\n";
    for (int i : GetShortestPathFromRootedTree(BFS(dg, 2),5)) {
        cout<<endl<<i;
    }
    
    return 0;
}
