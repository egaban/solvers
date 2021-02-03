#include <scip_cpp/Model.h>

#include <fstream>
#include <iostream>
#include <vector>

struct Instance {
  int n;               // Amount of items
  int W;               // Capacity
  std::vector<int> v;  // Values
  std::vector<int> w;  // Weights
};

Instance read_instance(std::ifstream& in) {
  Instance instance;

  in >> instance.n >> instance.W;

  instance.v.reserve(instance.n);
  instance.w.reserve(instance.n);

  for (int i = 0; i < instance.n; ++i) {
    in >> instance.v[i] >> instance.w[i];
  }

  return instance;
}

int main(int argc, char** argv) {
  std::ifstream input(argv[1]);
  scip::Model model(scip::ObjSense::Maximize);

  if (!input.is_open()) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  Instance instance = read_instance(input);

  model.create_constraint(scip::MinusInfinity, instance.W, "(1)");

  for (int i = 0; i < instance.n; ++i) {
    auto var_name = "X" + std::to_string(i);
    model.create_variable(scip::VariableType::Binary, instance.v[i], 0, 1,
                          var_name);
    model.add_contribution_to_constraint(var_name, instance.w[i], "(1)");
  }

  model.solve();

  return 0;
}
