#include <bits/stdc++.h>
using namespace std;
int main(){
    string s; getline(cin,s);
    while(!s.empty()&&(s.back()=='\n'||s.back()=='\r')) s.pop_back();
    int n=s.size();
    auto id=[](char c){ if(c==' ')return 52; if(c>='a'&&c<='z')return c-'a'; return 26+(c-'A'); };
    int S=2*n+2;
    vector<array<int,53>> nx(S); vector<int> len(S,0),lnk(S,-1);
    for(auto&a:nx)a.fill(-1);
    int sz=1,last=0;
    vector<int> M(n+1,0),dp(n+1,0);
    for(int i=0;i<n;i++){
        int c=id(s[i]);
        int cur=sz++; len[cur]=len[last]+1;
        int p=last;
        while(p!=-1&&nx[p][c]==-1){nx[p][c]=cur;p=lnk[p];}
        if(p==-1){lnk[cur]=0;M[i+1]=0;}
        else{
            M[i+1]=len[p]+1;
            int q=nx[p][c];
            if(len[p]+1==len[q])lnk[cur]=q;
            else{
                int cl=sz++; len[cl]=len[p]+1; nx[cl]=nx[q]; lnk[cl]=lnk[q];
                while(p!=-1&&nx[p][c]==q){nx[p][c]=cl;p=lnk[p];}
                lnk[q]=lnk[cur]=cl;
            }
        }
        last=cur;
        dp[i+1]=dp[i]+1;
        if(M[i+1]>0) dp[i+1]=min(dp[i+1],dp[i+1-M[i+1]]+3);
    }
    printf("%d\n",dp[n]);
}
