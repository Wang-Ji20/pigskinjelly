#include "lc_common.hh"
#include <functional>
#include <string>

/*
 * @lc app=leetcode.cn id=2999 lang=cpp
 *
 * [2999] 统计强大整数的数目
 *
 * https://leetcode.cn/problems/count-the-number-of-powerful-integers/description/
 *
 * algorithms
 * Hard (42.68%)
 * Likes:    52
 * Dislikes: 0
 * Total Accepted:    8.6K
 * Total Submissions: 19.2K
 * Testcase Example:  '1\n6000\n4\n"124"'
 *
 * 给你三个整数 start ，finish 和 limit 。同时给你一个下标从 0 开始的字符串 s ，表示一个
 * 正 整数。
 *
 * 如果一个 正 整数 x 末尾部分是 s （换句话说，s 是 x 的 后缀），且
 * x 中的每个数位至多是 limit ，那么我们称 x 是 强大的 。
 *
 * 请你返回区间 [start..finish] 内强大整数的 总数目 。
 *
 * 如果一个字符串 x 是 y 中某个下标开始（包括 0 ），到下标为 y.length -
 * 1 结束的子字符串，那么我们称 x 是 y
 * 的一个后缀。比方说，25 是 5125 的一个后缀，但不是 512 的后缀。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：start = 1, finish = 6000, limit = 4, s = "124"
 * 输出：5
 * 解释：区间 [1..6000] 内的强大数字为 124 ，1124 ，2124 ，3124 和 4124
 * 。这些整数的各个数位都 <= 4 且 "124" 是它们的后缀。注意 5124
 * 不是强大整数，因为第一个数位 5 大于 4 。 这个区间内总共只有这 5 个强大整数。
 *
 *
 * 示例 2：
 *
 *
 * 输入：start = 15, finish = 215, limit = 6, s = "10"
 * 输出：2
 * 解释：区间 [15..215] 内的强大整数为 110 和 210 。这些整数的各个数位都 <= 6 且
 * "10" 是它们的后缀。 这个区间总共只有这 2 个强大整数。
 *
 *
 * 示例 3：
 *
 *
 * 输入：start = 1000, finish = 2000, limit = 4, s = "3000"
 * 输出：0
 * 解释：区间 [1000..2000] 内的整数都小于 3000 ，所以 "3000"
 * 不可能是这个区间内任何整数的后缀。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= start <= finish <= 10^15
 * 1 <= limit <= 9
 * 1 <= s.length <= floor(log10(finish)) + 1
 * s 数位中每个数字都小于等于 limit 。
 * s 不包含任何前导 0 。
 *
 *
 */

// @lc code=start
class Solution {
public:
  long long
  numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
    string finish_s = to_string(finish);
    string start_s = to_string(start);
    start_s = string(finish_s.size() - start_s.size(), '0') + start_s;

    int n_digits = finish_s.size();
    vector<long long> memo_(n_digits, -1);
    int s_digits = s.size();
    int diff = n_digits - s_digits;

    function<long long(int, bool, bool)> dfs;
    // next digit is restricted by the former digit ...
    dfs = [&](int searching_digit,
              bool constraint_by_low,
              bool constraint_by_high) -> long long {
      if (searching_digit == n_digits) {
        return 1;
      }

      if (!constraint_by_low && !constraint_by_high &&
          memo_[searching_digit] != -1) {
        return memo_[searching_digit];
      }

      int dfs_lower_bound =
          constraint_by_low ? start_s[searching_digit] - '0' : 0;

      int dfs_upper_bound =
          constraint_by_high ? finish_s[searching_digit] - '0' : 9;

      long long result = 0;
      if (searching_digit < diff) {
        for (int i = dfs_lower_bound; i <= min(limit, dfs_upper_bound); i++) {
          result += dfs(searching_digit + 1,
                        constraint_by_low && i == dfs_lower_bound,
                        constraint_by_high && i == dfs_upper_bound);
        }
      } else {
        auto fixed_num = s[searching_digit - diff] - '0';
        if (fixed_num >= dfs_lower_bound && fixed_num <= dfs_upper_bound) {
          result += dfs(searching_digit + 1,
                        constraint_by_low && fixed_num == dfs_lower_bound,
                        constraint_by_high && fixed_num == dfs_upper_bound);
        }
      }

      if (!constraint_by_low && !constraint_by_high) {
        memo_[searching_digit] = result;
      }

      return result;
    };

    return dfs(0, true, true);
  }
};
// @lc code=end
