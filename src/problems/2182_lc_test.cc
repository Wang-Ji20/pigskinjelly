// xyutfpopdynbadwtvmxiemmu

#include "lc_common.hh"
#include "gtest/gtest.h"


class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        for (auto c: s) {
            memo_chars[c - 'a']++;
        }

        int largest_idx = find_next_char_idx(25);
        int second_largest_idx = find_next_char_idx(largest_idx - 1);
        string ans;
        ans.reserve(s.size());
        while (largest_idx != NOT_FOUND) {
            for (int repeat = 0; memo_chars[largest_idx] > 0 && repeat < repeatLimit; repeat++) {
                ans += 'a' + largest_idx;
                memo_chars[largest_idx]--;
            }
            if (memo_chars[largest_idx] == 0) {
                largest_idx = second_largest_idx;
                second_largest_idx = find_next_char_idx(second_largest_idx - 1);
                continue;
            }
            if (second_largest_idx == NOT_FOUND || memo_chars[second_largest_idx] == 0) {
                break;
            }
            memo_chars[second_largest_idx]--;
            ans += 'a' + second_largest_idx;
        }
        return ans;
    }

    constexpr static int NOT_FOUND = -1;

    // -1 => not found
    int find_next_char_idx(int idx) {
        while (idx > -1 && memo_chars[idx] == 0) {
            idx--;
        }
        return idx;
    }

private:
    array<int, 26> memo_chars = {0};
};

TEST(test_suite_name, test_name) {
    Solution s;
    cout << s.repeatLimitedString("xyutfpopdynbadwtvmxiemmu", 1);
}
