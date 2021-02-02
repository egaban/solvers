#include <scip/scip.h>
#include <scip/scipdefplugins.h>
#include <scip_cpp/Constraint.h>
#include <scip_cpp/Exception.h>

#include "Core.h"

namespace scip {

void Constraint::add_contribution(double coefficient,
                                  const Variable& variable) {
  contributions_.push_back({coefficient, variable});
}

Constraint::Constraint(Scip* scip, const std::string& name, double lhs,
                       double rhs)
    : lhs_(lhs), rhs_(rhs), scip_ptr_(nullptr) {
  assert(are_real_equals(lhs, rhs));

  auto retcode = SCIPcreateConsBasicLinear(scip, &scip_ptr_, name.c_str(), 0,
                                           nullptr, nullptr, lhs, rhs);

  if (retcode != SCIP_OKAY) {
    throw BadRetcodeException(retcode);
  }
}

}  // namespace scip
