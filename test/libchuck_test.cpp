#include <gtest/gtest.h>
#include "libchuck_test.hpp"

TEST_F(ChuckTest, sporking_single_file_no_args) {
    t_CKBOOL sporked = ck->sporkFile("test/sinetone_onesecond.ck");
    ASSERT_TRUE(sporked);
    t_CKBOOL ran = ck->run();
    ASSERT_TRUE(ran);
}

TEST_F(ChuckTest, sporking_single_file_one_arg) {
    t_CKBOOL sporked = ck->sporkFile("test/sinetone_onesecond.ck:220");
    ASSERT_TRUE(sporked);
    t_CKBOOL ran = ck->run();
    ASSERT_TRUE(ran);
}
