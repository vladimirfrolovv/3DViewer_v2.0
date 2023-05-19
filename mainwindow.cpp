#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->scale_slider->setSliderPosition(50);
  ui->scale_line_edit->setText("50");
  ui->x_move->setText("0");
  ui->y_move->setText("0");
  ui->z_move->setText("0");
  ui->x_rotate->setText("0");
  ui->y_rotate->setText("0");
  ui->z_rotate->setText("0");
  ui->x_move_slider->setSliderPosition(0);
  ui->y_move_slider->setSliderPosition(0);
  ui->z_move_slider->setSliderPosition(0);
  ui->x_rotate_slider->setSliderPosition(0);
  ui->y_rotate_slider->setSliderPosition(0);
  ui->z_rotate_slider->setSliderPosition(0);
  previous_value_slider_x = 0;
  previous_value_slider_y = 0;
  previous_value_slider_z = 0;
  previous_value_rotate_x = 0;
  previous_value_rotate_y = 0;
  previous_value_rotate_z = 0;
  previous_scale = 50.0;
  // settings
  //  load_setting();
  //  QSettings settings("settings.ini", QSettings::IniFormat);
  //  settings.beginGroup("Settings");

  //  ui->widget->background_color.setRedF(
  //      settings.value("save_Color_redF").toFloat());
  //  ui->widget->background_color.setGreenF(
  //      settings.value("save_Color_greenF").toFloat());
  //  ui->widget->background_color.setBlueF(
  //      settings.value("save_Color_blueF").toFloat());
  //  settings.endGroup();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::get_position(int x) {
  ui->label_vertex->setText(QString::number(x));
}

void MainWindow::on_EditFile_clicked() {
  QString str =
      QFileDialog::getOpenFileName(this, "Open file", "/Users", "*.obj");
  ui->filepath->setText(str);
  std::string v_str = str.toStdString();
  const char *strch = v_str.c_str();
  auto s = const_cast<char *>(strch);

  exit_st *st = (exit_st *)calloc(1, sizeof(exit_st));
  s21_parse(st, s);
  setting_to_center(st);
  double scale = normalize(st);
  set_scale(st, scale);
  ui->widget->res = st;
  QString buf_line = QString::number(st->amount_struct_pol / 2 / 2);
  ui->label_line->setText(buf_line);
  buf_line = QString::number(st->amount_struct_ver / 3);
  ui->label_vertex->setText(buf_line);
}

void MainWindow::on_scale_line_edit_returnPressed() {
  double value = ui->scale_line_edit->text().toDouble();
  if (ui->scale_line_edit->text().toDouble() <= 0) {
    value = 1;
  } else if (ui->scale_line_edit->text().toDouble() > 100) {
    value = 100;
  }
  ui->scale_line_edit->setText(QString::number(value));
  on_scale_slider_sliderMoved(value);
  ui->scale_slider->setValue(value);
  ui->widget->update();
}

void MainWindow::on_x_rotate_returnPressed() {
  ui->widget->scale = 1;
  double value = ui->x_rotate->text().toDouble();
  if (value > 100) {
    value = 100;
    ui->x_rotate->setText(QString::number(100));
  } else if (value < -100) {
    value = -100;
    ui->x_rotate->setText(QString::number(-100));
  }
  double radian = (value - previous_value_rotate_x) * (M_PI / 45.0);
  previous_value_rotate_x = (int)value;
  ui->x_rotate_slider->setValue((int)value);
  rotation_x(radian, ui->widget->res);
  ui->widget->update();
}

void MainWindow::on_y_rotate_returnPressed() {
  ui->widget->scale = 1;
  double value = ui->y_rotate->text().toDouble();
  if (value > 100) {
    value = 100;
    ui->y_rotate->setText(QString::number(100));
  } else if (value < -100) {
    value = -100;
    ui->y_rotate->setText(QString::number(-100));
  }
  double radian = (value - previous_value_rotate_y) * (M_PI / 45.0);
  previous_value_rotate_y = (int)value;
  ui->y_rotate_slider->setValue((int)value);
  rotation_y(radian, ui->widget->res);
  ui->widget->update();
}

