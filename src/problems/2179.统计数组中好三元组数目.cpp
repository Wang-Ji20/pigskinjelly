#include "lc_common.hh"

/*
 * @lc app=leetcode.cn id=2179 lang=cpp
 *
 * [2179] 统计数组中好三元组数目
 *
 * https://leetcode.cn/problems/count-good-triplets-in-an-array/description/
 *
 * algorithms
 * Hard (40.77%)
 * Likes:    97
 * Dislikes: 0
 * Total Accepted:    11.8K
 * Total Submissions: 21.8K
 * Testcase Example:  '[2,0,1,3]\n[0,1,2,3]'
 *
 * 给你两个下标从 0 开始且长度为 n 的整数数组 nums1 和 nums2 ，两者都是 [0, 1,
 * ..., n - 1] 的 排列 。
 *
 * 好三元组 指的是 3 个 互不相同 的值，且它们在数组 nums1
 * 和 nums2 中出现顺序保持一致。换句话说，如果我们将 pos1v 记为值 v 在
 * nums1 中出现的位置，pos2v 为值 v 在 nums2 中的位置，那么一个好三元组定义为 0
 * <= x, y, z <= n - 1 ，且 pos1x < pos1y < pos1z 和 pos2x < pos2y <
 * pos2z 都成立的 (x, y, z) 。
 *
 * 请你返回好三元组的 总数目 。
 *
 *
 *
 * 示例 1：
 *
 * 输入：nums1 = [2,0,1,3], nums2 = [0,1,2,3]
 * 输出：1
 * 解释：
 * 总共有 4 个三元组 (x,y,z) 满足 pos1x < pos1y < pos1z ，分别是 (2,0,1)
 * ，(2,0,3) ，(2,1,3) 和 (0,1,3) 。 这些三元组中，只有 (0,1,3) 满足 pos2x <
 * pos2y < pos2z 。所以只有 1 个好三元组。
 *
 *
 * 示例 2：
 *
 * 输入：nums1 = [4,0,1,3,2], nums2 = [4,1,0,2,3]
 * 输出：4
 * 解释：总共有 4 个好三元组 (4,0,3) ，(4,0,2) ，(4,1,3) 和 (4,1,2) 。
 *
 *
 *
 *
 * 提示：
 *
 *
 * n == nums1.length == nums2.length
 * 3 <= n <= 10^5
 * 0 <= nums1[i], nums2[i] <= n - 1
 * nums1 和 nums2 是 [0, 1, ..., n - 1] 的排列。
 *
 *
 */

// @lc code=start

class ArrayTree {
  vector<int> tree_;

  int
  lower_bit(int x) {
    return x & -x;
  }

public:
  ArrayTree(int n) { tree_.resize(n + 1, 0); }

  void
  update(int index, int delta) {
    for (; index < tree_.size(); index += lower_bit(index)) {
      tree_[index] += delta;
    }
  }

  long long
  query(int end) {
    long long answer = 0;
    for (; end > 0; end -= lower_bit(end)) {
      answer += tree_[end];
    }
    return answer;
  }
};

class Solution {
public:
  long long
  goodTriplets(vector<int> &nums1, vector<int> &nums2) {
    int n = nums1.size();
    vector<int> p(n);

    for (int i = 0; i < n; i++) {
      p[nums1[i]] = i;
    }

    long long ans = 0;
    ArrayTree t(n);
    for (int i = 0; i < n - 1; i++) {
      int y = p[nums2[i]];
      int less = t.query(y);
      ans += 1LL * less * (n - 1 - y - (i - less));
      t.update(y + 1, 1);
    }
    return ans;
  }
};
// @lc code=end
