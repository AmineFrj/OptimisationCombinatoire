#include "prim.h"
#include <functional>
#include <queue>
#include <iostream>
// Renvoie le poids de l'arbre couvrant minimal pour le graphe valué donné:
// N est le nombre de sommets, et "edges" liste toutes les arêtes du graphe,
// avec leur poids.
//
// EXEMPLE: N = 4, edges = [{0, 1, 23}, {1, 3, 13}, {2, 1, 6}, {3, 2, 11}, {0, 2, 41}]
//
//    .--[23]--1--[13]--.      Les noeuds sont 0,1,2,3.
//  .´         |         `.    Les poids des arêtes sont entre [ ].
// 0          [6]          3
//  `.         |         .´    Arbre couvrant minimal: 23 + 6 + 11 = 40.
//    `--[41]--2--[11]--´
//
//struct Edge {
//  int node1;
//  int node2;
//  int weight;
//};

struct NodeDist {
    int node;
    int dist;
    bool operator<(const NodeDist& other) const{
        return dist > other.dist;
    }
    NodeDist(int n, int d){
        node = n;
        dist = d;
    }
};

int Prim(int N, const vector<Edge>& edges){
//    auto cmp = [](NodeDist e1, NodeDist e2) { return e1.dist < e2.dist; };
    vector<int> visited;
    priority_queue<NodeDist> pq;
    //    priority_queue<NodeDist, vector<NodeDist>, decltype(cmp)> pq;

    int weight = 0, n = 0, choix;
    if (N > 1) {
        //    NodeDist tmp (0,0); = {} //init with 0s
        visited.push_back(edges[0].node1);
        for (Edge i : edges)
            if(i.node1 == edges[0].node1)
                pq.push(NodeDist(i.node2,i.weight));
            else if (i.node2 == edges[0].node1)
                pq.push(NodeDist(i.node1,i.weight));
        
        while (not pq.empty() && n<N-1){
            if (find(visited.begin(), visited.end(), pq.top().node) != visited.end())
                pq.pop();
            else{
                choix = pq.top().node;
                visited.push_back(choix);
    //            cout<<choix<<"---"<<pq.top().dist<<endl;
                weight += pq.top().dist;
                pq.pop();
                n++;
                for (Edge i : edges)
                    if ((i.node1 == choix) && (find(visited.begin(), visited.end(), i.node2) == visited.end()))
                        pq.push(NodeDist(i.node2,i.weight));
                    else if ((i.node2 == choix) && (find(visited.begin(), visited.end(), i.node1) == visited.end()))
                        pq.push(NodeDist(i.node1,i.weight));
            }
        }
    }
    return weight;
}

