#include <gtest/gtest.h>

#include "../Controller/controller.h"

TEST(ModelTests, Case1) {
  s21::Controller test;
  auto pair = test.GetPair("Obj/cube.obj");
  EXPECT_DOUBLE_EQ(pair.first[0], 0.49999975000012498);
}

TEST(ModelTests, Case2) {
  s21::Controller test;
  test.GetPair("Obj/cube.obj");
  auto test_size = test.GetModelSize();
  EXPECT_EQ(test_size.first, 24);
  EXPECT_EQ(test_size.second, 72);
}

TEST(ModelTests, Case3) {
  s21::Controller test;
  test.GetPair("Obj/monkey2.obj");
  auto test_size = test.GetModelSize();
  EXPECT_EQ(test_size.first, 23874);
  EXPECT_EQ(test_size.second, 94464);
}

TEST(ModelTests, Case4) {
  s21::Controller test;
  test.GetPair("Obj/monkey2.obj");
  test.SetModelScale(1.5);
  test.RotateModel(15, 0);
  test.RotateModel(13, 1);
  test.RotateModel(90, 2);
  EXPECT_DOUBLE_EQ(test.GetModel()->GetArr().first[0], 0.17944107522983926);
}
