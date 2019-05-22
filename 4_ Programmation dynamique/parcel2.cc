#include "parcel2.h"

// Le problème est le même, mais au lieu de renvoyer le gain maximum, on
// veut renvoyer la liste des parcelles à cultiver pour obtenir le gain maximal.
//
// EXEMPLE:
// OptimalParcels([3, 7, 2, 1, 8, 4, 3]) = [1, 4, 6] (indices choisis)
vector<int> OptimalParcels(const vector<int>& gain){
    vector<int> historique(gain.size()), opt;
    if(gain.size()>0){
        historique[0] = gain[0];
        if (gain.size() > 1) historique[1] = max(gain[0],gain[1]);
        for (int i = 2; i< gain.size(); i++)
            historique[i] = max(gain[i]+historique[i-2], historique[i-1]);
    //        if (gain[i]+historique[i-2] < historique[i-1]) {
    //            historique[i] = historique[i-1];
    //            opt.push_back(i-1);
    //        } else historique[i] = gain[i]+historique[i-2];
        
        int x = historique[gain.size()-1];
        for (int i = gain.size()-1; i > 0; i--) {
            if (historique[i]==x && historique[i]!=historique[i-1]) {
                    opt.push_back(i);
                    x -= gain[i];
            }
        }
        if (historique[0]==x) opt.push_back(0);
        reverse(opt.begin(),opt.end());
    }
//    if ( historique[gain.size()-1] != historique[gain.size()-1] ) {
//        opt.push_back(gain.size()-1);
//    }
    return opt;
}

