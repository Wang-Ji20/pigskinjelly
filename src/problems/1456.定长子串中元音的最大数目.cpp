#include "lc_common.hh"

/*
 * @lc app=leetcode.cn id=1456 lang=cpp
 *
 * [1456] 定长子串中元音的最大数目
 *
 * https://leetcode.cn/problems/maximum-number-of-vowels-in-a-substring-of-given-length/description/
 *
 * algorithms
 * Medium (60.34%)
 * Likes:    164
 * Dislikes: 0
 * Total Accepted:    99K
 * Total Submissions: 164.1K
 * Testcase Example:  '"abciiidef"\n3'
 *
 * 给你字符串 s 和整数 k 。
 *
 * 请返回字符串 s 中长度为 k 的单个子字符串中可能包含的最大元音字母数。
 *
 * 英文中的 元音字母 为（a, e, i, o, u）。
 *
 *
 *
 * 示例 1：
 *
 * 输入：s = "abciiidef", k = 3
 * 输出：3
 * 解释：子字符串 "iii" 包含 3 个元音字母。
 *
 *
 * 示例 2：
 *
 * 输入：s = "aeiou", k = 2
 * 输出：2
 * 解释：任意长度为 2 的子字符串都包含 2 个元音字母。
 *
 *
 * 示例 3：
 *
 * 输入：s = "leetcode", k = 3
 * 输出：2
 * 解释："lee"、"eet" 和 "ode" 都包含 2 个元音字母。
 *
 *
 * 示例 4：
 *
 * 输入：s = "rhythms", k = 4
 * 输出：0
 * 解释：字符串 s 中不含任何元音字母。
 *
 *
 * 示例 5：
 *
 * 输入：s = "tryhard", k = 4
 * 输出：1
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= s.length <= 10^5
 * s 由小写英文字母组成
 * 1 <= k <= s.length
 *
 *
 */

// @lc code=start
class Solution {

  bool
  isVowel(char c) {
    static unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    return vowels.contains(c);
  }

public:
  int
  maxVowels(string s, int k) {
    int n = s.size();

    // mutable state
    int start = 0;
    int end = 0;
    int global_answer = 0;
    int local_answer = 0;

    while (end < k) {
      local_answer += isVowel(s[end]) ? 1 : 0;
      end++;
      global_answer = max(global_answer, local_answer);
    }

    while (end < n) {
      if (isVowel(s[start])) {
        local_answer--;
      }
      start++;
      if (isVowel(s[end])) {
        local_answer++;
      }
      end++;
      global_answer = max(global_answer, local_answer);
    }

    return global_answer;
  }
};
// @lc code=end
