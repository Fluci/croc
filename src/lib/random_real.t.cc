// Created by Felice Serena 2016

#define BOOST_TEST_MODULE test module name
#include <boost/test/included/unit_test.hpp>

#include <cmath>
#include <random>

#include "random_real.h"

namespace {

struct F {
	F() {
		croc::random_real<>::set_random_engine(std::mt19937());
	}
	~F() {
		// tear down
	}
};

BOOST_FIXTURE_TEST_CASE(testRandomRealInteger, F) {
	croc::random_real<> r1;
	BOOST_TEST(r1.get_integer() == 0);

	croc::random_real<> r2(17);
	BOOST_TEST(r2.get_integer() == 17);

	croc::random_real<> r3(-19);
	BOOST_TEST(r3.get_integer() == -19);
}

BOOST_FIXTURE_TEST_CASE(testRandomRealGeneration, F) {
	croc::random_real<> rr;
	BOOST_TEST(rr.size() == 0);

	croc::random_real<>::block_type b0 = rr[0];
	BOOST_TEST(rr.size() == 1);

	croc::random_real<>::block_type b1 = rr[1];
	BOOST_TEST(rr.size() == 2);

	BOOST_TEST(rr[0] == b0);
	BOOST_TEST(rr[1] == b1);
}

// tests generation of randomness
BOOST_FIXTURE_TEST_CASE(testRandomRealRandomness, F) {
	croc::random_real<> rr;
	int i = 0;
	int ones = 0;
	const int runs = 1000;
	const int totalBits = runs*sizeof(croc::random_real<>::block_type)*8;
	for(; i < runs; i += 1) {
		std::bitset<sizeof(croc::random_real<>::block_type)*8> bits(rr[i]);
		ones += bits.count();
	}
	
	// simple  estimate of randomness
    
	const double off = std::abs((2.0*ones)/totalBits - 1.0);
	BOOST_TEST(off < 0.03);
}

BOOST_FIXTURE_TEST_CASE(testRandomRealLess, F) {
	croc::random_real<> r1;
	croc::random_real<> r2;

	// generate some numbers
	r1[3];

	BOOST_TEST((r1 < r2) != (r1 > r2));
	BOOST_TEST((r1 < r2) != (r2 < r1));
}

BOOST_FIXTURE_TEST_CASE(testRandomRealEquality, F) {
	croc::random_real<> r1;
	r1[4];

	croc::random_real<> r2(r1);

	BOOST_TEST(!(r1 == r2));

	// make them unequal
	r2[5];
	BOOST_TEST((r1 != r2));
}

BOOST_FIXTURE_TEST_CASE(testRandomRealLessEqual, F) {
	croc::random_real<> r1;
	r1[4];

	croc::random_real<> r2(r1);

	BOOST_TEST((r1 <= r2) != (r1 >= r2));
	BOOST_TEST(r1.size() > 5);
	BOOST_TEST(r2.size() > 5);
}

BOOST_FIXTURE_TEST_CASE(testRandomRealSelfEquality, F) {
	croc::random_real<> r1;
	r1[4];

	BOOST_TEST((r1 == r1));
	BOOST_TEST(r1.size() == 5);
}

BOOST_FIXTURE_TEST_CASE(testRandomRealSelfInEquality, F) {
	croc::random_real<> r1;
	r1[4];
	BOOST_TEST(!(r1 != r1));
	BOOST_TEST(r1.size() == 5);
}

BOOST_FIXTURE_TEST_CASE(testRandomRealSelfLess, F) {
	croc::random_real<> r1;
	r1[4];
	BOOST_TEST(!(r1 < r1));
	BOOST_TEST(r1.size() == 5);
}

BOOST_FIXTURE_TEST_CASE(testRandomRealSelfLarger, F) {
	croc::random_real<> r1;
	r1[4];
	BOOST_TEST(!(r1 > r1));
	BOOST_TEST(r1.size() == 5);
}

BOOST_FIXTURE_TEST_CASE(testRandomRealSelfLessEq, F) {
	croc::random_real<> r1;
	r1[4];
	BOOST_TEST((r1 <= r1));
	BOOST_TEST(r1.size() == 5);
}

BOOST_FIXTURE_TEST_CASE(testRandomRealSelfLargerEq, F) {
	croc::random_real<> r1;
	r1[4];
	BOOST_TEST((r1 >= r1));
	BOOST_TEST(r1.size() == 5);
}

BOOST_FIXTURE_TEST_CASE(testRandomRealIntegerCmp, F) {
	croc::random_real<> small(-1);
	croc::random_real<> normal;
	croc::random_real<> large(1);

	BOOST_TEST((small < normal));
	BOOST_TEST((normal < large));
	BOOST_TEST((small < large));
}

BOOST_FIXTURE_TEST_CASE(testRandomRealCopyLess, F) {
	croc::random_real<> r1;
	// generate some numbers
	r1[3];

	croc::random_real<> r2(r1);

	BOOST_TEST(!(r1 == r2));

	BOOST_TEST((r1 < r2) != (r1 > r2));
	BOOST_TEST((r1 < r2) != (r2 < r1));
}

}  // namespace
