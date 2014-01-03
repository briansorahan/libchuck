#include <gtest/gtest.h>
#include <chuck.h>
#include <chuck_def.h>

using chuck::Chuck;

TEST(Chuck, Instantiation) {
    Chuck * ck;
    t_CKBOOL created = chuck::Create(&ck, 8500);
    ASSERT_TRUE(created);
}
