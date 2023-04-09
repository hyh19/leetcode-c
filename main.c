#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct ListNode {
    int val;
    struct ListNode *next;
};

int left;  // 已使用的『左括号』数量
int right; // 已使用的『右括号』数量
char *path;   // 取 '(', ')' 为元素
int pathSize;
char **ans;
int ansSize;
int ansCapacity;

void backtrack(int n) {
    // 对于一个「合法」的括号字符串组合 p，必然对于任何 0 <= i < len(p) 都有：
    // 子串 p[0..i] 中左括号的数量都大于或等于右括号的数量
    if (left < right || left > n) {
        return;
    }
    // 一个「合法」括号组合的左括号数量一定等于右括号数量
    if (left == n && right == n) {
        char *res = calloc(2 * n + 1, sizeof(char));
        strcpy(res, path);
        if (ansSize == ansCapacity) {
            ansCapacity *= 2;
            ans = realloc(ans, sizeof(char *) * ansCapacity);

        }
        ans[ansSize++] = res;
        return;
    }
    // edge = 取 '(', ')' 为值
    // 使用『左括号』
    path[pathSize++] = '(';
    ++left;
    backtrack(n);
    --pathSize;
    --left;
    // 使用『右括号』
    path[pathSize++] = ')';
    ++right;
    backtrack(n);
    --pathSize;
    --right;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **generateParenthesis(int n, int *returnSize) {
    path = calloc(2 * n + 1, sizeof(char));
    ansCapacity = 8;
    ans = malloc(sizeof(char *) * ansCapacity);
    ansSize = pathSize = 0;
    left = right = 0;
    backtrack(n);
    *returnSize = ansSize;
    free(path);
    return ans;
}
// https://leetcode.cn/submissions/detail/391307976/