#include <bits/stdc++.h>
using namespace std;
int main(){
    string s; cin>>s; int n=s.size();
    vector<int> w(n); for(auto&x:w)cin>>x;
    int d; cin>>d;
    for(int i=0;i<d;i++){int b;cin>>b;b--;s[b]='X';w[b]=0;}
    string add; cin>>add;
    const string L="AEIOU";
    int cnt[5]={0};
    for(char ch:s){size_t p=L.find(ch); if(p!=string::npos)cnt[p]++;}
    for(char ch:add){size_t p=L.find(ch); if(p!=string::npos)cnt[p]++;}
    // pre[k][i] = weight of company k's bins among first i
    vector<vector<int>> pre(5,vector<int>(n+1,0));
    int total=0;
    for(int i=0;i<n;i++){
        for(int k=0;k<5;k++)pre[k][i+1]=pre[k][i]+(s[i]==L[k]?w[i]:0);
        total+=w[i];
    }
    const int NEG=-1e9;
    // dp[mask][pos]: max kept weight, companies in mask placed within first pos bins
    vector<vector<int>> dp(32,vector<int>(n+1,NEG));
    for(int p=0;p<=n;p++)dp[0][p]=0;
    for(int mask=1;mask<32;mask++){
        for(int p=0;p<=n;p++){
            int best=p>0?dp[mask][p-1]:NEG;
            for(int k=0;k<5;k++) if(mask>>k&1){
                int q=p-cnt[k]; if(q<0)continue;
                int v=dp[mask^(1<<k)][q]; if(v==NEG)continue;
                best=max(best,v+pre[k][p]-pre[k][q]);
            }
            dp[mask][p]=best;
        }
    }
    printf("%d\n",total-dp[31][n]);
}
