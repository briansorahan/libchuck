#include <gtest/gtest.h>
// #include "libchuck_test.hpp"
#include <chuck.h>
#include <chuck_def.h>

using chuck::Chuck;

// TEST(ChuckTest, Instantiation) {
//     Chuck * ck;
//     t_CKBOOL created = chuck::Create(&ck, 8500);
//     ASSERT_TRUE(created);
//     ck->Destroy();
// }

TEST(ChuckTest, sporkFile) {
    Chuck * ck;
    t_CKBOOL created = chuck::Create(&ck, 8500);
    ASSERT_TRUE(created);
    t_CKBOOL sporked = ck->sporkFile("test/sinetone_onesecond.ck");
    ASSERT_TRUE(sporked);
    ck->Destroy();
}
