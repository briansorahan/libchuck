#include <gtest/gtest.h>
#include <chuck.h>
#include <chuck_def.h>

class ChuckTest : public testing::Test {
protected:

    // Set this to true if you wish to call chuck::Yield yourself.
    bool skipYield;

    void Spork(unsigned int files, const char ** filenames) {
        skipYield = false;
        bool sporked = chuck::Spork(files, filenames);
        ASSERT_TRUE(sporked);
    }

    void TearDown() {
    }
};
