#include "planning.h"


// Renvoie le gain maximum qu'on peut amasser en faisant des missions,
// sachant qu'on ne peut pas faire 2 missions en meme temps.
// On peut commencer une mission exactement quand une autre mission s'arrete.
//
// Exemple:
// Si missions = { {0, 5, 1000},
//                 {3, 6, 495},
//                 {1, 3, 510} };
// Alors PlanningOpt(missions) devra renvoyer 1005 car on peut faire la
// mission #2 puis la mission #1.
int PlanningOpt(const vector<Mission>& missions){
	int maxH=0;
	for (int i = 0; i < missions.size(); ++i){
		if(missions[i].end_time>maxH) 
			maxH = missions[i].end_time;
	}
	vector<int> gains(maxH+1,0);
	bool changed;
	for (int i = 1; i <= gains.size(); ++i){
		changed = false;
		for (int j = 0; j < missions.size(); ++j){
			if(missions[j].end_time<=i){
				if((gains[missions[j].start_time]+missions[j].gain)>gains[i-1] && (gains[missions[j].start_time]+missions[j].gain)>gains[i]){
					gains[i] = gains[missions[j].start_time] + missions[j].gain;
					changed = true;
				}
			}
		}
		if(not changed)
			gains[i] = gains[i-1];
	}
	return gains[gains.size()-1];
}
