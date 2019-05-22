#include "flow.h"
#include "ortools/linear_solver/linear_solver.h"
#include <string>
#include <limits>
#include <vector>
#include <iostream>
using namespace operations_research;

vector<FlowOnArc> BestFlow(int num_nodes, const vector<BackboneArc>& backbone,
                           const vector<FlowDemand>& demands) {
	// double infinity = std::numeric_limits<double>::infinity();
    MPSolver solver("Flow", MPSolver::GLOP_LINEAR_PROGRAMMING);
    const int num_dem 	= demands.size();
    const int num_arcs 	= backbone.size();
    const int num_var 	= num_dem*num_arcs;

    MPVariable* var[num_var];
    MPConstraint* constr1[num_dem*num_nodes];
    MPObjective* obj = solver.MutableObjective();

    for (int i = 0; i < num_dem; ++i){
    	for (int j = 0; j < num_arcs; j++){
			var[j+num_arcs*i] = solver.MakeNumVar(0.,demands[i].demand,"D"+std::to_string(i)+" "+std::to_string(j));
    	}
    }

 	//calculer la fonction objective
	for(int i = 0; i < num_dem; i++){
	    for (int j = 0; j < num_arcs; ++j){
	    	if(backbone[j].from == demands[i].src)
	   		 	obj->SetCoefficient(var[j+num_arcs*i],demands[i].price);
	    	else if(backbone[j].to == demands[i].src)
				obj->SetCoefficient(var[j+num_arcs*i],-demands[i].price);
	    }
	}
    obj->SetMaximization();

    //contrainte#1 Vi #enti=#sorti
    bool src = false, dest = false;
    vector<double> fEnt,fSrt;
    for (int i = 0; i < num_dem; i++){
    	for (int j = 0; j < num_nodes; j++){
    		fEnt.clear();
    		fSrt.clear();
    		if(demands[i].src == j) src = true;
    			else if(demands[i].dst == j) dest = true;
    		for (int k = 0; k < num_arcs; k++)
    			if(backbone[k].from==j) fSrt.push_back(k+num_arcs*i); 
    				else if(backbone[k].to==j) fEnt.push_back(k+num_arcs*i);
    		if(src){
    				constr1[j+num_nodes*i] = solver.MakeRowConstraint(0,demands[i].demand);	 
    				src = false;
    				for(int l : fEnt)
	    						constr1[j+num_nodes*i]->SetCoefficient(var[l], -1.0);
	    			for(int l : fSrt)
	    						constr1[j+num_nodes*i]->SetCoefficient(var[l], 1.0);

    			}else if(dest) {
    					constr1[j+num_nodes*i] = solver.MakeRowConstraint(0,demands[i].demand); 
    					dest = false;
    					for(int l : fEnt)
	    						constr1[j+num_nodes*i]->SetCoefficient(var[l], 1.0);
	    				for(int l : fSrt)
	    					constr1[j+num_nodes*i]->SetCoefficient(var[l], -1.0);
    				}
    				else {	
    						constr1[j+num_nodes*i] = solver.MakeRowConstraint(0, 0);
	    					for(int l : fEnt)
	    						constr1[j+num_nodes*i]->SetCoefficient(var[l], 1.0);
	    					for(int l : fSrt)
	    						constr1[j+num_nodes*i]->SetCoefficient(var[l], -1.0);
    				}
    	}
    }

    MPConstraint* constr2[num_arcs];
    for (int i = 0; i < num_arcs; ++i){
    	constr2[i] = solver.MakeRowConstraint(0.0, backbone[i].capacity);
    	for (int j = 0; j < num_dem; ++j)
    		constr2[i]->SetCoefficient(var[i+num_arcs*j], 1.0);
    }
	solver.Solve();
	vector<FlowOnArc> v;
	for (int i = 0; i < num_dem; ++i){
		for (int j = 0; j < num_arcs; ++j){
			if(var[j+i*num_arcs]->solution_value()!=0.0){
				v.push_back({j,i,var[j+i*num_arcs]->solution_value()});
			}

		}
	}

	return v;
}


    /*
    //contrainte#1 Vi #enti=#sorti
    int flot_intr,flot_sort;
    for (int i = 1; i < num_nodes-1; ++i){
    	flot_sort = 0;
    	for (int j = 0; j < num_arcs; j++){
    		//le cas de src et dest  
	    	if(backbone[j].from == demands[i].src)
		    	for (int j = 0; j < num_dem; j++)
	   		 		constr1[i] -> SetCoefficient(var[i+num_arcs*j]->solution_value(), 1);
	    	if(backbone[j].to == demands[i].dest)
				for (int j = 0; j < num_dem; j++)
					flot_sort = var[i+num_arcs*j]->solution_value();
		}
		constr1[i] = solver.MakeRowConstraint(flot_sort, flot_sort);
    }

    //contrainte#1 SRC
    for (int j = 0; j < num_arcs; j++){
    	//le cas de src et dest  
	   	if(backbone[j].from == demands[i].src)
	    	for (int j = 0; j < num_dem; j++)
   		 		constr1[0] -> SetCoefficient(var[i+num_arcs*j]->solution_value(), 1);
	    if(backbone[j].to == demands[i].dest)
			for (int j = 0; j < num_dem; j++)
				flot_sort = var[i+num_arcs*j]->solution_value();
	}
    //contrainte#1 DEST
	for (int j = 0; j < num_arcs; j++){
    	//le cas de src et dest  
	   	if(backbone[j].from == demands[i].src)
	    	for (int j = 0; j < num_dem; j++)
   		 		constr1[num_nodes-1] -> SetCoefficient(var[i+num_arcs*j]->solution_value(), 1);
	   	if(backbone[j].to == demands[i].dest)
			for (int j = 0; j < num_dem; j++)
	  			flot_sort = var[i+num_arcs*j]->solution_value();
		}
	*/
    //contrainte#2 Vnoeud i #f<capacitei f1i+f2i+...+fni<capi