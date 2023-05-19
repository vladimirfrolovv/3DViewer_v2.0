#include "myopengl.h"

#include <QMoveEvent>
Myopengl::Myopengl(QWidget *parent) : QOpenGLWidget{parent} {
  res = (exit_st *)calloc(1, sizeof(exit_st));
}

void Myopengl::initializeGL() {
  initializeOpenGLFunctions();
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glTranslatef(0, 0, 0);
}
void Myopengl::resizeGL(int w, int h) {}

void Myopengl::paintGL() {
  glClearColor(background_color.redF(), background_color.greenF(),
               background_color.blueF(), 1);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnableClientState(GL_VERTEX_ARRAY);
  glLineWidth(thickness);
  set_scale(res, scale);
  striple_setting();

  glColor3f(line_color.redF(), line_color.greenF(), line_color.blueF());

  glPointSize(point_thickness);

  if (proection == 1) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 6);
    glTranslatef(0, 0, -3);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glTranslatef(0, 0, 0);
  }
  glVertexPointer(3, GL_DOUBLE, 0, res->vertex);

  glDrawElements(GL_LINES, res->amount_struct_pol, GL_UNSIGNED_INT,
                 res->poligons);

  if (form_points != 0) {
    point_setting();
    glDrawElements(GL_POINTS, res->amount_struct_pol, GL_UNSIGNED_INT,
                   res->poligons);
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void Myopengl::mouseMoveEvent(QMouseEvent *mo) {
  scale = 1;
  rotation_x(0.001 / M_PI * (mo->pos().y() - mPos.y()), res);
  rotation_y((0.001 / M_PI * (mo->pos().x() - mPos.x())) * -1, res);
  update();
}

void Myopengl::mousePressEvent(QMouseEvent *mo) {
  scale = 1;
  mPos = mo->pos();
}

void Myopengl::striple_setting() {
  if (striple == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
}

void Myopengl::point_setting() {
  glColor3d(points_color.redF(), points_color.greenF(), points_color.blueF());
  if (form_points == 2) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }
}
