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

  double get_objective_value(void) const { return objective_value_; }

  double get_variable_value(const std::string& name) const {
    return variable_values_.at(name);
  }

 private:
  void load_all_values(Scip* scip, SCIP_Sol* sol,
                       const Map<Variable const*>& variables);
};

}  // namespace scip
