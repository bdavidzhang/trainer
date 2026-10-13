#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; cin>>n; vector<long long> x(n),y(n); for(int i=0;i<n;i++)cin>>x[i]>>y[i];
    string s; cin>>s;
    vector<bool> used(n,false); int cur=0;
    for(int i=1;i<n;i++)if(make_pair(x[i],y[i])<make_pair(x[cur],y[cur]))cur=i;
    vector<int> res{cur}; used[cur]=true;
    auto cross=[&](int o,int a,int b){return (x[a]-x[o])*(y[b]-y[o])-(y[a]-y[o])*(x[b]-x[o]);};
    for(int i=0;i<n-1;i++){
        char c=i<n-2?s[i]:'L'; int b=-1;
        // for 'L' pick the point with all other remaining points to its left (most clockwise), so the next turn is forced left
        for(int j=0;j<n;j++){ if(used[j])continue;
            if(b<0){b=j;continue;}
            long long cr=cross(cur,b,j);
            if(c=='L'?cr<0:cr>0)b=j;
        }
        used[b]=true;res.push_back(b);cur=b;
    }
    for(int i=0;i<n;i++)printf("%d%c",res[i]+1,i+1<n?' ':'\n');
}
