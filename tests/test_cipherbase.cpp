#include <gtest/gtest.h>
#include "cipherbase.h"

class CipherBaseTest : public ::testing::Test {
protected:
    CipherBase cipher;
};

// Тест 1: установка и получение ключа
TEST_F(CipherBaseTest, SetAndGetKey) {
    QByteArray key = QByteArray::fromHex("00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff");
    cipher.setKey(key);
    EXPECT_EQ(cipher.getKey(), key);
}

// Тест 2: пустой ключ по умолчанию
TEST_F(CipherBaseTest, DefaultKeyIsEmpty) {
    EXPECT_TRUE(cipher.getKey().isEmpty());
}

// Тест 3: перезапись ключа
TEST_F(CipherBaseTest, OverwriteKey) {
    QByteArray key1(32, '\x01');
    QByteArray key2(32, '\x02');
    cipher.setKey(key1);
    cipher.setKey(key2);
    EXPECT_EQ(cipher.getKey(), key2);
}
