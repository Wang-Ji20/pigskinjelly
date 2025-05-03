#include "lc_common.hh"
#include <limits>

/*
 * @lc app=leetcode.cn id=1007 lang=cpp
 *
 * [1007] 行相等的最少多米诺旋转
 *
 * https://leetcode.cn/problems/minimum-domino-rotations-for-equal-row/description/
 *
 * algorithms
 * Medium (48.93%)
 * Likes:    155
 * Dislikes: 0
 * Total Accepted:    19.3K
 * Total Submissions: 35.2K
 * Testcase Example:  '[2,1,2,4,2,2]\n[5,2,6,2,3,2]'
 *
 * 在一排多米诺骨牌中，tops[i] 和 bottoms[i] 分别代表第 i
 * 个多米诺骨牌的上半部分和下半部分。（一个多米诺是两个从 1 到 6
 * 的数字同列平铺形成的 —— 该平铺的每一半上都有一个数字。）
 *
 * 我们可以旋转第 i 张多米诺，使得 tops[i] 和 bottoms[i] 的值交换。
 *
 * 返回能使 tops 中所有值或者 bottoms 中所有值都相同的最小旋转次数。
 *
 * 如果无法做到，返回 -1.
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
 * 输出：2
 * 解释：
 * 图一表示：在我们旋转之前， tops 和 bottoms 给出的多米诺牌。
 * 如果我们旋转第二个和第四个多米诺骨牌，我们可以使上面一行中的每个值都等于
 * 2，如图二所示。
 *
 *
 * 示例 2：
 *
 *
 * 输入：tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
 * 输出：-1
 * 解释： 在这种情况下，不可能旋转多米诺牌使一行的值相等。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 2 <= tops.length <= 2 * 10^4
 * bottoms.length == tops.length
 * 1 <= tops[i], bottoms[i] <= 6
 *
 *
 */

// @lc code=start
class Solution {
public:
  int
  minDominoRotations(vector<int> &tops, vector<int> &bottoms) {
    int n = tops.size();

    auto minop_change_to = [&](int target) -> int {
      int tops_changes = 0;
      int bottom_changes = 0;
      for (int i = 0; i < n; i++) {
        int top_value = tops[i];
        int bottom_value = bottoms[i];
        if (top_value == target) {
          if (bottom_value != target) {
            bottom_changes++;
          }
        } else if (bottom_value == target) {
          if (top_value != target) {
            tops_changes++;
          }
        } else {
          return -1;
        }
      }
      return min(tops_changes, bottom_changes);
    };

    int change_to_top_ops = minop_change_to(tops[0]);
    int change_to_bottom_ops = minop_change_to(bottoms[0]);

    if (change_to_top_ops == -1 && change_to_bottom_ops == -1) {
      return -1;
    }
    if (change_to_bottom_ops == -1) {
      return change_to_top_ops;
    }
    if (change_to_top_ops == -1) {
      return change_to_bottom_ops;
    }
    return min(change_to_bottom_ops, change_to_top_ops);
  }
};
// @lc code=end
