#include "diam1.h"
#include "bfs.1.h"
#include "bfs.2.h"
#include "bfs.3.h"
#include <stdlib.h>
#include <ctime>
#include <iostream>

// Étant donné un graphe, cette fonction renvoie soit:
// - un noeud (donc, un vector<int> avec un seul élément) "central",
//   qui minimise le "rayon" du graphe pour ce centre: le "rayon" est
//   la plus grande distance à un autre noeud du graphe.
// - une sous-clique centrale, c'est-à-dire un sous-ensemble de noeuds
//   tels qu'ils soient tous directement connectés entre eux par une
//   arête, et tel que le "rayon" soit minimal pour ce "multi-centre".
//
// Dans les 2 cas, on peut déduire une borne supérieure sur le diamètre
// du graphe:
// - si on a renvoyé un noeud de rayon R: Diamètre <= 2*R
// - si on a renvoyé une sous-clique de rayon R: Diamètre <= 2*R+1
//
// Pour faire simple, vous pourrez vous limiter à renvoyer un simple noeud.
// Pour être un peu meilleur, vous pourrez renvoyer une arête (2 noeuds
// liés par une arête). Voire une sous-clique...
//
// ATTENTION:
// Même temps maximal imparti que pour l'exercice précédent.
// Le score sera fonction de la borne sup du diamètre (voire formule en haut):
// plus elle est petite, meilleur sera le score.

vector<int> DiametreUB(const UndirectedGraph& graph){
    clock_t temps_max = clock() + (CLOCKS_PER_SEC * 0.05 + CLOCKS_PER_SEC *(graph.NumNodes()+graph.NumEdges()-4) *0.000001)/2;
    srand ((unsigned)time(0));
    vector<int> parents,distances, best_parents, center;
    int node = rand()%graph.NumNodes()-1, max = -1, best_max = -1, best_end = 0;
    while (clock() < temps_max) {
        node = rand()%(graph.NumNodes()-1);
        max = -1;
        parents = BFS(graph,node);
        distances = GetBfsDistances(parents);
        for (int i = 0; i < distances.size(); i++)
            if(distances[i] > max) {
                node = i;
                max = distances[i];
            }
        max = 0;
        parents = BFS(graph,node), distances = GetBfsDistances(parents);
        for (int i = 0; i < distances.size(); i++)
            if(distances[i] > max) {
                node = i;
                max = distances[i];
            }
        if(max > best_max){
            best_parents.clear();
            for(int i : parents)
                best_parents.push_back(i);
            best_max = max;
            best_end = node;
        }
    }
    vector<int> path;
    path = GetShortestPathFromRootedTree(best_parents,best_end);
//    if(path.size()%2==1)
        center.push_back(path[path.size()/2]);
//    else{
//        center.push_back(path[(int(path.size()/2))-1]);
//        center.push_back(path[path.size()/2]);
//    }
    return center;
}
