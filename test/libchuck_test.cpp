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

TEST_F(ChuckTest, sporking_two_files_two_args) {
    t_CKBOOL sporked1 = ck->sporkFile("test/sinetone_onesecond.ck:440:0.49");
    t_CKBOOL sporked2 = ck->sporkFile("test/sinetone_onesecond.ck:443:0.49");
    ASSERT_TRUE(sporked1);
    ASSERT_TRUE(sporked2);
    t_CKBOOL ran = ck->run();
    ASSERT_TRUE(ran);
}

TEST_F(ChuckTest, sporking_file_that_sporks_again) {
    t_CKBOOL sporked = ck->sporkFile("test/willsporkagain.ck");
    ASSERT_TRUE(sporked);
    t_CKBOOL ran = ck->run();
    ASSERT_TRUE(ran);
}
