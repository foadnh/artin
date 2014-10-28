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

TEST_F(GroupTest, AssignementOperator) {
	// Not really a group, but still ok for testing.
	artin::group<int> assignment(std::multiplies<int>(), 1, std::negate<int>());
	assignment = *integer_additive_group;
	EXPECT_EQ(0, assignment.Unit());
	EXPECT_EQ(5, assignment.Op(2, 3));
	EXPECT_EQ(-5, assignment.Invert(5));
}

// For EqualToOperator and NotEqualToOperator tests
int plus1(const int& x) {
	return x + 1;
}
const bool operator==(const std::function<int(const int&, const int&)>& first, const std::function<int(const int&, const int&)>& second) {
	return first(3, 4) == second(3, 4);
}
const bool operator==(const std::function<int(const int&)>& first, const std::function<int(const int&)>& second) {
	return first(6) == second(6);
}

TEST_F(GroupTest, EqualToOperator) {
	artin::monoid<int> integer_additive_monoid(std::plus<int>(), 0), integer_multiplicative_monoid(std::multiplies<int>(), 1);
	// Not really a group, but still ok for testing.
	artin::group<int> equal(integer_additive_monoid, std::negate<int>()),
		  unequal_1(integer_multiplicative_monoid, std::negate<int>()), unequal_2(integer_additive_monoid, plus1);
	EXPECT_TRUE(*integer_additive_group == equal);
	EXPECT_FALSE(*integer_additive_group == unequal_1);
	EXPECT_FALSE(*integer_additive_group == unequal_2);
}

TEST_F(GroupTest, NotEqualToOperator) {
	artin::monoid<int> integer_additive_monoid(std::plus<int>(), 0), integer_multiplicative_monoid(std::multiplies<int>(), 1);
	artin::group<int> equal(integer_additive_monoid, std::negate<int>()),
		  unequal_1(integer_multiplicative_monoid, std::negate<int>()), unequal_2(integer_additive_monoid, plus1);
	EXPECT_FALSE(*integer_additive_group != equal);
	EXPECT_TRUE(*integer_additive_group != unequal_1);
	EXPECT_TRUE(*integer_additive_group != unequal_2);
}

TEST_F(GroupTest, Power) {
	EXPECT_EQ(73068, integer_additive_group->power(3, 24356));
	EXPECT_EQ(-73068, integer_additive_group->power(3, -24356));
}

}  // namespace

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
