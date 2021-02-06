#include <scip/scip.h>
#include <scip/scipdefplugins.h>
#include <scip_cpp/Variable.h>

namespace scip {

SCIP_Vartype Variable::ConvertToScipVartype(VariableType t) {
  switch (t) {
    case VariableType::Binary:
      return SCIP_VARTYPE_BINARY;
    case VariableType::Integer:
      return SCIP_VARTYPE_INTEGER;
    case VariableType::Real:
      return SCIP_VARTYPE_CONTINUOUS;
    default:
      throw ScipException("Illegal VariableType");
  }
}

Variable::Variable(Scip* scip, VariableType type, double objective_value,
                   double lower_bound, double upper_bound,
                   const std::string& name)
    : type_(type),
      obj_(objective_value),
      lb_(lower_bound),
      ub_(upper_bound),
      scip_ptr_(scip),
      scip_var_ptr_(nullptr) {
  assert(is_leq(lb_, ub_));

  auto scip_vartype = ConvertToScipVartype(type);

  CHECK_RETCODE(SCIPcreateVarBasic(scip, &scip_var_ptr_, name.c_str(), lb_, ub_,
                                   obj_, scip_vartype));

  CHECK_RETCODE(SCIPaddVar(scip, scip_var_ptr_));
}

Variable::~Variable() { SCIPreleaseVar(scip_ptr_, &scip_var_ptr_); }

}  // namespace scip
