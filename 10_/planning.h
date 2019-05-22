#include <vector>
using namespace std;

struct Mission {
  int start_time;
  int end_time;  // Sera toujours >= start_time + 1.
  int gain;
};

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
int PlanningOpt(const vector<Mission>& missions);
