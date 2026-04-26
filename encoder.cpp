#include "encoder.h"

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

#include <QFile>
#include <QVector>

Encoder::Encoder(): CipherBase()
{
    generateKey(key);
    generateIV(iv);
}

bool Encoder::generateKey(QByteArray& key)
{
    key.resize(KEY_SIZE);
    if (RAND_bytes(reinterpret_cast<unsigned char*>(key.data()), key.size()) != 1)
    {
        handleError("Ошибка при генерации ключа!");
        return false;
    }
    return true;
}

bool Encoder::generateIV(QByteArray& iv)
{
    iv.resize(IV_SIZE);
    if (RAND_bytes(reinterpret_cast<unsigned char*>(iv.data()), iv.size()) != 1)
    {
        handleError("Ошибка при генерации идентификатора!");
        return false;
    }
    return true;
}

bool Encoder::encryptFile(const QString& inputPath, const QString& outputPath)
{
    QFile inFile(inputPath);
    QFile outFile(outputPath);

    if (!inFile.open(QIODevice::ReadOnly))
    {
        handleError("Ошибка при открытии шифруемого файла!");
        return false;
    }

    if (!outFile.open(QIODevice::WriteOnly))
    {
        handleError("Ошибка при открытии файла для записи результата!");
        return false;
    }

    outFile.write(iv.data(), iv.size());

    const unsigned char* keyData = reinterpret_cast<const unsigned char*>(key.constData());
    const unsigned char* ivData = reinterpret_cast<const unsigned char*>(iv.constData());

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, keyData, ivData) != 1)
    {
        handleError("Ошибка при инициализации шифра!");
        return false;
    }

    QByteArray inBuffer(BUFFER_SIZE, '\0');
    QByteArray outBuffer(BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH, '\0');
    int outLen = 0;

    while(!inFile.atEnd())
    {
        inBuffer = inFile.read(BUFFER_SIZE);

        if (EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(outBuffer.data()), &outLen,
                              reinterpret_cast<unsigned char*>(inBuffer.data()), BUFFER_SIZE) != 1)
        {
            handleError("Ошибка во время шифрования данных");
            return false;
        }

        outFile.write(outBuffer.constData(), outLen);
    }

    if (EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(outBuffer.data()), &outLen) != 1)
    {
        handleError("Ошибка во время финализации шифрования");
        return false;
    }

    outFile.write(outBuffer.constData(), outLen);

    QByteArray tag(16, '\0');

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, tag.size(),
                            tag.data()) != 1)
    {
        handleError("Ошибка во время получения тега шифрования");
        return false;
    }

    outFile.write(tag.constData(), tag.size());

    return true;
}


