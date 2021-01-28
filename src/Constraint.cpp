#include <assert.h>
#include <scip_cpp/Constraint.h>

constexpr auto epsilon = 1e-5;

namespace scip {

void Constraint::add_contribution(double coefficient,
                                  const Variable& variable) {
  contributions_.emplace_back(coefficient, variable);
}

Constraint::Constraint(double lhs, double rhs) : lhs_(lhs), rhs_(rhs) {
  assert(rhs - lhs >= -epsilon);
}

}  // namespace scip