void MainWindow::on_z_rotate_returnPressed() {
  ui->widget->scale = 1;
  double value = ui->z_rotate->text().toDouble();
  if (value > 100) {
    value = 100;
    ui->z_rotate->setText(QString::number(100));
  } else if (value < -100) {
    value = -100;
    ui->z_rotate->setText(QString::number(-100));
  }
  double radian = (value - previous_value_rotate_z) * (M_PI / 45.0);
  previous_value_rotate_z = (int)value;
  ui->z_rotate_slider->setValue((int)value);
  rotation_z(radian, ui->widget->res);
  ui->widget->update();
}

void MainWindow::on_x_move_returnPressed() {
  ui->widget->scale = 1;
  double a = ui->x_move->text().toDouble();
  if (a > 100) {
    a = 100;
    ui->x_move->setText(QString::number(100));
  } else if (a < -100) {
    a = -100;
    ui->x_move->setText(QString::number(-100));
  }
  s21_move(ui->widget->res, (a - previous_value_slider_x) * 0.01, 'x');
  previous_value_slider_x = (int)a;
  ui->x_move_slider->setValue((int)a);
  ui->widget->update();
}

void MainWindow::on_y_move_returnPressed() {
  ui->widget->scale = 1;
  double a = ui->y_move->text().toDouble();
  if (a > 100) {
    a = 100;
    ui->y_move->setText(QString::number(100));
  } else if (a < -100) {
    a = -100;
    ui->y_move->setText(QString::number(-100));
  }
  s21_move(ui->widget->res, (a - previous_value_slider_y) * 0.01, 'y');
  previous_value_slider_y = (int)a;
  ui->y_move_slider->setValue((int)a);
  ui->widget->update();
}

void MainWindow::on_z_move_returnPressed() {
  ui->widget->scale = 1;
  double a = ui->z_move->text().toDouble();
  if (a > 100) {
    a = 100;
    ui->z_move->setText(QString::number(100));
  } else if (a < -100) {
    a = -100;
    ui->z_move->setText(QString::number(-100));
  }
  s21_move(ui->widget->res, (a - previous_value_slider_z) * 0.01, 'z');
  previous_value_rotate_z = (int)a;
  ui->z_move_slider->setValue((int)a);
  ui->widget->update();
}

void MainWindow::on_backgroundcolor_clicked() {
  ui->widget->background_color =
      QColorDialog::getColor(Qt::white, this, tr("Select Color"));
  ui->widget->update();
}

void MainWindow::on_horizontalSlider_2_sliderReleased() {}

void MainWindow::on_comboBox_3_activated(int index) {
  ui->widget->scale = 1;
  if (index == 0) {
    ui->widget->striple = 0;
  } else {
    ui->widget->striple = 1;
  }
  ui->widget->update();
}

void MainWindow::on_scale_slider_sliderMoved(int position) {
  if ((position - previous_scale) < 0) {
    for (int i = 0; i < previous_scale - position; i++) {
      set_scale(ui->widget->res, 0.9);
      ui->widget->update();
    }

    previous_scale = position;

  } else if ((position - previous_scale) > 0) {
    for (int i = 0; i < position - previous_scale; i++) {
      set_scale(ui->widget->res, 1.1111);
      ui->widget->update();
    }
    previous_scale = position;
  }
  ui->scale_line_edit->setText(QString::number(position));
}

void MainWindow::on_Color_of_line_clicked() {
  ui->widget->line_color =
      QColorDialog::getColor(Qt::white, this, tr("Select Color"));
  ui->widget->update();
}

void MainWindow::on_parallel_pro_clicked() {
  ui->widget->proection = 0;
  ui->widget->update();
}

void MainWindow::on_central_pro_clicked() {
  ui->widget->proection = 1;
  ui->widget->update();
}

void MainWindow::on_color_points_but_clicked() {
  ui->widget->points_color =
      QColorDialog::getColor(Qt::white, this, tr("Select Color"));
  ui->widget->update();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position) {
  ui->widget->point_thickness = position;
  ui->widget->update();
}

