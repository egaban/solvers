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
  double lhs_;                // Lefthand side
  double rhs_;                // Righthand side
  Scip* scip_ptr_;            // Pointer to scip main struct
  SCIP_Cons* scip_cons_ptr_;  // Pointer to scip constraint struct

 public:
  Constraint(Scip* scip, const std::string& name, double lhs, double rhs);
  ~Constraint();

  SCIP_Cons* GetScipconsPointer(void) const { return scip_cons_ptr_; }

  /**
   * @brief Adds a variable to this constraint, given the variable and
   * coefficient.
   *
   * @param variable Variable reference
   * @param coefficient Contribution coefficient
   */
  void AddVariableContribution(const Variable& variable, double coefficient);
};

}  // namespace scip
