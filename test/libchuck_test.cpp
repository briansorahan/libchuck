#include <gtest/gtest.h>
#include "libchuck_test.hpp"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

bool received_int = false;
t_CKINT intval;
bool received_float = false;
t_CKFLOAT floatval;
bool received_string = false;
char strval[8192];

void receive_int(t_CKINT val) {
    received_int = true;
    intval = val;
}

void receive_float(t_CKFLOAT val) {
    received_float = true;
    floatval = val;
}

void receive_string(const char * s) {
    received_string = true;
    strcpy(strval, s);
}

TEST_F(ChuckTest, sporking_single_file_no_args) {
    unsigned int files = 1;
    const char * filenames[] = { "sinetone.ck" };
    Spork(files, filenames);
    bool finished = Run();
    ASSERT_TRUE(finished);
}

TEST_F(ChuckTest, sporking_single_file_one_arg) {
    unsigned int files = 1;
    const char * filenames[] = { "sinetone.ck:220" };
    Spork(files, filenames);
    bool finished = Run();
    ASSERT_TRUE(finished);
}

TEST_F(ChuckTest, sporking_two_files_two_args) {
    unsigned int files = 2;
    const char * filenames[] = {
        "sinetone.ck:440:0.49",
        "sinetone.ck:443:0.49"
    };
    Spork(files, filenames);
    bool finished = Run();
    ASSERT_TRUE(finished);
}

TEST_F(ChuckTest, sporking_file_that_sporks_again) {
    unsigned int files = 1;
    const char * filenames[] = { "willsporkagain.ck" };
    Spork(files, filenames);
    bool finished = Run();
    ASSERT_TRUE(finished);
}

TEST_F(ChuckTest, sporking_file_that_uses_builtin_event_classes) {
    unsigned int files = 1;
    const char * filenames[] = { "event-classes.ck" };
    Spork(files, filenames);
    bool finished = Run();
    ASSERT_TRUE(finished);
}

TEST_F(ChuckTest, sporking_file_that_uses_events) {
    unsigned int files = 1;
    const char * filenames[] = { "events.ck" };
    Spork(files, filenames);
    bool finished = Run();
    ASSERT_TRUE(finished);
}

TEST_F(ChuckTest, triggering_events_from_c) {
    unsigned int files = 1;
    const char * filenames[] = { "c2chuck.ck" };
    Spork(files, filenames);
    chuck::SendTo("foo", (t_CKINT) 4);
    bool finished = Run();
    ASSERT_TRUE(finished);
}

TEST_F(ChuckTest, triggering_c_events_from_chuck) {
    skipYield = true;
    unsigned int files = 1;
    const char * filenames[] = { "chuck2c.ck" };
    chuck::RegisterIntReceiver(&receive_int);
    chuck::RegisterFloatReceiver(&receive_float);
    chuck::RegisterStringReceiver(&receive_string);
    Spork(files, filenames);
    bool finished = Run();
    ASSERT_TRUE(finished);
    ASSERT_TRUE(received_int);
    ASSERT_EQ(4, intval);
    ASSERT_TRUE(received_float);
    ASSERT_EQ(2.71, floatval);
    ASSERT_TRUE(received_string);
    ASSERT_EQ(0, strcmp("libchuck", strval));
}
