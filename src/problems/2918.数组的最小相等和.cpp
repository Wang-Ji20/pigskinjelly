#include "lc_common.hh"

/*
 * @lc app=leetcode.cn id=2918 lang=cpp
 *
 * [2918] 数组的最小相等和
 *
 * https://leetcode.cn/problems/minimum-equal-sum-of-two-arrays-after-replacing-zeros/description/
 *
 * algorithms
 * Medium (37.22%)
 * Likes:    41
 * Dislikes: 0
 * Total Accepted:    18K
 * Total Submissions: 37.3K
 * Testcase Example:  '[3,2,0,1,0]\n[6,5,0]'
 *
 * 给你两个由正整数和 0 组成的数组 nums1 和 nums2 。
 *
 * 你必须将两个数组中的 所有 0 替换为 严格
 * 正整数，并且满足两个数组中所有元素的和 相等 。
 *
 * 返回 最小 相等和 ，如果无法使两数组相等，则返回 -1 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：nums1 = [3,2,0,1,0], nums2 = [6,5,0]
 * 输出：12
 * 解释：可以按下述方式替换数组中的 0 ：
 * - 用 2 和 4 替换 nums1 中的两个 0 。得到 nums1 = [3,2,2,1,4] 。
 * - 用 1 替换 nums2 中的一个 0 。得到 nums2 = [6,5,1] 。
 * 两个数组的元素和相等，都等于 12 。可以证明这是可以获得的最小相等和。
 *
 *
 * 示例 2：
 *
 *
 * 输入：nums1 = [2,0,2,0], nums2 = [1,4]
 * 输出：-1
 * 解释：无法使两个数组的和相等。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= nums1.length, nums2.length <= 10^5
 * 0 <= nums1[i], nums2[i] <= 10^6
 *
 *
 */

// @lc code=start
class Solution {
public:
  long long
  minSum(vector<int> &nums1, vector<int> &nums2) {
    long long sum_of_nums_1 = 0;
    long long sum_of_nums_2 = 0;
    int free_slot_1 = 0;
    int free_slot_2 = 0;

    // collect statistics
    for (int i : nums1) {
      sum_of_nums_1 += i;
      if (i == 0) {
        free_slot_1++;
      }
    }

    for (int i : nums2) {
      sum_of_nums_2 += i;
      if (i == 0) {
        free_slot_2++;
      }
    }

    long long bigger_sum = 0;
    long long lesser_sum = 0;
    int bigger_slots = 0;
    int lesser_slots = 0;

    if (sum_of_nums_1 < sum_of_nums_2) {
      bigger_sum = sum_of_nums_2;
      bigger_slots = free_slot_2;
      lesser_sum = sum_of_nums_1;
      lesser_slots = free_slot_1;
    } else {
      bigger_sum = sum_of_nums_1;
      bigger_slots = free_slot_1;
      lesser_sum = sum_of_nums_2;
      lesser_slots = free_slot_2;
    }

    if (bigger_sum == lesser_sum) {
      if (bigger_slots > 0 && lesser_slots > 0) {
        return bigger_sum + max(bigger_slots, lesser_slots);
      }
      return (bigger_slots == lesser_slots) ? bigger_sum + bigger_slots : -1;
    }

    if (lesser_slots == 0) {
      return -1;
    }

    if (bigger_slots == 0) {
      if (lesser_sum + lesser_slots > bigger_sum) {
        return -1;
      }
      return bigger_sum;
    }

    return max(bigger_sum + bigger_slots, lesser_sum + lesser_slots);
  }
};
// @lc code=end
