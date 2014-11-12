#include "finite_cyclic.h"
#include "gtest/gtest.h"

namespace {

int z4_order = 4;
int z4_bin_op(const int& lhs, const int& rhs) {
  return (lhs + rhs) % 4;
}
int z4_identity = 0;
int z4_invert(const int& value) {
  return (4 - value) % 4;
}

// The fixture for testing class FiniteCyclic.
class FiniteCyclicTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  FiniteCyclicTest() {
    // You can do set-up work for each test here.
  }

  virtual ~FiniteCyclicTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
    z4 = new artin::FiniteCyclic(4);
    z6 = new artin::FiniteCyclic(6);
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
    delete z4, z6;
  }

  // Objects declared here can be used by all tests in the test case for Foo.
  artin::FiniteCyclic *z4, *z6;
};

TEST_F(FiniteCyclicTest, Operation) {
  EXPECT_EQ(3, z4->Op(2, 1));
  EXPECT_EQ(0, z6->Op(8, 4));
}

TEST_F(FiniteCyclicTest, Identity) {
  EXPECT_EQ(0, z4->identity());
}

TEST_F(FiniteCyclicTest, Invert) {
  EXPECT_EQ(3, z4->Invert(1));
  EXPECT_EQ(0, z6->Invert(0));
}

TEST_F(FiniteCyclicTest, Order) {
  EXPECT_EQ(4, z4->order());
  EXPECT_EQ(6, z6->order());
}

TEST_F(FiniteCyclicTest, CopyConstructor) {
  artin::FiniteCyclic new_z4(*z4);
  EXPECT_EQ(3, new_z4.Op(2, 1));
  EXPECT_EQ(0, new_z4.identity());
  EXPECT_EQ(3, new_z4.Invert(1));
  EXPECT_EQ(4, new_z4.order());
}

TEST_F(FiniteCyclicTest, AssignementOperator) {
  artin::FiniteCyclic assignment(*z4);
  EXPECT_EQ(3, assignment.Op(2, 1));
  EXPECT_EQ(0, assignment.identity());
  EXPECT_EQ(3, assignment.Invert(1));
  EXPECT_EQ(4, assignment.order());
}

TEST_F(FiniteCyclicTest, OrderOfValue) {
  EXPECT_EQ(4, z4->order(5));
  EXPECT_EQ(3, z6->order(2));
}

TEST_F(FiniteCyclicTest, GenerateStaticOrder) {
  z4->GenerateStaticOrders();
  EXPECT_EQ(4, z4->order(1));
  EXPECT_EQ(1, z4->order(0));
}

TEST_F(FiniteCyclicTest, Power) {
  EXPECT_EQ(0, z4->Power(2, 650));
  EXPECT_EQ(2, z4->Power(3, 650));
}

TEST_F(FiniteCyclicTest, IsAbelian) {
  EXPECT_TRUE(z4->IsAbelian());
}

TEST_F(FiniteCyclicTest, IsCyclic) {
  EXPECT_TRUE(z4->IsCyclic());
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
