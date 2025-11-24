/******************************************************
Problem Statement: Longest Common Substring

Given two strings text1 and text2, return the **length**
of the longest common substring.

A substring must be **contiguous** in both strings.
Unlike subsequence, mismatching resets the count.

Test Case 1:
Input:
text1 = "abcjklp"
text2 = "acjkp"
Output: 3
Explanation: "cjk" or "jkl" length = 3

Test Case 2:
Input:
text1 = "abcdxyz"
text2 = "xyzabcd"
Output: 4
Explanation: "abcd"

******************************************************/

#include <bits/stdc++.h>
using namespace std;

/*----------------------------------------------------
1. Recursive Approach
------------------------------------------------------
We track a running count 'curr'.

Choices:
→ If characters match:
       curr = 1 + solve(i-1, j-1, curr+1)
→ If mismatch:
       curr resets to 0

We also explore:
→ solve(i-1, j, 0)
→ solve(i, j-1, 0)

Final answer is the maximum match found.
----------------------------------------------------*/
int recHelper(int i, int j, int curr, string &s1, string &s2)
{
    if (i < 0 || j < 0)
    {
        return curr;
    }

    int same = curr;
    if (s1[i] == s2[j])
    {
        same = recHelper(i - 1, j - 1, curr + 1, s1, s2);
    }

    int moveLeft = recHelper(i - 1, j, 0, s1, s2);
    int moveUp = recHelper(i, j - 1, 0, s1, s2);

    return max(same, max(moveLeft, moveUp));
}

int longestCommonSubstringRecursion(string &s1, string &s2)
{
    return recHelper((int)s1.size() - 1, (int)s2.size() - 1, 0, s1, s2);
}

/*----------------------------------------------------
2. Memoization Approach
------------------------------------------------------
For substrings, dp[i][j] represents only:
→ Longest common substring ending at i, j

Transition:
if s1[i] == s2[j]: dp[i][j] = 1 + dp[i-1][j-1]
else: dp[i][j] = 0

Final answer = max over all dp cells.
----------------------------------------------------*/
int memoHelper(int i, int j, string &s1, string &s2,
               vector<vector<int>> &dp, int &maxi)
{
    if (i < 0 || j < 0)
    {
        return 0;
    }

    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }

    if (s1[i] == s2[j])
    {
        dp[i][j] = 1 + memoHelper(i - 1, j - 1, s1, s2, dp, maxi);
        maxi = max(maxi, dp[i][j]);
    }
    else
    {
        dp[i][j] = 0;
    }

    memoHelper(i - 1, j, s1, s2, dp, maxi);
    memoHelper(i, j - 1, s1, s2, dp, maxi);

    return dp[i][j];
}

int longestCommonSubstringMemoization(string &s1, string &s2)
{
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n, vector<int>(m, -1));
    int maxi = 0;

    memoHelper(n - 1, m - 1, s1, s2, dp, maxi);

    return maxi;
}

/*----------------------------------------------------
3. Tabulation Approach (Best DP Solution)
------------------------------------------------------
dp[i][j] = LCS string ending at (i, j)

if s1[i-1] == s2[j-1]:
      dp[i][j] = 1 + dp[i-1][j-1]
else:
      dp[i][j] = 0
----------------------------------------------------*/
int longestCommonSubstringTabulation(string &s1, string &s2)
{
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int maxi = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
                maxi = max(maxi, dp[i][j]);
            }
            else
            {
                dp[i][j] = 0;
            }
        }
    }

    return maxi;
}

/*----------------------------------------------------
4. Space Optimized Approach
------------------------------------------------------
We only need:
→ prev[] for dp[i-1][..]
→ curr[] for dp[i][..]

curr[j] = 1 + prev[j-1] if match else 0
----------------------------------------------------*/
int longestCommonSubstringSpaceOptimized(string &s1, string &s2)
{
    int n = s1.size();
    int m = s2.size();

    vector<int> prev(m + 1, 0), curr(m + 1, 0);
    int maxi = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                curr[j] = 1 + prev[j - 1];
                maxi = max(maxi, curr[j]);
            }
            else
            {
                curr[j] = 0;
            }
        }
        prev = curr;
    }

    return maxi;
}

int main()
{
    string s1, s2;

    cout << "Enter text1: " << endl;
    getline(cin, s1);
    if (s1.size() == 0)
    {
        getline(cin, s1);
    }

    cout << "Enter text2: " << endl;
    getline(cin, s2);

    cout << "Using Recursion: " << longestCommonSubstringRecursion(s1, s2) << endl;
    cout << "Using Memoization: " << longestCommonSubstringMemoization(s1, s2) << endl;
    cout << "Using Tabulation: " << longestCommonSubstringTabulation(s1, s2) << endl;
    cout << "Using Space Optimized: " << longestCommonSubstringSpaceOptimized(s1, s2) << endl;

    return 0;
}
