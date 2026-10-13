#include <bits/stdc++.h>
using namespace std;
int main(){int n;long long D,L;scanf("%d %lld %lld",&n,&D,&L);priority_queue<long long,vector<long long>,greater<long long>>pq;
 for(int i=0;i<n;i++){long long x;scanf("%lld",&x);pq.push(x);}
 while(pq.size()>1){long long a=pq.top();pq.pop();long long b=pq.top();pq.pop();pq.push(max(a,b)+D);}
 printf("%lld\n",pq.top()+L);}
