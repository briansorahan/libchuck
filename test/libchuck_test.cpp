#include <gtest/gtest.h>
#include "libchuck_test.hpp"
#include <unistd.h>

TEST_F(ChuckTest, sporking_single_file_no_args) {
    unsigned int files = 1;
    const char * filenames[] = { "test/sinetone.ck" };
    Spork(files, filenames);
}

TEST_F(ChuckTest, sporking_single_file_one_arg) {
    unsigned int files = 1;
    const char * filenames[] = { "test/sinetone.ck:220" };
    Spork(files, filenames);
}

TEST_F(ChuckTest, sporking_two_files_two_args) {
    unsigned int files = 2;
    const char * filenames[] = {
        "test/sinetone.ck:440:0.49",
        "test/sinetone.ck:443:0.49"
    };
    Spork(files, filenames);
}

TEST_F(ChuckTest, sporking_file_that_sporks_again) {
    unsigned int files = 1;
    const char * filenames[] = { "test/willsporkagain.ck" };
    Spork(files, filenames);
}

TEST_F(ChuckTest, sporking_file_that_uses_builtin_event_classes) {
    unsigned int files = 1;
    const char * filenames[] = { "test/event-classes.ck" };
    Spork(files, filenames);
}

TEST_F(ChuckTest, sporking_file_that_uses_events) {
    int files = 1;
    const char * filenames[] = { "test/events.ck" };
    Spork(files, filenames);
}

// TEST_F(ChuckTest, triggering_events_from_c) {
//     t_CKBOOL sporked = ck->sporkFile("test/c2chuck.ck");
//     ASSERT_TRUE(sporked);
//     pid_t ran = ck->run();
//     ASSERT_TRUE(ran);
//     // Never makes it here because ck->run blocks
//     chuck::sendTo("foo", (t_CKINT) 4);
// }
