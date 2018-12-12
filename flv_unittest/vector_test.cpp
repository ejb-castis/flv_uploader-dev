#include <gtest/gtest.h>
#include <vector>


void erase_vector(std::vector<int>& v) {
    v.pop_back();
    v.pop_back();
    v.pop_back();
}
void erase_vector2(std::vector<int> v) {
    v.pop_back();
    v.pop_back();
    v.pop_back();
}


TEST(VECTOR, test)
{
  std::vector<int> a;
  a.push_back(1);
  a.push_back(2);
  a.push_back(3);

  EXPECT_EQ(3, a.size());
  erase_vector(a);
  EXPECT_EQ(0, a.size());

  std::vector<int> b;
  b.push_back(1);
  b.push_back(2);
  b.push_back(3);
  EXPECT_EQ(3, b.size());
  erase_vector2(b);
  EXPECT_EQ(3, b.size());
}
