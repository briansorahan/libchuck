#include <gtest/gtest.h>
#include <chuck.h>

using chuck::Chuck;

TEST(Chuck, Instantiation) {
    Chuck * ck = chuck::Create(8500);
}
