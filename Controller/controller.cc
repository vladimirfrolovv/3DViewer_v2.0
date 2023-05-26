#include "controller.h"

namespace s21 {
std::pair<double*, unsigned*> Controller::GetPair(std::string filename) {
  return adapter_->Convert(model_, filename);
}
std::pair<unsigned, unsigned> Controller::GetModelSize() {
  return model_->GetSize();
}
void Controller::RotateModel(double angle, char axis) {
  facade_->RotateModel(model_, angle, axis);
}
void Controller::MoveModel(double value, char axis) {
  facade_->MoveModel(model_, value, axis);
}
void Controller::SetModelScale(double scale) { model_->SetScale(scale); }
}  // namespace s21
