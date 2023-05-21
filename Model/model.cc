#include "model.h"

namespace s21 {

int Model::Parse(std ::string filename) {
  setlocale(LC_ALL, "en-US");
  setlocale(LC_NUMERIC, "C");
  int status = 0;
  std::string line;
  ifstream file(filename);
  if (file) {
    char *ptr = nullptr;
    int poligons_counter = 0;
    int vertex_counter = 0;
    if (!status) {
      while (getline(file, line) != -1) {
        ptr = const_cast<char *>(line.c_str());
        if (*ptr == 'v') {
          ParseVertex(ptr);
        } else if (*ptr == 'f') {
          ParseVertex(ptr);
        }
      }
    }
    fclose(file);

  } else {
    status = 1;
  }

  return status;
}

void Model::ParseVertex(char *ptr) {
  int counter_axis = 0;
  ptr++;
  if (*ptr == ' ') {
    while (*ptr != '\0') {
      if (!isdigit(*ptr) && *ptr != '-') {
        ptr++;
      } else {
        vertex.push_back(strtod(ptr, &ptr));
        MinMaxCoord(counter_axis, vertex.back());
        counter_axis++;
        while (*ptr == ' ') {
          ptr++;
        }
      }
    }
  }
}

void Model::ParsePoligons(char *ptr) {
  ptr++;
  int counter_first_pol = 0, first_poligon = 0, tmp_pol = 0;
  if (*ptr == ' ') {
    while (*ptr != '\0') {
      if (!isdigit(*ptr)) {
        ptr++;
      } else {
        if (counter_first_pol == 0) {
          poligons.push_back(strtol(ptr, &ptr, 0) - 1);
          first_poligon = poligons.back();
          counter_first_pol++;
        } else {
          tmp_pol = strtol(ptr, &ptr, 0) - 1;
          poligons.push_back(tmp_pol);
          poligons.push_back(tmp_pol);
        }
        while (*ptr != '\0' && *ptr != ' ') {
          ptr++;
        }
      }
    }
  }
  poligons.push_back(first_poligon);
}

void Model::MinMaxCoord(int counter_axis, double coord) {
  if (counter_axis == 0) {
    if (minmaxX[0] > coord) {
      minmaxX[0] = coord;
    }
    if (minmaxX[1] < coord) {
      minmaxX[1] = coord;
    }
  } else if (counter_axis == 1) {
    if (minmaxY[0] > coord) {
      minmaxY[0] = coord;
    }
    if (minmaxY[1] < coord) {
      minmaxY[1] = coord;
    }
  } else if (counter_axis == 2) {
    if (minmaxZ[0] > coord) {
      minmaxZ[0] = coord;
    }
    if (minmaxZ[1] < coord) {
      minmaxZ[1] = coord;
    }
  }
}

void Model::RotationX(double angle) {
  for (unsigned i = 0; i < vertex.size(); i += 3) {
    double temp_y = vertex[i + 1];
    double temp_z = vertex[i + 2];
    vertex[i + 1] = cos(angle) * temp_y + sin(angle) * temp_z;
    vertex[i + 2] = -sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void Model::RotationY(double angle) {
  for (unsigned i = 0; i < vertex.size(); i += 3) {
    double temp_x = vertex[i];
    double temp_z = vertex[i + 2];
    vertex[i] = cos(angle) * temp_x + sin(angle) * temp_z;
    vertex[i + 2] = -sin(angle) * temp_x + cos(angle) * temp_z;
  }
}

void Model::RotationZ(double angle) {
  for (unsigned i = 0; i < vertex.size(); i += 3) {
    double temp_x = vertex[i];
    double temp_y = vertex[i + 1];
    vertex[i] = cos(angle) * temp_x - sin(angle) * temp_y;
    vertex[i + 1] = sin(angle) * temp_x + cos(angle) * temp_y;
  }
}

void Model::SettingToCenter() {
  double centX = minmaxX[0] + (minmaxX[1] - minmaxX[0]) / 2;
  double centY = minmaxY[0] + (minmaxY[1] - minmaxY[0]) / 2;
  double centZ = minmaxZ[0] + (minmaxZ[1] - minmaxZ[0]) / 2;
  for (unsigned i = 0; i < vertex.size(); i += 3) {
    vertex[i] -= centX;
    vertex[i + 1] -= centY;
    vertex[i + 2] -= centZ;
  }
}
void Model::SetScale(double scale) {
  for (unsigned i = 0; i < vertex.size(); i++) {
    vertex[i] *= scale;
  }
}

void Model::Move(double a, char axis) {
  for (unsigned i = 0; i < vertex.size(); i += 3) {
    if (axis == 'x')
      vertex[i] += a;
    else if (axis == 'y')
      vertex[i + 1] += a;
    else if (axis == 'z')
      vertex[i + 2] += a;
  }
}

double Model::Normalize() {
  double x = minmaxX[1] - minmaxX[0];
  double y = minmaxY[1] - minmaxY[0];
  double z = minmaxZ[1] - minmaxZ[0];
  double d = fmax(fmax(x, y), z);
  double value = 0.5;
  double scale = (value - (value * (-1))) / d;
  return scale;
}

}  // namespace s21
