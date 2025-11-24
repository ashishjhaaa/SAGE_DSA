/******************************************************
Problem Statement: Coin Change 1 (Count Number of Ways)

You are given:
→ An array of coin denominations
→ A target amount

You can use **unlimited coins** of each type.
Return the **total number of ways** to make the amount.

Order DOES NOT matter.

Test Case 1:
Input:
n = 3, amount = 4
coins = [1, 2, 3]

Test Case 2:
Input:
n = 3, amount = 5
coins = [1, 2, 5]

******************************************************/

#include <bits/stdc++.h>
using namespace std;

/*----------------------------------------------------
1. Recursive Approach (Unbounded Knapsack)
------------------------------------------------------
At index i, two choices:

→ PICK the coin:
    stay at same index (i), reduce amount
    solve(i, amount - coins[i])

→ NOT PICK the coin:
    move to previous index
    solve(i-1, amount)

Base Cases:
→ If amount == 0 → found 1 valid way
→ If i == 0 → check if amount divisible by coins[0]
----------------------------------------------------*/

long long recHelper(int idx, int amount, vector<int> &coins)
{
    if (amount == 0)
    {
        return 1;
    }

    if (idx == 0)
    {
        return (amount % coins[0] == 0) ? 1 : 0;
    }

    long long notPick = recHelper(idx - 1, amount, coins);

    long long pick = 0;
    if (coins[idx] <= amount)
    {
        pick = recHelper(idx, amount - coins[idx], coins);
    }

    return pick + notPick;
}

long long countWaysRecursion(int n, int amount, vector<int> &coins)
{
    return recHelper(n - 1, amount, coins);
}

/*----------------------------------------------------
2. Memoization (Top-Down DP)
------------------------------------------------------
dp[idx][amount] stores number of ways.

Overlapping subproblems happen when computing
multiple PICK combinations.
----------------------------------------------------*/

long long memoHelper(int idx, int amount, vector<int> &coins,
                     vector<vector<long long>> &dp)
{
    if (amount == 0)
    {
        return 1;
    }

    if (idx == 0)
    {
        return (amount % coins[0] == 0) ? 1 : 0;
    }

    if (dp[idx][amount] != -1)
    {
        return dp[idx][amount];
    }

    long long notPick = memoHelper(idx - 1, amount, coins, dp);

    long long pick = 0;
    if (coins[idx] <= amount)
    {
        pick = memoHelper(idx, amount - coins[idx], coins, dp);
    }

    return dp[idx][amount] = pick + notPick;
}

long long countWaysMemoization(int n, int amount, vector<int> &coins)
{
    vector<vector<long long>> dp(n, vector<long long>(amount + 1, -1));
    return memoHelper(n - 1, amount, coins, dp);
}

/*----------------------------------------------------
3. Tabulation (Bottom-Up DP)
------------------------------------------------------
dp[i][a] = number of ways using coins[0..i] to make sum a

Transitions:
→ notPick = dp[i-1][a]
→ pick = dp[i][a - coins[i]]

Base:
dp[0][a] = 1 if a % coins[0] == 0
----------------------------------------------------*/
long long countWaysTabulation(int n, int amount, vector<int> &coins)
{
    vector<vector<long long>> dp(n, vector<long long>(amount + 1, 0));

    for (int a = 0; a <= amount; a++)
    {
        if (a % coins[0] == 0)
        {
            dp[0][a] = 1;
        }
    }

    for (int i = 1; i < n; i++)
    {
        for (int a = 0; a <= amount; a++)
        {
            long long notPick = dp[i - 1][a];

            long long pick = 0;
            if (coins[i] <= a)
            {
                pick = dp[i][a - coins[i]];
            }

            dp[i][a] = notPick + pick;
        }
    }

    return dp[n - 1][amount];
}

/*----------------------------------------------------
4. Space Optimized DP
------------------------------------------------------
Use 1-D dp array:
dp[a] += dp[a - coin]

We iterate from coin to amount, because order does NOT matter.
----------------------------------------------------*/
long long countWaysSpaceOptimized(int n, int amount, vector<int> &coins)
{
    vector<long long> dp(amount + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < n; i++)
    {
        for (int a = coins[i]; a <= amount; a++)
        {
            dp[a] += dp[a - coins[i]];
        }
    }

    return dp[amount];
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

    cout << "Using Recursion: " << countWaysRecursion(n, amount, coins) << endl;
    cout << "Using Memoization: " << countWaysMemoization(n, amount, coins) << endl;
    cout << "Using Tabulation: " << countWaysTabulation(n, amount, coins) << endl;
    cout << "Using Space Optimized: " << countWaysSpaceOptimized(n, amount, coins) << endl;

    return 0;
}
