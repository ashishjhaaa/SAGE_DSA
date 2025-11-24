/******************************************************
Problem Statement: Best Time to Buy and Sell Stock III

You are given prices[], where prices[i] is the stock
price on day i.

You are allowed **at most 2 transactions**.
Each transaction = 1 buy + 1 sell.
You must sell before buying again.

Return the **maximum profit** possible.

Test Case 1:
Input:
n = 6
prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation:
Buy at 0, sell at 3 (profit 3)
Buy at 1, sell at 4 (profit 3)
Total = 6

Test Case 2:
Input:
n = 5
prices = [1,2,3,4,5]
Output: 4
Explanation: One transaction is enough (buy at 1, sell at 5)

******************************************************/

#include <bits/stdc++.h>
using namespace std;

/*----------------------------------------------------
State Definition for Recursion:
(idx, canBuy, cap)
• idx = current day
• canBuy = 1 (allowed to buy) or 0 (must sell)
• cap = number of remaining transactions

Choices:
IF canBuy == 1:
    • Buy:  -prices[idx] + solve(idx+1, 0, cap)
    • Skip:              + solve(idx+1, 1, cap)
ELSE:
    • Sell:  prices[idx] + solve(idx+1, 1, cap-1)
    • Skip:              + solve(idx+1, 0, cap)

Base:
→ If idx == n OR cap == 0 → 0
----------------------------------------------------*/
int recHelper(int idx, int canBuy, int cap, vector<int> &prices)
{
    int n = prices.size();
    if (idx == n || cap == 0)
    {
        return 0;
    }

    if (canBuy)
    {
        int buy = -prices[idx] + recHelper(idx + 1, 0, cap, prices);
        int skip = recHelper(idx + 1, 1, cap, prices);
        return max(buy, skip);
    }
    else
    {
        int sell = prices[idx] + recHelper(idx + 1, 1, cap - 1, prices);
        int skip = recHelper(idx + 1, 0, cap, prices);
        return max(sell, skip);
    }
}

int stockIIIRecursion(vector<int> &prices)
{
    return recHelper(0, 1, 2, prices);
}

/*----------------------------------------------------
2. Memoization (Top-Down DP)
dp[idx][canBuy][cap]
----------------------------------------------------*/
int memoHelper(int idx, int canBuy, int cap, vector<int> &prices,
               vector<vector<vector<int>>> &dp)
{
    int n = prices.size();
    if (idx == n || cap == 0)
    {
        return 0;
    }

    if (dp[idx][canBuy][cap] != -1)
    {
        return dp[idx][canBuy][cap];
    }

    if (canBuy)
    {
        int buy = -prices[idx] + memoHelper(idx + 1, 0, cap, prices, dp);
        int skip = memoHelper(idx + 1, 1, cap, prices, dp);
        return dp[idx][canBuy][cap] = max(buy, skip);
    }
    else
    {
        int sell = prices[idx] + memoHelper(idx + 1, 1, cap - 1, prices, dp);
        int skip = memoHelper(idx + 1, 0, cap, prices, dp);
        return dp[idx][canBuy][cap] = max(sell, skip);
    }
}

int stockIIIMemoization(vector<int> &prices)
{
    int n = prices.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, -1)));
    return memoHelper(0, 1, 2, prices, dp);
}

/*----------------------------------------------------
3. Tabulation (Bottom-Up)
------------------------------------------------------
dp[idx][canBuy][cap]

Fill from idx = n-1 down to 0.
----------------------------------------------------*/
int stockIIITabulation(vector<int> &prices)
{
    int n = prices.size();
    vector<vector<vector<int>>> dp(n + 1,
                                   vector<vector<int>>(2, vector<int>(3, 0)));

    for (int idx = n - 1; idx >= 0; idx--)
    {
        for (int canBuy = 0; canBuy <= 1; canBuy++)
        {
            for (int cap = 1; cap <= 2; cap++)
            {
                if (canBuy)
                {
                    dp[idx][canBuy][cap] = max(
                        -prices[idx] + dp[idx + 1][0][cap],
                        dp[idx + 1][1][cap]);
                }
                else
                {
                    dp[idx][canBuy][cap] = max(
                        prices[idx] + dp[idx + 1][1][cap - 1],
                        dp[idx + 1][0][cap]);
                }
            }
        }
    }

    return dp[0][1][2];
}

/*----------------------------------------------------
4. Space Optimized (reduce 3D → 2D)
----------------------------------------------------*/
int stockIIISpaceOptimized(vector<int> &prices)
{
    int n = prices.size();

    vector<vector<int>> ahead(2, vector<int>(3, 0));
    vector<vector<int>> curr(2, vector<int>(3, 0));

    for (int idx = n - 1; idx >= 0; idx--)
    {
        for (int canBuy = 0; canBuy <= 1; canBuy++)
        {
            for (int cap = 1; cap <= 2; cap++)
            {
                if (canBuy)
                {
                    curr[canBuy][cap] = max(
                        -prices[idx] + ahead[0][cap],
                        ahead[1][cap]);
                }
                else
                {
                    curr[canBuy][cap] = max(
                        prices[idx] + ahead[1][cap - 1],
                        ahead[0][cap]);
                }
            }
        }

        ahead = curr;
    }

    return ahead[1][2];
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

    cout << "Using Recursion: " << stockIIIRecursion(prices) << endl;
    cout << "Using Memoization: " << stockIIIMemoization(prices) << endl;
    cout << "Using Tabulation: " << stockIIITabulation(prices) << endl;
    cout << "Using Space Optimized: " << stockIIISpaceOptimized(prices) << endl;

    return 0;
}