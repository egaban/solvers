#include <scip/scip.h>
#include <scip_cpp/Model.h>

#include "Common.h"

namespace scip {

Model::Model(void) : scip_ptr_(nullptr) {
  auto retcode = SCIPcreate(&scip_ptr_);

  if (retcode != SCIP_OKAY) {
    throw BadRetcodeException(retcode);
  }
}

Model::~Model() {
  for (auto& ptr : constraints_) delete ptr.second;
  for (auto& ptr : variables_) delete ptr.second;

  SCIPfree(&scip_ptr_);
}

void Model::create_variable(VariableType type, double objective_value,
                            double lower_bound, double upper_bound,
                            const std::string& name) {
#ifndef NDEBUG
  if (variables_.find(name) != variables_.end()) {
    throw ScipException("Variable with name " + name + " already exists.\n");
  }
#endif

  variables_[name] = new Variable(scip_ptr_, type, objective_value, lower_bound,
                                  upper_bound, name);
}

void Model::create_constraint(double lhs, double rhs, const std::string& name) {
#ifndef NDEBUG
  if (constraints_.find(name) != constraints_.end()) {
    throw ScipException("Constraint with name " + name + " already exists.\n");
  }
#endif

  constraints_[name] = new Constraint(scip_ptr_, name, lhs, rhs);
}

}  // namespace scip
