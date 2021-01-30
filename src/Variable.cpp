#include <scip/scip.h>
#include <scip/scipdefplugins.h>
#include <scip_cpp/Variable.h>

namespace scip {

static SCIP_Vartype convert_to_scip_vartype(VariableType t) {
  switch (t) {
    case VariableType::Binary:
      return SCIP_VARTYPE_BINARY;
    case VariableType::Integer:
      return SCIP_VARTYPE_INTEGER;
    case VariableType::Real:
      return SCIP_VARTYPE_CONTINUOUS;
  }
}

Variable::Variable(Scip* scip, VariableType type, double objective_value,
                   double lower_bound, double upper_bound,
                   const std::string& name)
    : type_(type),
      obj_(objective_value),
      lb_(lower_bound),
      ub_(upper_bound),
      scip_var_ptr_(nullptr) {
  auto scip_vartype = convert_to_scip_vartype(type);

  SCIPcreateVarBasic(scip, &scip_var_ptr_, name.c_str(), lb_, ub_, obj_,
                     scip_vartype);
  SCIPaddVar(scip, scip_var_ptr_);
}

}  // namespace scip
