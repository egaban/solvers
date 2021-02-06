#pragma once

#include <scip_cpp/Common.h>
#include <scip_cpp/Constraint.h>
#include <scip_cpp/Solution.h>
#include <scip_cpp/Variable.h>

struct Scip;

namespace scip {

enum class ObjSense { Minimize, Maximize };

class Model {
 private:
  Map<Constraint*> constraints_;
  Map<Variable const*> variables_;
  Scip* scip_ptr_;

 public:
  Model(ObjSense sense);
  ~Model();

  /**
   * @brief Creates and adds a variable to the model.
   *
   * @param type Variable type
   * @param objective_value Variable coefficient at objective function
   * @param lower_bound Variable lower bound
   * @param upper_bound Variable upper bound
   * @param name Variable name
   */
  void CreateVariable(VariableType type, double objective_value,
                      double lower_bound, double upper_bound,
                      const std::string& name);

  /**
   * @brief Creates and adds a constraint to the model. lhs <= constraint <=
   * rhs.
   *
   * @param lhs Lefthand side
   * @param rhs Righthand side
   * @param name Constraint name
   */
  void CreateConstraint(double lhs, double rhs, const std::string& name);

  /**
   * @brief Adds a variable contribution to constraint.
   *
   * @param variable_name variable name
   * @param coefficient variable coefficient
   * @param constraint_name constraint
   */
  void AddContributionToConstraint(const std::string& variable_name,
                                   double coefficient,
                                   const std::string& constraint_name);

  Constraint& GetConstraint(const std::string& name) {
    return *(constraints_.at(name));
  }

  const Variable& GetVariable(const std::string& name) const {
    return *(variables_.at(name));
  }

  void Solve(void);

  Solution GetBestSolution(void) const;

  bool HasFeasibleSolutions(void) const;
};

}  // namespace scip
