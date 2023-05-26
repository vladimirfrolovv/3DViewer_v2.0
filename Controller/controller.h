#ifndef CPP4_3D_VIEWER_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_
#define CPP4_3D_VIEWER_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_

#include "../Model/model.h"
#include "adapter.h"
#include "facade.h"

namespace s21 {
class Controller {
 public:
  Controller() { model_ = new Model; }
  ~Controller() { delete model_; }
  std::pair<double *, unsigned *> GetPair(std::string filename);
  std::pair<unsigned, unsigned> GetModelSize();
  void RotateModel(double angle, char axis);
  void MoveModel(double value, char axis);
  void SetModelScale(double scale);
  Model *GetModel() { return model_; }

 private:
  Model *model_;
  Adapter *adapter_;
  Facade *facade_;
};
}  // namespace s21

#endif  // CPP4_3D_VIEWER_V2_0_1_SRC_CONTROLLER_CONTROLLER_H_
