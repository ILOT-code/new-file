for (int i = n - 1; i >= 0; --i)
    for (int j = i + 1; j < n; ++j) {
        dp[0][i][j] = min(dp[0][i + 1][j] + a[i + 1] - a[i], dp[1][i + 1][j] + a[j] - a[i]);
        if (dp[0][i][j] >= b[i]) dp[0][i][j] = INF;
        dp[1][i][j] = min(dp[0][i][j - 1] + a[j] - a[i], dp[1][i][j - 1] + a[j] - a[j - 1]);
        if (dp[1][i][j] >= b[j]) dp[1][i][j] = INF;
    }