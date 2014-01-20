#include <gtest/gtest.h>
#include "libchuck_test.hpp"
#include <stdio.h>
#include <unistd.h>

bool received_int = false;
bool received_float = false;
bool received_string = false;

void receive_int(t_CKINT val) {
    received_int = true;
}

void receive_float(t_CKFLOAT val) {
    received_float = true;
}

void receive_string(const char * s) {
    received_string = true;
}

TEST_F(ChuckTest, sporking_single_file_no_args) {
    unsigned int files = 1;
    const char * filenames[] = { "test/sinetone.ck" };
    Spork(files, filenames);
    bool finished = chuck::Yield();
    ASSERT_TRUE(finished);
}

TEST_F(ChuckTest, sporking_single_file_one_arg) {
    unsigned int files = 1;
    const char * filenames[] = { "test/sinetone.ck:220" };
    Spork(files, filenames);
    bool finished = chuck::Yield();
    ASSERT_TRUE(finished);
}

TEST_F(ChuckTest, sporking_two_files_two_args) {
    unsigned int files = 2;
    const char * filenames[] = {
        "test/sinetone.ck:440:0.49",
        "test/sinetone.ck:443:0.49"
    };
    Spork(files, filenames);
    bool finished = chuck::Yield();
    ASSERT_TRUE(finished);
}

TEST_F(ChuckTest, sporking_file_that_sporks_again) {
    unsigned int files = 1;
    const char * filenames[] = { "test/willsporkagain.ck" };
    Spork(files, filenames);
    bool finished = chuck::Yield();
    ASSERT_TRUE(finished);
}

TEST_F(ChuckTest, sporking_file_that_uses_builtin_event_classes) {
    unsigned int files = 1;
    const char * filenames[] = { "test/event-classes.ck" };
    Spork(files, filenames);
    bool finished = chuck::Yield();
    ASSERT_TRUE(finished);
}

TEST_F(ChuckTest, sporking_file_that_uses_events) {
    unsigned int files = 1;
    const char * filenames[] = { "test/events.ck" };
    Spork(files, filenames);
    bool finished = chuck::Yield();
    ASSERT_TRUE(finished);
}

TEST_F(ChuckTest, triggering_events_from_c) {
    unsigned int files = 1;
    const char * filenames[] = { "test/c2chuck.ck" };
    Spork(files, filenames);
    chuck::SendTo("foo", (t_CKINT) 4);
    bool finished = chuck::Yield();
    ASSERT_TRUE(finished);
}

TEST_F(ChuckTest, triggering_c_events_from_chuck) {
    skipYield = true;
    unsigned int files = 1;
    const char * filenames[] = { "test/chuck2c.ck" };
    chuck::RegisterIntReceiver(&receive_int);
    chuck::RegisterFloatReceiver(&receive_float);
    chuck::RegisterStringReceiver(&receive_string);
    Spork(files, filenames);
    bool finished = chuck::Yield();
    ASSERT_TRUE(finished);
    ASSERT_TRUE(received_int);
    ASSERT_TRUE(received_float);
    ASSERT_TRUE(received_string);
}
