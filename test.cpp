#include <gtest/gtest.h>
#include "lib.h"

TEST(GreaterTest, first_byte){
  ip_address a = {"1", "99", "68", "23"};
  ip_address b = {"2", "13", "24", "64"};
  EXPECT_EQ(greater(a, b), false);
}

TEST(GreaterTest, last_byte){
  ip_address a = {"2", "2", "2", "4"};
  ip_address b = {"2", "2", "2", "2"};
  EXPECT_EQ(greater(a, b), true );
}

int main(int argc, char **argv){
testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}
