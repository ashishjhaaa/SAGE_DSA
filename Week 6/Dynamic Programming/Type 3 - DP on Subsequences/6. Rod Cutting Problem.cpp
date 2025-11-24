/******************************************************
Problem Statement: Rod Cutting Problem

You are given:
→ An integer N representing the length of the rod.
→ A price array where price[i] represents:
   selling price of a rod piece of length (i+1).

You can cut the rod into pieces of any size.
Each length can be used **multiple times**.

Return the **maximum profit** obtainable.

This is a classical **Unbounded Knapsack** problem.

Test Case 1:
Input:
N = 8
price = [1, 5, 8, 9, 10, 17, 17, 20]

Test Case 2:
Input:
N = 5
price = [2, 5, 7, 8, 10]

******************************************************/

#include <bits/stdc++.h>
using namespace std;

/*----------------------------------------------------
1. Recursive Approach
------------------------------------------------------
Equivalent to:

Given rods of lengths [1,2,3,...,N]
with prices price[0..N-1]

At index i:
length = i+1

Choices:
→ PICK:
    price[i] + solve(i, N - length)

→ NOT PICK:
    solve(i-1, N)

Base:
If i == 0:
    return N * price[0]
----------------------------------------------------*/
int recHelper(int idx, int rodLength, vector<int> &price)
{
    if (idx == 0)
    {
        return rodLength * price[0];
    }

    int notPick = recHelper(idx - 1, rodLength, price);

    int pick = INT_MIN;
    int currLength = idx + 1;

    if (currLength <= rodLength)
    {
        pick = price[idx] + recHelper(idx, rodLength - currLength, price);
    }

    return max(pick, notPick);
}

int rodCutRecursion(int n, vector<int> &price)
{
    return recHelper(n - 1, n, price);
}

/*----------------------------------------------------
2. Memoization (Top-Down DP)
------------------------------------------------------
dp[idx][rodLength] stores maximum profit.

Overlapping happens when repeatedly taking same piece.
----------------------------------------------------*/
int memoHelper(int idx, int rodLength, vector<int> &price,
               vector<vector<int>> &dp)
{
    if (idx == 0)
    {
        return rodLength * price[0];
    }

    if (dp[idx][rodLength] != -1)
    {
        return dp[idx][rodLength];
    }

    int notPick = memoHelper(idx - 1, rodLength, price, dp);

    int pick = INT_MIN;
    int currLength = idx + 1;

    if (currLength <= rodLength)
    {
        pick = price[idx] + memoHelper(idx, rodLength - currLength, price, dp);
    }

    return dp[idx][rodLength] = max(pick, notPick);
}

int rodCutMemoization(int n, vector<int> &price)
{
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    return memoHelper(n - 1, n, price, dp);
}

/*----------------------------------------------------
3. Tabulation (Bottom-Up)
------------------------------------------------------
dp[i][len] = max profit using rods[0..i] to make length len

Transition:
dp[i][len] = max(
    dp[i-1][len],
    price[i] + dp[i][len - (i+1)]
)

Base:
dp[0][len] = len * price[0]
----------------------------------------------------*/
int rodCutTabulation(int n, vector<int> &price)
{
    vector<vector<int>> dp(n, vector<int>(n + 1, 0));

    for (int len = 0; len <= n; len++)
    {
        dp[0][len] = len * price[0];
    }

    for (int i = 1; i < n; i++)
    {
        for (int len = 0; len <= n; len++)
        {
            int notPick = dp[i - 1][len];

            int pick = INT_MIN;
            int currLength = i + 1;

            if (currLength <= len)
            {
                pick = price[i] + dp[i][len - currLength];
            }

            dp[i][len] = max(pick, notPick);
        }
    }

    return dp[n - 1][n];
}

/*----------------------------------------------------
4. Space Optimized Approach
------------------------------------------------------
Use 1-D DP array:
dp[len] = max profit for length len

dp[len] = max(dp[len], price[i] + dp[len - (i+1)])
----------------------------------------------------*/
int rodCutSpaceOptimized(int n, vector<int> &price)
{
    vector<int> dp(n + 1, 0);

    for (int len = 0; len <= n; len++)
    {
        dp[len] = len * price[0];
    }

    for (int i = 1; i < n; i++)
    {
        int currLength = i + 1;

        for (int len = currLength; len <= n; len++)
        {
            dp[len] = max(dp[len], price[i] + dp[len - currLength]);
        }
    }

    return dp[n];
}

int main()
{
    int n;

    cout << "Enter N: " << endl;
    cin >> n;

    vector<int> price(n);
    cout << "Enter prices for lengths 1 to N: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> price[i];
    }

    cout << "Using Recursion: " << rodCutRecursion(n, price) << endl;
    cout << "Using Memoization: " << rodCutMemoization(n, price) << endl;
    cout << "Using Tabulation: " << rodCutTabulation(n, price) << endl;
    cout << "Using Space Optimized: " << rodCutSpaceOptimized(n, price) << endl;

    return 0;
}