#include <bits/stdc++.h>
using namespace std;
int main(){
// faces: 0 top,1 bottom,2 front,3 back,4 left,5 right
typedef array<int,6> P;
P g1={0,1,4,5,3,2}; // spin about vertical axis: new front = old left, new back = old right, new left = old back, new right = old front
P g2={3,2,0,1,4,5}; // roll about left-right axis: new top = old back, new bottom = old front, new front = old top, new back = old bottom
set<P> S;vector<P> q;P id={0,1,2,3,4,5};S.insert(id);q.push_back(id);
for(size_t i=0;i<q.size();i++){for(P g:{g1,g2}){P r;for(int j=0;j<6;j++)r[j]=q[i][g[j]];if(S.insert(r).second)q.push_back(r);}}
// q should have 24 elements
int n;scanf("%d",&n);vector<int>cnt(46656,0);int best=0;
for(int i=0;i<n;i++){int a[6];for(int j=0;j<6;j++){scanf("%d",&a[j]);a[j]--;}
int mn=INT_MAX;for(auto&p:q){int c=0;for(int j=0;j<6;j++)c=c*6+a[p[j]];mn=min(mn,c);}
best=max(best,++cnt[mn]);}
printf("%d\n",best);}
