/******************************************************
Problem Statement: Coin Change 2 (Minimum Coins)

You are given:
→ An array of coin denominations
→ A target amount

Each coin can be used **unlimited** times.
Return the **minimum number of coins** needed to make the amount.

If it is impossible, return -1.

This is the classic "unbounded knapsack - minimum coins" problem.

Test Case 1:
Input:
n = 3, amount = 11
coins = [1, 2, 5]

Test Case 2:
Input:
n = 3, amount = 7
coins = [2, 4, 6]

******************************************************/

#include <bits/stdc++.h>
using namespace std;

/*----------------------------------------------------
1. Recursive Approach
------------------------------------------------------
At index i:

Two choices:
→ PICK:  1 + solve(i, amount - coins[i])    (stay at same index)
→ NOT PICK: solve(i-1, amount)

Base Cases:
→ If amount == 0 → 0 coins needed
→ If idx == 0:
       if amount % coins[0] == 0 → amount/coins[0]
       else return large number
----------------------------------------------------*/
int recHelper(int idx, int amount, vector<int> &coins)
{
    if (amount == 0)
    {
        return 0;
    }

    if (idx == 0)
    {
        if (amount % coins[0] == 0)
        {
            return amount / coins[0];
        }
        return 1e9;
    }

    int notPick = recHelper(idx - 1, amount, coins);

    int pick = 1e9;
    if (coins[idx] <= amount)
    {
        pick = 1 + recHelper(idx, amount - coins[idx], coins);
    }

    return min(pick, notPick);
}

int minCoinsRecursion(int n, int amount, vector<int> &coins)
{
    int ans = recHelper(n - 1, amount, coins);
    return (ans >= 1e9) ? -1 : ans;
}

/*----------------------------------------------------
2. Memoization (Top-Down)
------------------------------------------------------
dp[idx][amount] stores minimum coins needed.

Overlapping Subproblems when picking repeatedly.
----------------------------------------------------*/
int memoHelper(int idx, int amount, vector<int> &coins,
               vector<vector<int>> &dp)
{
    if (amount == 0)
    {
        return 0;
    }

    if (idx == 0)
    {
        if (amount % coins[0] == 0)
        {
            return amount / coins[0];
        }
        return 1e9;
    }

    if (dp[idx][amount] != -1)
    {
        return dp[idx][amount];
    }

    int notPick = memoHelper(idx - 1, amount, coins, dp);

    int pick = 1e9;
    if (coins[idx] <= amount)
    {
        pick = 1 + memoHelper(idx, amount - coins[idx], coins, dp);
    }

    return dp[idx][amount] = min(pick, notPick);
}

int minCoinsMemoization(int n, int amount, vector<int> &coins)
{
    vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
    int ans = memoHelper(n - 1, amount, coins, dp);
    return (ans >= 1e9) ? -1 : ans;
}

/*----------------------------------------------------
3. Tabulation (Bottom-Up DP)
------------------------------------------------------
dp[i][a] = minimum coins to make amount a
Transition:
dp[i][a] = min(
    dp[i-1][a],
    1 + dp[i][a - coins[i]]
)

Base:
dp[0][a] = a / coins[0] if divisible else INF
----------------------------------------------------*/
int minCoinsTabulation(int n, int amount, vector<int> &coins)
{
    vector<vector<int>> dp(n, vector<int>(amount + 1, 1e9));

    for (int a = 0; a <= amount; a++)
    {
        if (a % coins[0] == 0)
        {
            dp[0][a] = a / coins[0];
        }
    }

    for (int i = 1; i < n; i++)
    {
        for (int a = 0; a <= amount; a++)
        {
            int notPick = dp[i - 1][a];

            int pick = 1e9;
            if (coins[i] <= a)
            {
                pick = 1 + dp[i][a - coins[i]];
            }

            dp[i][a] = min(pick, notPick);
        }
    }

    return (dp[n - 1][amount] >= 1e9) ? -1 : dp[n - 1][amount];
}

/*----------------------------------------------------
4. Space Optimized Approach
------------------------------------------------------
Use a 1-D dp array:
dp[a] = minimum coins to make a

Transition:
dp[a] = min(dp[a], 1 + dp[a - coins[i]])
----------------------------------------------------*/
int minCoinsSpaceOptimized(int n, int amount, vector<int> &coins)
{
    vector<int> dp(amount + 1, 1e9);

    dp[0] = 0;

    for (int i = 0; i < n; i++)
    {
        for (int a = coins[i]; a <= amount; a++)
        {
            dp[a] = min(dp[a], 1 + dp[a - coins[i]]);
        }
    }

    return (dp[amount] >= 1e9) ? -1 : dp[amount];
}

int main()
{
    int n, amount;

    cout << "Enter n: " << endl;
    cin >> n;

    vector<int> coins(n);
    cout << "Enter coin values: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }

    cout << "Enter amount: " << endl;
    cin >> amount;

    cout << "Using Recursion: " << minCoinsRecursion(n, amount, coins) << endl;
    cout << "Using Memoization: " << minCoinsMemoization(n, amount, coins) << endl;
    cout << "Using Tabulation: " << minCoinsTabulation(n, amount, coins) << endl;
    cout << "Using Space Optimized: " << minCoinsSpaceOptimized(n, amount, coins) << endl;

    return 0;
}