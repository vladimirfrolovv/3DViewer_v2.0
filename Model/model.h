#ifndef SRC_S21_3DVIEWER_H_
#define SRC_S21_3DVIEWER_H_

#include <locale.h>

#include <cmath>
#include <cstring>
#include <fstream>
#include <vector>

namespace s21 {

class Model {
 public:
  /// @brief Main function of parsing obj file and make
  /// @param st exit struct with data
  /// @param filename name obj file
  /// @return error
  int Parse(std ::string filename);
  /// @brief function for parse coordinates point
  /// @param vertex_counter
  /// @param ptr pointer for current line
  /// @param st struct
  /// @param capacity_ver current capacity array of coordinates
  /// @return error
  void ParseVertex(char* ptr);
  /// @brief function for parse poligons
  /// @param ptr pointer for current line
  /// @param st struct
  /// @param poligons_counter counter current amount poligons
  /// @param capacity_pol current capacity array of poligons
  /// @return error
  void ParsePoligons(char* ptr);
  /// @brief functoin for find max and min coordinates of all axis
  /// @param st struct
  /// @param counter_axis counter of current axis
  /// @param coord current coordinate
  void MinMaxCoord(int counter_axis, double coord);
  /// @brief function find coefficient for normalize value  coordinate points to
  /// -1 / 1
  /// @param st struct
  /// @return coefficient
  double Normalize();
  /// @brief function for setting model on center of widget
  /// @param st struct
  void SettingToCenter();
  /// @brief function for multiplication coordinates point on necessary
  /// coefiiciant of scale
  /// @param st struct
  /// @param scale scale
  void SetScale(double scale);
  /// @brief functoin for rotation along the axis x on necessary angle
  /// @param angle
  /// @param st
  void RotationX(double angle);
  /// @brief functoin for rotation along the axis y on necessary angle
  /// @param angle
  /// @param st
  void RotationY(double angle);
  /// @brief functoin for rotation along the axis z on necessary angle
  /// @param angle
  /// @param st
  void RotationZ(double angle);
  /// @brief functoin for moving model on necessary coefficient along the axis
  /// @param st
  /// @param a coefficient
  /// @param axis
  void Move(double a, char axis);

  std::pair<double*, unsigned*> GetArr();
  void Converter();
  std::pair<unsigned, unsigned> GetSize();

  ~Model() {
    delete vertex_;
    delete poligons_;
  }

 private:
  std::vector<double> vertex;
  std::vector<unsigned> poligons;
  double* vertex_;
  unsigned* poligons_;
  double minmaxX[2] = {0};
  double minmaxY[2] = {0};
  double minmaxZ[2] = {0};
};
}  // namespace s21

#endif  // SRC_S21_3DVIEWER_H_
