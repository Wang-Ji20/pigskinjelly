#include "lc_common.hh"

/*
 * @lc app=leetcode.cn id=2302 lang=cpp
 *
 * [2302] 统计得分小于 K 的子数组数目
 *
 * https://leetcode.cn/problems/count-subarrays-with-score-less-than-k/description/
 *
 * algorithms
 * Hard (58.50%)
 * Likes:    82
 * Dislikes: 0
 * Total Accepted:    25.4K
 * Total Submissions: 42.1K
 * Testcase Example:  '[2,1,4,3,5]\n10'
 *
 * 一个数组的 分数 定义为数组之和 乘以 数组的长度。
 *
 *
 * 比方说，[1, 2, 3, 4, 5] 的分数为 (1 + 2 + 3 + 4 + 5) * 5 = 75 。
 *
 *
 * 给你一个正整数数组 nums 和一个整数 k ，请你返回 nums 中分数 严格小于 k 的 非空整数子数组数目。
 *
 * 子数组 是数组中的一个连续元素序列。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums = [2,1,4,3,5], k = 10
 * 输出：6
 * 解释：
 * 有 6 个子数组的分数小于 10 ：
 * - [2] 分数为 2 * 1 = 2 。
 * - [1] 分数为 1 * 1 = 1 。
 * - [4] 分数为 4 * 1 = 4 。
 * - [3] 分数为 3 * 1 = 3 。
 * - [5] 分数为 5 * 1 = 5 。
 * - [2,1] 分数为 (2 + 1) * 2 = 6 。
 * 注意，子数组 [1,4] 和 [4,3,5] 不符合要求，因为它们的分数分别为 10 和
 * 36，但我们要求子数组的分数严格小于 10 。
 *
 * 示例 2：
 *
 *
 * 输入：nums = [1,1,1], k = 5
 * 输出：5
 * 解释：
 * 除了 [1,1,1] 以外每个子数组分数都小于 5 。
 * [1,1,1] 分数为 (1 + 1 + 1) * 3 = 9 ，大于 5 。
 * 所以总共有 5 个子数组得分小于 5 。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^5
 * 1 <= k <= 10^15
 *
 *
 */

// @lc code=start
class Solution {
public:
  long long
  countSubarrays(vector<int> &nums, long long k) {
    int n = nums.size();
    long long answer = 0;

    int right = 0;
    int left = 0;
    long long sum = 0;

    for (; right < n; right++) {
      sum += nums[right];
      while (sum * (right - left + 1) >= k) {
        sum -= nums[left];
        left++;
      }
      answer += right - left + 1;
    }

    return answer;
  }

  long long
  countSubarrays_prefix(vector<int> &nums, long long k) {
    int n = nums.size();
    long long answer = 0;

    // for quick calculation of subarray
    vector<long long> prefix_sum(nums.size() + 1, 0);
    for (int i = 0; i < nums.size(); i++) {
      prefix_sum[i + 1] = nums[i] + prefix_sum[i];
    }

    // include l, exclude r
    auto calculate_sum = [&](int l, int r) -> long long {
      return prefix_sum[r] - prefix_sum[l];
    };

    for (int left = 0; left < n; left++) {
      for (int right = left + 1; right <= n; right++) {
        if (calculate_sum(left, right) * (right - left) < k) {
          answer++;
        }
      }
    }

    return answer;
  }
};
// @lc code=end
