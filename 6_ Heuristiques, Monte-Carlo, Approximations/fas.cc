#include "fas.h"
#include <iostream>
using namespace std;
// Renvoie un sous-graphe de "graph" (même noeuds, mais un sous-ensemble des
// arcs), acyclique, et avec le plus d'arcs possible.
// Comme les exercices précédents, vous aurez un temps maximal par graphe,
// un peu supérieur cette fois:
// Tmax = 50ms + (M+N)*10µs
//
// Le score sera:
// - 0 si la sortie est incorrecte, ne serait-ce que sur un ensemble de test.
// - si toutes les sorties sont correctes, la somme des scores:
//   - chaque score sera de 0 si le temps max est dépassé
//   - sinon il dépendra du nombre d'arcs du graphe que vous renvoyez.

//int unionFind(const DirectedGraph& graphSrc, const DirectedGraph& other, DirectedGraph& copy){
//
//    vector<vector<int>> ind(graphSrc.NumNodes(),vector<int>(0));
//    vector<vector<int>> findAll(graphSrc.NumNodes(),vector<int>(0));
//    int count = 0;
//    for (int i = 0; i < graphSrc.NumNodes(); i++)
//        for(int j : graphSrc.Neighbors(i)){
//            if(i!=j){
//                findAll[i].push_back(j);
//                ind[j].push_back(i);
//                for(int k : findAll[j]){
//                    findAll[i].push_back(k) ;
//                    ind[k].push_back(i);
//                }
//                for(int k : ind[i]){
//                    findAll[k].push_back(j);
//                    ind[j].push_back(k);
//                }
//                
//            }
//        }
//    
//
//    for (int i = 0; i < graphSrc.NumNodes(); i++)
//        for(int j : other.Neighbors(i)){
//            if(ind[i]!=ind[j]){
//                if(i!=j){
//                    count++;
//                    findAll[ind[i]].push_back(j);
//                    for(int k : findAll[j]){
//                        ind[k]=ind[i];
//                        findAll[ind[i]].push_back(k);
//                    }
//                    findAll[j].clear();
//                    ind[j]=ind[i];
//    //                save = ind[j];
//                    copy.AddArc(i,j);
////                for(int k=0; k<ind.size(); k++)
////                    if(ind[k]==save) ind[k]=ind[i];
//                 }
//            }
//        }
//    return count;
//}

DirectedGraph MaxDAG(const DirectedGraph& graph){
    clock_t temps_max = clock() + (CLOCKS_PER_SEC * 0.05 + CLOCKS_PER_SEC *(graph.NumNodes()+graph.NumArcs()-4) *0.00001)/2;
    vector<int> classif;
    int g0N = 0, g1N = 0;
    for (int i = 0; i < graph.NumNodes(); i++)
        classif.push_back(i);
    
        DirectedGraph g0(graph.NumNodes()),g1(graph.NumNodes());
        g0N = 0;
        g1N = 0;
        random_shuffle(classif.begin(),classif.end());
        for (int i = 0; i < graph.NumNodes(); i++)
            for(int j : graph.Neighbors(i))
                if(classif[i]>classif[j]){
                    g0.AddArc(i,j);
                    g0N++;
                }
                else if (classif[i]<classif[j]){
                    g1.AddArc(i,j);
                    g1N++;
                }

    if (g1N>g0N) {
        DirectedGraph* tmp;
        tmp = &g1;
        g1=g0;
        g0=*tmp;
    }
    
    vector<vector<int>> ind(g0.NumNodes(),vector<int>());
    vector<vector<int>> findAll(g0.NumNodes(),vector<int>());
    for (int i = 0; i < g0.NumNodes(); i++)
        for(int j : g0.Neighbors(i)){
            if (clock()>temps_max) goto here;
                for(int k : findAll[j]){
                    findAll[i].push_back(k);
                    ind[k].push_back(i);
                }
                for(int k : ind[i]){
                    findAll[k].push_back(j);
                    ind[j].push_back(k);
                }
            findAll[i].push_back(j);
            ind[j].push_back(i);
        }
        
        for (int i = 0; i < g1.NumNodes(); i++)
            for(int j : g1.Neighbors(i)){
                if (clock()>temps_max) goto here;
                    if(find(ind[i].begin(),ind[i].end(),j)==ind[i].end()){
                        for(int k : findAll[j]){
                            findAll[i].push_back(k) ;
                            ind[k].push_back(i);
                        }
                        for(int k : ind[i]){
                            findAll[k].push_back(j);
                            ind[j].push_back(k);
                        }
                        findAll[i].push_back(j);
                        ind[j].push_back(i);
//                        g0.AddArc(i,j);
                    }
            }
here:
        return g0;
}

