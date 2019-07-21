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
#define ll long long int
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
#define N 500009*30
ll n;
ll ar[ N ];
struct node{
    int data;
    node* left;
    node* right;
};
node* root[ N ];
node* build_trie(ll bit){
    node* nod = new node;
    nod->data = 0;nod->left = NULL;nod->right = NULL;
    if ( bit == -1 )
        return nod;
    nod->left = build_trie(bit-1);
    return nod;
}
node* insert_trie( node* par, ll bit, ll value)
{
    node* nod = new node;
    if ( par != NULL )
        nod->data = par->data + 1;
    else
        nod->data = 1;
    nod->left = nod->right = NULL;
    if ( bit == -1 )
        return nod;
    if ( value&(1<<bit) )
        nod->right=insert_trie(par==NULL?NULL:par->right,bit-1,value),nod->left = par==NULL?NULL:par->left;
    else
        nod->left=insert_trie(par==NULL?NULL:par->left,bit-1,value),nod->right = par==NULL?NULL:par->right;
    return nod;
}
ll query ( ll l, ll r, ll x ){
    node* nodr = root[r];
    node* nodl = root[l-1];
    ll ans =0;
    for ( ll i = 30; i >= 0; i --){

        ll leftval = ((nodr==NULL or nodr->left==NULL)?0:nodr->left->data) - ((nodl==NULL or nodl->left==NULL)?0:nodl->left->data);
        ll rightval = ((nodr==NULL or nodr->right==NULL)?0:nodr->right->data) - ((nodl==NULL or nodl->right==NULL)?0:nodl->right->data);
        // cout << i << endl;
        if ( x&(1<<i) ){
            if ( leftval )
                ans|=(1<<i),nodr = (nodr==NULL?NULL:nodr->left),nodl = (nodl==NULL?NULL:nodl->left);
            else
                nodr = (nodr==NULL?NULL:nodr->right),nodl = (nodl==NULL?NULL:nodl->right);
        }
        else{
            // if ( i == 0 )
            //     cout << i << " " << rightval << " " << nodl << endl;
            if ( rightval )
                ans|=(1<<i),nodr = (nodr==NULL?NULL:nodr->right),nodl = (nodl==NULL?NULL:nodl->right);
            else
                nodr = (nodr==NULL?NULL:nodr->left),nodl = (nodl==NULL?NULL:nodl->left);
        }
    }
    return ans;
}
int main()
{

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    cin >> n;
    for ( ll i = 1; i <= n; i ++)
        cin >> ar[i];
    root[0] = build_trie(30);
    for ( ll i = 1; i <= n; i ++)
        root[i]=insert_trie(root[i-1],30,ar[i]);
    // return 0;
    ll q;
    cin >> q;
    while ( q-- )
    {
        ll l,r,x;
        cin >> l >> r >> x;
        cout << query(l,r,x) <<"\n";
    }
}





