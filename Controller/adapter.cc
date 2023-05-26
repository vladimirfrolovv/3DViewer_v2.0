#include "adapter.h"

namespace s21 {
std::pair<double *, unsigned *> Adapter::Convert(Model *model,
                                                 std::string filename) {
  model->Parse(filename);
  return model->GetArr();
}
}  // namespace s21
