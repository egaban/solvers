#pragma once

#include <scip_cpp/Common.h>
#include <scip_cpp/Variable.h>

#include <limits>
#include <list>

struct Scip;
struct SCIP_Cons;

namespace scip {

constexpr auto MinusInfinity = std::numeric_limits<double>::min();
constexpr auto Infinity = std::numeric_limits<double>::max();

struct Contribution {
  double coefficient;
  Variable const& variable;
};

class Constraint {
 private:
  double lhs_;                             // Lefthand side
  double rhs_;                             // Righthand side
  std::list<Contribution> contributions_;  // Contribution list
  Scip* scip_ptr_;                         // Pointer to scip main struct
  SCIP_Cons* scip_cons_ptr_;               // Pointer to scip constraint struct

 public:
  Constraint(Scip* scip, const std::string& name, double lhs, double rhs);
  ~Constraint();

  void add_contribution(double coefficient, const Variable& variable);

  const std::list<Contribution>& get_contributions(void) const {
    return contributions_;
  }

  SCIP_Cons* get_scipcons_ptr(void) const { return scip_cons_ptr_; }
};

}  // namespace scip
