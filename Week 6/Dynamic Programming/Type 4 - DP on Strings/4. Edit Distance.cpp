/******************************************************
Problem Statement: Edit Distance (Levenshtein Distance)

Given two strings word1 and word2, return the minimum
number of operations required to convert word1 into word2.

Allowed operations:
1. Insert a character
2. Delete a character
3. Replace a character

Test Case 1:
Input:
word1 = "horse"
word2 = "ros"
Output: 3
Explanation:
horse → rorse (replace 'h' → 'r')
rorse → rose  (delete 'r')
rose  → ros   (delete 'e')

Test Case 2:
Input:
word1 = "intention"
word2 = "execution"
Output: 5

******************************************************/

#include <bits/stdc++.h>
using namespace std;

/*----------------------------------------------------
1. Recursive Approach
------------------------------------------------------
Choices at (i, j):
→ If characters match:
       solve(i-1, j-1)

→ Else, 3 operations when mismatch:
   1. Insert:
        1 + solve(i, j-1)
   2. Delete:
        1 + solve(i-1, j)
   3. Replace:
        1 + solve(i-1, j-1)

Base Cases:
→ If i < 0: need j+1 insertions
→ If j < 0: need i+1 deletions
----------------------------------------------------*/
int recHelper(int i, int j, string &s1, string &s2)
{
    if (i < 0)
    {
        return j + 1;
    }
    if (j < 0)
    {
        return i + 1;
    }

    if (s1[i] == s2[j])
    {
        return recHelper(i - 1, j - 1, s1, s2);
    }

    int insertOp = 1 + recHelper(i, j - 1, s1, s2);
    int deleteOp = 1 + recHelper(i - 1, j, s1, s2);
    int replaceOp = 1 + recHelper(i - 1, j - 1, s1, s2);

    return min({insertOp, deleteOp, replaceOp});
}

int editDistanceRecursion(string &s1, string &s2)
{
    return recHelper(s1.size() - 1, s2.size() - 1, s1, s2);
}

/*----------------------------------------------------
2. Memoization (Top-Down DP)
------------------------------------------------------
dp[i][j] stores the minimum operations needed to convert
s1[0..i] to s2[0..j].

Overlapping occurs for same (i,j) states repeatedly.
----------------------------------------------------*/
int memoHelper(int i, int j, string &s1, string &s2,
               vector<vector<int>> &dp)
{
    if (i < 0)
    {
        return j + 1;
    }
    if (j < 0)
    {
        return i + 1;
    }

    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }

    if (s1[i] == s2[j])
    {
        return dp[i][j] = memoHelper(i - 1, j - 1, s1, s2, dp);
    }

    int insertOp = 1 + memoHelper(i, j - 1, s1, s2, dp);
    int deleteOp = 1 + memoHelper(i - 1, j, s1, s2, dp);
    int replaceOp = 1 + memoHelper(i - 1, j - 1, s1, s2, dp);

    return dp[i][j] = min({insertOp, deleteOp, replaceOp});
}

int editDistanceMemoization(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return memoHelper(n - 1, m - 1, s1, s2, dp);
}

/*----------------------------------------------------
3. Tabulation (Bottom-Up DP)
------------------------------------------------------
dp[i][j] → operations to convert s1 prefix of length i
           to s2 prefix of length j

Initialization:
dp[0][j] = j     (insert j chars)
dp[i][0] = i     (delete i chars)

Transitions:
If match:
    dp[i][j] = dp[i-1][j-1]
Else:
    dp[i][j] = 1 + min(
                     dp[i][j-1],   // insert
                     dp[i-1][j],   // delete
                     dp[i-1][j-1]  // replace
                  )
----------------------------------------------------*/
int editDistanceTabulation(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = i;
    }
    for (int j = 0; j <= m; j++)
    {
        dp[0][j] = j;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = 1 + min({
                                   dp[i][j - 1],    // insert
                                   dp[i - 1][j],    // delete
                                   dp[i - 1][j - 1] // replace
                               });
            }
        }
    }

    return dp[n][m];
}

/*----------------------------------------------------
4. Space Optimized Approach (2 rows)
------------------------------------------------------
We only use prev[] and curr[] of size m+1.

Transitions same as tabulation.
----------------------------------------------------*/
int editDistanceSpaceOptimized(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();

    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int j = 0; j <= m; j++)
    {
        prev[j] = j;
    }

    for (int i = 1; i <= n; i++)
    {
        curr[0] = i;

        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                curr[j] = prev[j - 1];
            }
            else
            {
                curr[j] = 1 + min({
                                  curr[j - 1], // insert
                                  prev[j],     // delete
                                  prev[j - 1]  // replace
                              });
            }
        }

        prev = curr;
    }

    return prev[m];
}

int main()
{
    string s1, s2;

    cout << "Enter word1: " << endl;
    cin >> s1;

    cout << "Enter word2: " << endl;
    cin >> s2;

    cout << "Using Recursion: " << editDistanceRecursion(s1, s2) << endl;
    cout << "Using Memoization: " << editDistanceMemoization(s1, s2) << endl;
    cout << "Using Tabulation: " << editDistanceTabulation(s1, s2) << endl;
    cout << "Using Space Optimized: " << editDistanceSpaceOptimized(s1, s2) << endl;

    return 0;
}