#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;scanf("%d",&n);
    vector<vector<int>> s(n);
    vector<int> vals;
    for(int i=0;i<n;i++){
        int k;scanf("%d",&k);s[i].resize(k);
        for(auto&x:s[i]){scanf("%d",&x);vals.push_back(x);}
    }
    sort(vals.begin(),vals.end());vals.erase(unique(vals.begin(),vals.end()),vals.end());
    int V=vals.size();
    for(auto&v:s)for(auto&x:v)x=lower_bound(vals.begin(),vals.end(),x)-vals.begin();
    const int B=300;
    vector<int> mark(V,-1),owner(V,-1);
    auto out=[&](int a,int b,int i,int j){
        printf("%d %d %d %d\n",vals[a],vals[b],i+1,j+1);
    };
    // large sets
    for(int i=0;i<n;i++) if((int)s[i].size()>=B){
        for(int x:s[i])mark[x]=i;
        for(int j=0;j<n;j++){
            if(j==i)continue;
            if((int)s[j].size()>=B&&j<i)continue;
            int first=-1;
            for(int x:s[j]) if(mark[x]==i){
                if(first<0)first=x; else {out(first,x,i,j);return 0;}
            }
        }
    }
    // small sets: for each value x, list small sets containing it
    vector<vector<int>> occ(V);
    for(int i=0;i<n;i++) if((int)s[i].size()<B) for(int x:s[i])occ[x].push_back(i);
    fill(mark.begin(),mark.end(),-1);
    for(int x=0;x<V;x++){
        for(int t:occ[x]){
            for(int y:s[t]){
                if(y<=x)continue;
                if(mark[y]==x){out(x,y,owner[y],t);return 0;}
                mark[y]=x;owner[y]=t;
            }
        }
    }
    puts("impossible");
}
