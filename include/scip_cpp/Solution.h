#pragma once

#include <scip_cpp/Common.h>
#include <scip_cpp/Variable.h>

struct Scip;
struct SCIP_Sol;

namespace scip {

class Solution {
 private:
  double objective_value_;
  Map<double> variable_values_;

 public:
  Solution(Scip* scip, SCIP_Sol* sol, const Map<Variable const*>& variables);

  /**
   * @return This solution's objective function value
   */
  double GetObjectiveValue(void) const { return objective_value_; }

  /**
   * @param name Variable name
   * @return The variable value on the solution
   */
  double GetVariableValue(const std::string& name) const {
    return variable_values_.at(name);
  }

 private:
  void LoadAllValues(Scip* scip, SCIP_Sol* sol,
                     const Map<Variable const*>& variables);
};

}  // namespace scip
