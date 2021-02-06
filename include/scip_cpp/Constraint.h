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

class Constraint {
 private:
  double lhs_;                             // Lefthand side
  double rhs_;                             // Righthand side
  Scip* scip_ptr_;                         // Pointer to scip main struct
  SCIP_Cons* scip_cons_ptr_;               // Pointer to scip constraint struct

 public:
  Constraint(Scip* scip, const std::string& name, double lhs, double rhs);
  ~Constraint();

  SCIP_Cons* get_scipcons_ptr(void) const { return scip_cons_ptr_; }

  void AddVariableContribution(const Variable& variable, double coefficient);
};

}  // namespace scip
