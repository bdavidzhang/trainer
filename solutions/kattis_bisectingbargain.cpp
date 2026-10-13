#include <bits/stdc++.h>
using namespace std;
// Merging coins (1+1->2, 2+2+1->5, 5x2->10, ...) only shrinks the set of subset sums,
// so an unsplittable multiset can be assumed canonical: small bounded counts, rest in 500s.
typedef bitset<5001> B;
int n,half; int val[9]={1,2,5,10,20,50,100,200,500}; int mx[8]={1,4,1,1,4,1,1,4}; int c[9];
bool rec(int idx,int rem,const B&bs){
 if(idx==8){ if(rem%500)return false; c[8]=rem/500; B b=bs;
  for(int q=0;q<c[8]&&!b[half];q++) b|=b<<500;
  return !b[half]; }
 B b=bs;
 for(int q=0;q<=mx[idx]&&q*val[idx]<=rem;q++){
  if(q) b|=b<<val[idx];
  c[idx]=q; if(rec(idx+1,rem-q*val[idx],b))return true;}
 return false;}
int main(){cin>>n;
 if(n%2){vector<int>o;int r=n;for(int j=8;j>=0;j--)while(r>=val[j]){o.push_back(val[j]);r-=val[j];}
  cout<<o.size()<<"\n";for(size_t i=0;i<o.size();i++)cout<<o[i]<<" \n"[i+1==o.size()];return 0;}
 half=n/2; B b0; b0[0]=1;
 if(rec(0,n,b0)){int tot=0;for(int j=0;j<9;j++)tot+=c[j];cout<<tot<<"\n";bool f=true;
  for(int j=0;j<9;j++)for(int q=0;q<c[j];q++){if(!f)cout<<" ";f=false;cout<<val[j];}cout<<"\n";}
 else cout<<"splittable\n";}
