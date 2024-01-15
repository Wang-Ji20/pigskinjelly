#include "lc_common.hh"

class Solution {
public:
  auto
  dayOfYear(const string &date) -> int {
    const auto [year, month, day] = split_date(date);
    const auto leap = is_leap_year(year);
    int days = day;
    for (int i = 1; i < month; i++) {
      days += static_cast<int>(i == 2 && leap);
      days += month_days[i];
    }
    return days;
  }

  auto
  split_date(const string &date) -> tuple<int, int, int> {
    return make_tuple(stoi(date.substr(0, 4)),
                      stoi(date.substr(5, 7)),
                      stoi(date.substr(8, 10)));
  }

  inline auto
  is_leap_year(int year) -> bool {
    return year % 100 == 0 ? year % 400 == 0 : year % 4 == 0;
  }

  const std::array<int, 13> month_days = {
    0,
    31,
    28,
    31,
    30,
    31,
    30,
    31,
    31,
    30,
    31,
    30,
    31
  };
};
