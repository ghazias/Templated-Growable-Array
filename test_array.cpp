#include "catch.hpp"
#include "template_array.hpp"
#include <string>

TEST_CASE("Constructor") {
	dsc::Array<int> arr;
	REQUIRE(arr.size() == 0);
}

TEST_CASE("Array has correct size") {
	REQUIRE(dsc::Array<int>(5).size() == 5);
	REQUIRE(dsc::Array<std::string>(18).size() == 18);
	REQUIRE(dsc::Array<double>(300).size() == 300);
}

TEST_CASE("Can access size of const array") {
	const dsc::Array<char> array(8);
	REQUIRE(array.size() == 8);
}
