
#include "parcel.h"
using namespace std;

// Le gain de cultiver la parcelle #i est gain[i]. Si on cultive la parcelle
// #i, on ne peut pas cultiver la parcelle #i-1 ni la parcelle #i+1.
// Cette fonction renvoie le gain maximum.
//
// EXEMPLE:
// MaxGain([3, 7, 2, 1, 8, 4, 3]) = 18
int MaxGain(const vector<int>& gain){
//    vector<int> newGain(gain.size(),-1);
//    return maxGainRec(gain,newGain,n-1);
    int i = 0, i_ = 0, c;
    for (int p = 0; p < gain.size(); p++) {
        c = i;
        i = max(gain[p] + i_ , i);
        i_ = max(i_,c);
    }
    return max(i,i_);
}

//int maxGainRec(const vector<int>& gain, vector<int>& newGain,int i){
//    if(i==0){
//        rec=gain[0];
//    }
//    if (i==1) {
//        rec=newre();
//    }
//    rec = max(maxGainRec(,,i-1),gain[i]+newc(,,i-2));
//    newGain[i]=rec;
//    return rec;
//}

