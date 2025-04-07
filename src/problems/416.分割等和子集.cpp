#include "lc_common.hh"

/*
 * @lc app=leetcode.cn id=416 lang=cpp
 *
 * [416] 分割等和子集
 *
 * https://leetcode.cn/problems/partition-equal-subset-sum/description/
 *
 * algorithms
 * Medium (53.31%)
 * Likes:    2306
 * Dislikes: 0
 * Total Accepted:    729.5K
 * Total Submissions: 1.4M
 * Testcase Example:  '[1,5,11,5]'
 *
 * 给你一个 只包含正整数 的 非空 数组 nums
 * 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [1,5,11,5]
 * 输出：true
 * 解释：数组可以分割成 [1, 5, 5] 和 [11] 。
 *
 * 示例 2：
 *
 *
 * 输入：nums = [1,2,3,5]
 * 输出：false
 * 解释：数组不能分割成两个元素和相等的子集。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1
 * 1
 *
 *
 */

// @lc code=start
class Solution {
public:
  bool
  canPartition(vector<int> &nums) {
    return fastestPartition(nums);
  }

  bool
  slowPartition(vector<int> &nums) {
    long long all_sums = accumulate(nums.begin(), nums.end(), 0LL);
    if (all_sums % 2 == 1) {
      return false;
    }

    long long half_sum = all_sums / 2;

    unordered_map<int, unordered_map<long long, bool>> memo;

    function<bool(int, long long)> select_subsets =
        [&](int i, long long accumulated_value) {
          if (memo.contains(i) && memo[i].contains(accumulated_value)) {
            return memo[i][accumulated_value];
          }
          if (accumulated_value == 0) {
            return memo[i][accumulated_value] = true;
          }
          if (i == 0) {
            return memo[i][accumulated_value] = false;
          }
          return memo[i][accumulated_value] =
                     (select_subsets(i - 1, accumulated_value - nums[i]) ||
                      select_subsets(i - 1, accumulated_value));
        };
    return select_subsets(nums.size() - 1, half_sum);
  }

  bool
  fasterPartition(vector<int> &nums) {
    long long all_sum = accumulate(nums.begin(), nums.end(), 0LL);
    if (all_sum % 2 == 1) {
      return false;
    }
    long long half_sum = all_sum / 2;

    vector<vector<bool>> table(nums.size() + 1,
                               vector<bool>(half_sum + 1, false));
    // table[i + 1][j] = table[i][j] || table[i][j - nums[i]]
    // initial table[0][0] = true
    table[0][0] = true;
    for (int i = 0; i < nums.size(); i++) {
      for (int j = 0; j <= half_sum; j++) {
        table[i + 1][j] =
            table[i][j] || (j >= nums[i] && table[i][j - nums[i]]);
      }
    }

    return table[nums.size()][half_sum];
  }

  bool
  fastestPartition(vector<int> &nums) {
    long long all_sum = accumulate(nums.begin(), nums.end(), 0LL);
    if (all_sum % 2 == 1) {
      return false;
    }
    long long half_sum = all_sum / 2;

    vector<bool> table(half_sum + 1, false);
    // table[i + 1][j] = table[i][j] || table[i][j - nums[i]]
    // initial table[0][0] = true
    // only related to the last state of i
    // reverse because latter j depends on earlier j
    table[0] = true;
    for (int num : nums) {
      for (long long j = half_sum; j > -1; j--) {
        table[j] = table[j] || (j >= num && table[j - num]);
      }
    }

    return table[half_sum];
  }
};
// @lc code=end
