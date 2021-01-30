#pragma once

#include <scip_cpp/Variable.h>

#include <list>

namespace scip {

struct Contribution {
  double coefficient;
  Variable const& variable;
};

class Constraint {
 private:
  double lhs_;
  double rhs_;
  std::list<Contribution> contributions_;

 public:
  Constraint(double lhs, double rhs);

  void add_contribution(double coefficient, const Variable& variable);

  const std::list<Contribution>& get_contributions_(void) const {
    return contributions_;
  }
};

}  // namespace scip
