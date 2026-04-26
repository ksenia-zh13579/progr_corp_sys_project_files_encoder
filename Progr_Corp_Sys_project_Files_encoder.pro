QT       += core gui

INCLUDEPATH += C:/msys64/ucrt64/include
LIBS += -L C:/msys64/ucrt64/lib -lssl -lcrypto

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cipherbase.cpp \
    decodedialog.cpp \
    decoder.cpp \
    encodedialog.cpp \
    encodedialog.cpp \
    encoder.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    cipherbase.h \
    decodedialog.h \
    decoder.h \
    encodedialog.h \
    encodedialog.h \
    encoder.h \
    mainwindow.h

FORMS += \
    decodedialog.ui \
    encodedialog.ui \
    encodedialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
