#include "decoder.h"

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <QFile>
#include <QDebug>

Decoder::Decoder(QByteArray key): CipherBase(key) {}

bool Decoder::decryptFile(const QString& inputPath, const QString& outputPath)
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

    QByteArray iv = inFile.read(IV_SIZE);

    if (iv.size() != IV_SIZE)
    {
        handleError("Ошибка присчитывании идентификатора из файла");
        return false;
    }

    const unsigned char* keyData = reinterpret_cast<const unsigned char*>(key.constData());
    const unsigned char* ivData = reinterpret_cast<const unsigned char*>(iv.constData());

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr,
                           keyData, ivData) != 1)
    {
        handleError("Ошибка при инициализации дешифратора!");
        return false;
    }

    int encryptedSize = inFile.size() - IV_SIZE - TAG_SIZE;

    if (encryptedSize < 0)
    {
        handleError("Ошибка: неверный размер файла!");
        return false;
    }

    QByteArray inBuffer;
    QByteArray outBuffer;
    outBuffer.resize(BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH);

    int bytesRead = 0;
    int outLen = 0;

    while (bytesRead < encryptedSize) {
        int toRead = qMin(BUFFER_SIZE, encryptedSize - bytesRead);
        inBuffer = inFile.read(toRead);

        if (inBuffer.isEmpty()) break;

        if (EVP_DecryptUpdate(ctx,
                              reinterpret_cast<unsigned char*>(outBuffer.data()),
                              &outLen,
                              reinterpret_cast<const unsigned char*>(inBuffer.constData()),
                              inBuffer.size()) != 1) {
            handleError("Ошибка при расшифровании данных");
            return false;
        }

        outFile.write(outBuffer.constData(), outLen);
        bytesRead += inBuffer.size();
    }

    QByteArray tag = inFile.read(TAG_SIZE);
    if (tag.size() != TAG_SIZE)
    {
        handleError("Ошибка при чтении тега аутентификации");
        return false;
    }

    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, tag.size(),
                            reinterpret_cast<unsigned char*>(tag.data())) != 1)
    {
        handleError("Ошибка при установке тега аутентификации");
        return false;
    }

    if (EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(outBuffer.data()),
                            &outLen) != 1)
    {
        handleError("Ошибка аутентификации! Файл был изменен или ключ неверен");
        return false;
    }

    if (outLen > 0) {
        outFile.write(outBuffer.constData(), outLen);
    }

    qDebug() << "Файл успешно расшифровани!";
    return true;
}
