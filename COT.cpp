#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<bits/stdc++.h>
#include<stack>
#include<queue>
#include<list>
#include<vector>
#include<bitset>
#include<unordered_map>
#define fio ios_base::sync_with_stdio(false)
#define mod 1000000007
#define mod1 mod
#define mod2 1000000007
#define li long long int
#define ll int
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define readi(x) scanf("%d",&x)
#define  reads(x)  scanf("%s", x)
#define readl(x) scanf("%I64d",&x)
#define rep(i,n) for(i=0;i<n;i++)
#define revp(i,n) for(i=(n-1);i>=0;i--)
#define myrep1(i,a,b) for(i=a;i<=b;i++)
#define myrep2(i,a,b) for(i=b;i>=a;i--)
#define pb push_back
#define mp make_pair
#define fi first
#define sec second
#define MAXN 1000000000000000005
#define MINN -10000000000000000
#define INTMAX 1000001000
#define pii pair<ll,ll> 
using namespace std;
#define N 120009
ll n,m;
ll T[ N ];
ll ar[ N ];
ll P[ N ][ 25 ];
ll L [ N ];
set < ll > s;
unordered_map < ll,ll > comp;
unordered_map < ll,ll > rev;
ll dist;
vector < vector < ll > > adjlist ( N );
struct node{
    int data;
    node* left;
    node* right;
};
node* root[ N ];
node* build ( ll low, ll high, ll pos )
{
    node* nod = new node;
    nod->data = 0;
    if ( low == high )
        nod->left = nod->right = NULL;
    else{
        ll mid = (low + high) >> 1;
        nod->left = build(low,mid,2*pos+1);
        nod->right = build(mid+1,high,2*pos+2);
    }
    return nod;
}
void dfs ( ll i, ll par )
{
    T[i] = par;
    L[i] = L[par]+1;
    for ( auto it : adjlist[i] )
        if ( it != par )
            dfs(it,i);
}
void buildsparsetable()
{
    memset(P,-1,sizeof P);
    for(ll i=1;i<=n;i++)//check for N 
        P[i][0]=T[i];
    P[1][0] = -1;
    for ( ll j = 1; (1<<j)<= n; j ++)
        for ( ll i = 1; i <=n ; i ++)
            if ( P[i][j-1] != -1 )
                P[i][j] = P[P[i][j-1]][j-1];
}
ll lca ( ll a, ll b )
{
    if ( L[a] < L[b] )
        swap(a,b);
    ll jump = abs(L[b]-L[a]);
    for ( ll i = 20; i >= 0; i --)
        if ( jump&(1<<i) )
            a = P[a][i];
    if ( a == b )
        return a;
    for ( ll i = 20; i >= 0; i --)
        if ( P[a][i] != -1 and P[b][i] != -1 and P[a][i] != P[b][i] )
            a = P[a][i], b = P[b][i];
    return T[a];
}
node* update ( ll q, ll low, ll high, ll pos, node* par)
{
    node* nod = new node;
    if ( low == high and low == q)
    {
        nod->data = par->data + 1;
        nod->left = nod->right=NULL;
        return nod;
    } 
    else{
        ll mid = (low + high)>>1;
        if ( q <= mid )
        {
            nod->left = update(q,low,mid,2*pos+1,par->left);
            nod->right = par->right;
        }
        else{
            nod->right = update(q,mid+1,high,2*pos+2,par->right);
            nod->left = par->left;
        }
        nod->data = nod->left->data + nod->right->data ;
        return nod;
    }
}
void dfsper ( ll i, ll par )
{
    root[i] = update(comp[ar[i]],1,dist,0,root[par]);
    for ( auto it : adjlist[i] )
        if ( it != par )
            dfsper(it,i);
}
ll query ( ll low, ll high, node* a,node* b, node* lc, node* plc, ll k )
{
    if ( low == high )
        return rev[low];
    else{
        ll mid = (low + high)>>1;
        ll val = (a->left)->data + (b->left)->data - (lc->left)->data - (plc->left)->data;
        if (  val >= k )
            return query(low,mid,a->left,b->left,lc->left,plc->left,k);
        else
            return query(mid+1,high,a->right,b->right,lc->right,plc->right,k-val);
    }
}
ll queryab ( ll a, ll b , ll k ){
    ll l = lca(a,b);
    return query(1,dist,root[a],root[b],root[l],root[T[l]],k);
}
int main()
{

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    cin >> n >> m;
    for ( ll i = 1; i <= n; i ++)
        cin >> ar[i],s.insert(ar[i]);
    dist = s.size();
    ll x = 1;
    for ( auto it : s )
    {
        comp[it]=x;
        rev[x++]=it;
    }
    for ( ll i = 1; i <= n-1; i ++)
    {
        ll a,b;
        cin >> a >> b;
        adjlist[a].pb(b);
        adjlist[b].pb(a);
    }
    dfs(1,0);
    buildsparsetable();
    root[0] = build(1,dist,0);

    dfsper(1,0);
    while ( m-- )
    {
        ll a,b,k;
        cin >> a >> b >> k;
        cout << queryab(a,b,k) <<"\n";
    }
}





