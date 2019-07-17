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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// #include "boost/algorithm/string.hpp"
#define fio ios_base::sync_with_stdio(false)
#define mod 1000000007
#define mod1 mod
#define mod2 1000000007
#define li long long int
#define ll li
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
#define pdd pair<double,double>
#define pic pair<int,char>
#define N 400005
#define lgn 20
#define ddouble long double
#define minus minu
#define PI 3.1415926535
 
 
// #define INTMAX 200000000 
 
// using namespace boost;
// #define si short int
 
using namespace std;
using namespace __gnu_pbds;             
typedef priority_queue<ll, vector<ll > > max_pq;
typedef priority_queue<pii, vector<pii> , greater<pii>  > min_pq;
ll toint(const string &s) {stringstream ss; ss << s; ll x; ss >> x; return x;}
string tostring ( ll number ){stringstream ss; ss<< number; return ss.str();}
 
// using namespace __gnu_pbds;         
// typedef priority_queue<pair<ll,char> , vector<pair<ll , char> > > max_pq;
// typedef priority_queue<pii , vector<pii > ,greater<pii > > min_pq;
typedef tree<pii , null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> OST;
// typedef priority_queue<pair < ll , pair < pii , ll > >  , vector<pair < ll , pair < pii , ll > >  > ,greater<pair < ll , pair < pii , ll > >  > > min_pq;
#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
    template <typename Arg1>
    void __f(const char* name, Arg1&& arg1){
        cout << name << " : " << arg1 << std::endl;
        //use cerr if u want to display at the bottom
    }
    template <typename Arg1, typename... Args>
    void __f(const char* names, Arg1&& arg1, Args&&... args){
        const char* comma = strchr(names + 1, ','); cout.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
    }
#else
#define trace(...)
#endif
#define nn 2000005
ll P[ N ][lgn+2];
ll T[ N ];
pii edge[ N ];
ll L[ N ];
ll n,t;
ll id[ N ];
ll sz[ N ];
ll special [ N ];
vector < vector < pii > > adjlist ( N );
ll thisnodespos[N],thisnodesch[N];
ll thischainst[N];
ll segarr[ N ];
ll ar[ N ];
ll seg[ N << 2 ];
void dfs ( ll i , ll par )
{
    T[i] = par;
    L[i] = L[par]+1;
    ll x = 0;
    for ( auto it : adjlist[i] )
        if ( it.fi != par )
            dfs(it.fi,i),x += sz[it.fi],ar[it.fi]=it.sec;
    sz[i] = x + 1;
    ll bigchild = 0,maxsz = 0;
    for ( auto it : adjlist[i] )
        if ( it.fi != par )
            if ( sz[it.fi] > maxsz )
                maxsz = sz[it.fi],bigchild=it.fi;
    special[i]=bigchild;
}
void dfs2 ( ll i, ll par, ll& chno, ll& pos, ll st )
{
    thisnodesch[i]=chno;
    thisnodespos[i] = pos;
    segarr[pos]=ar[i];
    if ( st )
        thischainst[chno]=i;
    if ( special[i] )
        dfs2(special[i],i,chno,(++pos),0);
    for ( auto it : adjlist[i] )
    {
        if ( it.fi != par and it.fi != special[i] )
        {
            dfs2(it.fi,i,(++chno),(++pos),1);
        }
    }
}
void build ( ll low, ll high, ll pos )
{
    if ( low == high )
        seg[pos] = segarr[low];
    else
    {
        ll mid = ( low + high ) >> 1;
        build ( low, mid, 2*pos + 1);
        build ( mid + 1, high, 2*pos + 2);
        seg[pos] = max(seg[2*pos+1],seg[2*pos+2]);
    }
}
ll query ( ll qlow, ll qhigh, ll low, ll high, ll pos )
{
    if ( qlow > qhigh )
        return 0;
    if ( qlow <= low and qhigh >= high )
        return seg[pos];
    else if ( qhigh < low or qlow > high )
        return 0;
    else
    {
        ll mid = (low + high) >> 1;
        ll ql = query(qlow,qhigh,low,mid,2*pos+1);
        ll qr = query(qlow,qhigh,mid+1,high,2*pos+2);
        return max(ql,qr);
    }
}
void update ( ll q, ll low, ll high, ll pos, ll val )
{
    if ( low == high and low == q )
        seg[pos] = val;
    else if ( q < low or q > high )
        return;
    else{
        ll mid = ( low + high ) >> 1;
        update(q,low,mid,2*pos+1,val);
        update(q,mid+1,high,2*pos+2,val);
        seg[pos] = max(seg[2*pos+1],seg[2*pos+2]);
    }
}
void buildsparsetable ( )
{
    memset(P,-1,sizeof P);
    for ( ll i = 1; i <= n; i ++)
        P[i][0] = T[i];
    for ( ll j = 1; j <= lgn; j ++)
        for ( ll i = 1; i <= n; i ++)
            if ( P[i][j-1] != -1 )
                P[i][j] = P[P[i][j-1]][j-1];
}
ll lca ( ll a, ll b)
{
    if ( L[a] < L[b] )
        swap(a,b);
    ll jump = L[a]-L[b];
    for ( ll i = lgn; i >= 0; i --)
        if ( (1<<i)&jump )
            a = P[a][i];
    // a and b are at same level
    if ( a == b )
        return a;
    for ( ll i = lgn; i >= 0; i --)
        if ( P[a][i] != -1 and P[b][i] != -1 and P[a][i]!=P[b][i] )
            a = P[a][i],b = P[b][i];
    return T[a];
}
inline ll find_max(ll u,ll lc){
    ll ans = 0;
    while ( thisnodesch[u] != thisnodesch[lc] ){
        ll l = thisnodespos[thischainst[thisnodesch[u]]];
        ll r = thisnodespos[u];
        ans = max(ans,query(l,r,1,n,0));
        u = T[thischainst[thisnodesch[u]]];
    }
    ans = max(ans,query(thisnodespos[lc]+1,thisnodespos[u],1,n,0));
    return ans;
}
ll query_hld( ll u, ll v )
{
    ll lc = lca(u,v);
    ll ans = find_max(u,lc);
    ans = max(ans,find_max(v,lc));
    return ans;
}
void update_hld ( ll idx, ll val)
{
    ll a = edge[idx].fi, b = edge[idx].sec;
    if ( L[a] > L[b] )
        update(thisnodespos[a],1,n,0,val);
    else
        update(thisnodespos[b],1,n,0,val);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    cin >> t;
    while ( t-- )
    {
        cin >> n;
        for ( ll i = 1; i <= n-1; i ++)
        {
            ll a,b,c;
            cin >> a >> b >> c;
            adjlist[a].pb({b,c});
            adjlist[b].pb({a,c});
            edge[i] = {a,b};
        }
        dfs(1,0);
        ll chno = 1, pos = 1;
        dfs2(1,0,chno,pos,1);
        build(1,n,0);
        buildsparsetable();
        string s;
        ll l,r;
        cin >> s;
        while ( s != "DONE" ){
            cin >> l >> r;
            if ( s == "QUERY" )
                cout << query_hld(l,r) <<"\n";
            else
                update_hld(l,r);
            cin >> s;
        }
        for ( ll i = 1; i <= n; i ++)
            adjlist[i].clear();

    }

    
}




