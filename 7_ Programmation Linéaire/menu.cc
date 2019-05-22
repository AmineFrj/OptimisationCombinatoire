#include "menu.h"
#include "ortools/linear_solver/linear_solver.h"
#include <string>
#include <limits>

using namespace operations_research;
// CONSEILS -- BIEN LES LIRE EN ENTIER!
// - Regarder le fichier "../examples/cpp/linear_programming.cc" pour voir
//   comment définir des variables, des contraintes, et l'objectif.
// - Contrairement a l'exemple, on a pas un nombre constant, prédéfini, de
//   variables et de contraintes: elles dépendent de l'entrée. Il peut
//   être utile de créér un tableau de MPVariable* stockant les variables
//   créées pour modéliser le problème. Idem pour les contraintes.
//   Et on les crééra dans des boucles "for" a priori.
// - N'oubliez pas qu'après Solve() il faut encore renvoyer la solution
//   dans le format demandé!
vector<double> MenuMoinsCher(const vector<double>& ajr,
                             const vector<vector<double>>& apports_par_ingredient,
                             const vector<double>& prix_par_ingredient) {
    double infinity = std::numeric_limits<double>::infinity();
    MPSolver solver("ex1", MPSolver::GLOP_LINEAR_PROGRAMMING);
    const int num_ingredients = apports_par_ingredient.size();
    const int num_elements = ajr.size();
    
    MPVariable* var[num_ingredients];
    MPConstraint* cst[num_elements];
    MPObjective* obj = solver.MutableObjective();

    //calculer la fonction objective
    for (int i = 0; i < num_ingredients; i++) {
        var[i] = solver.MakeNumVar(0.,infinity,"V"+std::to_string(i));
        obj->SetCoefficient(var[i],prix_par_ingredient[i]);
    }
    //definir les contraintes
    for (int i = 0; i < num_elements; i++) {
        cst[i] = solver.MakeRowConstraint(ajr[i], infinity);
        for (int j = 0; j < num_ingredients; j++)
            cst[i] -> SetCoefficient(var[j], apports_par_ingredient[j][i]);
    }
    obj -> SetMinimization();
	solver.Solve();
    vector<double> ret;
    for(MPVariable* i : var)
        ret.push_back(i->solution_value());
//    MPSolver::ResultStatus result_status = sowlver.Solve();
    return ret;
    
}

