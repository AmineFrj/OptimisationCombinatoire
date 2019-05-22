#include <vector>
#include <stack>
#include <iostream>
#include <limits>
#include "ugraph.h"  // Vous l'avez: il était dans test.tar.gz.

using namespace std;
// Étant donné un graph non dirigé, renvoie un coloriage utilisant
// aussi peu de couleurs que possible.
// Entrée: le graphe non dirigé.
// Valeur de retour: le nombre de couleur C de votre coloriage.
// Sortie: "color" doit contenir autant d'élément que le nombre de noeuds
//         du graphe: color[i] sera la couleur du noeud #i.
//         color[i] doit etre entre 0 et C-1, et deux noeuds ayant une
//         arête en commun ne peuvent pas avoir la même couleur.
//
// NOTE: On attends pas un algorithme optimal (NP complet!), mais votre
// heuristique devra etre aussi "bonne" que possible.

struct degree{
    int node;
    int deg;
    degree(int n, int d){
        node = n;
        deg = d;
    }
    bool operator<( const degree& other ) const {
        return deg > other.deg;
    }
};

int Color(const UndirectedGraph& graph, vector<int>* color){
    color->resize(graph.NumNodes());
    vector<degree> degrees;
    int col = 0;
    UndirectedGraph g = graph;
    
    for (int i = 0; i < graph.NumNodes(); i++) degrees.push_back(degree(i,graph.Neighbors(i).size())); //cout<<degrees[i].node<<"  "<<degrees[i].deg<<endl;
    sort(degrees.begin(),degrees.end());
    int treated = 0;
    while (treated < graph.NumNodes()) {
        (*color)[degrees[0].node] = col;
        vector<int> neigh = graph.Neighbors(degrees[0].node);
        vector<int> Effacee;
        for (int i = 1; i < degrees.size(); i++) {
            if(find(neigh.begin(),neigh.end(),degrees[i].node)==neigh.end()){
                bool cdt = true;
                vector<int> neigh2 = graph.Neighbors(degrees[i].node);
                for(int k : Effacee){
                    if(find(neigh2.begin(),neigh2.end(),k)!=neigh2.end()){
                        cdt = false;
                        break;
                    }
                }
                if(cdt){
                    (*color)[degrees[i].node] = col;
                    Effacee.push_back(degrees[i].node);
                    degrees.erase(degrees.begin()+i);
                    treated++;
                    i--;
                }
            }
        }

        degrees.erase(degrees.begin());
        treated++;
        col++;
    }
    return col+1;
}



//int Color(const UndirectedGraph& graph, vector<int>* color){  // La sortie. N'oubliez pas de la remplir!
//    //phase 1 empiler
//    int min, n=0, ii;
//    vector<degree> degrees;
////    vector<int> &color2 = *color;
//    stack<int> pile;
//    //copier les degres
//    for (int i = 0; i < graph.NumNodes(); i++) degrees.push_back(degree(i,graph.Degree(i)));
//    for(int compt = 0; compt < graph.NumNodes(); compt++){
////        cout<<compt<<endl;
//        min = numeric_limits<int>::max();
//        for (int i = 0; i < degrees.size(); i++)
//            if(degrees[i].deg>=0 && degrees[i].deg<min){
//                min = degrees[i].deg;
//                n = degrees[i].node;
//                ii = i;
//            }
//        pile.push(n);
//        degrees.erase(degrees.begin()+ii);
////        degree[n] = numeric_limits<int>::max();
//
//        for(int i : graph.Neighbors(n))
//            for(degree d : degrees)
//                if(d.node == i){
//                    d.deg--;
//                    break;
//                }
//    }
//
//    bool trouve;
//    vector<int> newGraph;
//    //phase 2 remplissage
//    color->resize(graph.NumNodes(),-1);
//    while (not pile.empty()) {
//        for (int couleur = 0; couleur < graph.NumNodes(); couleur++) {
//            trouve = false;
//            vector<int> neigh = graph.Neighbors(pile.top());
//            for(int i : newGraph){
//                for(int j : neigh){
//                    if(i==j && (*color)[j]==couleur){
//                        trouve = true;
//                        goto test;
//                    }
//                }
//            }
//        test:
//            if(!trouve){
//                (*color)[pile.top()] = couleur;
//                break;
//            }
//        }
//        newGraph.push_back(pile.top());
//        pile.pop();
//    }
////    color = &color2;
//    return *max_element(color->begin(),color->end())+1;
//}
