#include "encoder.h"

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

#include <QFile>
#include <QDebug>

Encoder::Encoder(): CipherBase()
{
    key = generateRandSec(KEY_SIZE);
}

QByteArray Encoder::generateRandSec(int secSize)
{
    QByteArray randSec(secSize, '\0');
    RAND_bytes(reinterpret_cast<unsigned char*>(randSec.data()), randSec.size());
    return randSec;
}

QByteArray Encoder::getKey()
{
    return key;
}

bool Encoder::encryptFile(const QString& inputPath, const QString& outputPath)
{
    emit startWorking();

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

    QByteArray iv(IV_SIZE, '\0');
    iv = generateRandSec(IV_SIZE);

    outFile.write(iv.data(), iv.size());

    const unsigned char* keyData = reinterpret_cast<const unsigned char*>(key.constData());
    const unsigned char* ivData = reinterpret_cast<const unsigned char*>(iv.constData());

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, keyData, ivData) != 1)
    {
        handleError("Ошибка при инициализации шифра!");
        return false;
    }

    QByteArray inBuffer;
    QByteArray outBuffer(BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH, '\0');

    int bytesRead = 0;
    int outLen = 0;

    while(!inFile.atEnd())
    {
        int toRead = qMin(BUFFER_SIZE, inFile.size() - bytesRead);
        inBuffer = inFile.read(toRead);

        if (EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(outBuffer.data()), &outLen,
                              reinterpret_cast<const unsigned char*>(inBuffer.constData()), inBuffer.size()) != 1)
        {
            handleError("Ошибка во время шифрования данных");
            return false;
        }

        outFile.write(outBuffer.constData(), outLen);
        bytesRead += inBuffer.size();
    }

    if (EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(outBuffer.data()), &outLen) != 1)
    {
        handleError("Ошибка во время финализации шифрования");
        return false;
    }

    outFile.write(outBuffer.constData(), outLen);

    QByteArray tag(TAG_SIZE, '\0');

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, tag.size(),
                            tag.data()) != 1)
    {
        handleError("Ошибка во время получения тега шифрования");
        return false;
    }

    outFile.write(tag.constData(), tag.size());

    qDebug() << "Файл успешно расшифрован!";
    emit finishWorking();

    return true;
}


