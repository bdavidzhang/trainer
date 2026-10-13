#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int n;
vector<pair<int,int>> J;
double solve(vector<pair<int,int>>&R){
    int m=R.size();
    vector<ull> v; v.reserve((size_t)n*m);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){
        long long dx=J[i].first-R[j].first,dy=J[i].second-R[j].second;
        ull d=dx*dx+dy*dy;
        v.push_back((d<<20)|((ull)i<<10)|j);
    }
    sort(v.begin(),v.end());
    vector<char> uj(n,0),ur(m,0);
    double s=0; int cnt=0;
    for(ull x:v){
        int j=x&1023,i=(x>>10)&1023;
        if(uj[i]||ur[j])continue;
        uj[i]=ur[j]=1; s+=sqrt((double)(x>>20));
        if(++cnt==n)break;
    }
    return s;
}
int main(){
    int m,p; scanf("%d %d %d",&n,&m,&p);
    J.resize(n); vector<pair<int,int>> A(m),B(p);
    for(auto&q:J)scanf("%d %d",&q.first,&q.second);
    for(auto&q:A)scanf("%d %d",&q.first,&q.second);
    for(auto&q:B)scanf("%d %d",&q.first,&q.second);
    printf("%.9f\n",solve(A)+solve(B));
}
