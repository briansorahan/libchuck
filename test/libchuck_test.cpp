#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gtest/gtest.h>

#include <chuck.h>
#include "libchuck_test.hpp"

// bool received_int = false;
// t_CKINT intval;
// bool received_float = false;
// t_CKFLOAT floatval;
// bool received_string = false;
// char strval[8192];

// void receive_int(t_CKINT val) {
//     received_int = true;
//     intval = val;
// }

// void receive_float(t_CKFLOAT val) {
//     received_float = true;
//     floatval = val;
// }

// void receive_string(const char * s) {
//     received_string = true;
//     strcpy(strval, s);
// }

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
    unsigned int files = 1;
    const char * filenames[] = { "chuck2c.ck" };

    TestIntReceiver intrec;
    TestFloatReceiver floatrec;
    TestStringReceiver stringrec;

    chuck::RegisterIntReceiver("foo", &intrec);
    chuck::RegisterFloatReceiver("bar", &floatrec);
    chuck::RegisterStringReceiver("baz", &stringrec);

    Spork(files, filenames);
    bool finished = Run();
    ASSERT_TRUE(finished);

    intrec.assertReceived(4);
    floatrec.assertReceived(2.71);
    stringrec.assertReceived("libchuck");
}

bool received_foo_int = false;
t_CKINT foo_intval;
void receive_foo_int(t_CKINT val) {
    foo_intval = val;
    received_foo_int = true;
}

TEST_F(ChuckTest, roundtrip_events) {
    unsigned int files = 1;
    const char * filenames[] = { "roundtrip.ck" };
    TestIntReceiver intrec;

    // chuck::RegisterIntReceiver("foo", &intrec);
    Spork(files, filenames);
    bool finished = Run();
    ASSERT_TRUE(finished);
}
