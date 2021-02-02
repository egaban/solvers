#include <scip_cpp/Exception.h>

namespace scip {

const char* BadRetcodeException::what(void) const noexcept {
  switch (retcode_) {
    case SCIP_ERROR:
      return "SCIP_ERROR";
    case SCIP_NOMEMORY:
      return "SCIP_NOMEMORY";
    case SCIP_READERROR:
      return "SCIP_READERROR";
    case SCIP_WRITEERROR:
      return "SCIP_WRITEERROR";
    case SCIP_NOFILE:
      return "SCIP_NOFILE";
    case SCIP_FILECREATEERROR:
      return "SCIP_FILECREATEERROR";
    case SCIP_LPERROR:
      return "SCIP_LPERROR";
    case SCIP_NOPROBLEM:
      return "SCIP_NOPROBLEM";
    case SCIP_INVALIDCALL:
      return "SCIP_INVALIDCALL";
    case SCIP_INVALIDDATA:
      return "SCIP_INVALIDDATA";
    case SCIP_INVALIDRESULT:
      return "SCIP_INVALIDRESULT";
    case SCIP_PLUGINNOTFOUND:
      return "SCIP_PLUGINNOTFOUND";
    case SCIP_PARAMETERUNKNOWN:
      return "SCIP_PARAMETERUNKNOWN";
    case SCIP_PARAMETERWRONGTYPE:
      return "SCIP_PARAMETERWRONGTYPE";
    case SCIP_PARAMETERWRONGVAL:
      return "SCIP_PARAMETERWRONGVAL";
    case SCIP_KEYALREADYEXISTING:
      return "SCIP_KEYALREADYEXISTING";
    case SCIP_MAXDEPTHLEVEL:
      return "SCIP_MAXDEPTHLEVEL";
    case SCIP_BRANCHERROR:
      return "SCIP_BRANCHERROR";
  }
  return "Unknown retcode";
}

}  // namespace scip
