QT       += core gui opengl openglwidgets
include(QtGifImage/gifimage/qtgifimage.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    View/main.cpp \
    View/mainwindow.cpp \
    View/myopengl.cpp \
    Model/model.cc \
    Controller/controller.cc

HEADERS += \
    View/mainwindow.h \
    View/myopengl.h \
    Controller/controller.h \
    Model/model.h

FORMS += \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

