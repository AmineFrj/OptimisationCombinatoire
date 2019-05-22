//
//  bfs3.cpp
//  Td2
//
//  Created by FERDJAOUI Amine on 28/09/2018.
//  Copyright © 2018 FERDJAOUI Amine. All rights reserved.
//

#include "bfs3.hpp"

using namespace std;

vector<int> GetShortestPathFromRootedTree(const vector<int>& parent, int target){
    vector<int> shortestP;
    int parents = parent[target], i = target;
    if (parent[target]!=-1){
        shortestP.push_back(i);
        while (parents!=i) {
            i = parents;
            parents = parent[parents];
            shortestP.push_back(i);
        }
    }
    reverse(shortestP.begin(), shortestP.end());
    return shortestP;
}
