#include "facade.h"

namespace s21 {
void Facade::RotateModel(Model *model, double angle, char axis) {
  if (axis == 'x')
    model->RotationX(angle);
  else if (axis == 'y')
    model->RotationY(angle);
  else if (axis == 'z')
    model->RotationZ(angle);
}
void Facade::MoveModel(Model *model, double value, char axis) {
  if (axis == 'x')
    model->Move(value, 0U);
  else if (axis == 'y')
    model->Move(value, 1U);
  else if (axis == 'z')
    model->Move(value, 2U);
}
}  // namespace s21
