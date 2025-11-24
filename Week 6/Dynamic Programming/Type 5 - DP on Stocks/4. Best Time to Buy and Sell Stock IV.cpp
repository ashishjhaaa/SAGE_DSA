/******************************************************
Problem Statement: Best Time to Buy and Sell Stock IV

You are given:
→ An integer K (maximum number of transactions allowed)
→ An array prices[] of length n

Each transaction = 1 BUY + 1 SELL.
You must sell before buying again.

Return the maximum profit possible.

Test Case 1:
Input:
n = 6, K = 2
prices = [3,3,5,0,0,3,1,4]
Output: 6

Test Case 2:
Input:
n = 6, K = 3
prices = [2,4,1,7,5,3]
Output: 8
Explanation:
Buy at 2 sell at 4 → 2
Buy at 1 sell at 7 → 6
Total = 8

******************************************************/

#include <bits/stdc++.h>
using namespace std;

/*----------------------------------------------------
1. Recursive Approach
------------------------------------------------------
State: (idx, buy, cap)

IF buy == 1:
    Two choices:
        • Buy  → -prices[idx] + solve(idx+1, 0, cap)
        • Skip → solve(idx+1, 1, cap)

ELSE (must sell):
    Two choices:
        • Sell → prices[idx] + solve(idx+1, 1, cap-1)
        • Skip → solve(idx+1, 0, cap)

Base:
→ If idx == n or cap == 0 → profit = 0
----------------------------------------------------*/
int recHelper(int idx, int buy, int cap, vector<int> &prices)
{
    int n = prices.size();

    if (idx == n || cap == 0)
    {
        return 0;
    }

    if (buy)
    {
        int take = -prices[idx] + recHelper(idx + 1, 0, cap, prices);
        int skip = recHelper(idx + 1, 1, cap, prices);
        return max(take, skip);
    }
    else
    {
        int take = prices[idx] + recHelper(idx + 1, 1, cap - 1, prices);
        int skip = recHelper(idx + 1, 0, cap, prices);
        return max(take, skip);
    }
}

int stockIVRecursion(vector<int> &prices, int K)
{
    return recHelper(0, 1, K, prices);
}

/*----------------------------------------------------
2. Memoization
dp[idx][buy][cap]
----------------------------------------------------*/
int memoHelper(int idx, int buy, int cap, vector<int> &prices,
               vector<vector<vector<int>>> &dp)
{
    int n = prices.size();

    if (idx == n || cap == 0)
    {
        return 0;
    }

    if (dp[idx][buy][cap] != -1)
    {
        return dp[idx][buy][cap];
    }

    if (buy)
    {
        int take = -prices[idx] + memoHelper(idx + 1, 0, cap, prices, dp);
        int skip = memoHelper(idx + 1, 1, cap, prices, dp);
        return dp[idx][buy][cap] = max(take, skip);
    }
    else
    {
        int take = prices[idx] + memoHelper(idx + 1, 1, cap - 1, prices, dp);
        int skip = memoHelper(idx + 1, 0, cap, prices, dp);
        return dp[idx][buy][cap] = max(take, skip);
    }
}

int stockIVMemoization(vector<int> &prices, int K)
{
    int n = prices.size();

    vector<vector<vector<int>>> dp(
        n, vector<vector<int>>(2, vector<int>(K + 1, -1)));

    return memoHelper(0, 1, K, prices, dp);
}

/*----------------------------------------------------
3. Tabulation
------------------------------------------------------
dp[idx][buy][cap]

Bottom-up form.
----------------------------------------------------*/
int stockIVTabulation(vector<int> &prices, int K)
{
    int n = prices.size();
    vector<vector<vector<int>>> dp(
        n + 1, vector<vector<int>>(2, vector<int>(K + 1, 0)));

    for (int idx = n - 1; idx >= 0; idx--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            for (int cap = 1; cap <= K; cap++)
            {
                if (buy)
                {
                    dp[idx][buy][cap] = max(
                        -prices[idx] + dp[idx + 1][0][cap],
                        dp[idx + 1][1][cap]);
                }
                else
                {
                    dp[idx][buy][cap] = max(
                        prices[idx] + dp[idx + 1][1][cap - 1],
                        dp[idx + 1][0][cap]);
                }
            }
        }
    }

    return dp[0][1][K];
}

/*----------------------------------------------------
4. Space Optimized
------------------------------------------------------
We keep only "ahead" and "curr" 2×(K+1) matrices.
----------------------------------------------------*/
int stockIVSpaceOptimized(vector<int> &prices, int K)
{
    int n = prices.size();

    vector<vector<int>> ahead(2, vector<int>(K + 1, 0));
    vector<vector<int>> curr(2, vector<int>(K + 1, 0));

    for (int idx = n - 1; idx >= 0; idx--)
    {
        for (int buy = 0; buy <= 1; buy++)
        {
            for (int cap = 1; cap <= K; cap++)
            {
                if (buy)
                {
                    curr[buy][cap] = max(
                        -prices[idx] + ahead[0][cap],
                        ahead[1][cap]);
                }
                else
                {
                    curr[buy][cap] = max(
                        prices[idx] + ahead[1][cap - 1],
                        ahead[0][cap]);
                }
            }
        }

        ahead = curr;
    }

    return ahead[1][K];
}

int main()
{
    int n, K;
    cout << "Enter n: " << endl;
    cin >> n;

    vector<int> prices(n);
    cout << "Enter prices: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> prices[i];
    }

    cout << "Enter K (max transactions): " << endl;
    cin >> K;

    cout << "Using Recursion: " << stockIVRecursion(prices, K) << endl;
    cout << "Using Memoization: " << stockIVMemoization(prices, K) << endl;
    cout << "Using Tabulation: " << stockIVTabulation(prices, K) << endl;
    cout << "Using Space Optimized: " << stockIVSpaceOptimized(prices, K) << endl;

    return 0;
}
