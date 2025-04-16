#include "lc_common.hh"

/*
 * @lc app=leetcode.cn id=307 lang=cpp
 *
 * [307] 区域和检索 - 数组可修改
 *
 * https://leetcode.cn/problems/range-sum-query-mutable/description/
 *
 * algorithms
 * Medium (53.91%)
 * Likes:    765
 * Dislikes: 0
 * Total Accepted:    97.1K
 * Total Submissions: 180K
 * Testcase Example:
 * '["NumArray","sumRange","update","sumRange"]\n[[[1,3,5]],[0,2],[1,2],[0,2]]'
 *
 * 给你一个数组 nums ，请你完成两类查询。
 *
 *
 * 其中一类查询要求 更新 数组 nums 下标对应的值
 * 另一类查询要求返回数组 nums 中索引 left 和索引 right 之间（ 包含 ）的nums元素的
 * 和 ，其中 left <= right
 *
 *
 * 实现 NumArray 类：
 *
 *
 * NumArray(int[] nums) 用整数数组 nums 初始化对象
 * void update(int index, int val) 将 nums[index] 的值 更新 为 val
 * int sumRange(int left, int right)
 * 返回数组 nums 中索引 left 和索引 right 之间（ 包含 ）的nums元素的
 * 和 （即，nums[left] + nums[left + 1], ..., nums[right]）
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：
 * ["NumArray", "sumRange", "update", "sumRange"]
 * [[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
 * 输出：
 * [null, 9, null, 8]
 *
 * 解释：
 * NumArray numArray = new NumArray([1, 3, 5]);
 * numArray.sumRange(0, 2); // 返回 1 + 3 + 5 = 9
 * numArray.update(1, 2);   // nums = [1,2,5]
 * numArray.sumRange(0, 2); // 返回 1 + 2 + 5 = 8
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= nums.length <= 3 * 10^4
 * -100 <= nums[i] <= 100
 * 0 <= index < nums.length
 * -100 <= val <= 100
 * 0 <= left <= right < nums.length
 * 调用 update 和 sumRange 方法次数不大于 3 * 10^4 
 *
 *
 */

// @lc code=start
class NumArray {
  vector<int> numbers_;
  vector<int> tree_;

  static int
  lower_bit(int x) {
    return x & -x;
  }

  int
  sum_prefix(int i) {
    int answer = 0;
    for (; i > 0; i -= lower_bit(i)) {
      answer += tree_[i];
    }
    return answer;
  }

public:
  NumArray(vector<int> &nums) {
    // copy
    numbers_ = nums;
    tree_.resize(nums.size() + 1, 0);
    for (int i = 1; i <= nums.size(); i++) {
      tree_[i] += nums[i - 1];
      int next = i + lower_bit(i);
      if (next < tree_.size()) {
        tree_[next] += tree_[i];
      }
    }
  }

  void
  update(int index, int val) {
    int delta = val - numbers_[index];
    numbers_[index] = val;
    for (int i = index + 1; i < tree_.size(); i += lower_bit(i)) {
      tree_[i] += delta;
    }
  }

  int
  sumRange(int left, int right) {
    return sum_prefix(right + 1) - sum_prefix(left);
  }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
// @lc code=end
