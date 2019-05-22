#include "job.h"
#include "ortools/linear_solver/linear_solver.h"
#include <string>
#include <iostream>
using namespace operations_research;

vector<int> BestJobAssignment(const vector<Resources>& jobs,
                              const vector<Resources>& machines){
  const int num_jobs = jobs.size();
  const int num_machines = machines.size();
  MPSolver solver("Job solver", MPSolver::CBC_MIXED_INTEGER_PROGRAMMING);
  MPObjective* objective = solver.MutableObjective();
  
  vector<vector<MPVariable*>> jobs_assig(num_jobs);
  for (int i = 0; i < num_jobs; ++i){
  	for (int j = 0; j < num_machines; ++j){
  		jobs_assig[i].push_back(solver.MakeIntVar(0, 1,"Job" + std::to_string(i) + "=>" + std::to_string(j)));
  	}
  }

  //constraintes de l'unicite du job
  for (int i = 0; i < num_jobs; ++i){
  	MPConstraint* ct = solver.MakeRowConstraint(0, 1);
  	for (int j = 0; j < num_machines; ++j){
  		ct->SetCoefficient(jobs_assig[i][j], 1);
  	}
  }

  // //Ne pas depasser les ressourses
  // for (int i = 0; i < num_jobs; ++i){
  // 	for (int j = 0; j < num_machines; ++j){
  // 		//CPU
  // 		MPConstraint* ct = solver.MakeRowConstraint(0, machines[j].cpu);
  // 		ct->SetCoefficient(jobs_assig[i][j], jobs[i].cpu);
  // 		//RAM
  // 		ct = solver.MakeRowConstraint(0, machines[j].ram);
  // 		ct->SetCoefficient(jobs_assig[i][j], jobs[i].ram);
  // 		//DISK
  // 		ct = solver.MakeRowConstraint(0, machines[j].disk);
  // 		ct->SetCoefficient(jobs_assig[i][j], jobs[i].disk);
  // 	}
  // }


  for (int i = 0; i < num_machines; ++i){
  	//CPU
  	MPConstraint* ct = solver.MakeRowConstraint(0, machines[i].cpu);
  	for (int j = 0; j < num_jobs; ++j){
  		ct->SetCoefficient(jobs_assig[j][i], jobs[j].cpu);
  	}
  	//RAM
  	ct = solver.MakeRowConstraint(0, machines[i].ram);
  	for (int j = 0; j < num_jobs; ++j){
  		ct->SetCoefficient(jobs_assig[j][i], jobs[j].ram);
  	}
  	//DISK
  	ct = solver.MakeRowConstraint(0, machines[i].disk);
  	for (int j = 0; j < num_jobs; ++j){
  		ct->SetCoefficient(jobs_assig[j][i], jobs[j].disk);
  	}
  }

  for (int i = 0; i < num_jobs; ++i){
  	for (int j = 0; j < num_machines; ++j){
  		objective->SetCoefficient(jobs_assig[i][j], 1);
  	}
  }
  objective->SetMaximization();

  solver.Solve();
  bool nonAff = true;
  vector<int> toReturn;
  for (int i = 0; i < num_jobs; ++i){
      for (int j = 0; j < num_machines; ++j){
      	nonAff = true;
      	if(jobs_assig[i][j]->solution_value() == 1){
      		 // std::cout<<i<<j<<"OK\n";
      		toReturn.push_back(j);
      		nonAff = false;
      		break;
      	}
      }
      if(nonAff){
     	toReturn.push_back(-1);
      	nonAff = true;
      }
  }
  return toReturn;
}

