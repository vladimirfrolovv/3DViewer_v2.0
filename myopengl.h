#ifndef CPP4_3D_VIEWER_V2_0_1_SRC_MYOPENGL_H_
#define CPP4_3D_VIEWER_V2_0_1_SRC_MYOPENGL_H_

#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QMoveEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QThread>

#include "View/mainwindow.h"

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
  ~Myopengl() {}
  std::pair<double *, unsigned *> res;
  std::pair<unsigned, unsigned> size;
  QPoint mPos;
  double point_thickness = 0;

 protected:
  void PointSetting();
  void StripleSetting();
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
};

#endif  // CPP4_3D_VIEWER_V2_0_1_SRC_MYOPENGL_H_
