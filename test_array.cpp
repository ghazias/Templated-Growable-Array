#include <string>

#include "catch.hpp"
#include "template_array.hpp"
#include "template_array.hpp"  // include guard

TEST_CASE("Arrays can be constructed") {
  dsc::Array<int> arr;
  REQUIRE(arr != NULL);
}

TEST_CASE("Arrays can be copy constructed") {
  dsc::Array<std::string> test(3);
  test[0] = "Hello, ";
  test[1] = "my name is ";
  test[2] = "Adrian";

  dsc::Array<std::string> test2(test);
  REQUIRE(test2[0] == "Hello, ");
  REQUIRE(test2[1] == "my name is ");
  REQUIRE(test2[2] == "Adrian");
}

TEST_CASE("Can set and access array elements") {
  dsc::Array<char> char_arr(3);
  char_arr[0] = 'a';
  char_arr[1] = 'b';
  char_arr[2] = 'c';

  REQUIRE(char_arr[0] == 'a');
  REQUIRE(char_arr[1] == 'b');
  REQUIRE(char_arr[2] == 'c');

  dsc::Array<int> int_arr(3);
  int_arr[0] = 122;
  int_arr[1] = 984;
  int_arr[2] = 21;

  REQUIRE(int_arr[0] == 122);
  REQUIRE(int_arr[1] == 984);
  REQUIRE(int_arr[2] == 21);
}

TEST_CASE("== Operator") {
  dsc::Array<int> test(3);
  dsc::Array<int> test2(3);

  test[0] = 12;
  test[1] = 9;
  test[2] = 66;
  test2[0] = 88;
  test2[1] = 17;
  test2[2] = 15;

  REQUIRE_FALSE(test == test2);

  dsc::Array<int> test3 = test2;
  REQUIRE(&test2 != &test3);
  REQUIRE(test2 == test3);
}

TEST_CASE("Arrays have correct size") {
  REQUIRE(dsc::Array<int>(5).size() == 5);
  REQUIRE(dsc::Array<std::string>(18).size() == 18);
  REQUIRE(dsc::Array<double>(300).size() == 300);
}

TEST_CASE("Const arrays have correct size") {
  REQUIRE(const dsc::Array<char>(8).size() == 8);
}

TEST_CASE("Arrays have correct capacity") {
  dsc::Array<int> test(4);
  REQUIRE(test.capacity() == 4);

  dsc::Array<std::string> test2(8);
  REQUIRE(test.capacity() == 8);
}

TEST_CASE("At() returns correct address") {
  dsc::Array<int> test2(0);
  REQUIRE(test.at(0) == nullptr);

  dsc::Array<char> test(3);
  test[0] = 't';
  test[1] = 'k';
  test[2] = 'j';

  REQUIRE(&test.at(0) == &test[0]);
  REQUIRE(&test.at(1) == &test[1]);
  REQUIRE(&test.at(2) == &test[2]);

  // how to test out of bounds?
  // REQUIRE thrown exception?
}

TEST_CASE("Front()") {
  dsc::Array<bool> test(3);
  REQUIRE(test.front() == nullptr);  // empty test

  test[0] = true;
  test[1] = false;
  test[2] = true;

  REQUIRE(test.front() == true);  // non empty test
}

TEST_CASE("Back()") {
  dsc::Array<std::string> test(3);
  REQUIRE(test.back() == nullptr);  // empty test

  test[0] = "obnoxious";
  test[1] = "bloviate";
  test[2] = "visceral";
  REQUIRE(test.back() == "visceral");  // non empty test
}

TEST_CASE("Can access data()") {
  dsc::Array<int> test(1);
  REQUIRE(test.data() == nullptr);

  test[0] = 41;
  REQUIRE(test.data() != nullptr);
}

// test cases for begin() and end()
// test by iterators?

TEST_CASE("Reserve()") {
  dsc::Array<int> test(4);
  test.reserve(13);
  REQUIRE(test.capacity() == 13);
}

TEST_CASE("pop_back()") {
  // pop empty list
  dsc::Array<int> test(6);
  // not sure what to test for here
  // pop list with one element
  test[0] = 20;
  REQUIRE(test[0] == 20);
  // pop list with more than one element
  test[1] = 62;
  REQUIRE(test[1] == 62);
}

TEST_CASE("push_back()") {
  dsc::Array<int> test(4);
  // push empty list
  test.push_back(777);
  REQUIRE(test[0] == 777);
  // push value to list of one element
  test.push_back(18);
  REQUIRE(test[1] == 18);
  // push value to list of more than one
  test.push_back(200);
  REQUIRE(test[2] == 200);
}

TEST_CASE("insert()") {
  // insert empty list
  dsc::Array<char> test(6);
  REQUIRE(test[0] == nullptr);

  // insert to list of one element
  test.insert('b');
  REQUIRE(test[0] == 'b');

  // insert to list of more than one element
  test.insert('m');
  test.insert('f');

  REQUIRE(test[1] == 'm');
  REQUIRE(test[2] == 'f');
}
