#include<bits/stdc++.h>
#define vi vector<LL>
#define pii pair<int,int>
#define fr first
#define sc second
#define MAX 50010
#define LL  long long int
#define ll  long long int
#define LLL long long int
#define inf 1e15
#define INF 10000000
#define mod 1000000007
#define N 65
#define mMax 30010
#define nMax 2010
#define SZ(a) a.size()
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(A) A.begin(),A.end()
using namespace std;
LL bigmod(LL a,LL b,LL Mod)
{
    if(b==0) return 1ll;
    if(b%2) return (a*bigmod(a,b-1,Mod))%Mod;
    LL c=bigmod(a,b/2,Mod);
    return (c*c)%Mod;
}

vector<ll>M, C;
int pointer;
//Returns true if either line l1 or
//line l3 is always better than line l2
bool bad(int l1, int l2, int l3)
{
	/*
	intersection(l1,l2) has x-coordinate (b1-b2)/(m2-m1)
	intersection(l1,l3) has x-coordinate (C1-C3)/(m3-m1)
	set the former greater than the latter, and
	cross-multiply to eliminate division
	*/
	return (1.0 * (C[l3] - C[l1]) * (M[l1] - M[l2])) <=
	       (1.0 *(C[l2] - C[l1]) * (M[l1] - M[l3]));
}
void add(long long m, long long c)
{
//First, let's add it to the end
	M.push_back(m);
	C.push_back(c);
//If the penultimate is now made irrelevant
//between the antepenultimate and the ultimate,
//remove it. Repeat as many times as necessary
	while (M.size() >= 3 &&
	        bad(M.size() - 3, M.size() - 2, M.size() - 1))
	{
		M.erase(M.end() - 2);
		C.erase(C.end() - 2);
	}
}
//Returns the minimum y-coordinate of any
//intersection between a given vertical line
//and the lower envelope
long long query(long long x)
{
//If we removed what was the best line for the
//previous query, then the newly inserted line
//is now the best for that query
	if (pointer > M.size()) pointer = M.size() - 1;
//Any better line must be to the right, since
//query values are non-decreasing
	while (pointer < M.size() - 1 && (M[pointer + 1]*x +C[pointer + 1] < M[pointer]*x + C[pointer]))
		pointer++; //MinValue Wanted...
	return M[pointer]*x + C[pointer];
}
LL A[100010];
LL B[100010];
LL dp[100010];
int main()
{
	int n;
	pointer=0;
	cin>>n;
	for(int i=0;i<n;i++)
		scanf("%lld",&A[i]);
	for(int i=0;i<n;i++)
		scanf("%lld",&B[i]);
	dp[0]=0;
	add(B[0],0);
	for(int i=1;i<n;i++)
	{
		dp[i]=query(A[i]);
		add(B[i],dp[i]);
	}
	cout<<dp[n-1]<<endl;
	return 0;
}
