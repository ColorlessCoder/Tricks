#include<bits/stdc++.h>
#define unt unsigned long long int
using namespace std;
int dp[255][255];
int root[255][255];
int A[255];
int B[255];
int main()
{
    int T,I=1;
  //  cin>>T;
        int n,m;
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&A[i]);
            B[i]=B[i-1]+A[i];
            dp[i][i]=0;
            root[i][i]=i;
        }
        for(int k=2;k<=n;k++)
        {
            for(int i=1;i<=(n-k+1);i++)
            {
                int y=i+k-1;
                int a=root[i][y-1];
                int b=root[i+1][y];
                int ans=1e9;
                int r=0;
                for(int j=a;j<=b;j++)
                {
                    int w=B[y]-B[i-1];
                    w-=A[j];
                    if(j!=i) w+=dp[i][j-1];
                    if(j!=y) w+=dp[j+1][y];
                    if(ans > w)
                    {
                        ans=w;
                        r=j;
                    }
                }
                dp[i][y]=ans;
                root[i][y]=r;
            }
        }
        printf("%d\n",dp[1][n]);
    }
    return 0;
}
