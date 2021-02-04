#include <scip/scip.h>
#include <scip_cpp/Solution.h>

namespace scip {

Solution::Solution(Scip* scip, SCIP_Sol* sol,
                   const Map<Variable const*>& variables)
    : objective_value_(SCIPsolGetOrigObj(sol)) {
  load_all_values(scip, sol, variables);
}

void Solution::load_all_values(Scip* scip, SCIP_Sol* sol,
                               const Map<Variable const*>& variables) {
  for (const auto& [name, var] : variables) {
    auto var_ptr = var->get_scipvar_pointer();
    variable_values_[name] = SCIPgetSolVal(scip, sol, var_ptr);
  }
}

}  // namespace scip
