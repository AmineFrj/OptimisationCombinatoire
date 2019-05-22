#include "sac1.h"
#include <algorithm>
// On a un sac à dos de capacité C, et des objets de poids p[0], p[1], ...
// On veut selectionner le plus grand nombre possible d'objets tel que
// la somme de leurs poids soit <= C.
// Cette fonction renvoie ce nombre maximal d'objets.
//
// EXEMPLE: C=12, p=[4, 7, 2, 5, 5, 1, 10]
//          -> renvoie 4 car on peut mettre 4 objets au maximum
//             (de poids 4, 2, 5, 1: 4+2+5+1 = 12)
int Sac1(int C, const vector<int>& p){
    int CC = 0, gain = 0;
    vector<int> other = p;
    sort(other.begin(),other.end());
    
    for (int i = 0; i < other.size(); i++) {
        if(CC + other[i] <= C){
            CC += other[i];
            gain++;
        } else return gain;
    }
    return gain;
}
