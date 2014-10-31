#include "group.h"
#include "gtest/gtest.h"

namespace {

// The fixture for testing class Group.
class GroupTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  GroupTest() {
    // You can do set-up work for each test here.
  }

  virtual ~GroupTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
    integer_additive_group = new artin::Group<int>(std::plus<int>(), 0,
        std::negate<int>());
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
    delete integer_additive_group;
  }

  // Objects declared here can be used by all tests in the test case for Foo.
  artin::Group<int>* integer_additive_group;
};

TEST_F(GroupTest, Identity) {
  EXPECT_EQ(0, integer_additive_group->identity());
}

TEST_F(GroupTest, Operation) {
  EXPECT_EQ(5, integer_additive_group->Op(2, 3));
}

TEST_F(GroupTest, Invert) {
  EXPECT_EQ(-5, integer_additive_group->Invert(5));
}

TEST_F(GroupTest, MonoidConstructor) {
  artin::Monoid<int> integer_additive_monoid(std::plus<int>(), 0);
  artin::Group<int> new_integer_additive_group(integer_additive_monoid,
      std::negate<int>());
  EXPECT_EQ(0, new_integer_additive_group.identity());
  EXPECT_EQ(5, new_integer_additive_group.Op(2, 3));
  EXPECT_EQ(-5, new_integer_additive_group.Invert(5));
}

TEST_F(GroupTest, CopyConstructor) {
  artin::Group<int> new_integer_additive_group(*integer_additive_group);
  EXPECT_EQ(0, new_integer_additive_group.identity());
  EXPECT_EQ(5, new_integer_additive_group.Op(2, 3));
  EXPECT_EQ(-5, new_integer_additive_group.Invert(5));
}

TEST_F(GroupTest, AssignementOperator) {
  // Not really a group, but still ok for testing.
  artin::Group<int> assignment(std::multiplies<int>(), 1, std::negate<int>());
  assignment = *integer_additive_group;
  EXPECT_EQ(0, assignment.identity());
  EXPECT_EQ(5, assignment.Op(2, 3));
  EXPECT_EQ(-5, assignment.Invert(5));
}

// For EqualToOperator and NotEqualToOperator tests
int plus1(const int& x) {
  return x + 1;
}
const bool operator==(const std::function<int(const int&, const int&)>& first,
                      const std::function<int(const int&, const int&)>& sec) {
  return first(3, 4) == sec(3, 4);
}
const bool operator==(const std::function<int(const int&)>& first,
                      const std::function<int(const int&)>& sec) {
  return first(6) == sec(6);
}

TEST_F(GroupTest, EqualToOperator) {
  artin::Monoid<int> integer_additive_monoid(std::plus<int>(), 0),
        integer_multiplicative_monoid(std::multiplies<int>(), 1);
  // Not really a group, but still ok for testing.
  artin::Group<int> equal(integer_additive_monoid, std::negate<int>()),
        unequal_1(integer_multiplicative_monoid, std::negate<int>()),
        unequal_2(integer_additive_monoid, plus1);
  EXPECT_TRUE(*integer_additive_group == equal);
  EXPECT_FALSE(*integer_additive_group == unequal_1);
  EXPECT_FALSE(*integer_additive_group == unequal_2);
}

TEST_F(GroupTest, NotEqualToOperator) {
  artin::Monoid<int> integer_additive_monoid(std::plus<int>(), 0),
        integer_multiplicative_monoid(std::multiplies<int>(), 1);
  artin::Group<int> equal(integer_additive_monoid, std::negate<int>()),
        unequal_1(integer_multiplicative_monoid, std::negate<int>()),
        unequal_2(integer_additive_monoid, plus1);
  EXPECT_FALSE(*integer_additive_group != equal);
  EXPECT_TRUE(*integer_additive_group != unequal_1);
  EXPECT_TRUE(*integer_additive_group != unequal_2);
}

TEST_F(GroupTest, Power) {
  EXPECT_EQ(73068, integer_additive_group->Power(3, 24356));
  EXPECT_EQ(-73068, integer_additive_group->Power(3, -24356));
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
