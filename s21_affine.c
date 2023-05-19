#include "s21_3DViewer.h"

void rotation_x(double angle, exit_st *st) {
  for (unsigned i = 0; i < st->amount_struct_ver; i += 3) {
    double temp_y = st->vertex[i + 1];
    double temp_z = st->vertex[i + 2];
    st->vertex[i + 1] = cos(angle) * temp_y + sin(angle) * temp_z;
    st->vertex[i + 2] = -sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void rotation_y(double angle, exit_st *st) {
  for (unsigned i = 0; i < st->amount_struct_ver; i += 3) {
    double temp_x = st->vertex[i];
    double temp_z = st->vertex[i + 2];
    st->vertex[i] = cos(angle) * temp_x + sin(angle) * temp_z;
    st->vertex[i + 2] = -sin(angle) * temp_x + cos(angle) * temp_z;
  }
}

void rotation_z(double angle, exit_st *st) {
  for (unsigned i = 0; i < st->amount_struct_ver; i += 3) {
    double temp_x = st->vertex[i];
    double temp_y = st->vertex[i + 1];
    st->vertex[i] = cos(angle) * temp_x - sin(angle) * temp_y;
    st->vertex[i + 1] = sin(angle) * temp_x + cos(angle) * temp_y;
  }
}

void setting_to_center(exit_st *st) {
  double centX = st->minmaxX[0] + (st->minmaxX[1] - st->minmaxX[0]) / 2;
  double centY = st->minmaxY[0] + (st->minmaxY[1] - st->minmaxY[0]) / 2;
  double centZ = st->minmaxZ[0] + (st->minmaxZ[1] - st->minmaxZ[0]) / 2;
  for (unsigned i = 0; i < st->amount_struct_ver; i += 3) {
    st->vertex[i] -= centX;
    st->vertex[i + 1] -= centY;
    st->vertex[i + 2] -= centZ;
  }
}
void set_scale(exit_st *st, double scale) {
  for (unsigned i = 0; i < st->amount_struct_ver; i++) {
    st->vertex[i] *= scale;
  }
}

void s21_move(exit_st *st, double a, char axis) {
  for (unsigned i = 0; i < st->amount_struct_ver; i += 3) {
    if (axis == 'x')
      st->vertex[i] += a;
    else if (axis == 'y')
      st->vertex[i + 1] += a;
    else if (axis == 'z')
      st->vertex[i + 2] += a;
  }
}

double normalize(exit_st *st) {
  double x = st->minmaxX[1] - st->minmaxX[0];
  double y = st->minmaxY[1] - st->minmaxY[0];
  double z = st->minmaxZ[1] - st->minmaxZ[0];
  double d = fmax(fmax(x, y), z);
  double value = 0.5;
  double scale = (value - (value * (-1))) / d;
  return scale;
}
