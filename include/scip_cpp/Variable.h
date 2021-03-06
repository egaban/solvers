#pragma once

#include <scip/type_var.h>
#include <scip_cpp/Common.h>

struct Scip;
struct SCIP_Var;

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
  Scip* scip_ptr_;          // Pointer to SCIP main structure
  SCIP_Var* scip_var_ptr_;  // Pointer to the SCIP_Var

 public:
  Variable(Scip* scip, VariableType type, double objective_value,
           double lower_bound, double upper_bound, const std::string& name);
  ~Variable();

  SCIP_Var* GetScipvarPointer(void) const { return scip_var_ptr_; }

 private:
  static SCIP_Vartype ConvertToScipVartype(VariableType t);
};

}  // namespace scip
