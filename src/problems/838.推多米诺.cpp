#include "lc_common.hh"

/*
 * @lc app=leetcode.cn id=838 lang=cpp
 *
 * [838] 推多米诺
 *
 * https://leetcode.cn/problems/push-dominoes/description/
 *
 * algorithms
 * Medium (55.94%)
 * Likes:    353
 * Dislikes: 0
 * Total Accepted:    47.5K
 * Total Submissions: 82.5K
 * Testcase Example:  '"RR.L"'
 *
 * n
 * 张多米诺骨牌排成一行，将每张多米诺骨牌垂直竖立。在开始时，同时把一些多米诺骨牌向左或向右推。
 *
 * 每过一秒，倒向左边的多米诺骨牌会推动其左侧相邻的多米诺骨牌。同样地，倒向右边的多米诺骨牌也会推动竖立在其右侧的相邻多米诺骨牌。
 *
 * 如果一张垂直竖立的多米诺骨牌的两侧同时有多米诺骨牌倒下时，由于受力平衡，
 * 该骨牌仍然保持不变。
 *
 * 就这个问题而言，我们会认为一张正在倒下的多米诺骨牌不会对其它正在倒下或已经倒下的多米诺骨牌施加额外的力。
 *
 * 给你一个字符串 dominoes 表示这一行多米诺骨牌的初始状态，其中：
 *
 *
 * dominoes[i] = 'L'，表示第 i 张多米诺骨牌被推向左侧，
 * dominoes[i] = 'R'，表示第 i 张多米诺骨牌被推向右侧，
 * dominoes[i] = '.'，表示没有推动第 i 张多米诺骨牌。
 *
 *
 * 返回表示最终状态的字符串。
 *
 *
 * 示例 1：
 *
 *
 * 输入：dominoes = "RR.L"
 * 输出："RR.L"
 * 解释：第一张多米诺骨牌没有给第二张施加额外的力。
 *
 *
 * 示例 2：
 *
 *
 * 输入：dominoes = ".L.R...LR..L.."
 * 输出："LL.RR.LLRRLL.."
 *
 *
 *
 *
 * 提示：
 *
 *
 * n == dominoes.length
 * 1 <= n <= 10^5
 * dominoes[i] 为 'L'、'R' 或 '.'
 *
 *
 */

// @lc code=start
class Solution {
public:
  string
  pushDominoes(string dominoes) {
    int n = dominoes.size();
    string answer(dominoes);

    vector<int> nearest_R(n, -1);

    int R_position = -1;
    for (int i = 0; i < n; i++) {
      if (dominoes[i] == 'R') {
        R_position = i;
      } else if (dominoes[i] == 'L') {
        R_position = -1;
      }
      nearest_R[i] = R_position;
    }

    int L_position = -1;
    for (int i = n - 1; i > -1; i--) {
      if (dominoes[i] == 'L') {
        L_position = i;
        continue;
      }
      if (dominoes[i] == 'R') {
        L_position = -1;
        continue;
      }
      // .
      if (nearest_R[i] == -1 && L_position == -1) {
        continue;
      }

      if (nearest_R[i] == -1) {
        answer[i] = 'L';
        continue;
      }

      if (L_position == -1) {
        answer[i] = 'R';
        continue;
      }

      int diff = (i - nearest_R[i]) - (L_position - i);
      if (diff == 0) {
        continue;
      }

      answer[i] = diff < 0 ? 'R' : 'L';
    }

    return answer;
  }
};
// @lc code=end
