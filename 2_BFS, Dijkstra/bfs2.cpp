//
//  bfs2.cpp
//  Td2
//
//  Created by FERDJAOUI Amine on 28/09/2018.
//  Copyright © 2018 FERDJAOUI Amine. All rights reserved.
//

#include "bfs2.hpp"

using namespace std;

vector<int> GetBfsDistances(const vector<int>& parent){
    vector<int> bfsDist(parent.size(),0);
    int dist,racine,j;
    for (int i=0; i<parent.size(); i++) {
        dist = 0;
        j=i;
        racine = parent[i];
        while (racine!=j && racine!=-1) {
            j=racine;
            racine = parent[racine];
            dist++;
        }
        bfsDist[i]=dist;
    }
    return bfsDist;
}
