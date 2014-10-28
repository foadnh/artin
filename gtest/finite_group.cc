#include "../inc/finite_group.hpp"
#include "gtest/gtest.h"

namespace {

int s3_order = 6;
int s3_table[6][6] = {
	{0, 1, 2, 3, 4, 5},
	{1, 2, 0, 4, 5, 3},
	{2, 0, 1, 5, 3, 4},
	{3, 5, 4, 0, 2, 1},
	{4, 3, 5, 1, 0, 2},
	{5, 4, 3, 2, 1, 0}
};
int s3_bin_op(const int& lhs, const int& rhs) {
	return s3_table[lhs][rhs];
}
int s3_unit = 0;
int s3_invert(const int& value) {
	for (int i = 0; i < 6; i++)
		if (s3_table[value][i] == s3_unit)
			return i;
}

int z4_order = 4;
int z4_bin_op (const int& lhs, const int& rhs) {
	return (lhs + rhs) % 4;
}
int z4_unit = 0;
int z4_invert (const int& value) {
	return (4 - (value % 4)) % 4;
}

// The fixture for testing class group.
class FiniteGroupTest : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	FiniteGroupTest() {
		// You can do set-up work for each test here.
	}

	virtual ~FiniteGroupTest() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		s3 = new artin::FiniteGroup<>(s3_bin_op, s3_unit, s3_invert, s3_order);
		z4 = new artin::FiniteGroup<>(z4_bin_op, z4_unit, z4_invert, z4_order);
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
		delete s3;
	}

	// Objects declared here can be used by all tests in the test case for Foo.
	artin::FiniteGroup<> *s3;
	artin::FiniteGroup<int> *z4;
};

TEST_F(FiniteGroupTest, Operation) {
	EXPECT_EQ(5, s3->Op(3, 1));
}

TEST_F(FiniteGroupTest, Unit) {
	EXPECT_EQ(0, s3->Unit());
}

TEST_F(FiniteGroupTest, Invert) {
	EXPECT_EQ(2, s3->Invert(1));
}

TEST_F(FiniteGroupTest, Order) {
	EXPECT_EQ(6, s3->order());
}

TEST_F(FiniteGroupTest, GroupConstructor) {
	artin::group<int> s3_as_group(s3_bin_op, s3_unit, s3_invert);
	artin::FiniteGroup<int> s3_as_finite_group(s3_as_group, s3_order);
	EXPECT_EQ(2, s3_as_finite_group.Invert(1));
	EXPECT_EQ(0, s3_as_finite_group.Unit());
	EXPECT_EQ(5, s3_as_finite_group.Op(3,1));
	EXPECT_EQ(6, s3_as_finite_group.order());
}

TEST_F(FiniteGroupTest, CopyConstructor) {
	artin::FiniteGroup<> new_s3(*s3);
	EXPECT_EQ(2, new_s3.Invert(1));
	EXPECT_EQ(0, new_s3.Unit());
	EXPECT_EQ(5, new_s3.Op(3,1));
	EXPECT_EQ(6, new_s3.order());
}

TEST_F(FiniteGroupTest, AssignementOperator) {
	artin::FiniteGroup<> assignment(*z4);
	assignment.generate_static_orders();
	s3->generate_static_orders();
	assignment = *s3;
	EXPECT_EQ(2, assignment.Invert(1));
	EXPECT_EQ(0, assignment.Unit());
	EXPECT_EQ(5, assignment.Op(3,1));
	EXPECT_EQ(6, assignment.order());
}

TEST_F(FiniteGroupTest, OrderForElement) {
	EXPECT_EQ(3, s3->order(1));
	EXPECT_EQ(2, s3->order(4));
}

TEST_F(FiniteGroupTest, GenerateStaticOrder) {
	s3->generate_static_orders();
	EXPECT_EQ(3, s3->order(1));
	EXPECT_EQ(2, s3->order(4));
}

TEST_F(FiniteGroupTest, Power) {
	EXPECT_EQ(0, z4->power(2, 650));
	z4->generate_static_orders();
	EXPECT_EQ(0, z4->power(2, 650));
}

}  // namespace

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
