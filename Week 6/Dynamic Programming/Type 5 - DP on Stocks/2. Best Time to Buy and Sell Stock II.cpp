/******************************************************
Problem Statement: Best Time to Buy and Sell Stock II

You are given an array prices[] where prices[i] is the
stock price on day i.

You are allowed to make **unlimited transactions**:
→ Buy → Sell → Buy → Sell ... (any number of times)
BUT you must sell before buying again.

Return the **maximum possible profit**.

Test Case 1:
Input:
n = 6
prices = [7, 1, 5, 3, 6, 4]
Output: 7
Explanation:
Buy at 1, sell at 5 → profit 4
Buy at 3, sell at 6 → profit 3
Total = 7

Test Case 2:
Input:
n = 5
prices = [1, 2, 3, 4, 5]
Output: 4
Explanation: Buy at 1, sell at 5

******************************************************/

#include <bits/stdc++.h>
using namespace std;

/*----------------------------------------------------
1. Recursive Approach
------------------------------------------------------
State: (idx, canBuy)

→ If canBuy == 1:
       • Buy: -prices[idx] + solve(idx+1, 0)
       • Skip: solve(idx+1, 1)

→ If canBuy == 0:
       • Sell: prices[idx] + solve(idx+1, 1)
       • Skip: solve(idx+1, 0)

Base:
→ If idx == n → return 0

Unlimited transactions allowed.
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

int stockIIRecursion(vector<int> &prices)
{
    return recHelper(0, 1, prices);
}

/*----------------------------------------------------
2. Memoization (Top-Down DP)
------------------------------------------------------
dp[idx][canBuy] → maximum profit from idx.

Overlapping states appear on repeated decisions.
----------------------------------------------------*/
int memoHelper(int idx, int canBuy, vector<int> &prices,
               vector<vector<int>> &dp)
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

int stockIIMemoization(vector<int> &prices)
{
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2, -1));
    return memoHelper(0, 1, prices, dp);
}

/*----------------------------------------------------
3. Tabulation (Bottom-Up)
------------------------------------------------------
dp[idx][canBuy]

dp[n][0] = dp[n][1] = 0

Fill from bottom to top.
----------------------------------------------------*/
int stockIITabulation(vector<int> &prices)
{
    int n = prices.size();
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));

    for (int idx = n - 1; idx >= 0; idx--)
    {
        dp[idx][1] = max(-prices[idx] + dp[idx + 1][0],
                         dp[idx + 1][1]);

        dp[idx][0] = max(prices[idx] + dp[idx + 1][1],
                         dp[idx + 1][0]);
    }

    return dp[0][1];
}

/*----------------------------------------------------
4. Space Optimized (2 variables)
------------------------------------------------------
We only need next day's state:
aheadBuy, aheadSell
----------------------------------------------------*/
int stockIISpaceOptimized(vector<int> &prices)
{
    int aheadBuy = 0, aheadSell = 0;
    int currBuy = 0, currSell = 0;

    for (int idx = prices.size() - 1; idx >= 0; idx--)
    {
        currBuy = max(-prices[idx] + aheadSell, aheadBuy);
        currSell = max(prices[idx] + aheadBuy, aheadSell);

        aheadBuy = currBuy;
        aheadSell = currSell;
    }

    return aheadBuy;
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

    cout << "Using Recursion: " << stockIIRecursion(prices) << endl;
    cout << "Using Memoization: " << stockIIMemoization(prices) << endl;
    cout << "Using Tabulation: " << stockIITabulation(prices) << endl;
    cout << "Using Space Optimized: " << stockIISpaceOptimized(prices) << endl;

    return 0;
}
