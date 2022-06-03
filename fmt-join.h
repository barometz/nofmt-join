/*
Copyright (c) 2012 - present, Victor Zverovich

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

--- Optional exception to the license ---

As an exception, if, as a result of your compiling your source code, portions
of this Software are embedded into a machine-executable object form of such
source code, you may redistribute such embedded portions in such object form
without including the above copyright and permission notices.
*/

#pragma once

#include <format>
#include <ranges>
#include <string_view>

template <typename It, typename Sentinel, typename Char>
struct arg_join {
  It begin;
  Sentinel end;
  std::basic_string_view<Char> sep;

  arg_join(It b, Sentinel e, std::basic_string_view<Char> s)
      : begin(b), end(e), sep(s) {}
};

template <typename It, typename Sentinel, typename Char>
struct std::formatter<arg_join<It, Sentinel, Char>, Char>
    : std::formatter<typename std::iterator_traits<It>::value_type, Char> {
  template <typename FormatContext>
  auto format(const arg_join<It, Sentinel, Char>& value, FormatContext& ctx)
      -> decltype(ctx.out()) {
    using base = formatter<typename std::iterator_traits<It>::value_type, Char>;
    auto it = value.begin;
    auto out = ctx.out();
    if (it != value.end) {
      out = base::format(*it++, ctx);
      while (it != value.end) {
        out = std::copy(value.sep.begin(), value.sep.end(), out);
        ctx.advance_to(out);
        out = base::format(*it++, ctx);
      }
    }
    return out;
  }
};

/**
  Returns an object that formats the iterator range `[begin, end)` with elements
  separated by `sep`.
 */
template <typename It, typename Sentinel>
arg_join<It, Sentinel, char> join(It begin, Sentinel end, std::string_view sep) {
  return {begin, end, sep};
}

template <typename It, typename Sentinel>
arg_join<It, Sentinel, wchar_t> join(It begin, Sentinel end, std::wstring_view sep) {
  return {begin, end, sep};
}

/**
  \rst
  Returns an object that formats `range` with elements separated by `sep`.
  **Example**::
    std::vector<int> v = {1, 2, 3};
    fmt::print("{}", fmt::join(v, ", "));
    // Output: "1, 2, 3"
  ``fmt::join`` applies passed format specifiers to the range elements::
    fmt::print("{:02}", fmt::join(v, ", "));
    // Output: "01, 02, 03"
  \endrst
 */
template <typename Range>
arg_join<std::ranges::iterator_t<Range>, std::ranges::sentinel_t<Range>, char> join(
    Range&& range, std::string_view sep) {
  return join(std::begin(range), std::end(range), sep);
}

template <typename Range>
arg_join<std::ranges::iterator_t<Range>, std::ranges::sentinel_t<Range>, wchar_t> join(
    Range&& range, std::wstring_view sep) {
  return join(std::begin(range), std::end(range), sep);
}
