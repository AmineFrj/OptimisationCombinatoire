#include "job.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <limits>
#include "ortools/linear_solver/linear_solver.h"

using namespace operations_research;
using namespace std;

// Cette fonction nous aide a extraire la resource numero #n:
// 0->cpu, 1->ram, 2->disk.
double NthResource(const Resources& r, int n) {
  return n == 0 ? r.cpu : n == 1 ? r.ram : r.disk;
}

void setHash(vector<int>& hash, int posOrig){
	hash.push_back(posOrig);
}

int getHash(vector<int>& hash, int nouvPos){
	return hash[nouvPos];
}

vector<int> BestJobAssignment0(const vector<Resources>& jobs,
                               const vector<double>& profits,
                               const vector<Resources>& machines) {

  MPSolver solver("Mon solveur", MPSolver::CBC_MIXED_INTEGER_PROGRAMMING);
  const double lowest_double = -numeric_limits<double>::max();
  vector<Resources> bestJobs;
  vector<int> hashJobs;
  // vector<Resources> jobs2 = jobs;
  vector<double> profits2 = profits;

  // const int mach=30;
  int nj, nm, time;

  switch(jobs.size()){
  	case 0 ... 100 :
  		nj = jobs.size()-1;
  		nm = machines.size()-1;
  		time = 300;
  		break;
  	case 101 ... 150 :
  		nj = jobs.size()*19/20;
  		nm = machines.size();
  		time = 100;
  		break;
  	case 151 ... 200 :
  		nj = jobs.size()*16/20;
  		nm = machines.size()-2;
  		time = 200;
  		break;
  	case 201 ... 300 :
  		nj = jobs.size()*32/40;
  		nm = machines.size()-4;
  		time = 300;
  		break;
  	case 301 ... 500 :
  		nj = jobs.size()*26/40;
  		nm = machines.size()-3;
  		time = 300;
  		break;
  	case 501 ... 800 :
  		if(machines.size()<200){
	  		nj = jobs.size()*16/40;
	  		nm = machines.size();
	  		time = 400;
	  		}else if(machines.size()<300){
		  		nj = jobs.size()*33/80;
		  		nm = machines.size()*42/100;
		  		time = 500;
				  	}else {
				  		nj = jobs.size()*57/100;
				  		nm = machines.size()*39/100;
				  		time = 600;
			  		}
  		break;
  	case 801 ... 1500 :
  		nj = jobs.size()*22/100;
  		nm = machines.size()*38/100;
  		time = 800;
  		break;
  	default:
  		nj = jobs.size()*19/100;
  		nm = machines.size()*25/100;
  		time = 1500;
  		break;
  }

  for (int i = 0; i < nj; ++i){
  	int indMax = max_element(profits2.begin(),profits2.end())-profits2.begin();
  	profits2[indMax] = lowest_double;
  	bestJobs.push_back(jobs[indMax]);
  	hashJobs.push_back(indMax);
  }

  vector<Resources> bestMachines, machines2 ;
  vector<int> hashMachines;

  for (int i = 0; i < machines.size(); ++i){
  	Resources r;
  	r.ram = machines[i].ram;
  	r.cpu = machines[i].cpu;
  	r.disk = machines[i].disk;
  	machines2.push_back(r);
  }

  for (int i = 0; i < nm; ++i){
  	int indMax = max_element(machines2.begin(),machines2.end(),
  		[](Resources a1, Resources a2){
  				return (a1.cpu< a2.cpu && a1.ram< a2.ram && a1.disk< a2.disk);
  				})-machines2.begin();
  	machines2[indMax].cpu = lowest_double;
  	machines2[indMax].ram = lowest_double;
  	machines2[indMax].disk = lowest_double;
  	bestMachines.push_back(machines[indMax]);
  	hashMachines.push_back(indMax);
  }  


  // for (int i = 0; i < jobs.size()-1; ++i){
  // 	if(profits[i]>profits[i+1]){
  // 		bestJobs.push_back(jobs[i]);
  // 		hashJobs.push_back(i);
  // 	}else{
  // 		bestJobs.push_back(jobs[i+1]);
  // 		hashJobs.push_back(i+1);
  // 	}
  // 	i++;
  // }

  // for (int i = 0; i < machines.size()-1; ++i){
  // 	if(machines[i].cpu+machines[i].ram+machines[i].disk>machines[i+1].cpu+machines[i+1].ram+machines[i+1].disk){
  // 		bestMachines.push_back(machines[i]);
  // 		hashMachines.push_back(i);
  // 	}else {
  // 		bestMachines.push_back(machines[i]);
  // 		hashMachines.push_back(i);
  // 	}
  // 	i++;
  // }

  // vector<Resources> machines2;

  // for (int i = 0; i < machines.size()*1/10; ++i){
  // 	machines2.push_back(machines[i]);
  // }

  const int num_jobs = bestJobs.size();
  const int num_machines = bestMachines.size();

  MPObjective* objective = solver.MutableObjective();
  objective->SetMaximization();

  // On definit les variables: var[i][j]=1 si on fait tourner le job #i sur la
  // machine #j.
  vector<vector<MPVariable*>> var(num_jobs);
  for (int i = 0; i < num_jobs; ++i) {
    for (int j = 0; j < num_machines; ++j) {
      MPVariable* v = solver.MakeBoolVar("Job" + std::to_string(i) + "On" +
                                         std::to_string(j));
      var[i].push_back(v);
      // Contribution de cet ingrédient au prix total (l'objectif).
      objective->SetCoefficient(v, profits[hashJobs[i]]);
    }
  }

  // Chaque job tourne au plus une fois.
  for (int i = 0; i < num_jobs; ++i) {
    MPConstraint* ct = solver.MakeRowConstraint(0, 1, "");  // TODO: name
    for (int j = 0; j < num_machines; ++j) {
      ct->SetCoefficient(var[i][j], 1.0);
    }
  }

  // Les jobs tournant sur une machine ne doivent pas consommer plus de
  // resources que la machine! On fait la meme chose pour chaque type de
  // resource.
  for (int j = 0; j < num_machines; ++j) {
    for (int res = 0; res < 3; ++res) {
      MPConstraint* ct =  // TODO: name
          solver.MakeRowConstraint(0, NthResource(bestMachines[j], res), "");
      for (int i = 0; i < num_jobs; ++i) {
        ct->SetCoefficient(var[i][j], NthResource(bestJobs[i], res));
      }
    }
  }

  // On résout! Le problème devrait admettre une solution optimale
  // trouvable sans trop de problème.
  // solver.EnableOutput();
  solver.set_time_limit(10000-time);
  solver.Solve();
  cout <<"OK";
  // On renvoie la solution.
  vector<int> assignment(jobs.size(), -1);
  for (int i = 0; i < num_jobs; ++i) {
    for (int j = 0; j < num_machines; ++j) {
      if (var[i][j]->solution_value() > 0.5) {
        if (assignment[hashJobs[i]] != -1) {
          cerr << "BUG: double assignment, Job #" << i << ", machines #"
               << assignment[i] << " and #" << j << endl;
          exit(1);
        }
        assignment[hashJobs[i]] = hashMachines[j];
      }
    }
  }
  return assignment;
}
