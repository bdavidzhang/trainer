#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
struct T{int to,c[3];};
vector<T> tr[4];
void dfs(int start,int cur,int nxt,int c1,int c2,int c3){
    if(cur==3){ tr[start].push_back({nxt,{c1,c2,c3}}); return; }
    int r=(cur&1)?1:0, o=1-r;
    dfs(start,cur|(1<<r),nxt,c1+1,c2,c3);                       // square
    if(cur==0) dfs(start,3,nxt,c1,c2+1,c3);                      // vertical domino
    if(!(nxt>>r&1)) dfs(start,cur|(1<<r),nxt|(1<<r),c1,c2+1,c3); // horizontal domino
    if(nxt==0) dfs(start,cur|(1<<r),3,c1,c2,c3+1);               // L: this cell + whole next column
    if(cur==0){
        if(!(nxt>>o&1)) dfs(start,3,nxt|(1<<o),c1,c2,c3+1);
        if(!(nxt>>r&1)) dfs(start,3,nxt|(1<<r),c1,c2,c3+1);
    }
}
int main(){
    for(int m=0;m<4;m++) dfs(m,m,0,0,0,0);
    long long n;
    if(!(cin>>n)) return 0;
    array<array<ull,4>,4> dp{}; // dp[mask] = {ways, s1,s2,s3}
    dp[0][0]=1;
    for(long long i=0;i<n;i++){
        array<array<ull,4>,4> nd{};
        for(int m=0;m<4;m++) if(dp[m][0]) for(auto&t:tr[m]){
            nd[t.to][0]+=dp[m][0];
            for(int k=0;k<3;k++) nd[t.to][k+1]+=dp[m][k+1]+dp[m][0]*(ull)t.c[k];
        }
        dp=nd;
    }
    cout<<dp[0][0]<<" "<<dp[0][1]<<" "<<dp[0][2]<<" "<<dp[0][3]<<"\n";
}
