# <nofmt/join.h>

This is a port of the `fmt::join` function template from the excellent [`{fmt}`](https://fmt.dev/) library to work with
the now-standardized `std::format`. It is based on fmt 7.1.3 -
see [6fa0832d](../../commit/6fa0832decf88e81c6baa0b3aa18fe8dd76d3981) for the main diff.

## Examples

(Abridged from main.cpp, which has a few more.)

```c++
using nofmt::join;

// Plain string concatenation, like python's str.join
TEST_STREQ("1", std::format("{}", join(std::vector<int>{1}, "+")));
TEST_STREQ("1+2", std::format("{}", join(std::vector<int>{1, 2}, "+")));

// Formatting the values before they're concatenated
float floatArray[]{0.3f, 3.14f, 1.618f};
TEST_STREQ("0.30, 3.14, 1.62", std::format("{:.2f}", join(floatArray, ", ")));

// Works with all standard sequence containers
std::list<uint8_t> macAddress{0x0A, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
TEST_STREQ("0A:BB:CC:DD:EE:FF", std::format("{:02X}", join(macAddress, ":")));
```

## License

`nofmt/join.h` is mostly copied from the upstream's `fmt/format.h`, so it retains the license used by `{fmt}` 7.1.3 (a
modified MIT license; see the file for the full text).
