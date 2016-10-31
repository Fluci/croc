#define BOOST_TEST_MODULE test module name
#include <boost/test/included/unit_test.hpp>
#include "random_real.h"

BOOST_AUTO_TEST_CASE(testRandomRealInit)
{
	croc::random_real rr;
	BOOST_TEST(&rr);
}
