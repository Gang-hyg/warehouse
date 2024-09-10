QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    class.cpp \
    course.cpp \
    enroll.cpp \
    grade.cpp \
    initialize.cpp \
    main.cpp \
    password.cpp \
    revise.cpp \
    selection.cpp \
    student.cpp \
    teaacher.cpp \
    widget.cpp

HEADERS += \
    class.h \
    course.h \
    enroll.h \
    grade.h \
    initialize.h \
    password.h \
    revise.h \
    selection.h \
    student.h \
    teaacher.h \
    widget.h

FORMS += \
    class.ui \
    course.ui \
    enroll.ui \
    grade.ui \
    initialize.ui \
    password.ui \
    revise.ui \
    selection.ui \
    student.ui \
    teaacher.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
