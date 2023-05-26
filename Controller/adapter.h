#ifndef CPP4_3D_VIEWER_V2_0_1_SRC_CONTROLLER_ADAPTER_H_
#define CPP4_3D_VIEWER_V2_0_1_SRC_CONTROLLER_ADAPTER_H_

#include <iostream>

#include "../Model/model.h"

namespace s21 {
class Adapter {
 public:
  std::pair<double *, unsigned *> Convert(Model *model, std::string filename);
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V2_0_1_SRC_CONTROLLER_ADAPTER_H_
