#include "decoder.h"

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

Decoder::Decoder(QByteArray key, QByteArray iv): CipherBase(key, iv) {}

bool Decoder::decryptFile(const QString& inputPath, const QString& outputFile)
{

}