void MainWindow::on_reset_clicked() {
  QString str = ui->filepath->text();
  std::string v_str = str.toStdString();
  const char *strch = v_str.c_str();
  auto s = const_cast<char *>(strch);

  exit_st *st = (exit_st *)calloc(1, sizeof(exit_st));
  s21_parse(st, s);
  setting_to_center(st);
  double scale = normalize(st);
  set_scale(st, scale);
  ui->widget->res = st;
  ui->scale_slider->setValue(50);
  ui->scale_line_edit->setText(QString::number(50));
  previous_scale = 50;
  previous_value_rotate_x = 0;
  previous_value_rotate_y = 0;
  previous_value_rotate_z = 0;
  previous_value_slider_x = 0;
  previous_value_slider_y = 0;
  previous_value_slider_z = 0;
  ui->x_move_slider->setValue(0);
  ui->y_move_slider->setValue(0);
  ui->z_move_slider->setValue(0);
  ui->x_rotate_slider->setValue(0);
  ui->y_rotate_slider->setValue(0);
  ui->z_rotate_slider->setValue(0);
  ui->x_move->setText(QString::number(0));
  ui->y_move->setText(QString::number(0));
  ui->z_move->setText(QString::number(0));
  ui->x_rotate->setText(QString::number(0));
  ui->y_rotate->setText(QString::number(0));
  ui->z_rotate->setText(QString::number(0));
  ui->widget->update();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value) {
  ui->widget->scale = 1;
  ui->widget->thickness = value;
  ui->widget->update();
}

void MainWindow::on_x_move_slider_valueChanged(int value) {
  s21_move(ui->widget->res, (value - previous_value_slider_x) * 0.01, 'x');
  ui->x_move->setText(QString::number(value));
  previous_value_slider_x = value;
  ui->widget->update();
}

void MainWindow::on_y_move_slider_valueChanged(int value) {
  s21_move(ui->widget->res, (value - previous_value_slider_y) * 0.01, 'y');
  ui->y_move->setText(QString::number(value));
  previous_value_slider_y = value;
  ui->widget->update();
}

void MainWindow::on_z_move_slider_valueChanged(int value) {
  s21_move(ui->widget->res, (value - previous_value_slider_z) * 0.01, 'z');
  ui->z_move->setText(QString::number(value));
  previous_value_slider_z = value;
  ui->widget->update();
}

void MainWindow::on_x_rotate_slider_valueChanged(int value) {
  double radian = (value - previous_value_rotate_x) * (M_PI / 45.0);
  rotation_x(radian, ui->widget->res);
  ui->x_rotate->setText(QString::number(value));
  previous_value_rotate_x = value;
  ui->widget->update();
}

void MainWindow::on_y_rotate_slider_valueChanged(int value) {
  double radian = (value - previous_value_rotate_y) * (M_PI / 45.0);
  rotation_y(radian, ui->widget->res);
  ui->y_rotate->setText(QString::number(value));
  previous_value_rotate_y = value;
  ui->widget->update();
}

void MainWindow::on_z_rotate_slider_valueChanged(int value) {
  double radian = (value - previous_value_rotate_z) * (M_PI / 45.0);
  rotation_z(radian, ui->widget->res);
  ui->z_rotate->setText(QString::number(value));
  previous_value_rotate_z = value;
  ui->widget->update();
}

void MainWindow::on_Choice_points_activated(int index) {
  double buf_scale = ui->widget->scale;
  ui->widget->scale = 1;
  ui->widget->form_points = index;
  ui->widget->update();
  ui->widget->scale = buf_scale;
}

void MainWindow::on_pushButton_4_clicked() {
  if (!ui->filepath->text().isEmpty()) {
    int option = ui->comboBox_2->currentIndex();
    frame = new QImage;
    if (option == 2) {
      gif = new QGifImage;
      timer = new QTimer(this);
      time = 0;
      connect(timer, SIGNAL(timeout()), this, SLOT(saveGifFrame()));
      ui->pushButton_4->setDisabled(true);
      timer->start(10);
    } else if (option == 1) {
      *frame = ui->widget->grabFramebuffer();
      QString img =
          QFileDialog::getSaveFileName(this, NULL, NULL, "BPM (*.bmp)");
      frame->save(img);
    } else if (option == 0) {
      *frame = ui->widget->grab().toImage();
      QString img =
          QFileDialog::getSaveFileName(this, NULL, NULL, "JPEG (*.jpeg)");
      frame->save(img);
    }
  }
}

