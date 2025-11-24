/******************************************************
Problem Statement: Best Time to Buy and Sell Stock I

You are given an array `prices` where prices[i] is the
stock price on day i.

You are allowed ONLY one transaction:
→ Buy once
→ Sell once

Return the maximum profit possible. If no profit is
possible, return 0.

Test Case 1:
Input:
n = 6
prices = [7, 1, 5, 3, 6, 4]
Output: 5
Explanation: Buy at 1, sell at 6 → profit = 5

Test Case 2:
Input:
n = 5
prices = [7, 6, 4, 3, 1]
Output: 0
Explanation: Prices decline, so no profit.

******************************************************/

#include <bits/stdc++.h>
using namespace std;

/*----------------------------------------------------
1. Recursive Approach
------------------------------------------------------
State: (idx, canBuy)
→ canBuy == 1: choice to buy or skip
    - buy: -prices[idx] + solve(idx+1, 0)
    - skip: solve(idx+1, 1)
→ canBuy == 0: choice to sell or skip
    - sell: prices[idx] + solve(idx+1, 1)
    - skip: solve(idx+1, 0)

Base: idx == n => 0
Time: exponential (2^n)
----------------------------------------------------*/
int recHelper(int idx, int canBuy, vector<int> &prices)
{
    int n = prices.size();
    if (idx == n)
    {
        return 0;
    }

    if (canBuy)
    {
        int buy = -prices[idx] + recHelper(idx + 1, 0, prices);
        int skip = recHelper(idx + 1, 1, prices);
        return max(buy, skip);
    }
    else
    {
        int sell = prices[idx] + recHelper(idx + 1, 1, prices);
        int skip = recHelper(idx + 1, 0, prices);
        return max(sell, skip);
    }
}

int maxProfitRecursion(vector<int> &prices)
{
    return recHelper(0, 1, prices);
}

/*----------------------------------------------------
2. Memoization (Top-Down)
------------------------------------------------------
dp[idx][canBuy] caches results for states.
Time: O(n)
Space: O(n)
----------------------------------------------------*/

int memoHelper(int idx, int canBuy, vector<int> &prices, vector<vector<int>> &dp)
{
    int n = prices.size();
    if (idx == n)
    {
        return 0;
    }
    if (dp[idx][canBuy] != -1)
    {
        return dp[idx][canBuy];
    }

    if (canBuy)
    {
        int buy = -prices[idx] + memoHelper(idx + 1, 0, prices, dp);
        int skip = memoHelper(idx + 1, 1, prices, dp);
        return dp[idx][canBuy] = max(buy, skip);
    }
    else
    {
        int sell = prices[idx] + memoHelper(idx + 1, 1, prices, dp);
        int skip = memoHelper(idx + 1, 0, prices, dp);
        return dp[idx][canBuy] = max(sell, skip);
    }
}

int maxProfitMemoization(vector<int> &prices)
{
    int n = prices.size();
    if (n == 0)
        return 0;
    vector<vector<int>> dp(n, vector<int>(2, -1));
    return memoHelper(0, 1, prices, dp);
}

/*----------------------------------------------------
3. Tabulation (Bottom-Up)
------------------------------------------------------
Build dp from idx = n down to 0.
dp[idx][canBuy] → best profit from idx.
Time: O(n)
Space: O(n)
----------------------------------------------------*/

int maxProfitTabulation(vector<int> &prices)
{
    int n = prices.size();
    if (n == 0)
    {
        return 0;
    }
    vector<vector<int>> dp(n + 1, vector<int>(2, 0)); // dp[n][*] = 0

    for (int idx = n - 1; idx >= 0; idx--)
    {
        dp[idx][1] = max(-prices[idx] + dp[idx + 1][0], dp[idx + 1][1]);
        dp[idx][0] = max(prices[idx] + dp[idx + 1][1], dp[idx + 1][0]);
    }

    return dp[0][1];
}

/*----------------------------------------------------
4. Space Optimized Approach
------------------------------------------------------
Only need next day's values -> two variables.
Time: O(n)
Space: O(1)
----------------------------------------------------*/
int maxProfitSpaceOptimized(vector<int> &prices)
{
    int n = prices.size();
    if (n == 0)
        return 0;

    int aheadBuy = 0;  // dp[i+1][1]
    int aheadSell = 0; // dp[i+1][0]
    int currBuy = 0;
    int currSell = 0;

    for (int idx = n - 1; idx >= 0; idx--)
    {
        currBuy = max(-prices[idx] + aheadSell, aheadBuy);
        currSell = max(prices[idx] + aheadBuy, aheadSell);

        aheadBuy = currBuy;
        aheadSell = currSell;
    }

    return aheadBuy; // dp[0][1]
}

int main()
{
    int n;
    cout << "Enter n: " << endl;
    cin >> n;

    vector<int> prices(n);
    cout << "Enter prices: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> prices[i];
    }

    cout << "Using Recursion: " << maxProfitRecursion(prices) << endl;
    cout << "Using Memoization: " << maxProfitMemoization(prices) << endl;
    cout << "Using Tabulation: " << maxProfitTabulation(prices) << endl;
    cout << "Using Space Optimized: " << maxProfitSpaceOptimized(prices) << endl;

    return 0;
}
