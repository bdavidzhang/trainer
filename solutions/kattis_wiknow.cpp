#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    vector<int> s(n); vector<int> last(n+1,-1); vector<vector<int>> occ(n+1);
    for(int i=0;i<n;i++){scanf("%d",&s[i]); last[s[i]]=i; occ[s[i]].push_back(i);}
    int LG=1; while((1<<LG)<=n) LG++;
    vector<vector<int>> sp(LG, vector<int>(n));
    for(int i=0;i<n;i++) sp[0][i]=last[s[i]];
    for(int j=1;j<LG;j++) for(int i=0;i+(1<<j)<=n;i++) sp[j][i]=max(sp[j-1][i],sp[j-1][i+(1<<(j-1))]);
    auto qmax=[&](int l,int r){ // inclusive
        int j=31-__builtin_clz(r-l+1); return max(sp[j][l],sp[j][r-(1<<j)+1]);
    };
    for(int a=1;a<=n;a++){
        auto &o=occ[a]; bool ok=false;
        for(size_t i=0;i+1<o.size()&&!ok;i++){
            if(o[i]+1<=o[i+1]-1 && qmax(o[i]+1,o[i+1]-1)>o[i+1]) ok=true;
        }
        if(ok){
            int best=INT_MAX;
            for(size_t i=0;i+1<o.size();i++)
                for(int d=o[i]+1;d<o[i+1];d++) if(last[s[d]]>o[i+1]) best=min(best,s[d]);
            printf("%d %d\n",a,best); return 0;
        }
    }
    puts("-1");
}
