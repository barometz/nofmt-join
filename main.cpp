#include "nofmt/join.h"

#include <array>
#include <iostream>
#include <list>

bool test_string_equal(std::string_view expected,
                       std::string_view expression,
                       std::string_view actual) {
  if (const auto expectedEval = (expected); actual != expectedEval) {
    std::cerr << "Test failure:" << std::endl;
    std::cerr << "  Expression: " << expression << std::endl;
    std::cerr << "  Expected:   " << expectedEval << std::endl;
    std::cerr << "  Actual:     " << actual << std::endl;
    return false;
  }
  return true;
}

#define TEST_STREQ(expected, expression) \
  test_string_equal((expected), #expression, (expression))

int main() {
  bool result = true;

  using nofmt::join;

  // Plain string concatenation, like python's str.join
  result &= TEST_STREQ("", std::format("{}", join(std::vector<int>{}, "+")));
  result &= TEST_STREQ("1", std::format("{}", join(std::vector<int>{1}, "+")));
  result &=
      TEST_STREQ("1+2", std::format("{}", join(std::vector<int>{1, 2}, "+")));

  // Formatting the values before they're concatenated
  const float floatArray[]{0.3f, 3.14f, 1.618f};
  result &= TEST_STREQ("0.30, 3.14, 1.62",
                       std::format("{:.2f}", join(floatArray, ", ")));

  // Works with all standard sequence containers
  const std::array<uint8_t, 6> macAddress{0x0A, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
  result &= TEST_STREQ("0A:BB:CC:DD:EE:FF",
                       std::format("{:02X}", join(macAddress, ":")));
  const std::list<std::string> messages{"hello", "world", "!"};
  result &=
      TEST_STREQ("hello\nworld\n!", std::format("{}", join(messages, "\n")));

  // As well as iterator pairs.
  const std::vector<int> someValues{10, 20, 30, 40, 50};
  result &= TEST_STREQ(
      "40, 50",
      std::format("{}", join(someValues.begin() + 3, someValues.end(), ", ")));

  return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
