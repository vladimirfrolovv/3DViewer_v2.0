#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <mainwindow.h>
#include <stdlib.h>

#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QMoveEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QThread>

#include "s21_3DViewer.h"

class Myopengl : public QOpenGLWidget, public QOpenGLFunctions {
 public:
  int save_set = 0;
  double thickness = 1;
  Myopengl(QWidget *parent = nullptr);
  double scale = 1;
  QColor background_color = QColorConstants::Black;
  QColor points_color = QColorConstants::White;
  QColor line_color = QColorConstants::White;
  int striple = 0;
  int proection = 0;
  int form_points = 0;
  ~Myopengl() {
    if (res) {
      s21_remove_struct(res);
      free(res);
    }
  }
  exit_st *res;
  QPoint mPos;
  double point_thickness = 0;

 protected:
  void point_setting();
  void striple_setting();
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
};

#endif  // MYOPENGL_H
