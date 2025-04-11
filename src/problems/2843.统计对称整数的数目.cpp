#include "lc_common.hh"
#include <string>
#include <vector>

/*
 * @lc app=leetcode.cn id=2843 lang=cpp
 *
 * [2843] 统计对称整数的数目
 *
 * https://leetcode.cn/problems/count-symmetric-integers/description/
 *
 * algorithms
 * Easy (71.84%)
 * Likes:    37
 * Dislikes: 0
 * Total Accepted:    22.5K
 * Total Submissions: 29.1K
 * Testcase Example:  '1\n100'
 *
 * 给你两个正整数 low 和 high 。
 *
 * 对于一个由 2 * n 位数字组成的整数 x ，如果其前 n 位数字之和与后 n
 * 位数字之和相等，则认为这个数字是一个对称整数。
 *
 * 返回在 [low, high] 范围内的 对称整数的数目 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：low = 1, high = 100
 * 输出：9
 * 解释：在 1 到 100 范围内共有 9 个对称整数：11、22、33、44、55、66、77、88 和
 * 99 。
 *
 *
 * 示例 2：
 *
 *
 * 输入：low = 1200, high = 1230
 * 输出：4
 * 解释：在 1200 到 1230 范围内共有 4 个对称整数：1203、1212、1221 和 1230 。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= low <= high <= 10^4
 *
 *
 */

// @lc code=start
class Solution {

  bool
  is_sym(int num) {
    string num_str = to_string(num);
    if (num_str.size() % 2 == 1) {
      return false;
    }

    int first_half = 0;
    int i = 0;
    for (; i < num_str.size() / 2; i++) {
      first_half += num_str[i] - '0';
    }

    int second_half = 0;
    for (; i < num_str.size(); i++) {
      second_half += num_str[i] - '0';
    }

    return first_half == second_half;
  }

public:
  int
  countSymmetricIntegers(int low, int high) {
    int answer = 0;
    for (int i = low; i <= high; i++) {
      answer += is_sym(i) ? 1 : 0;
    }
    return answer;
  }

  auto
  dp_version(int low, int high) -> int {
    string low_s = to_string(low);
    string high_s = to_string(high);
    int n = high_s.size();
    int m = n / 2;
    int diff_lh = n - low_s.size();

    vector memo(n, vector(diff_lh + 1, vector<int>(m * 18 + 1, -1)));
    function<int(int, int, int, bool, bool)> dfs;
    dfs = [&](int i, int start, int diff, bool limit_low, bool limit_high)
        -> int {
      if (i == n) {
        return diff == m * 9;
      }

      if (start != -1 && !limit_low && !limit_high &&
          memo[i][start][diff] != -1) {
        return memo[i][start][diff];
      }

      int lo = limit_low && i >= diff_lh ? low_s[i - diff_lh] - '0' : 0;
      int hi = limit_high ? high_s[i] - '0' : 9;

      if (start < 0 && (n - 1) % 2 == 1) {
        return lo > 0 ? 0 : dfs(i + 1, start, diff, true, false);
      }

      int res = 0;
      bool is_left = start < 0 || i < (start + n) / 2;
      for (int d = lo; d <= hi; d++) {
        res += dfs(i + 1,
                   start < 0 && d > 0 ? i : start,
                   diff + (is_left ? d : -d),
                   limit_low && d == lo,
                   limit_high && d == hi);
      }

      if (start != -1 && !limit_low && !limit_high) {
        memo[i][start][diff] = res;
      }

      return res;
    };

    return dfs(0, -1, m * 9, true, true);
  }
};
// @lc code=end
