#include <gtest/gtest.h>
#include <chuck.h>
#include <chuck_def.h>

using chuck::Chuck;

class ChuckTest : public testing::Test {
protected:
    Chuck * ck;

    void Spork(unsigned int files, const char ** filenames) {
        bool sporked = chuck::Spork(files, filenames);
        ASSERT_TRUE(sporked);
    }

    void TearDown() {
        bool finished = chuck::Yield();
        ASSERT_TRUE(finished);
    }
};
