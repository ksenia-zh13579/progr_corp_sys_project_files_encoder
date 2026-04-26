#ifndef CIPHERBASE_H
#define CIPHERBASE_H

#include <QObject>
#include <QByteArray>
#include <QString>

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

class CipherBase
{
    Q_OBJECT
protected:
    QByteArray iv, key;
    EVP_CIPHER_CTX* ctx;

    static void handleError(QString message);
public:
    // CipherBase();
    CipherBase(QByteArray key = NULL, QByteArray iv = NULL);
    ~CipherBase();

    static const int KEY_SIZE = 32;
    static const int IV_SIZE = 12;
    static const int TAG_SIZE = 16;
    static const int BUFFER_SIZE = 1024 * 1024;
signals:
    void errorMessage(QString message);
};

#endif // CIPHERBASE_H
