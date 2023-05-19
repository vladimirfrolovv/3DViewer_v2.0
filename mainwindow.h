#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QFrame>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>

#include "QtGifimage/gifimage/qgifimage.h"
#include "s21_3DViewer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 public slots:
  void get_position(int x);

 private slots:

  void on_EditFile_clicked();

  void on_scale_line_edit_returnPressed();

  void on_x_rotate_returnPressed();

  void on_y_rotate_returnPressed();

  void on_z_rotate_returnPressed();

  void on_x_move_returnPressed();

  void on_y_move_returnPressed();

  void on_z_move_returnPressed();

  void on_backgroundcolor_clicked();

  void on_horizontalSlider_2_sliderReleased();

  void on_comboBox_3_activated(int index);

  void on_scale_slider_sliderMoved(int position);

  void on_Save_set_clicked();

  void on_Color_of_line_clicked();

  void on_parallel_pro_clicked();

  void on_central_pro_clicked();

  void on_color_points_but_clicked();

  void on_horizontalSlider_sliderMoved(int position);

  void on_reset_clicked();

  void on_horizontalSlider_2_valueChanged(int value);

  void on_x_move_slider_valueChanged(int value);

  void on_y_move_slider_valueChanged(int value);

  void on_z_move_slider_valueChanged(int value);

  void on_x_rotate_slider_valueChanged(int value);

  void on_y_rotate_slider_valueChanged(int value);

  void on_z_rotate_slider_valueChanged(int value);

  void on_Choice_points_activated(int index);

  void on_pushButton_4_clicked();

  void saveGifFrame();

  void load_setting();

  void on_load_set_but_clicked();

 private:
  Ui::MainWindow *ui;
  int previous_value_slider_x;
  int previous_value_slider_y;
  int previous_value_slider_z;
  QTimer *timer;
  QGifImage *gif;
  QImage *frame;
  QString gifSavePath;
  int time;
  int previous_value_rotate_x;
  int previous_value_rotate_y;
  int previous_value_rotate_z;

  double previous_scale;
};
#endif  // MAINWINDOW_H
