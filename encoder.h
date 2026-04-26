#ifndef ENCODER_H
#define ENCODER_H

#include "cipherbase.h"

#include <QString>
#include <QByteArray>

class Encoder : public CipherBase
{
    Q_OBJECT
protected:
    static bool generateKey(QByteArray& key);
    static bool generateIV(QByteArray& iv);
public:
    Encoder();
    bool encryptFile(const QString& inputPath, const QString& outputFile);
};

#endif // ENCODER_H
