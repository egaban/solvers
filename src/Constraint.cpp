#include <scip/scip.h>
#include <scip/scipdefplugins.h>
#include <scip_cpp/Constraint.h>

#include "Common.h"

namespace scip {

void Constraint::add_contribution(double coefficient,
                                  const Variable& variable) {
  contributions_.push_back({coefficient, variable});
}

Constraint::Constraint(Scip* scip, const std::string& name, double lhs,
                       double rhs)
    : lhs_(lhs), rhs_(rhs), scip_cons_ptr_(nullptr) {
  assert(is_leq(lhs, rhs));

  CHECK_RETCODE(SCIPcreateConsBasicLinear(scip, &scip_cons_ptr_, name.c_str(), 0,
                                          nullptr, nullptr, lhs, rhs));
  CHECK_RETCODE(SCIPaddCons(scip, scip_cons_ptr_));
}

}  // namespace scip
