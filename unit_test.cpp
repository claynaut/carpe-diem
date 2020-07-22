#include "gtest/gtest.h"

#include "task_test.hpp"
#include "category_test.hpp"
#include "lower_test.hpp"
#include "upper_test.hpp"
#include "visitor_test.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
