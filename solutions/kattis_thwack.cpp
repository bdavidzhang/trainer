#include <bits/stdc++.h>
using namespace std;
int n; string s;
int memo[101][101][2][2];
// grundy of piece s[l..r] (contiguous stones), first char flipped if fl, last flipped if fr
int gr(int l,int r,int fl,int fr){
    if(l>=r) return 0;
    int &m=memo[l][r][fl][fr];
    if(m>=0) return m;
    auto c=[&](int k){ int v=(s[k]=='B'); if(k==l&&fl) v^=1; if(k==r&&fr) v^=1; return v; };
    vector<char> seen(260,0);
    for(int i=l;i<r;i++) if(c(i)!=c(i+1)){
        // i captures i+1: left [l..i-1], right [i+1..r] with first flipped
        int a=gr(l,i-1,fl,0);
        int b=gr(i+1,r,1,fr);
        seen[a^b]=1;
        // i+1 captures i: left [l..i] last flipped, right [i+2..r]
        a=gr(l,i,fl,1);
        b=gr(i+2,r,0,fr);
        seen[a^b]=1;
    }
    int g=0; while(seen[g]) g++;
    return m=g;
}
int main(){
    cin>>n>>s;
    memset(memo,-1,sizeof memo);
    // segments
    vector<pair<int,int>> segs; vector<int> sg(n,-1);
    for(int i=0;i<n;){
        if(s[i]=='.'){i++;continue;}
        int j=i; while(j+1<n&&s[j+1]!='.') j++;
        for(int k=i;k<=j;k++) sg[k]=segs.size();
        segs.push_back({i,j}); i=j+1;
    }
    int tot=0; vector<int> gv;
    for(auto&p:segs){gv.push_back(gr(p.first,p.second,0,0)); tot^=gv.back();}
    vector<pair<int,int>> res;
    for(int i=0;i+1<n;i++) if(s[i]!='.'&&s[i+1]!='.'&&s[i]!=s[i+1]){
        int l=segs[sg[i]].first,r=segs[sg[i]].second;
        int rest=tot^gv[sg[i]];
        if((rest^gr(l,i-1,0,0)^gr(i+1,r,1,0))==0) res.push_back({i+1,i+2});
        if((rest^gr(l,i,0,1)^gr(i+2,r,0,0))==0) res.push_back({i+2,i+1});
    }
    sort(res.begin(),res.end());
    printf("%d\n",(int)res.size());
    for(auto&p:res) printf("%d %d\n",p.first,p.second);
}
