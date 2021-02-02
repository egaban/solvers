#pragma once

#include <scip_cpp/Constraint.h>
#include <scip_cpp/Variable.h>

#include <map>
#include <string>

struct Scip;

namespace scip {

class Model {
 private:
  std::map<std::string, Constraint const*> constraints_;
  std::map<std::string, Variable const*> variables_;
  Scip* scip_ptr_;

 public:
  Model(void);
  ~Model();

  void create_variable(VariableType type, double objective_value,
                       double lower_bound, double upper_bound,
                       const std::string& name);

  void create_constraint(double lhs, double rhs, const std::string& name);

 private:
};

}  // namespace scip
