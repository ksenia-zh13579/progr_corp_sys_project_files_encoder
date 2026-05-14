#ifndef DECODER_H
#define DECODER_H

#include "cipherbase.h"
#include <QByteArray>

class Decoder : public CipherBase
{
    Q_OBJECT
public:
    Decoder(const QByteArray& key);
    bool decryptFile(const QString& inputPath, const QString& outputFile);
};

#endif // DECODER_H
