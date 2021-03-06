#-------------------------------------------------
#
# Project created by QtCreator 2021-09-10T21:33:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

#**********************************************
#INCLUDEPATH += /usr/include/python2.7
#LIBS += -lpython2.7
#**********************************************

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dialog_backup.cpp \
    dialog_restore.cpp \
    dialog_password.cpp \
    dialog_packname.cpp \
    dialog_pwfordecrypt.cpp \
    dialog_compare.cpp \
    dialog_compare_result.cpp \
    dialog_success.cpp \
    file_time.cpp \
    huffman.cpp \
    filesystem.cpp \
    Client.cpp \
    pack.cpp \
    lock_safe.cpp \
    dialog_realtime.cpp

HEADERS += \
        mainwindow.h \
    dialog_backup.h \
    dialog_restore.h \
    dialog_password.h \
    dialog_packname.h \
    dialog_pwfordecrypt.h \
    dialog_compare.h \
    dialog_compare_result.h \
    dialog_success.h \
    file_time.h \
    huffman.h \
    filesystem.h \
    Client.h \
    pack.h \
    lock_safe.h \
    FileHead.h \
    dialog_realtime.h

FORMS += \
        mainwindow.ui \
    dialog_backup.ui \
    dialog_restore.ui \
    dialog_password.ui \
    dialog_packname.ui \
    dialog_pwfordecrypt.ui \
    dialog_compare.ui \
    dialog_compare_result.ui \
    dialog_success.ui \
    dialog_realtime.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \


