#include <stdio.h>
int main()
{   int weight = 10;
    int N = 5;
  
    int w[N];
    int v[N];
    for (int i = 0; i < N; i++)
    {
        scanf("%d",&w[i]);
        scanf("%d",&v[i]);
    }
    int dp[N][weight];
    for (int i = 0; i < weight; i++)
    {
        if (i+1 < w[0])
        {
            dp[0][i] = 0;
        }else
        {
            dp[0][i] = v[0];

        }
        printf("%d",dp[0][i]);
    }
    printf("\n");
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j < weight; j++)
        {
            if (j+1>= w[i] && dp[i-1][j] < dp[i-1][j-w[i]]+v[i])
            {
                dp[i][j] = dp[i-1][j-w[i]]+v[i];
            }
            else
            {
                dp[i][j] = dp[i-1][j];
            }
            printf("%d",dp[i][j]);
        }
        printf("\n");
    }
    printf("%d",dp[N-1][weight-1]);
    return 0;
}