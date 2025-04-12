#include "lc_common.hh"
#include <utility>

/*
 * @lc app=leetcode.cn id=3272 lang=cpp
 *
 * [3272] 统计好整数的数目
 *
 * https://leetcode.cn/problems/find-the-count-of-good-integers/description/
 *
 * algorithms
 * Hard (52.63%)
 * Likes:    20
 * Dislikes: 0
 * Total Accepted:    4.7K
 * Total Submissions: 6.6K
 * Testcase Example:  '3\n5'
 *
 * 给你两个 正 整数 n 和 k 。
 *
 * 如果一个整数 x 满足以下条件，那么它被称为 k 回文 整数 。
 *
 *
 * x 是一个 回文整数 。
 * x 能被 k 整除。
 *
 *
 * 如果一个整数的数位重新排列后能得到一个 k 回文整数 ，那么我们称这个整数为 好
 * 整数。比方说，k = 2 ，那么 2020 可以重新排列得到 2002 ，2002 是一个 k
 * 回文串，所以 2020 是一个好整数。而 1010 无法重新排列数位得到一个 k 回文整数。
 *
 * 请你返回 n 个数位的整数中，有多少个 好 整数。
 *
 * 注意 ，任何整数在重新排列数位之前或者之后 都不能 有前导 0 。比方说 1010
 * 不能重排列得到 101 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：n = 3, k = 5
 *
 * 输出：27
 *
 * 解释：
 *
 * 部分好整数如下：
 *
 *
 * 551 ，因为它可以重排列得到 515 。
 * 525 ，因为它已经是一个 k 回文整数。
 *
 *
 *
 * 示例 2：
 *
 *
 * 输入：n = 1, k = 4
 *
 * 输出：2
 *
 * 解释：
 *
 * 两个好整数分别是 4 和 8 。
 *
 *
 * 示例 3：
 *
 *
 * 输入：n = 5, k = 6
 *
 * 输出：2468
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= n <= 10
 * 1 <= k <= 9
 *
 *
 */

// @lc code=start
class Solution {
public:
  long long
  countGoodIntegers(int n, int k) {
    vector<long long> factorial(20, 1);
    for (int i = 1; i < 20; i++) {
      factorial[i] = i * factorial[i - 1];
    }

    // when n = 4, half is (4 - 1) / 2 = 1
    // when n = 3, half is (3 + 1) / 2 = 1
    int half_digits = (n - 1) / 2;

    // enumerate all Ns
    // when n = 4, base = 10
    long long base = pow(10LL, half_digits);
    unordered_set<string> visited;
    long long result = 0;

    for (long long i = base; i < 10 * base; i++) {
      string base_s = to_string(i);
      base_s += (n % 2 == 0) ? string(base_s.rbegin(), base_s.rend())
                             : string(base_s.rbegin() + 1, base_s.rend());
      long long i_full_number = stoll(base_s);
      if (i_full_number % k != 0) {
        continue;
      }

      string sorted_copy_base_s = base_s;
      sort(sorted_copy_base_s.begin(), sorted_copy_base_s.end());
      if (visited.contains(sorted_copy_base_s)) {
        continue;
      }
      visited.insert(sorted_copy_base_s);

      map<int, int> num_freq;
      for (char c : sorted_copy_base_s) {
        num_freq[c - '0']++;
      }

      long long subproblem_result = (n - num_freq[0]) * factorial[n - 1];
      for (auto &&v : num_freq) {
        // (n - num_freq[0]) may initialize num_freq[0] as 0
        if (v.second > 0) {
          subproblem_result /= factorial[v.second];
        }
      }

      result += subproblem_result;
    }

    return result;
  }
};
// @lc code=end
