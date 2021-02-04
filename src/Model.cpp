#include <scip/scip.h>
#include <scip/scipdefplugins.h>
#include <scip_cpp/Model.h>

namespace scip {

Model::Model(ObjSense sense) : scip_ptr_(nullptr) {
  CHECK_RETCODE(SCIPcreate(&scip_ptr_));
  CHECK_RETCODE(SCIPincludeDefaultPlugins(scip_ptr_));

  auto scip_objsense = (sense == ObjSense::Minimize) ? SCIP_OBJSENSE_MINIMIZE
                                                     : SCIP_OBJSENSE_MAXIMIZE;

  // TODO: name parameter
  CHECK_RETCODE(SCIPcreateProbBasic(scip_ptr_, "Scip problem"));
  CHECK_RETCODE(SCIPsetObjsense(scip_ptr_, scip_objsense));
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

void Model::add_contribution_to_constraint(const std::string& variable_name,
                                           double coefficient,
                                           const std::string& constraint_name) {
  auto& variable = get_variable(variable_name);
  auto& constraint = get_constraint(constraint_name);

  constraint.add_contribution(coefficient, variable);
}

void Model::solve(void) {
  load_all_contributions();

#ifdef DEBUG_MODEL
  CHECK_RETCODE(SCIPwriteOrigProblem(scip_ptr_, "teste.lp", "lp", FALSE));
#endif

  CHECK_RETCODE(SCIPsolve(scip_ptr_));
}

void Model::load_all_contributions(void) {
  for (auto& cons : constraints_) {
    load_constraint_contributions(*(cons.second));
  }
}

void Model::load_constraint_contributions(const Constraint& constraint) {
  auto cons_ptr = constraint.get_scipcons_ptr();

  for (const auto& contribution : constraint.get_contributions()) {
    auto var_ptr = contribution.variable.get_scipvar_pointer();
    auto coef = contribution.coefficient;
    CHECK_RETCODE(SCIPaddCoefLinear(scip_ptr_, cons_ptr, var_ptr, coef));
  }
}

}  // namespace scip
