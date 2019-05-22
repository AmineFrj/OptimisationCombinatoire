#include "diam1.h"
#include "bfs.1.h"
#include "bfs.2.h"
#include <stdlib.h>
#include <ctime>
#include <iostream>
// Étant donné un graphe, cette fonction trouve 2 noeuds dont la distance
// (la longueur du plus court chemin entre ces 2 noeuds) est la plus grande
// possible: cela représentera une borne inférieure du diamètre.
//
// ATTENTION:
// Votre algorithme devra tourner en un temps maximal imparti par graphe:
// Tmax = 50ms + (M+N)*1µs, où M est le nombre d'arêtes et N de noeuds.
// Ça correspond a du O(M+N).
// Par exemple, si M = 10M (10 millions), N = 1M (1million), Tmax = 11.05s.
//
// Ensuite, le score dépendra uniquement du diamètre obtenu: plus il est
// grand, meilleur sera votre score.
// Mais si le temps dépasse (sur ma machine!), le score sera 0: gardez une
// bonne marge!
pair<int, int> DiametreLB(const UndirectedGraph& graph){
//    const time_t T = std::time(0), temps_max = CLOCKS_PER_SEC;
    clock_t temps_max = clock() + (CLOCKS_PER_SEC * 0.05 + CLOCKS_PER_SEC *(graph.NumNodes()+graph.NumEdges()-4) *0.000001)/2;
    pair<int,int> diam,best_diam;
    srand ((unsigned)time(0));
    vector<int> parents,distances;
    int node = rand()%graph.NumNodes()-1, max = -1, best_max = -1;
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
        diam.first = node;
        for (int i = 0; i < distances.size(); i++)
            if(distances[i] > max) {
                node = i;
                max = distances[i];
            }
        diam.second = node;
        if(max > best_max){
            best_max = max;
            best_diam = diam;
        }
    }
    return best_diam;
}
//    pair<int,int>
//    srand (time(NULL));
//    srand((unsigned)time(0));
//    rand() % n;//entre 0 et n-1
//    random_shuffle(v_begin(),v_end());
//    const clock_t = clock();
//    clock_t temps_max = clock() + CLOCKS_PER_SEC * (temps_en_sec);
//    while(clock()<temps_max)
