/******************************************************
Problem Statement: Partition Equal Subset Sum

You are given an array of positive integers.
Return TRUE (1) if the array can be partitioned into
two subsets such that both subsets have equal sum.
Else return FALSE (0).

This reduces to:
Check if any subset equals target = totalSum / 2.

If totalSum is odd → direct answer is 0.

Test Case 1:
Input:
n = 4
arr = [1, 5, 11, 5]

Test Case 2:
Input:
n = 3
arr = [1, 2, 5]

******************************************************/

#include <bits/stdc++.h>
using namespace std;

/************ RECURSION ON SUBSET SUM **************/
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

bool partitionRecursion(int n, vector<int> &arr)
{
    int sum = accumulate(arr.begin(), arr.end(), 0);

    if (sum % 2 == 1)
    {
        return false;
    }

    int target = sum / 2;
    return recHelper(n - 1, target, arr);
}

/************ MEMOIZATION **************/
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

bool partitionMemoization(int n, vector<int> &arr)
{
    int sum = accumulate(arr.begin(), arr.end(), 0);

    if (sum % 2 == 1)
    {
        return false;
    }

    int target = sum / 2;

    vector<vector<int>> dp(n, vector<int>(target + 1, -1));
    return memoHelper(n - 1, target, arr, dp);
}

/************ TABULATION **************/
bool partitionTabulation(int n, vector<int> &arr)
{
    int sum = accumulate(arr.begin(), arr.end(), 0);

    if (sum % 2 == 1)
    {
        return false;
    }

    int target = sum / 2;

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

/************ SPACE OPTIMIZED DP **************/
bool partitionSpaceOptimized(int n, vector<int> &arr)
{
    int sum = accumulate(arr.begin(), arr.end(), 0);

    if (sum % 2 == 1)
    {
        return false;
    }

    int target = sum / 2;

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
    int n;
    cout << "Enter n: " << endl;
    cin >> n;

    vector<int> arr(n);
    cout << "Enter array values: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Using Recursion: " << partitionRecursion(n, arr) << endl;
    cout << "Using Memoization: " << partitionMemoization(n, arr) << endl;
    cout << "Using Tabulation: " << partitionTabulation(n, arr) << endl;
    cout << "Using Space Optimized: " << partitionSpaceOptimized(n, arr) << endl;

    return 0;
}