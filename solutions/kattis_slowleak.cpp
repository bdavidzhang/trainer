#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=LLONG_MAX/4;
int main(){int n,m,t;ll d;scanf("%d %d %d %lld",&n,&m,&t,&d);
 vector<int>st(t);for(auto&x:st){scanf("%d",&x);x--;}
 st.push_back(0);st.push_back(n-1);
 vector<vector<ll>>g(n,vector<ll>(n,INF));for(int i=0;i<n;i++)g[i][i]=0;
 for(int i=0;i<m;i++){int a,b;ll k;scanf("%d %d %lld",&a,&b,&k);a--;b--;g[a][b]=min(g[a][b],k);g[b][a]=g[a][b];}
 for(int k=0;k<n;k++)for(int i=0;i<n;i++){ll x=g[i][k];if(x>=INF)continue;for(int j=0;j<n;j++){ll y=x+g[k][j];if(y<g[i][j])g[i][j]=y;}}
 int s=st.size();vector<vector<ll>>h(s,vector<ll>(s,INF));
 for(int i=0;i<s;i++)for(int j=0;j<s;j++){ll x=g[st[i]][st[j]];if(x<=d)h[i][j]=x;}
 for(int k=0;k<s;k++)for(int i=0;i<s;i++){ll x=h[i][k];if(x>=INF)continue;for(int j=0;j<s;j++){ll y=x+h[k][j];if(y<h[i][j])h[i][j]=y;}}
 ll r=h[s-2][s-1];if(r>=INF)puts("stuck");else printf("%lld\n",r);}
