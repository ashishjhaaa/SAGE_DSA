/******************************************************
Problem Statement: Count Subsets With Sum = K

You are given:
→ An array of positive integers
→ A target integer K

Return the number of subsets whose sum is exactly K.

Unlike normal subset sum (true/false), here we COUNT
all possible subsets.

Test Case 1:
Input:
n = 4, k = 5
arr = [1, 2, 3, 2]

Test Case 2:
Input:
n = 5, k = 3
arr = [1, 1, 1, 1, 1]

******************************************************/

#include <bits/stdc++.h>
using namespace std;

/*----------------------------------------------------
1. Recursive Approach
------------------------------------------------------
At index i, 2 choices:

→ Pick element:
    count(i-1, target - arr[i])

→ Skip element:
    count(i-1, target)

Total subsets = pick + notPick

Base Cases:
→ If target == 0 → 1 valid subset found
→ If idx == 0 → check if arr[0] == target
----------------------------------------------------*/

int recHelper(int idx, int target, vector<int> &arr)
{
    if (target == 0)
    {
        return 1;
    }

    if (idx == 0)
    {
        return arr[0] == target ? 1 : 0;
    }

    int notPick = recHelper(idx - 1, target, arr);

    int pick = 0;
    if (arr[idx] <= target)
    {
        pick = recHelper(idx - 1, target - arr[idx], arr);
    }

    return pick + notPick;
}

int countRecursion(int n, int target, vector<int> &arr)
{
    return recHelper(n - 1, target, arr);
}

/*----------------------------------------------------
2. Memoization (Top-Down DP)
------------------------------------------------------
dp[idx][target] will store number of subsets.

Overlapping subproblems:
(i, t) appears repeatedly in recursion branches.
----------------------------------------------------*/

int memoHelper(int idx, int target, vector<int> &arr,
               vector<vector<int>> &dp)
{
    if (target == 0)
    {
        return 1;
    }

    if (idx == 0)
    {
        return arr[0] == target ? 1 : 0;
    }

    if (dp[idx][target] != -1)
    {
        return dp[idx][target];
    }

    int notPick = memoHelper(idx - 1, target, arr, dp);

    int pick = 0;
    if (arr[idx] <= target)
    {
        pick = memoHelper(idx - 1, target - arr[idx], arr, dp);
    }

    return dp[idx][target] = (pick + notPick);
}

int countMemoization(int n, int target, vector<int> &arr)
{
    vector<vector<int>> dp(n, vector<int>(target + 1, -1));
    return memoHelper(n - 1, target, arr, dp);
}

/*----------------------------------------------------
3. Tabulation (Bottom-Up DP)
------------------------------------------------------
dp[i][t] = number of subsets from arr[0..i] with sum t

Initialization:
dp[i][0] = 1       (empty subset)
dp[0][arr[0]] = 1  (if arr[0] <= target)

Transition:
dp[i][t] = dp[i-1][t] + dp[i-1][t - arr[i]]
----------------------------------------------------*/
int countTabulation(int n, int target, vector<int> &arr)
{
    vector<vector<int>> dp(n, vector<int>(target + 1, 0));

    for (int i = 0; i < n; i++)
    {
        dp[i][0] = 1;
    }

    if (arr[0] <= target)
    {
        dp[0][arr[0]] = 1;
    }

    for (int i = 1; i < n; i++)
    {
        for (int t = 0; t <= target; t++)
        {
            int notPick = dp[i - 1][t];

            int pick = 0;
            if (arr[i] <= t)
            {
                pick = dp[i - 1][t - arr[i]];
            }

            dp[i][t] = pick + notPick;
        }
    }

    return dp[n - 1][target];
}

/*----------------------------------------------------
4. Space Optimized Approach
------------------------------------------------------
1-D dp array — *counting version*.

Backward loop to avoid overwriting previous row:
dp[t] += dp[t - arr[i]]
----------------------------------------------------*/
int countSpaceOptimized(int n, int target, vector<int> &arr)
{
    vector<int> dp(target + 1, 0);

    dp[0] = 1;

    if (arr[0] <= target)
    {
        dp[arr[0]] += 1;
    }

    for (int i = 1; i < n; i++)
    {
        for (int t = target; t >= arr[i]; t--)
        {
            dp[t] += dp[t - arr[i]];
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

    cout << "Using Recursion: " << countRecursion(n, target, arr) << endl;
    cout << "Using Memoization: " << countMemoization(n, target, arr) << endl;
    cout << "Using Tabulation: " << countTabulation(n, target, arr) << endl;
    cout << "Using Space Optimized: " << countSpaceOptimized(n, target, arr) << endl;

    return 0;
}