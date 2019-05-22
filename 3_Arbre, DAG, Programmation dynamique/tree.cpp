//
//  tree.cpp
//  Td2
//
//  Created by FERDJAOUI Amine on 04/10/2018.
//  Copyright © 2018 FERDJAOUI Amine. All rights reserved.
//

#include "tree.hpp"

vector<vector<int>> ParentVectorToChildrenVector(const vector<int>& parent){
    vector<vector<int>> children(parent.size(),vector<int>(0));
    for(int i = 0; i < parent.size(); i++)
        if(parent[i]!=-1) children[parent[i]].push_back(i) ;
    
    return children;
}

// Exemple:
//    .3.     vector<vector<int>> enfants = [ [], [], [1], [2, 0, 4], [] ]
//  .' | '.
//  2  0  4   -> AllHeights(enfants) = [0, 0, 1, 2, 0]
//  |
//  1

int Height(const vector<vector<int>>& enfants, int node){
    if (enfants[node].empty()) return 0;
    int tmp = 0;
    for(int i : enfants[node])
        tmp = max(tmp, Height(enfants, i));
    
    return tmp+1;
}

vector<int> AllHeights(const vector<vector<int>>& enfants){
    vector<int> heights(enfants.size(),-1);
    HeightRec(enfants, 0, heights);
    return heights;
}


void HeightRec(const vector<vector<int>>& enfants, int node, vector<int>& heights){
    if (enfants[node].empty()) heights[node] = 0;
    int tmp = 0;
    for(int i : enfants[node]){
        HeightRec(enfants, i, heights);
        tmp = max(tmp, heights[i]);
    }
    heights[node] = tmp+1;
}

