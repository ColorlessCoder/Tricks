#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<map>
#include<list>
#include<queue>
#include<iostream>
#include<algorithm>
#include<set>
#include<deque>
#include<stack>
#define vi vector<int>
#define vll vector<LL>
#define pii pair<int,int>
#define pli pair<LL,int>
#define pll pair<LL,LL>
#define fr first
#define sc second
#define MAX 50010
#define LL   long long int
#define ll   long long int
//#define LLL long long int
#define inf (1ll<<62)
#define INF 10000000
#define mod 1000000007
//#define N 65
#define mMax 30010
#define nMax 2010
#define SZ(a) a.size()
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define rep1(i,b) for(int i=1;i<=b;i++)
#define rep2(i,b) for(int i=0;i<b;i++)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define all(A) A.begin(),A.end()
#define isf(a) scanf("%d",&a);
#define Lsf(a) scanf("%I64d",&a);
#define lsf(a) scanf("%lld",&a);
#define csf(a) scanf("%c",&a);
#define vedge vector<Edge>
using namespace std;
LL bigmod(LL a,LL b,LL Mod)
{
    if(b==0) return 1ll;
    if(b%2) return (a*bigmod(a,b-1,Mod))%Mod;
    LL c=bigmod(a,b/2,Mod);
    return (c*c)%Mod;
}

///Divide and Conquer Trick

struct Edge{
	int u,v,l,r,f;
	Edge(){}
	Edge(int a,int b,int c,int d,int zz=0)
	{
		u=a;
		v=b;
		l=c;
		r=d;
		f=zz;
	}
	void rein(int x,int y){
		u=x;v=y;
	}
};
vector<vi> E;
int comp[100010];
vi vis;
/// for finding the number of component in the graph
void dfs(int u,int col)
{
	
	comp[u]=col;
	rep2(i,SZ(E[u]))
	if(comp[E[u][i]]==-1)
	dfs(E[u][i],col);
	return;
}
/// adding edge between biconnected components
void add(int u,int v)
{
	E[u].pb(v);E[v].pb(u);
}
vi ans;
int query[100010];
/// this technique would be easier to understand  if you learn a (n+m)sqrt(n+m)
/// algorithm to solve this problem.
/// start of divide and conquer
/// 0. We will save our queries as edges and each edge will have a lifetime 
/// ie starting time = when it was added in the graph and 
/// ending time = when it will be deleted or removed
/// eg. if at time t1 we get a query to add edge e and at time t2 we get a request 
/// to remove it then lifetime will be [t1,t2] .
/// 1.Each time we will compress the graph where the graph build with
/// the edges that cover the block [L,R] since for this range we are
/// only sure about the existence of these edges.
/// 2. Key optimization: We will delete all components that are not mentioned
/// in the block[L,R] . Eg. if a edge added at time 5 then we dont care about
///  it at range [2,4]. Thus every range wil have no more than R-L+1 edges.
/// So at any level we process no more then m edges where m is # of query
/// and maximum level lgm . So compexity O(mlgm).
void D_C(int L,int R,vedge edges,int n)
{
	if(L>R) return;
	if(query[R+1]-query[L] <=0) 
	{
		return;
	}
	rep2(i,n) E[i].clear();
	vedge nedges;
	///building graph
	rep2(i,SZ(edges))
	{
		if(edges[i].l<=L && edges[i].r>=R && edges[i].f==0) add(edges[i].u,edges[i].v);
		else if(edges[i].l<R && edges[i].r>L)	nedges.pb(edges[i]);
		else if(edges[i].l>=L && edges[i].r<=R && edges[i].f==1)	nedges.pb(edges[i]);
	}
	int m=0;
	rep2(i,n) comp[i]=-1;
	///finding components
	rep2(i,n)
	if(comp[i]==-1)
		dfs(i,m++);
	vi deg(n,0);
	rep2(i,SZ(nedges)){
	nedges[i].u=comp[nedges[i].u];
	nedges[i].v=comp[nedges[i].v];
	if(nedges[i].u != nedges[i].v)
	deg[nedges[i].u]++,deg[nedges[i].v]++;
	}
	n=0;
	edges.clear();
	///removing the components that are not mentioned in this block
	rep2(i,m) if(deg[i]) comp[i]=n++;
	rep2(i,SZ(nedges)){
	nedges[i].u=comp[nedges[i].u];
	nedges[i].v=comp[nedges[i].v];
	}
	//a/answering connection query
	if(L==R)
	{
		if(query[R+1]-query[R] == 1) ans.pb(nedges[0].u==nedges[0].v);
		return;
	}
	/// divide
	int mid=(L+R)>>1;
	D_C(L,mid,nedges,n);
	D_C(mid+1,R,nedges,n);
	return;
}
map<pii,int> Map;
int main()
{
       int T=10000000;
       while(T--);/// wasting time :D
	int n,m;
	char str[10];
	cin>>n>>m;
	E.assign(n+1,vi());
	vedge edges;
	rep2(i,m)
	{
		int a,b;
		scanf("%s %d %d",str,&a,&b);
		if(a>b) swap(a,b);
		if(str[0]=='a') Map[mp(a,b)]=i;
		else if(str[0]=='r') 
		{
			int &temp=Map[mp(a,b)];
			/// setting lifetime for edges
			edges.pb(Edge(a,b,temp,i));
			temp=-1;
		}
		else {edges.pb(Edge(a,b,i,i,1));query[i+1]=1;}
		query[i+1]=query[i]+query[i+1];
	}
	for(map<pii,int>::iterator it=Map.begin();it!=Map.end();it++)
		if(it->sc!=-1) /// taking only those edges that are not removed
			edges.pb(Edge(it->fr.fr,it->fr.sc,it->sc,m));
	D_C(0,m-1,edges,n);
	rep2(i,SZ(ans))
	if(ans[i]==0) printf("NO\n");
	else printf("YES\n");
	return 0;
}
