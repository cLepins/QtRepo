QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    doctorview.cpp \
    idatabase.cpp \
    loginview.cpp \
    main.cpp \
    masterview.cpp \
    medicineview.cpp \
    patienteditview.cpp \
    patientview.cpp \
    recordview.cpp \
    welcomeview.cpp

HEADERS += \
    doctorview.h \
    idatabase.h \
    loginview.h \
    masterview.h \
    medicineview.h \
    patienteditview.h \
    patientview.h \
    recordview.h \
    welcomeview.h

FORMS += \
    doctorview.ui \
    loginview.ui \
    masterview.ui \
    medicineview.ui \
    patienteditview.ui \
    patientview.ui \
    recordview.ui \
    welcomeview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    lab4.qrc

DISTFILES += \
    img/修改.png \
    img/删除.png \
    img/查找.png \
    img/添加.png