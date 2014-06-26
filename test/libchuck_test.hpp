#include <string.h>
#include <gtest/gtest.h>
#include <chuck.h>
#include <chuck_def.h>

using chuck::Chuck;

class ChuckTest : public testing::Test {
protected:
    Chuck * chuck;

    void SetUp() {
        ASSERT_TRUE(chuck::Create(&chuck));
    }

    void Spork(unsigned int files, const char ** filenames) {
        ASSERT_TRUE(chuck->Spork(files, filenames));
    }

    bool Run() {
        chuck->RunVM();
        return chuck->Wait();
    }

    void TearDown() {
        chuck->Destroy();
    }
};

class TestIntReceiver : public chuck::IntReceiver {
public:
    TestIntReceiver() {
        receivedVal = false;
    }

    void receive(t_CKINT val) {
        receivedVal = true;
        intval = val;
    }

    void assertReceived(t_CKINT val) {
        ASSERT_TRUE(receivedVal);
        ASSERT_EQ(intval, val);
    }

private:
    bool receivedVal;
    t_CKINT intval;
};

class TestFloatReceiver : public chuck::FloatReceiver {
public:
    TestFloatReceiver() {
        receivedVal = false;
    }

    void receive(t_CKFLOAT val) {
        receivedVal = true;
        floatval = val;
    }

    void assertReceived(t_CKFLOAT val) {
        ASSERT_TRUE(receivedVal);
        ASSERT_EQ(floatval, val);
    }

private:
    bool receivedVal;
    t_CKFLOAT floatval;
};

class TestStringReceiver : public chuck::StringReceiver {
public:
    TestStringReceiver() {
        receivedVal = false;
    }

    void receive(const char * s) {
        receivedVal = true;
        strncpy(strval, s, STRING_LEN);
    }

    void assertReceived(const char * s) {
        ASSERT_TRUE(receivedVal);
        ASSERT_EQ(0, strncmp(strval, s, STRING_LEN));
    }

private:
    static const unsigned int STRING_LEN = 1024;

    bool receivedVal;
    char strval[STRING_LEN];
};
