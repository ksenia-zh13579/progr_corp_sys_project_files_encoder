#include "encoder.h"
#include <gtest/gtest.h>
#include <QTemporaryDir>
#include <QFile>
#include <QDir>

class EncoderUnitTest : public ::testing::Test {
protected:
    void SetUp() override {
        tempDir = std::make_unique<QTemporaryDir>();
        ASSERT_TRUE(tempDir->isValid());
        testDir = tempDir->path();
    }

    QString testDir;
    std::unique_ptr<QTemporaryDir> tempDir;
};

TEST_F(EncoderUnitTest, EncryptSmallFile) {
    QString input = testDir + "/in.txt";
    QFile f(input);
    ASSERT_TRUE(f.open(QIODevice::WriteOnly));
    f.write("Test data");
    f.close();

    QString output = testDir + "/out.enc";
    Encoder enc;
    EXPECT_TRUE(enc.encryptFile(input, output));
    QFile out(output);
    EXPECT_TRUE(out.exists());
    EXPECT_GT(out.size(), 12 + 16);
}

TEST_F(EncoderUnitTest, EncryptEmptyFile) {
    QString input = testDir + "/empty.txt";
    QFile f(input);
    ASSERT_TRUE(f.open(QIODevice::WriteOnly));
    f.close();

    QString output = testDir + "/empty.enc";
    Encoder enc;
    EXPECT_TRUE(enc.encryptFile(input, output));
    QFile out(output);
    EXPECT_EQ(out.size(), 12 + 16);
}

TEST_F(EncoderUnitTest, EncryptNonexistentInput) {
    Encoder enc;
    EXPECT_FALSE(enc.encryptFile(testDir + "/no_such.txt", testDir + "/out.enc"));
}

TEST_F(EncoderUnitTest, InvalidOutputPath) {
    QString input = testDir + "/in.txt";
    QFile f(input);
    ASSERT_TRUE(f.open(QIODevice::WriteOnly));
    f.write("x");
    f.close();

    Encoder enc;
    EXPECT_FALSE(enc.encryptFile(input, ""));
}

TEST_F(EncoderUnitTest, EncryptLargeFile) {
    QString input = testDir + "/large.bin";
    QFile f(input);
    ASSERT_TRUE(f.open(QIODevice::WriteOnly));
    const int size = 10 * 1024 * 1024; // 10 МБ
    QByteArray data(size, '\xAB');
    f.write(data);
    f.close();

    QString output = testDir + "/large.enc";
    Encoder enc;
    EXPECT_TRUE(enc.encryptFile(input, output));
    QFile out(output);
    EXPECT_TRUE(out.exists());
    EXPECT_EQ(out.size(), static_cast<qint64>(size + 12 + 16));
}

TEST_F(EncoderUnitTest, ReuseEncoderForMultipleFiles) {
    QString input1 = testDir + "/file1.txt";
    QString input2 = testDir + "/file2.txt";
    QFile f1(input1); ASSERT_TRUE(f1.open(QIODevice::WriteOnly)); f1.write("First"); f1.close();
    QFile f2(input2); ASSERT_TRUE(f2.open(QIODevice::WriteOnly)); f2.write("Second"); f2.close();

    Encoder enc;
    EXPECT_TRUE(enc.encryptFile(input1, testDir + "/out1.enc"));
    EXPECT_TRUE(enc.encryptFile(input2, testDir + "/out2.enc"));
}
