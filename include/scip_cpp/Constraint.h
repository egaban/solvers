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
  double lhs_;                             // Lefthand side
  double rhs_;                             // Righthand side
  std::list<Contribution> contributions_;  // Contribution list
  SCIP_Cons* scip_cons_ptr_;               // Pointer to scip constraint struct

 public:
  Constraint(Scip* scip, const std::string& name, double lhs, double rhs);

  void add_contribution(double coefficient, const Variable& variable);

  const std::list<Contribution>& get_contributions(void) const {
    return contributions_;
  }

  SCIP_Cons* get_scip_ptr(void) const { return scip_cons_ptr_; }
};

}  // namespace scip
