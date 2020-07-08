#-------------------------------------------------
#
# Project created by QtCreator 2019-07-06T16:46:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sts
TEMPLATE = app
RC_FILE+=version.rc
RC_ICONS = icon.ico
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

SOURCES += \
        about.cpp \
        course_manage.cpp \
        course_select.cpp \
        main.cpp \
        mainwindow.cpp \
        score_input.cpp \
        score_search.cpp \
        staff.cpp \
        staff_check.cpp \
        staff_manage.cpp \
        student.cpp \
        student_inquiry.cpp \
        student_judge.cpp \
        student_manage.cpp \
        system.cpp \
        system_display.cpp

HEADERS += \
        about.h \
        course_manage.h \
        course_select.h \
        mainwindow.h \
        score_input.h \
        score_search.h \
        staff.h \
        staff_check.h \
        staff_manage.h \
        student.h \
        student_inquiry.h \
        student_judge.h \
        student_manage.h \
        system.h \
        system_display.h

FORMS += \
        about.ui \
        course_manage.ui \
        course_select.ui \
        mainwindow.ui \
        score_input.ui \
        score_search.ui \
        staff.ui \
        staff_check.ui \
        staff_manage.ui \
        student.ui \
        student_inquiry.ui \
        student_judge.ui \
        student_manage.ui \
        system.ui \
        system_display.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
