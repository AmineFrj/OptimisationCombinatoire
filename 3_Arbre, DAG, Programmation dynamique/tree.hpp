//
//  tree.hpp
//  Td2
//
//  Created by FERDJAOUI Amine on 04/10/2018.
//  Copyright © 2018 FERDJAOUI Amine. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp

#include <stdio.h>
#include <vector>
using namespace std;

// Entrée: le tableau de parents d'un arbre enraciné (ou d'une forêt d'arbres
// enracinés): parent[i] = -1 si le noeud i est une racine, et sinon c'est
// le noeud parent de i dans l'arbre qui contient i.
//
// Sortie: le tableau des liste d'enfants: l'élément i du tableau de sortie
// est un vector<int> listant tous les enfants du noeud i (il pourra etre
// vide si i n'a pas d'enfants), dans un ordre quelconque.
//
// Exemple:
//
//    .3.     vector<int> parents = [3, 2, 3, -1, 3, 1]  // size()=6 = num nodes
//   .'|'.
//  2  0  4   vector<vector<int>> enfants = [ [],
//  |                                         [5],
//  1                                         [1],
//  |                                         [2, 0, 4],
//  5                                         [],
//                                            [] ]
vector<vector<int>> ParentVectorToChildrenVector(const vector<int>& parent);

// Entrée: un arbre, représenté par son tableau d'enfants (la sortie de la fonction
// faite dans la question précédente), et un noeud X de cet arbre.
//
// Sortie: la hauteur du sous-arbre de X: 0 si X n'a pas d'enfant, 1 si X n'a que des
// enfants qui n'ont eux-mêmes pas d'enfants, etc.
//
// Indice: la fonction pourra être récursive.
//
// Exemple:
//    .3.     vector<vector<int>> enfants = [ [], [], [1], [2, 0, 4], [] ]
//   .'|'.
//  2  0  4   -> Height(enfants, 0) = 0 ;   Height(enfants, 1) = 0
//  |         -> Height(enfants, 2) = 1 ;   Height(enfants, 3) = 2
//  1         -> Height(enfants, 4) = 0
int Height(const vector<vector<int>>& enfants, int node);

// Entrée: un arbre, représenté par son tableau d'enfants (la sortie de la
// fonction faite dans la question précédente).
//
// Sortie: les hauteurs de tous les noeuds de l'arbre (le tableau des valeurs
// de Height(i) pour tous les noeuds i de 0 à N-1).
//
// Complexité: O(N).
//
// Indice: vous pourrez utiliser une fonction auxilliaire récursive, déclarée
// et définie dans le .cc, qui ressemblera beaucoup à la Height() de la
// question précédente, à la différence qu'elle utilisera la mémorisation.
//
// Exemple:
//    .3.     vector<vector<int>> enfants = [ [], [], [1], [2, 0, 4], [] ]
//  .' | '.
//  2  0  4   -> AllHeights(enfants) = [0, 0, 1, 2, 0]
//  |
//  1
vector<int> AllHeights(const vector<vector<int>>& enfants);
void HeightRec(const vector<vector<int>>& enfants, int node, vector<int>& heights);

#endif /* tree_hpp */
