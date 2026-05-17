#include "encoder.h"
#include "decoder.h"
#include <gtest/gtest.h>
#include <QTemporaryDir>
#include <QFile>

class DecoderUnitTest : public ::testing::Test {
protected:
    void SetUp() override {
        tempDir = std::make_unique<QTemporaryDir>();
        ASSERT_TRUE(tempDir->isValid());
        testDir = tempDir->path();
    }

    QByteArray encryptHelper(const QString& input, const QString& output) {
        Encoder enc;
        enc.encryptFile(input, output);
        return enc.getKey();
    }

    QString testDir;
    std::unique_ptr<QTemporaryDir> tempDir;
};

TEST_F(DecoderUnitTest, DecryptValidFile) {
    QString original = testDir + "/orig.txt";
    QFile f(original);
    ASSERT_TRUE(f.open(QIODevice::WriteOnly));
    f.write("Hello");
    f.close();

    QString encrypted = testDir + "/enc.dat";
    QByteArray key = encryptHelper(original, encrypted);

    QString decrypted = testDir + "/dec.txt";
    Decoder dec;
    dec.setKey(key);
    EXPECT_TRUE(dec.decryptFile(encrypted, decrypted));

    QFile out(decrypted);
    ASSERT_TRUE(out.open(QIODevice::ReadOnly));
    EXPECT_EQ(out.readAll(), "Hello");
}

TEST_F(DecoderUnitTest, WrongKey) {
    QString original = testDir + "/orig.txt";
    QFile f(original);
    ASSERT_TRUE(f.open(QIODevice::WriteOnly));
    f.write("Secret");
    f.close();

    QString encrypted = testDir + "/enc.dat";
    QByteArray key = encryptHelper(original, encrypted);
    key[0] ^= 0xFF; // портим ключ

    Decoder dec;
    dec.setKey(key);
    EXPECT_FALSE(dec.decryptFile(encrypted, testDir + "/out.txt"));
}

TEST_F(DecoderUnitTest, CorruptedEncryptedFile) {
    QString original = testDir + "/orig.txt";
    QFile f(original);
    ASSERT_TRUE(f.open(QIODevice::WriteOnly));
    f.write("Data");
    f.close();

    QString encrypted = testDir + "/enc.dat";
    QByteArray key = encryptHelper(original, encrypted);

    QFile enc(encrypted);
    ASSERT_TRUE(enc.open(QIODevice::ReadWrite));
    enc.seek(20);
    char c;
    enc.read(&c, 1);
    enc.seek(20);
    c = ~c;
    enc.write(&c, 1);
    enc.close();

    Decoder dec;
    dec.setKey(key);
    EXPECT_FALSE(dec.decryptFile(encrypted, testDir + "/bad.txt"));
}

TEST_F(DecoderUnitTest, FileTooSmall) {
    QFile small(testDir + "/tiny.bin");
    ASSERT_TRUE(small.open(QIODevice::WriteOnly));
    small.write("123");
    small.close();

    Decoder dec;
    dec.setKey(QByteArray(32, 0));
    EXPECT_FALSE(dec.decryptFile(small.fileName(), testDir + "/out.txt"));
}

TEST_F(DecoderUnitTest, NonexistentInputFile) {
    Decoder dec;
    dec.setKey(QByteArray(32, 0));
    EXPECT_FALSE(dec.decryptFile(testDir + "/no_such.enc", testDir + "/out.txt"));
}

TEST_F(DecoderUnitTest, InvalidOutputPath) {
    QString original = testDir + "/orig.txt";
    QFile f(original);
    ASSERT_TRUE(f.open(QIODevice::WriteOnly));
    f.write("x");
    f.close();

    QString encrypted = testDir + "/enc.dat";
    QByteArray key = encryptHelper(original, encrypted);

    Decoder dec;
    dec.setKey(key);
    EXPECT_FALSE(dec.decryptFile(encrypted, ""));
}
