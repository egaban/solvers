#pragma once

#include <scip_cpp/Constraint.h>
#include <scip_cpp/Variable.h>

#include <map>
#include <string>

struct Scip;

namespace scip {

class Model {
 private:
  std::map<std::string, Constraint*> constraints_;
  std::map<std::string, Variable const*> variables_;
  Scip* scip_ptr_;

 public:
  Model(void);
  ~Model();

  void create_variable(VariableType type, double objective_value,
                       double lower_bound, double upper_bound,
                       const std::string& name);

  void create_constraint(double lhs, double rhs, const std::string& name);

  /**
   * @brief Adds a variable contribution to constraint.
   *
   * @param variable_name variable name
   * @param coefficient variable coefficient
   * @param constraint_name constraint
   */
  void add_contribution_to_constraint(const std::string& variable_name,
                                      double coefficient,
                                      const std::string& constraint_name);

  Constraint& get_constraint(const std::string& name) {
    return *(constraints_.at(name));
  }

  const Variable& get_variable(const std::string& name) const {
    return *(variables_.at(name));
  }

};

}  // namespace scip
