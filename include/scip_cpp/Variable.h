#pragma once

#include <string>

struct Scip;

namespace scip {

enum class VariableType {
  Binary,
  Integer,
  Real,
};

class Variable {
 private:
  double lb_;               // Lower bound
  double ub_;               // Upper bound
  double obj_;              // Objective value
  VariableType type_;       // Variable type
  SCIP_Var* scip_var_ptr_;  // Pointer to the SCIP_Var

 public:
  Variable(Scip* scip, VariableType type, double objective_value,
           double lower_bound, double upper_bound, const std::string& name);
};

}  // namespace scip