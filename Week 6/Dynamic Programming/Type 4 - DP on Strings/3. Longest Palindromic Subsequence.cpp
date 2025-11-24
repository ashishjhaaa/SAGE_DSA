/******************************************************
Problem Statement: Longest Palindromic Subsequence (LPS)

You are given a string s.
Return the length of the **longest palindromic subsequence**.

A subsequence follows original index order but does not
need to be contiguous.

Key Relation:
LPS(s) = LCS(s, reverse(s))

Test Case 1:
Input:
s = "bbbab"
Output: 4
Explanation: LPS = "bbbb"

Test Case 2:
Input:
s = "agbdba"
Output: 5
Explanation: LPS = "abdba"

******************************************************/

#include <bits/stdc++.h>
using namespace std;

/*----------------------------------------------------
1. Recursive Approach
------------------------------------------------------
Let s1 = s, s2 = reverse(s)

Choices (LCS logic):
→ If s1[i] == s2[j]:
      1 + solve(i-1, j-1)
→ Else:
      max(solve(i-1, j), solve(i, j-1))

Base:
→ If i < 0 or j < 0 → return 0
----------------------------------------------------*/

int recHelper(int i, int j, string &a, string &b)
{
    if (i < 0 || j < 0)
    {
        return 0;
    }

    if (a[i] == b[j])
    {
        return 1 + recHelper(i - 1, j - 1, a, b);
    }

    int left = recHelper(i - 1, j, a, b);
    int right = recHelper(i, j - 1, a, b);

    return max(left, right);
}

int lpsRecursion(string &s)
{
    string t = s;
    reverse(t.begin(), t.end());
    return recHelper(s.size() - 1, t.size() - 1, s, t);
}

/*----------------------------------------------------
2. Memoization Approach
------------------------------------------------------
We use dp[i][j] to store LPS length (same as LCS).
----------------------------------------------------*/
int memoHelper(int i, int j, string &a, string &b,
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

    if (a[i] == b[j])
    {
        return dp[i][j] = 1 + memoHelper(i - 1, j - 1, a, b, dp);
    }

    int left = memoHelper(i - 1, j, a, b, dp);
    int right = memoHelper(i, j - 1, a, b, dp);

    return dp[i][j] = max(left, right);
}

int lpsMemoization(string &s)
{
    string t = s;
    reverse(t.begin(), t.end());

    int n = s.size();
    int m = t.size();

    vector<vector<int>> dp(n, vector<int>(m, -1));
    return memoHelper(n - 1, m - 1, s, t, dp);
}

/*----------------------------------------------------
3. Tabulation Approach
------------------------------------------------------
Classic LCS table:
dp[i][j] = LPS for s1[0..i-1], s2[0..j-1]

Transitions:
→ If match: 1 + dp[i-1][j-1]
→ Else:     max(dp[i-1][j], dp[i][j-1])
----------------------------------------------------*/

int lpsTabulation(string &s)
{
    string t = s;
    reverse(t.begin(), t.end());

    int n = s.size();
    int m = t.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
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
4. Space Optimized Approach (2 rows)
------------------------------------------------------
prev[j], curr[j] approach:
If match:
    curr[j] = 1 + prev[j-1]
Else:
    curr[j] = max(prev[j], curr[j-1])
----------------------------------------------------*/

int lpsSpaceOptimized(string &s)
{
    string t = s;
    reverse(t.begin(), t.end());

    int n = s.size();
    vector<int> prev(n + 1, 0), curr(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (s[i - 1] == t[j - 1])
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

    return prev[n];
}

int main()
{
    string s;

    cout << "Enter string: " << endl;
    getline(cin, s);
    if (s.size() == 0)
    {
        getline(cin, s);
    }

    cout << "Using Recursion: " << lpsRecursion(s) << endl;
    cout << "Using Memoization: " << lpsMemoization(s) << endl;
    cout << "Using Tabulation: " << lpsTabulation(s) << endl;
    cout << "Using Space Optimized: " << lpsSpaceOptimized(s) << endl;

    return 0;
}
