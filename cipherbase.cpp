#include "cipherbase.h"

#include <QDebug>

CipherBase::CipherBase(QByteArray key, QByteArray iv) : key(key), iv(iv)
{
    ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
    {
        handleError("Ошибка при определении контекста шифра!");
        return;
    }
}

CipherBase::~CipherBase()
{
    EVP_CIPHER_CTX_free(ctx);
}

void CipherBase::handleError(QString message)
{
    qCritical() << message << '\n';
    // emit errorMessage(message);
}
