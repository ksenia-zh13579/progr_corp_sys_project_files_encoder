#include "cipherbase.h"

#include <QDebug>

const int CipherBase::KEY_SIZE = 32;
const int CipherBase::IV_SIZE = 12;
const int CipherBase::TAG_SIZE = 16;
const int CipherBase::BUFFER_SIZE = 1024 * 1024;

CipherBase::CipherBase(const QByteArray& key) : key(key)
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
    emit errorMessage(message);
}
