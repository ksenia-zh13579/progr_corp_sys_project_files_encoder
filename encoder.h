#ifndef ENCODER_H
#define ENCODER_H

#include "cipherbase.h"

#include <QString>
#include <QByteArray>

class Encoder : public CipherBase
{
    Q_OBJECT
protected:
    static QByteArray generateRandSec(int secSize);
public:
    Encoder();
    bool encryptFile(const QString& inputPath, const QString& outputPath);
};

#endif // ENCODER_H
