#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "../s21_3DViewer.h"

START_TEST(test_1) {
  exit_st *st = calloc(1, sizeof(exit_st));
  s21_parse(st, "Obj/Cube.obj");
  ck_assert_int_eq(st->amount_struct_ver / 3, 8);
  s21_remove_struct(st);
  free(st);
}
END_TEST

START_TEST(test_2) {
  exit_st *st = calloc(1, sizeof(exit_st));
  s21_parse(st, "Obj/Cube.obj");
  ck_assert_int_eq(st->amount_struct_pol / 4, 12);
  s21_remove_struct(st);
  free(st);
}
END_TEST

START_TEST(test_3) {
  exit_st *st = calloc(1, sizeof(exit_st));
  st->vertex = calloc(3, sizeof(double));
  st->vertex[0] = 1.1;
  st->vertex[1] = 1.2;
  st->vertex[2] = 1.3;
  st->amount_struct_ver = 3;
  rotation_x(10, st);
  rotation_y(10, st);
  rotation_z(10, st);
  ck_assert_double_eq_tol(st->vertex[0], -0.357989, 6);
  ck_assert_double_eq_tol(st->vertex[1], 1.810763, 6);
  ck_assert_double_eq_tol(st->vertex[2], 0.965909, 6);
  s21_remove_struct(st);
  free(st);
}
END_TEST

START_TEST(test_4) {
  exit_st *st = calloc(1, sizeof(exit_st));
  st->vertex = calloc(3, sizeof(double));
  st->vertex[0] = 2;
  st->vertex[1] = 3;
  st->vertex[2] = 4;
  st->amount_struct_ver = 3;
  normalize(st);
  set_scale(st, 2);
  ck_assert_double_eq_tol(st->vertex[0], 4, 6);
  ck_assert_double_eq_tol(st->vertex[1], 6, 6);
  ck_assert_double_eq_tol(st->vertex[2], 6, 6);
  s21_remove_struct(st);
  free(st);
}
END_TEST

START_TEST(test_5) {
  exit_st *st = calloc(1, sizeof(exit_st));
  st->vertex = calloc(3, sizeof(double));
  st->vertex[0] = 2;
  st->vertex[1] = 3;
  st->vertex[2] = 4;
  st->amount_struct_ver = 3;
  setting_to_center(st);
  s21_move(st, 0.5, 'x');
  s21_move(st, 0.5, 'y');
  s21_move(st, 0.5, 'z');
  ck_assert_double_eq_tol(st->vertex[0], 2.5, 6);
  ck_assert_double_eq_tol(st->vertex[1], 3.5, 6);
  ck_assert_double_eq_tol(st->vertex[2], 3.5, 6);
  s21_remove_struct(st);
  free(st);
}
END_TEST

START_TEST(test_6) {
  exit_st *st = calloc(1, sizeof(exit_st));
  int status = s21_parse(st, "asd");
  ck_assert_int_eq(status, 1);
  free(st);
}
END_TEST

Suite *s21_viewer_tests_create() {
  {
    Suite *s21_viewer = suite_create("s21_viewer");
    TCase *s21_viewer_tests = tcase_create("S21_VIEWER");
    tcase_add_test(s21_viewer_tests, test_1);
    tcase_add_test(s21_viewer_tests, test_2);
    tcase_add_test(s21_viewer_tests, test_3);
    tcase_add_test(s21_viewer_tests, test_4);
    tcase_add_test(s21_viewer_tests, test_5);
    tcase_add_test(s21_viewer_tests, test_6);
    suite_add_tcase(s21_viewer, s21_viewer_tests);
    return s21_viewer;
  }
}

END_TEST
int main() {
  Suite *s21_viewer = s21_viewer_tests_create();
  SRunner *s21_viewer_runner = srunner_create(s21_viewer);
  int number_failed;
  srunner_run_all(s21_viewer_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(s21_viewer_runner);
  srunner_free(s21_viewer_runner);

  return number_failed == 0 ? 0 : 1;
}
