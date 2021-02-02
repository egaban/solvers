#pragma once

#include <scip_cpp/Variable.h>

#include <list>

struct Scip;
struct SCIP_Cons;

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
  SCIP_Cons* scip_ptr_;

 public:
  Constraint(Scip* scip, const std::string& name, double lhs, double rhs);

  void add_contribution(double coefficient, const Variable& variable);

  const std::list<Contribution>& get_contributions_(void) const {
    return contributions_;
  }
};

}  // namespace scip
