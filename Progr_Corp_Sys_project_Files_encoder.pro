QT += core gui widgets

# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD/include
INCLUDEPATH += "C:/msys64/ucrt64/include"

CONFIG += c++17
CONFIG -= entrypoint

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/cipherbase.cpp \
    src/decodedialog.cpp \
    src/decoder.cpp \
    src/encodedialog.cpp \
    src/encoder.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    include/cipherbase.h \
    include/decodedialog.h \
    include/decoder.h \
    include/encodedialog.h \
    include/encoder.h \
    include/mainwindow.h

FORMS += \
    ui/decodedialog.ui \
    ui/encodedialog.ui \
    ui/mainwindow.ui

# LIBS += -lws2_32 -lssl -lcrypto -lgcc
# LIBS += -L"C:/Program Files/OpenSSL-Win64/lib" -lssl -lcrypto
# LIBS += -luser32 -lgdi32 -ladvapi32 -lcrypt32
# LIBS += -lmingw32
LIBS += "C:/msys64/ucrt64/lib/libssl.dll.a" \
        "C:/msys64/ucrt64/lib/libcrypto.dll.a" \
        -lcrypt32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    .gitignore

