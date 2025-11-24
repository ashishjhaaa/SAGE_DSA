/******************************************************
Problem Statement: Longest Common Subsequence (LCS)

Given two strings text1 and text2, return the **length**
of their longest common subsequence.

A subsequence follows the original order but does not
need to be contiguous.

Test Case 1:
Input:
text1 = "abcde"
text2 = "ace"
Output: 3
LCS = "ace"

Test Case 2:
Input:
text1 = "aggtab"
text2 = "gxtxayb"
Output: 4
LCS = "gtab"

******************************************************/

#include <bits/stdc++.h>
using namespace std;

/*----------------------------------------------------
1. Recursive Approach
------------------------------------------------------
Choices:
→ If s1[i] == s2[j]:
       1 + solve(i-1, j-1)
→ Else:
       max(solve(i-1, j), solve(i, j-1))

Base:
→ If i < 0 or j < 0 → return 0
----------------------------------------------------*/
int recHelper(int i, int j, string &s1, string &s2)
{
    if (i < 0 || j < 0)
    {
        return 0;
    }

    if (s1[i] == s2[j])
    {
        return 1 + recHelper(i - 1, j - 1, s1, s2);
    }

    int move1 = recHelper(i - 1, j, s1, s2);
    int move2 = recHelper(i, j - 1, s1, s2);

    return max(move1, move2);
}

int lcsRecursion(string &s1, string &s2)
{
    return recHelper(s1.size() - 1, s2.size() - 1, s1, s2);
}

/*----------------------------------------------------
2. Memoization (Top-Down DP)
------------------------------------------------------
dp[i][j] = LCS length for prefixes ending at i, j

We store results to avoid recomputation.
----------------------------------------------------*/
int memoHelper(int i, int j, string &s1, string &s2,
               vector<vector<int>> &dp)
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
        return dp[i][j] = 1 + memoHelper(i - 1, j - 1, s1, s2, dp);
    }

    int move1 = memoHelper(i - 1, j, s1, s2, dp);
    int move2 = memoHelper(i, j - 1, s1, s2, dp);

    return dp[i][j] = max(move1, move2);
}

int lcsMemoization(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return memoHelper(n - 1, m - 1, s1, s2, dp);
}

/*----------------------------------------------------
3. Tabulation (Bottom-Up DP)
------------------------------------------------------
dp[i][j] = LCS of s1[0..i-1] & s2[0..j-1]

If match:
    1 + dp[i-1][j-1]
Else:
    max(dp[i-1][j], dp[i][j-1])
----------------------------------------------------*/

int lcsTabulation(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[n][m];
}

/*----------------------------------------------------
4. Space Optimized Approach (2-row DP)
------------------------------------------------------
We only keep prev[] and curr[]

curr[j] =
    if match → 1 + prev[j-1]
    else → max(prev[j], curr[j-1])
----------------------------------------------------*/

int lcsSpaceOptimized(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                curr[j] = 1 + prev[j - 1];
            }
            else
            {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        prev = curr;
    }

    return prev[m];
}

int main()
{
    string s1, s2;

    cout << "Enter text1: " << endl;
    cin >> s1;
    cout << "Enter text2: " << endl;
    cin >> s2;

    cout << "Using Recursion: " << lcsRecursion(s1, s2) << endl;
    cout << "Using Memoization: " << lcsMemoization(s1, s2) << endl;
    cout << "Using Tabulation: " << lcsTabulation(s1, s2) << endl;
    cout << "Using Space Optimized: " << lcsSpaceOptimized(s1, s2) << endl;

    return 0;
}
