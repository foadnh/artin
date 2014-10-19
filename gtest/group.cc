#include "../inc/group.hpp"
#include "gtest/gtest.h"

namespace {

// The fixture for testing class group.
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
		integer_additive_group = new artin::group<int>(std::plus<int>(), 0, std::negate<int>());
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
		delete integer_additive_group;
	}

	// Objects declared here can be used by all tests in the test case for Foo.
	artin::group<int>* integer_additive_group;
};

TEST_F(GroupTest, Unit) {
	EXPECT_EQ(0, integer_additive_group->Unit());
}

TEST_F(GroupTest, Operation) {
	EXPECT_EQ(5, integer_additive_group->Op(2, 3));
}

TEST_F(GroupTest, Invert) {
	EXPECT_EQ(-5, integer_additive_group->Invert(5));
}

TEST_F(GroupTest, MonoidConstructor) {
	artin::monoid<int> integer_additive_monoid(std::plus<int>(), 0);
	artin::group<int> new_integer_additive_group(integer_additive_monoid, std::negate<int>());
	EXPECT_EQ(0, new_integer_additive_group.Unit());
	EXPECT_EQ(5, new_integer_additive_group.Op(2, 3));
	EXPECT_EQ(-5, new_integer_additive_group.Invert(5));
}

TEST_F(GroupTest, CopyConstructor) {
	artin::group<int> new_integer_additive_group(*integer_additive_group);
	EXPECT_EQ(0, new_integer_additive_group.Unit());
	EXPECT_EQ(5, new_integer_additive_group.Op(2, 3));
	EXPECT_EQ(-5, new_integer_additive_group.Invert(5));
}

// If we uncomment assignment operator, we have to uncomment this function.
/*TEST_F(GroupTest, Assignement) {
	artin::group<int> assignment(*integer_additive_group);
	assignment = *integer_multiplicative_;
	EXPECT_EQ(1, assignment.Unit());
	EXPECT_EQ(6, assignment.Op(2, 3));
}*/

}  // namespace

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
