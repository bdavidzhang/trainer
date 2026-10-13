#include <bits/stdc++.h>
using namespace std;
int main(){int n;scanf("%d",&n);vector<pair<long long,long long>>v(n);for(auto&p:v)scanf("%lld %lld",&p.second,&p.first);
sort(v.begin(),v.end());priority_queue<long long>q;long long tot=0;
for(auto&p:v){q.push(p.second);tot+=p.second;if(tot>p.first){tot-=q.top();q.pop();}}
printf("%d\n",(int)q.size());}
