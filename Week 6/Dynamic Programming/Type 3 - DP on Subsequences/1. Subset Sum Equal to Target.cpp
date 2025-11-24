/******************************************************
Problem Statement: Subset Sum Equal to Target

You are given:
→ An array of integers
→ A target value

Return TRUE (1) if there exists **any subset** whose sum
is exactly equal to the target. Otherwise, return FALSE (0).

You may choose each element at most once.

Test Case 1:
Input:
n = 4, target = 11
arr = [2, 3, 7, 8]

Test Case 2:
Input:
n = 5, target = 9
arr = [1, 2, 3, 4, 9]

******************************************************/

#include <bits/stdc++.h>
using namespace std;

/*----------------------------------------------------
1. Recursive Approach
------------------------------------------------------
At index i, we have 2 choices:

→ Pick the element:
    solve(i-1, target - arr[i])

→ Skip the element:
    solve(i-1, target)

Return true if either choice leads to success.

Base Cases:
→ If target == 0 → subset found → return true
→ If i == 0 → check if arr[0] matches target
----------------------------------------------------*/

bool recHelper(int idx, int target, vector<int> &arr)
{
    if (target == 0)
    {
        return true;
    }

    if (idx == 0)
    {
        return arr[0] == target;
    }

    bool notPick = recHelper(idx - 1, target, arr);

    bool pick = false;
    if (arr[idx] <= target)
    {
        pick = recHelper(idx - 1, target - arr[idx], arr);
    }

    return pick || notPick;
}

bool subsetSumRecursion(int n, int target, vector<int> &arr)
{
    return recHelper(n - 1, target, arr);
}

/*----------------------------------------------------
2. Memoization (Top-Down DP)
------------------------------------------------------
Overlapping Subproblems:
solve(i, t) is repeated for different branches.

Use dp[i][t] to store boolean results.
----------------------------------------------------*/

bool memoHelper(int idx, int target, vector<int> &arr,
                vector<vector<int>> &dp)
{
    if (target == 0)
    {
        return true;
    }

    if (idx == 0)
    {
        return arr[0] == target;
    }

    if (dp[idx][target] != -1)
    {
        return dp[idx][target];
    }

    bool notPick = memoHelper(idx - 1, target, arr, dp);

    bool pick = false;
    if (arr[idx] <= target)
    {
        pick = memoHelper(idx - 1, target - arr[idx], arr, dp);
    }

    return dp[idx][target] = (pick || notPick);
}

bool subsetSumMemoization(int n, int target, vector<int> &arr)
{
    vector<vector<int>> dp(n, vector<int>(target + 1, -1));
    return memoHelper(n - 1, target, arr, dp);
}

/*----------------------------------------------------
3. Tabulation (Bottom-Up DP)
------------------------------------------------------
dp[i][t] = true if we can make 't' using arr[0..i]

Base initialization:
dp[i][0] = true  (zero sum is always possible)
dp[0][arr[0]] = true (only if <= target)

Transition:
dp[i][t] = dp[i-1][t] OR
           dp[i-1][t - arr[i]]
----------------------------------------------------*/

bool subsetSumTabulation(int n, int target, vector<int> &arr)
{
    vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

    for (int i = 0; i < n; i++)
    {
        dp[i][0] = true;
    }

    if (arr[0] <= target)
    {
        dp[0][arr[0]] = true;
    }

    for (int i = 1; i < n; i++)
    {
        for (int t = 1; t <= target; t++)
        {
            bool notPick = dp[i - 1][t];

            bool pick = false;
            if (arr[i] <= t)
            {
                pick = dp[i - 1][t - arr[i]];
            }

            dp[i][t] = pick || notPick;
        }
    }

    return dp[n - 1][target];
}

/*----------------------------------------------------
4. Space Optimized Approach
------------------------------------------------------
Use a 1-D dp array:

dp[t] = can we form sum 't'?

Traverse t backwards to avoid overwriting data.
----------------------------------------------------*/

bool subsetSumSpaceOptimized(int n, int target, vector<int> &arr)
{
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    if (arr[0] <= target)
    {
        dp[arr[0]] = true;
    }

    for (int i = 1; i < n; i++)
    {
        for (int t = target; t >= arr[i]; t--)
        {
            dp[t] = dp[t] || dp[t - arr[i]];
        }
    }

    return dp[target];
}

int main()
{
    int n, target;
    cout << "Enter n: " << endl;
    cin >> n;

    vector<int> arr(n);
    cout << "Enter array values: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Enter target: " << endl;
    cin >> target;

    cout << "Using Recursion: " << subsetSumRecursion(n, target, arr) << endl;
    cout << "Using Memoization: " << subsetSumMemoization(n, target, arr) << endl;
    cout << "Using Tabulation: " << subsetSumTabulation(n, target, arr) << endl;
    cout << "Using Space Optimized: " << subsetSumSpaceOptimized(n, target, arr) << endl;

    return 0;
}