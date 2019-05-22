#include "sac2.h"
#include <float.h>
#include <algorithm>

struct str
{
    int ind;
    double val;
};

struct greater
{
    template<class T>
    bool operator()(T const &a, T const &b) const { return a > b; }
};

//bool comp(str s1, str s2){
//    if (s1.val>s2.val) return true;
//    else return false;
//}

// On a un sac à dos de capacité C, et des objets de poids p[0], p[1], ...
// et de valeurs v[0], v[1], ...
// Cette fonction renvoie la valeur maximale que l'on peut collecter dans le sac
// à dos, en supposant qu'on peut mettre les objets de manière fractionnaire.
//
// EXEMPLE: C=12, p=[4, 7, 2, 5, 5, 1, 10], v=[3.1, 99, 0.1, 0.2, 6.6, 0.4, 111]
// -> Doit renvoyer 154.5. Explication:
//    la solution optimale est de prendre l'objet #1 en entier (poids 7, valeur 99)
//    et la moitié de l'objet #6 (poids 10, valeur 111).
//    On a bien un poids total de 7*1 + 10*0.5 = 12.
//    On obtient une valeur totale de 99*1 + 111*0.5 = 154.5
double Sac2(int C, const vector<int>& p, const vector<double>& v){
    double CC = 0;
    vector<str> objVal(p.size());
    double gain = 0;
    
    for (int i = 0; i < p.size(); i++){
        if (p[i] == 0) objVal[i].val = DBL_MAX;
        else objVal[i].val = v[i]/p[i];
        objVal[i].ind = i;
    }
    sort(objVal.begin(),objVal.end(),[](str s1, str s2){return s1.val>s2.val;});
    
    for (int i = 0; i < objVal.size(); i++) {
        if (CC+p[objVal[i].ind] <= C) {
            CC += p[objVal[i].ind];
            gain += v[objVal[i].ind];
        } else {
            return gain+v[objVal[i].ind]*(C-CC)/p[objVal[i].ind];
        }
    }
    
    return gain;
}
