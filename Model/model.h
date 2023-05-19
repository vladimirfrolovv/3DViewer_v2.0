#ifndef SRC_S21_3DVIEVER_H_
#define SRC_S21_3DVIEVER_H_

#include <cmath>
#include <cstring>
#include <vector>
namespace s21 {
    class Model {
    public:


/// @brief Main function of parsing obj file and make
/// @param st exit struct with data
/// @param filename name obj file
/// @return error
int s21_parse(exit_st *st, char *filename);
/// @brief function of memory allocation for struct
/// @param st struct
/// @return error if memory dont allocate
int s21_init_struct(exit_st *st);
/// @brief function for parse coordinates point
/// @param vertex_counter
/// @param ptr pointer for current line
/// @param st struct
/// @param capacity_ver current capacity array of coordinates
/// @return error
int parse_vertex(int *vertex_counter, char *ptr, exit_st *st,
                 int *capacity_ver);
/// @brief function for parse poligons
/// @param ptr pointer for current line
/// @param st struct
/// @param poligons_counter counter current amount poligons
/// @param capacity_pol current capacity array of poligons
/// @return error
int parse_poligons(char *ptr, exit_st *st, int *poligons_counter,
                   int *capacity_pol);
/// @brief free memory struct
/// @param st
void s21_remove_struct(exit_st *st);

/// @brief functoin for find max and min coordinates of all axis
/// @param st struct
/// @param counter_axis counter of current axis
/// @param coord current coordinate
void s21_minmax_cord(exit_st *st, int counter_axis, double coord);

/// @brief function find coefficient for normalize value  coordinate points to
/// -1 / 1
/// @param st struct
/// @return coefficient
double normalize(exit_st *st);
/// @brief function for setting model on center of widget
/// @param st struct
void setting_to_center(exit_st *st);
/// @brief function for multiplication coordinates point on necessary
/// coefiiciant of scale
/// @param st struct
/// @param scale scale
void set_scale(exit_st *st, double scale);
/// @brief functoin for rotation along the axis x on necessary angle
/// @param angle
/// @param st
void rotation_x(double angle, exit_st *st);
/// @brief functoin for rotation along the axis y on necessary angle
/// @param angle
/// @param st
void rotation_y(double angle, exit_st *st);
/// @brief functoin for rotation along the axis z on necessary angle
/// @param angle
/// @param st
void rotation_z(double angle, exit_st *st);
/// @brief functoin for moving model on necessary coefficient along the axis
/// @param st
/// @param a coefficient
/// @param axis
void s21_move(exit_st *st, double a, char axis);
    private:
        std::vector<double> vertex();
        std::vector<unsigned> poligons();
        unsigned amount_struct_pol = 0;
        unsigned amount_struct_ver = 0;
        double minmaxX[2] = 0;
        double minmaxY[2] = 0;
        double minmaxZ[2] = 0;

} exit_st;
};
}




#endif  // SRC_S21_3DVIEVER_H_
