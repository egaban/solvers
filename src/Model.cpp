#include <scip/scip.h>
#include <scip_cpp/Exception.h>
#include <scip_cpp/Model.h>

namespace scip {

Model::Model(void) : scip_ptr_(nullptr) {
  auto retcode = SCIPcreate(&scip_ptr_);

  if (retcode != SCIP_OKAY) {
    throw BadRetcodeException(retcode);
  }
}

void Model::create_variable(VariableType type, double objective_value,
                            double lower_bound, double upper_bound,
                            const std::string& name) {
  if (variables_.find(name) != variables_.end()) {
    throw ScipException("Variable with name " + name + " already exists.\n");
  }

  variables_[name] = new Variable(scip_ptr_, type, objective_value, lower_bound,
                                  upper_bound, name);
}

Model::~Model() {
  for (auto& ptr : constraints_) delete ptr.second;
  for (auto& ptr : variables_) delete ptr.second;
}

}  // namespace scip
