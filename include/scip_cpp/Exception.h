#pragma once

#include <scip/type_retcode.h>

#include <exception>
#include <string>

namespace scip {

class BadRetcodeException : public std::exception {
 private:
  SCIP_RETCODE retcode_;

 public:
  BadRetcodeException(SCIP_RETCODE retcode) : retcode_(retcode) {}

  const char* what(void) const noexcept override;
};

class ScipException : public std::exception {
 private:
  std::string msg_;

  std::string retcode_as_string(void) const;

 public:
  ScipException(const std::string& msg) : msg_(msg) {}

  const char* what(void) const noexcept override { return msg_.c_str(); }
};

}  // namespace scip
