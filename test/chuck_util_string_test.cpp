#include <gtest/gtest.h>
#include <string.h>

#include <string>
#include <vector>

#include <util_string.h>

using std::string;
using std::vector;

TEST(extract_args, Splits_Strings_At_Colons) {
    const char * str = "file:arg1:arg2";
    string filename;
    vector<string> args;
    extract_args(str, filename, args);
    ASSERT_EQ(0, strcmp(filename.c_str(), "file"));
}
