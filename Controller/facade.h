#ifndef CPP4_3D_VIEWER_V2_0_1_SRC_CONTROLLER_FACADE_H_
#define CPP4_3D_VIEWER_V2_0_1_SRC_CONTROLLER_FACADE_H_

#include "../Model/model.h"

namespace s21 {
class Facade {
 public:
  void RotateModel(Model *model, double angle, char axis);
  void MoveModel(Model *model, double value, char axis);
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V2_0_1_SRC_CONTROLLER_FACADE_H_
