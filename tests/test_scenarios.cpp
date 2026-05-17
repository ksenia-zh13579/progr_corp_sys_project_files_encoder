#include "encoder.h"
#include "decoder.h"
#include <gtest/gtest.h>
#include <QTemporaryDir>
#include <QFile>

class ScenarioTest : public ::testing::Test {
protected:
    void SetUp() override {
        tempDir = std::make_unique<QTemporaryDir>();
        ASSERT_TRUE(tempDir->isValid());
        testDir = tempDir->path();
    }

    QString testDir;
    std::unique_ptr<QTemporaryDir> tempDir;
};

TEST_F(ScenarioTest, EncryptThenDecryptWithSameKey) {
    QString originalFile = testDir + "/data.txt";
    QByteArray originalData = "Hello, world! Это тестовые данные 123.";
    QFile f(originalFile);
    ASSERT_TRUE(f.open(QIODevice::WriteOnly));
    f.write(originalData);
    f.close();

    QString encryptedFile = testDir + "/data.enc";
    Encoder encoder;
    ASSERT_TRUE(encoder.encryptFile(originalFile, encryptedFile));

    QByteArray key = encoder.getKey();

    QString decryptedFile = testDir + "/data.dec";
    Decoder decoder;
    decoder.setKey(key);
    ASSERT_TRUE(decoder.decryptFile(encryptedFile, decryptedFile));

    QFile out(decryptedFile);
    ASSERT_TRUE(out.open(QIODevice::ReadOnly));
    QByteArray decryptedData = out.readAll();
    out.close();

    EXPECT_EQ(originalData, decryptedData);
}

TEST_F(ScenarioTest, WrongKeyFails) {
    QString original = testDir + "/original.txt";
    QByteArray content = "Secret data";
    QFile f(original);
    f.open(QIODevice::WriteOnly);
    f.write(content);
    f.close();

    QString encrypted = testDir + "/encrypted.dat";
    Encoder encoder;
    encoder.encryptFile(original, encrypted);

    QByteArray wrongKey(32, '\x55');
    Decoder decoder;
    decoder.setKey(wrongKey);

    QString decrypted = testDir + "/decrypted.txt";
    EXPECT_FALSE(decoder.decryptFile(encrypted, decrypted));
}

TEST_F(ScenarioTest, CorruptedEncryptedFile) {
    QString original = testDir + "/original.txt";
    QFile f(original);
    f.open(QIODevice::WriteOnly);
    f.write("Important data");
    f.close();

    QString encrypted = testDir + "/encrypted.dat";
    Encoder encoder;
    encoder.encryptFile(original, encrypted);

    QFile encFile(encrypted);
    encFile.open(QIODevice::ReadWrite);
    encFile.seek(20);
    char c;
    encFile.read(&c, 1);
    encFile.seek(20);
    c = ~c;
    encFile.write(&c, 1);
    encFile.close();

    Decoder decoder;
    decoder.setKey(encoder.getKey());
    EXPECT_FALSE(decoder.decryptFile(encrypted, testDir + "/bad.txt"));
}
