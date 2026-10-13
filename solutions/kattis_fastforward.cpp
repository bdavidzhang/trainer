#include <bits/stdc++.h>
using namespace std;
int main(){int n;long long c;scanf("%d %lld",&n,&c);vector<int>d(2*n);for(int i=0;i<n;i++){scanf("%d",&d[i]);d[i+n]=d[i];}
 int N=2*n;vector<int>nx(N+1,N);
 {long long s=0;int j=0;for(int i=0;i<N;i++){while(j<N&&s<c){s+=d[j++];}nx[i]=(s>=c)?j:N;s-=d[i];}}
 // forest rooted at N; children in CSR
 vector<int>cnt(N+2,0),ch(N);for(int i=0;i<N;i++)cnt[nx[i]+1]++;for(int i=1;i<=N+1;i++)cnt[i]+=cnt[i-1];
 {vector<int>pos(cnt.begin(),cnt.end()-1);for(int i=0;i<N;i++)ch[pos[nx[i]]++]=i;}
 vector<int>ans(n),path,it;path.reserve(N+1);it.reserve(N+1);
 path.push_back(N);it.push_back(cnt[N]);
 while(!path.empty()){int v=path.back();int &p=it.back();
  if(p<cnt[v+1]){int u=ch[p++];
   if(u<n){ // ancestors path[0..sz-1], values decreasing with depth; count those <= u+n-1
    int lim=u+n-1;int lo=0,hi=path.size(); // first index with path[idx]<=lim
    while(lo<hi){int mid=(lo+hi)/2;if(path[mid]<=lim)hi=mid;else lo=mid+1;}
    ans[u]=(int)path.size()-lo;}
   path.push_back(u);it.push_back(cnt[u]);}
  else{path.pop_back();it.pop_back();}}
 for(int i=0;i<n;i++)printf("%d%c",ans[i],i==n-1?'\n':' ');}
