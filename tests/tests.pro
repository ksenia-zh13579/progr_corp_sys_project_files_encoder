include(gtest_dependency.pri)

QT += core gui widgets
TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
# CONFIG += thread
# CONFIG -= qt

INCLUDEPATH += "C:/msys64/ucrt64/include"

LIBS += "C:/msys64/ucrt64/lib/libssl.dll.a" \
        "C:/msys64/ucrt64/lib/libcrypto.dll.a" \
        -lcrypt32

INCLUDEPATH += $$PWD/../include

HEADERS += \
    $$PWD/../include/cipherbase.h \
    $$PWD/../include/encoder.h \
    $$PWD/../include/decoder.h

SOURCES += \
    $$PWD/../src/cipherbase.cpp \
    $$PWD/../src/encoder.cpp \
    $$PWD/../src/decoder.cpp

SOURCES += \
        main.cpp \
        test_cipherbase.cpp \
        test_decoder.cpp \
        test_encoder.cpp \
        test_scenarios.cpp

# Копирование библиотек OpenSSL в папку с собранным приложением
win32 {
    CONFIG(debug, debug|release) {
        # Путь к DLL-библиотекам в вашей системе
        OPENSSL_DLL_PATH = "C:/msys64/ucrt64/bin"
        # Целевая папка, куда копируется собранный .exe
        DEST_DIR = $$OUT_PWD/debug

        # Команда для копирования файлов в Windows
        QMAKE_POST_LINK += copy /Y \"$$OPENSSL_DLL_PATH\\libcrypto-3-x64.dll\" \"$$DEST_DIR\" && \
                           copy /Y \"$$OPENSSL_DLL_PATH\\libssl-3-x64.dll\" \"$$DEST_DIR\"
    }
}
