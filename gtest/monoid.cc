#include "monoid.h"
#include "gtest/gtest.h"

namespace {

// The fixture for testing class Monoid.
class MonoidTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  MonoidTest() {
    // You can do set-up work for each test here.
  }

  virtual ~MonoidTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
    integer_additive_monoid = new artin::Monoid<int>(std::plus<int>(), 0);
    integer_multiplicative_monoid = new artin::Monoid<int>(
      std::multiplies<int>(), 1);
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
    delete integer_additive_monoid;
    delete integer_multiplicative_monoid;
  }

  // Objects declared here can be used by all tests in the test case for Foo.
  artin::Monoid<int>* integer_additive_monoid;
  artin::Monoid<int>* integer_multiplicative_monoid;
};

TEST_F(MonoidTest, Identity) {
  EXPECT_EQ(0, integer_additive_monoid->identity());
  EXPECT_EQ(1, integer_multiplicative_monoid->identity());
}

TEST_F(MonoidTest, Operation) {
  EXPECT_EQ(5, integer_additive_monoid->Op(2, 3));
  EXPECT_EQ(6, integer_multiplicative_monoid->Op(2, 3));
}

TEST_F(MonoidTest, CopyConstructor) {
  artin::Monoid<int> new_integer_additive_monoid(*integer_additive_monoid);
  artin::Monoid<int> new_integer_multiplicative_monoid(
    *integer_multiplicative_monoid);
  EXPECT_EQ(0, new_integer_additive_monoid.identity());
  EXPECT_EQ(1, new_integer_multiplicative_monoid.identity());
  EXPECT_EQ(5, new_integer_additive_monoid.Op(2, 3));
  EXPECT_EQ(6, new_integer_multiplicative_monoid.Op(2, 3));
}

TEST_F(MonoidTest, AssignementOperator) {
  artin::Monoid<int> assignment(*integer_additive_monoid);
  assignment = *integer_multiplicative_monoid;
  EXPECT_EQ(1, assignment.identity());
  EXPECT_EQ(6, assignment.Op(2, 3));
}

// For EqualToOperator and NotEqualToOperator tests
const bool operator==(const std::function<int(const int&, const int&)>& first,
                      const std::function<int(const int&, const int&)>& sec) {
  // It don't really tests equality but enough for unit test.
  return first(3, 4) == sec(3, 4);
}

TEST_F(MonoidTest, EqualToOperator) {
  artin::Monoid<int> equal(std::plus<int>(), 0),
        unequal_1(std::plus<int>(), 1), unequal_2(std::multiplies<int>(), 0);
  EXPECT_TRUE(*integer_additive_monoid == equal);
  EXPECT_FALSE(*integer_additive_monoid == unequal_1);
  EXPECT_FALSE(*integer_additive_monoid == unequal_2);
}

TEST_F(MonoidTest, NotEqualToOperator) {
  artin::Monoid<int> equal(std::plus<int>(), 0),
        unequal_1(std::plus<int>(), 1), unequal_2(std::multiplies<int>(), 0);
  EXPECT_FALSE(*integer_additive_monoid != equal);
  EXPECT_TRUE(*integer_additive_monoid != unequal_1);
  EXPECT_TRUE(*integer_additive_monoid != unequal_2);
}

TEST_F(MonoidTest, Power) {
  EXPECT_EQ(0, integer_additive_monoid->Power(3, 0));
  EXPECT_EQ(3, integer_additive_monoid->Power(3, 1));
  EXPECT_EQ(63, integer_additive_monoid->Power(3, 21));
  EXPECT_EQ(73068, integer_additive_monoid->Power(3, 24356));
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



