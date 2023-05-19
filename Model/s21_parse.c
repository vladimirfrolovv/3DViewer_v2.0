#include <locale.h>

#include "s21_3DViewer.h"
// int main() {

//  exit_st *st = (exit_st *)calloc(1, sizeof(exit_st));
// s21_parse(st, "test.obj");
//  // printf("%d", st->amount_struct_ver);
//  for (unsigned i = 0; i < st->amount_struct_ver; i++) {
//    printf("v %lf ", st->vertex[i]);
//    printf("%lf ", st->vertex[i + 1]);
//    printf("%lf\n", st->vertex[i + 2]);
//    i += 2;
//  }
//  // for (int i = 0; i < st->amount_struct_pol; i++) {
//  //   printf(" %d", st->poligons[i]);
//  // }
//  // printf("%d", st->amount_struct_pol);
//  // printf("%lf ", st->minmaxY[0]);
//  // printf("%lf", st->minmaxY[1]);
//  // double scale = normalize(st);
//  // set_scale(st, scale);
//  // printf("%lf ", st->vertex[0]);
//  // printf("%lf ", st->vertex[1]);
//  // printf("%lf", st->vertex[2]);
//  s21_remove_struct(st);
//  free(st);
//  return 0;
//}
int s21_parse(exit_st *st, char *filename) {
  setlocale(LC_ALL, "en-US");
  setlocale(LC_NUMERIC, "C");
  int status = 0;
  char *line = NULL;
  size_t size_line = 0;
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    char *ptr = NULL;
    int poligons_counter = 0;
    int vertex_counter = 0;
    int capacity_ver = 3;
    int capacity_pol = 3;
    status = s21_init_struct(st);
    if (!status) {
      while (getline(&line, &size_line, file) != -1 && !status) {
        ptr = line;
        if (*ptr == 'v') {
          status = parse_vertex(&vertex_counter, ptr, st, &capacity_ver);
        } else if (*ptr == 'f') {
          status = parse_poligons(ptr, st, &poligons_counter, &capacity_pol);
        }
      }
    }
    free(line);
    fclose(file);
    st->amount_struct_pol = poligons_counter;
    st->amount_struct_ver = vertex_counter;
  } else {
    status = 1;
  }
  return status;
}

int s21_init_struct(exit_st *st) {
  int status = 0;
  st->amount_struct_pol = 0;
  st->amount_struct_ver = 0;
  if ((st->poligons = (unsigned *)calloc(3, sizeof(unsigned))) == NULL) {
    status = 1;
  }
  if ((st->vertex = (double *)calloc(3, sizeof(double))) == NULL) {
    status = 1;
  }
  return status;
}

int parse_vertex(int *vertex_counter, char *ptr, exit_st *st,
                 int *capacity_ver) {
  int status = 0;
  int counter_axis = 0;
  ptr++;
  if (*ptr == ' ') {
    while (*ptr != '\0') {
      if (!isdigit(*ptr) && *ptr != '-') {
        ptr++;
      } else {
        if (*vertex_counter < *capacity_ver) {
          st->vertex[*vertex_counter] = strtod(ptr, &ptr);
          if (*vertex_counter == 0) {
            st->minmaxX[0] = st->vertex[*vertex_counter];
            st->minmaxX[1] = st->vertex[*vertex_counter];
          }
          if (*vertex_counter == 1) {
            st->minmaxY[0] = st->vertex[*vertex_counter];
            st->minmaxY[1] = st->vertex[*vertex_counter];
          }
          if (*vertex_counter == 2) {
            st->minmaxZ[0] = st->vertex[*vertex_counter];
            st->minmaxZ[1] = st->vertex[*vertex_counter];
          }
          s21_minmax_cord(st, counter_axis, st->vertex[*vertex_counter]);
          counter_axis++;
          *vertex_counter += 1;
          while (*ptr != '\0' && *ptr == ' ') {
            ptr++;
          }
        } else {
          double *tmp;

          *capacity_ver *= 2;

          if ((tmp = realloc(st->vertex, *capacity_ver * sizeof(double))) ==

              NULL) {
            return 1;

          } else {
            st->vertex = tmp;
          }
        }
      }
    }
  }

  return status;
}

int parse_poligons(char *ptr, exit_st *st, int *poligons_counter,
                   int *capacity_pol) {
  ptr++;
  int i = 0;
  int status = 0;
  int first_poligon = 0;
  int tmp_pol = 0;
  if (*ptr == ' ') {
    while (*ptr != '\0') {
      if (!isdigit(*ptr)) {
        ptr++;
      } else {
        if (*poligons_counter < *capacity_pol - 1) {
          if (i == 0) {
            st->poligons[*poligons_counter] = strtol(ptr, &ptr, 0) - 1;
            first_poligon = st->poligons[*poligons_counter];
            *poligons_counter += 1;
            i++;
          } else {
            tmp_pol = strtol(ptr, &ptr, 0) - 1;
            st->poligons[*poligons_counter] = tmp_pol;
            *poligons_counter += 1;
            st->poligons[*poligons_counter] = tmp_pol;
            *poligons_counter += 1;
          }
          while (*ptr != '\0' && *ptr != ' ') {
            ptr++;
          }
        } else {
          unsigned *tmp;
          *capacity_pol *= 2;
          if ((tmp = realloc(st->poligons, *capacity_pol * sizeof(unsigned))) ==
              NULL) {
            return 1;
          } else {
            st->poligons = tmp;
          }
        }
      }
    }
    st->poligons[*poligons_counter] = first_poligon;
    *poligons_counter += 1;
  }
  return status;
}

void s21_remove_struct(exit_st *st) {
  free(st->vertex);
  free(st->poligons);
}

void s21_minmax_cord(exit_st *st, int counter_axis, double coord) {
  if (counter_axis == 0) {
    if (st->minmaxX[0] > coord) {
      st->minmaxX[0] = coord;
    }
    if (st->minmaxX[1] < coord) {
      st->minmaxX[1] = coord;
    }
  } else if (counter_axis == 1) {
    if (st->minmaxY[0] > coord) {
      st->minmaxY[0] = coord;
    }
    if (st->minmaxY[1] < coord) {
      st->minmaxY[1] = coord;
    }
  } else if (counter_axis == 2) {
    if (st->minmaxZ[0] > coord) {
      st->minmaxZ[0] = coord;
    }
    if (st->minmaxZ[1] < coord) {
      st->minmaxZ[1] = coord;
    }
  }
}
