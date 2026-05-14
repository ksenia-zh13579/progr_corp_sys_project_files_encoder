#ifndef CIPHERBASE_H
#define CIPHERBASE_H

#include <QObject>
#include <QByteArray>
#include <QString>

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

class CipherBase: public QObject
{
    Q_OBJECT
protected:
    QByteArray key;
    EVP_CIPHER_CTX* ctx;

    void handleError(QString message);
public:
    // CipherBase();
    CipherBase(const QByteArray& key = QByteArray());
    ~CipherBase();

    static const int KEY_SIZE;
    static const int IV_SIZE;
    static const int TAG_SIZE;
    static const int BUFFER_SIZE;
signals:
    void errorMessage(QString message);
    void startWorking(QString message);
    void finishWorking(QString message);
};

#endif // CIPHERBASE_H
