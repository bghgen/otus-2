#include <gtest/gtest.h>
#include "lib.h"

TEST(GreaterTest, first_byte){
  IP::ip_address a = {"1", "99", "68", "23"};
  IP::ip_address b = {"2", "13", "24", "64"};
  EXPECT_EQ(IP::greater(a, b), false);
}

TEST(GreaterTest, last_byte){
  IP::ip_address a = {"2", "2", "2", "4"};
  IP::ip_address b = {"2", "2", "2", "2"};
  EXPECT_EQ(IP::greater(a, b), true );
}

TEST(SplitTest, test1){
  std::string a = "2,255,67,7";
  auto b = IP::split(a, ',');
  IP::ip_address c = {"2","255","67","7"};
  EXPECT_EQ(b, c);
}

TEST(SplitTest, test2){
  std::string test = "2,255,67,7";
  IP::ip_address res = {"2","255","67","7"};
  EXPECT_EQ(IP::split(test, ','), res);
}

TEST(SplitTest, test3){
  EXPECT_EQ(IP::split("", '.'), IP::ip_address {""});
}

TEST(SplitTest, test4){
  EXPECT_EQ(IP::split("11", '.'), IP::ip_address {"11"});
}

TEST(SplitTest, test5){
  IP::ip_address res = {"", "", ""};
  EXPECT_EQ(IP::split("..", '.'), res);
}

TEST(SplitTest, test6){
  IP::ip_address res = {"11", ""};
  EXPECT_EQ(IP::split("11.", '.'), res);
}

TEST(SplitTest, test7){
  IP::ip_address res = {"", "11"};
  EXPECT_EQ(IP::split(".11", '.'), res);
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
