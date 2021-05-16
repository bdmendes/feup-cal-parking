#include <iostream>
#include "../lib/googletest-master/googletest/include/gtest/gtest.h"

int main(){
    std::cout << "Running all tests..." << std::endl;
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}