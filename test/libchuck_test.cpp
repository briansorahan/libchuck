#include <gtest/gtest.h>
#include "libchuck_test.hpp"
#include <unistd.h>

TEST_F(ChuckTest, sporking_single_file_no_args) {
    t_CKBOOL sporked = ck->sporkFile("test/sinetone.ck");
    ASSERT_TRUE(sporked);
    t_CKBOOL ran = ck->runBlocking();
    ASSERT_TRUE(ran);
}

TEST_F(ChuckTest, sporking_single_file_one_arg) {
    t_CKBOOL sporked = ck->sporkFile("test/sinetone.ck:220");
    ASSERT_TRUE(sporked);
    t_CKBOOL ran = ck->runBlocking();
    ASSERT_TRUE(ran);
}

TEST_F(ChuckTest, sporking_two_files_two_args) {
    t_CKBOOL sporked1 = ck->sporkFile("test/sinetone.ck:440:0.49");
    t_CKBOOL sporked2 = ck->sporkFile("test/sinetone.ck:443:0.49");
    ASSERT_TRUE(sporked1);
    ASSERT_TRUE(sporked2);
    t_CKBOOL ran = ck->runBlocking();
    ASSERT_TRUE(ran);
}

TEST_F(ChuckTest, sporking_file_that_sporks_again) {
    t_CKBOOL sporked = ck->sporkFile("test/willsporkagain.ck");
    ASSERT_TRUE(sporked);
    t_CKBOOL ran = ck->runBlocking();
    ASSERT_TRUE(ran);
}

TEST_F(ChuckTest, sporking_file_that_uses_builtin_event_classes) {
    t_CKBOOL sporked = ck->sporkFile("test/event-classes.ck");
    ASSERT_TRUE(sporked);
    t_CKBOOL ran = ck->runBlocking();
    ASSERT_TRUE(ran);
}

TEST_F(ChuckTest, sporking_file_that_uses_events) {
    t_CKBOOL sporked = ck->sporkFile("test/events.ck");
    ASSERT_TRUE(sporked);
    t_CKBOOL ran = ck->runBlocking();
    ASSERT_TRUE(ran);
}

// TEST_F(ChuckTest, triggering_events_from_c) {
//     t_CKBOOL sporked = ck->sporkFile("test/c2chuck.ck");
//     ASSERT_TRUE(sporked);
//     pid_t ran = ck->run();
//     ASSERT_TRUE(ran);
//     // Never makes it here because ck->run blocks
//     chuck::sendTo("foo", (t_CKINT) 4);
// }
