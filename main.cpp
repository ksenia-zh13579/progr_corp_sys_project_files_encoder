#include "mainwindow.h"

#include <QApplication>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
