#include <bits/stdc++.h>
using namespace std;
int n,m;vector<int> pl;
void gen(int c,int mask){if(c>=m){pl.push_back(mask);return;}gen(c+1,mask);if(c+1<m)gen(c+2,mask|(3<<c));}
int main(){cin>>n>>m;vector<string>g(n);for(auto&s:g)cin>>s;
 gen(0,0);int K=pl.size(),L=n/2;const int INF=1e9;
 vector<int>need(L,0);for(int k=0;k<L;k++)for(int c=0;c<m;c++)if(g[2*k][c]=='#'||g[2*k+1][c]=='#')need[k]|=1<<c;
 // ok[P][Q]: every can of P has a column covered in Q
 vector<vector<char>>ok(K,vector<char>(K,1));
 for(int a=0;a<K;a++)for(int b=0;b<K;b++){int P=pl[a],Q=pl[b];int c=0;while(c<m){if(P>>c&1){if(!((Q>>c)&3)){ok[a][b]=0;break;}c+=2;}else c++;}}
 vector<int>dp(K,INF),nd(K);
 for(int a=0;a<K;a++)if((pl[a]&need[L-1])==need[L-1])dp[a]=__builtin_popcount(pl[a])/2;
 for(int k=L-2;k>=0;k--){for(int a=0;a<K;a++){nd[a]=INF;if((pl[a]&need[k])!=need[k])continue;int best=INF;for(int b=0;b<K;b++)if(ok[a][b])best=min(best,dp[b]);if(best<INF)nd[a]=best+__builtin_popcount(pl[a])/2;}dp=nd;}
 printf("%d\n",*min_element(dp.begin(),dp.end()));}
