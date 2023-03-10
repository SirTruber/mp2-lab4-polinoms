#include <gtest.h>

int main(int argc, char **argv) {
    system("chcp 1251");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
