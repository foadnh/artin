#include "../inc/monoid.hpp"
#include "gtest/gtest.h"

namespace {

// The fixture for testing class monoid.
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
		integer_additive_monoid = new artin::monoid<int>(std::plus<int>(), 0);
		integer_multiplicative_monoid = new artin::monoid<int>(std::multiplies<int>(), 1);
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
		delete integer_additive_monoid;
		delete integer_multiplicative_monoid;
	}

	// Objects declared here can be used by all tests in the test case for Foo.
	artin::monoid<int>* integer_additive_monoid;
	artin::monoid<int>* integer_multiplicative_monoid;
};

TEST_F(MonoidTest, Unit) {
	EXPECT_EQ(0, integer_additive_monoid->Unit());
	EXPECT_EQ(1, integer_multiplicative_monoid->Unit());
}

TEST_F(MonoidTest, Operation) {
	EXPECT_EQ(5, integer_additive_monoid->Op(2, 3));
	EXPECT_EQ(6, integer_multiplicative_monoid->Op(2, 3));
}

TEST_F(MonoidTest, CopyConstructor) {
	artin::monoid<int> new_integer_additive_monoid(*integer_additive_monoid);
	artin::monoid<int> new_integer_multiplicative_monoid(*integer_multiplicative_monoid);
	EXPECT_EQ(0, new_integer_additive_monoid.Unit());
	EXPECT_EQ(1, new_integer_multiplicative_monoid.Unit());
	EXPECT_EQ(5, new_integer_additive_monoid.Op(2, 3));
	EXPECT_EQ(6, new_integer_multiplicative_monoid.Op(2, 3));
}

// If we uncomment assignment operator, we have to uncomment this function.
/*TEST_F(MonoidTest, Assignement) {
	artin::monoid<int> assignment(*integer_additive_monoid);
	assignment = *integer_multiplicative_monoid;
	EXPECT_EQ(1, assignment.Unit());
	EXPECT_EQ(6, assignment.Op(2, 3));
}*/

}  // namespace

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
