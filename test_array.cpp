#include <string>
#include "catch.hpp"
#include <sstream>
#include <utility>

#include "template_array.hpp"
#include "template_array.hpp"  // include guard

TEST_CASE("Empty constructor test") {
  dsc::Array<int> arr;

  REQUIRE(arr.size() == 0);
  REQUIRE(arr.capacity() == 3);
}

TEST_CASE("Size constructor test") {
  dsc::Array<char> arr(8);

  REQUIRE(arr.size() == 0);
  REQUIRE(arr.capacity() == 8);
}

TEST_CASE("Can set and access array elements") {
  dsc::Array<char> char_arr(3);
  char_arr[0] = 'a';
  char_arr[1] = 'b';
  char_arr[2] = 'c';

  REQUIRE(char_arr[0] == 'a');
  REQUIRE(char_arr[1] == 'b');
  REQUIRE(char_arr[2] == 'c');
}

// this case seems redundant with the above
TEST_CASE("Can set and access array elements of ints") {
  dsc::Array<int> int_arr(3);
  int_arr[0] = 122;
  int_arr[1] = 984;
  int_arr[2] = 21;

  REQUIRE(int_arr[0] == 122);
  REQUIRE(int_arr[1] == 984);
  REQUIRE(int_arr[2] == 21);
}

TEST_CASE("Arrays can be copy constructed; deep copy") {
  dsc::Array<int> source(3);
  source[0] = 8;
  source[1] = 9;
  source[2] = 10;

  dsc::Array<int> copy(source);
  REQUIRE(&copy.at(0) != &source.at(0));
}

TEST_CASE("Copy constructed array has correct values") {
  dsc::Array<std::string> source(3);
  source[0] = "Hello, ";
  source[1] = "my name is ";
  source[2] = "Adrian";

  dsc::Array<std::string> copy(
      source);  // better to compare with literals or src contents?
  REQUIRE(copy.at(0) == source.at(0));
  REQUIRE(copy.at(1) == source.at(1));
  REQUIRE(copy.at(2) == source.at(2));

  REQUIRE(copy.size() == source.size());
  REQUIRE(copy.capacity() == source.capacity());
}

TEST_CASE("Copy assignment") {
  dsc::Array<int> source;
  source[0] = 12;
  source[1] = 13;
  source[2] = 14;
  dsc::Array<int> copy = source;

  REQUIRE(copy.at(0) == 12);
  REQUIRE(&copy.at(0) != &source.at(0));

  REQUIRE(copy.at(1) == 13);
  REQUIRE(&copy.at(1) != &source.at(1));

  REQUIRE(copy.at(2) == 14);
  REQUIRE(&copy.at(2) != &source.at(2));
}

TEST_CASE("Copy assignment handles self assignment correctly") {
  dsc::Array<double> arr(4);
  arr[0] = 12.1;
  arr[1] = 12.5;
  arr[2] = 13.3;
  arr[3] = 18.9;

  int* addresses[] = {&arr[0], &arr[1], &arr[2]};
  arr = arr;
  
  REQUIRE(&arr == )

}

TEST_CASE("Arrays can be move constructed") {
  dsc::Array<int> original(6);
  original[0] = 4;
  original[1] = 6;
  original[2] = 7;
  original[3] = 9;
  original[4] = 22;
  original[5] = 54;

  int* addresses[] = {&original.at(0), &original.at(1), &original.at(2),
                      &original.at(3), &original.at(4), &original.at(5)};

  dsc::Array<int> moved = std::move(original);
  REQUIRE(moved.at(0) == 4);
  REQUIRE(moved.at(1) == 6);
  REQUIRE(moved.at(2) == 7);

  REQUIRE(moved.size() == original.size());
  REQUIRE(moved.capacity() == original.capacity());

  REQUIRE(&moved.at(0) == addresses[0]);
  REQUIRE(&moved.at(1) == addresses[1]);
  REQUIRE(&moved.at(2) == addresses[2]);
}