void MainWindow::saveGifFrame() {
  time++;
  *frame = ui->widget->grab().toImage();
  rotation_y(M_PI / 25.0, ui->widget->res);
  ui->widget->update();
  gif->addFrame(*frame, 100);
  if (time >= 50) {
    timer->stop();
    gifSavePath = QFileDialog::getSaveFileName(this, NULL, NULL, "GIF (*.gif)");
    if (!gifSavePath.isNull()) {
      gif->save(gifSavePath);
      ui->pushButton_4->setEnabled(true);
    };
  }
}

void MainWindow::load_setting() {
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.beginGroup("Settings");

  ui->widget->save_set = settings.value("save_save_set").toFloat();
  if (ui->widget->save_set == 1) {
    ui->widget->background_color.setRedF(
        settings.value("save_Color_redF").toFloat());
    ui->widget->background_color.setGreenF(
        settings.value("save_Color_greenF").toFloat());
    ui->widget->background_color.setBlueF(
        settings.value("save_Color_blueF").toFloat());

    ui->widget->points_color.setRedF(
        settings.value("save_Color_point_redF").toFloat());
    ui->widget->points_color.setGreenF(
        settings.value("save_Color_point_greenF").toFloat());
    ui->widget->points_color.setBlueF(
        settings.value("save_Color_point_blueF").toFloat());

    ui->widget->line_color.setRedF(
        settings.value("save_Color_line_redF").toFloat());
    ui->widget->line_color.setGreenF(
        settings.value("save_Color_line_greenF").toFloat());
    ui->widget->line_color.setBlueF(
        settings.value("save_Color_line_blueF").toFloat());

    ui->widget->striple = settings.value("save_line_style").toInt();
    ui->comboBox_3->setCurrentIndex(ui->widget->striple);

    ui->widget->form_points = settings.value("save_points_style").toInt();
    ui->Choice_points->setCurrentIndex(ui->widget->form_points);

    ui->widget->thickness = settings.value("save_line_thickness").toDouble();
    ui->horizontalSlider_2->setValue(
        (int)(settings.value("save_line_thickness").toDouble()));

    ui->widget->point_thickness =
        settings.value("save_point_thickness").toDouble();
    ui->horizontalSlider->setValue(
        (int)(settings.value("save_point_thickness").toDouble()));

    if ((int)settings.value("save_proection").toDouble()) {
      ui->central_pro->setChecked(1);
      ui->widget->proection = 1;
    } else {
      ui->widget->proection = 0;
    }

    settings.endGroup();
  }
}

void MainWindow::on_Save_set_clicked() {
  ui->widget->save_set = 1;

  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.beginGroup("Settings");

  settings.setValue("save_save_set", ui->widget->save_set);

  settings.setValue("save_Color_redF", ui->widget->background_color.redF());
  settings.setValue("save_Color_greenF", ui->widget->background_color.greenF());
  settings.setValue("save_Color_blueF", ui->widget->background_color.blueF());

  settings.setValue("save_Color_point_redF", ui->widget->points_color.redF());
  settings.setValue("save_Color_point_greenF",
                    ui->widget->points_color.greenF());
  settings.setValue("save_Color_point_blueF", ui->widget->points_color.blueF());

  settings.setValue("save_Color_line_redF", ui->widget->line_color.redF());
  settings.setValue("save_Color_line_greenF", ui->widget->line_color.greenF());
  settings.setValue("save_Color_line_blueF", ui->widget->line_color.blueF());

  settings.setValue("save_line_style", ui->widget->striple);

  settings.setValue("save_points_style", ui->widget->form_points);

  settings.setValue("save_line_thickness", ui->widget->thickness);
  printf("save line_thickness = %lf", ui->widget->thickness);

  settings.setValue("save_point_thickness", ui->widget->point_thickness);

  settings.setValue("save_proection", ui->widget->proection);

  settings.endGroup();
}

void MainWindow::on_load_set_but_clicked() {
  load_setting();
  ui->widget->update();
}
