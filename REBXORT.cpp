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
#define N 400005*32
#define lgn 30
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
ll tri[ N ][ 2 ];
ll n;
ll ar[ N ],pre[ N ];
ll pos = 1,maxpos = 1;
void trie_insert( ll x ){
    pos = 1;
    for ( ll i = lgn; i >= 0; i --)
    {
        ll bit = (x&(1<<i))?1:0;
        if ( tri[pos][bit] == -1 )
           tri[pos][bit]=(++maxpos);
        pos = tri[pos][bit];
    }
}
ll trie_find_max ( ll x ){
    pos = 1;
    ll max_xor = 0;
    for ( ll i = lgn; i >= 0; i --)
    {
        ll req_bit = (x&(1<<i))?0:1;
        if ( tri[pos][req_bit] == -1 )
            pos = tri[pos][!req_bit];
        else
            pos = tri[pos][req_bit],(max_xor |= (1<<i));
    }
    return max_xor;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    memset(tri,-1,sizeof tri);
    cin >> n;
    for ( ll i = 1; i <= n; i ++)
        cin >> ar[i];
    trie_insert(0);
    ll p = 0;
    for ( ll i = 1; i <= n; i ++)
    {
        p ^= ar[i];
        pre[i] = max(pre[i-1],trie_find_max(p));
        trie_insert(p);
    }
    memset(tri,-1,sizeof tri);
    trie_insert(0);
    p = 0;
    ll ans = 0;
    ll s = 0;
    for ( ll i = n; i >= 1; i --)
    {
        ans = max(ans,pre[i]+s);
        p ^= ar[i];
        s = max(s,trie_find_max(p));
        trie_insert(p);
    }
    cout << ans;
}




