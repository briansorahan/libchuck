#include <gtest/gtest.h>
#include <chuck.h>
#include <chuck_def.h>

using chuck::Chuck;

class ChuckTest : public testing::Test {
protected:
    Chuck * ck;

    void SetUp() {
        t_CKBOOL created = chuck::Create(&ck, 8500);
        ASSERT_TRUE(created);
    }

    void TearDown() {
        ck->Destroy();
    }
};