TEST_CASE("Arrays can be move assigned; larger = smaller") {
  dsc::Array<float> smaller(4);
  smaller[0] = 50.5;
  smaller[1] = 51.4;
  smaller[2] = 52.3;
  smaller[3] = 53.2;

  dsc::Array<float> larger(10);
  larger = std::move(smaller);
  ////////////////////////////////////////////////////////////
  REQUIRE(larger.size() == 10);
  REQUIRE(larger.capacity() == )
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

  dsc::Array<int> test3(3);
  test3[0] = 88;
  test3[1] = 17;
  test3[2] = 15;
  REQUIRE(test2 == test3);
}

TEST_CASE("Arrays have correct size") {
  REQUIRE(dsc::Array<int>(5).size() == 0);
  REQUIRE(dsc::Array<std::string>(18).size() == 0);
  REQUIRE(dsc::Array<double>(300).size() == 0);
}

TEST_CASE("Const arrays have correct size") {
  const dsc::Array<char> arr(8);
  REQUIRE(arr.size() == 0);
}

TEST_CASE("Arrays have correct capacity") {
  dsc::Array<int> test(4);
  REQUIRE(test.capacity() == 4);

  dsc::Array<std::string> test2(8);
  REQUIRE(test2.capacity() == 8);
}

TEST_CASE("At() returns correct address") {
  dsc::Array<float> empty(0);
  REQUIRE_THROWS(empty.at(0));

  dsc::Array<char> nonempty(3);
  nonempty[0] = 't';
  nonempty[1] = 'k';
  nonempty[2] = 'j';

  REQUIRE(&nonempty.at(0) == &nonempty[0]);
  REQUIRE(&nonempty.at(1) == &nonempty[1]);
  REQUIRE(&nonempty.at(2) == &nonempty[2]);
}

TEST_CASE("At() throws out of bounds exception for invalid index") {
  dsc::Array<int> test(0);
  REQUIRE_THROWS(test.at(1));
}

TEST_CASE("Front()") {
  dsc::Array<int> test(3);

  test[0] = 13;
  test[1] = 4;
  test[2] = 72;
  REQUIRE(test.front() == 13);  // non empty test
}

TEST_CASE("Back()") {
  dsc::Array<std::string> test(3);

  test[0] = "obnoxious";
  test[1] = "bloviate";
  test[2] = "visceral";
  REQUIRE(test.back() == "visceral");  // non empty test
}

TEST_CASE("Can access data()") {
  dsc::Array<int> test(1);

  test[0] = 41;
  REQUIRE(test.data() != nullptr);
}

TEST_CASE("Reserve()") {
  dsc::Array<int> test(4);
  test.reserve(13);

  REQUIRE(test.capacity() == 13);
}

TEST_CASE("pop_back()") {
  dsc::Array<int> test(6);
  test[0] = 20;
  REQUIRE(test.pop_back() == 20);  // pop list with one element
  REQUIRE(test.size() == 0);

  test[0] = 62;  // pop list with more than one element
  test[1] = 88;
  test[2] = 4;
  REQUIRE(test.pop_back() == 4);
  REQUIRE(test.size() == 2);
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

TEST_CASE("push_back() stress test") {
  dsc::Array<std::size_t> test(3005);

  for (std::size_t i = 0; i < test.size(); ++i) {
    test.push_back(i);
  }

  for (std::size_t i = 0; i < test.size(); ++i) {
    REQUIRE(test.at(i) == i);
  }
}

TEST_CASE("insert()") {
  // insert empty list
  dsc::Array<char> test(6);

  // insert to list of one element
  test.insert('b', 0);
  REQUIRE(test[0] == 'b');

  // insert to list of more than one element
  test.insert('m', 1);
  test.insert('f', 2);

  REQUIRE(test[1] == 'm');
  REQUIRE(test[2] == 'f');
}
