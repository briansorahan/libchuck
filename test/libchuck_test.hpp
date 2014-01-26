#include <gtest/gtest.h>
#include <chuck.h>
#include <chuck_def.h>

using chuck::Chuck;

class ChuckTest : public testing::Test {
protected:
    Chuck * chuck;

    void SetUp() {
        bool created = chuck::Create(&chuck);
        ASSERT_TRUE(created);
    }

    void Spork(unsigned int files, const char ** filenames) {
        bool sporked = chuck->Spork(files, filenames);
        ASSERT_TRUE(sporked);
    }

    bool Run() {
        return chuck->Run();
    }

    void TearDown() {
    }
};
