#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct It{bool ins;char c;ll l,r;bool operator==(const It&o)const{return ins==o.ins&&(ins?c==o.c:(l==o.l&&r==o.r));}};
const ll INF=(ll)4e18;
vector<It> rd(){vector<It>v;v.push_back({false,0,1,INF});string op;
 while(cin>>op){if(op[0]=='E')break;ll p;cin>>p;char c=0;if(op[0]=='I')cin>>c;
  // find item containing position p
  size_t i=0;ll off=p; // off is 1-based offset within item i
  while(true){ll len=v[i].ins?1:(v[i].r-v[i].l+1);if(off<=len)break;off-=len;i++;}
  if(op[0]=='I'){It n{true,c,0,0};
   if(v[i].ins||off==1)v.insert(v.begin()+i,n);
   else{It a=v[i],b=v[i];a.r=a.l+off-2;b.l=a.r+1;v[i]=a;v.insert(v.begin()+i+1,n);v.insert(v.begin()+i+2,b);}
  }else{
   if(v[i].ins)v.erase(v.begin()+i);
   else{ll x=v[i].l+off-1;It a=v[i],b=v[i];a.r=x-1;b.l=x+1;
    vector<It>rep;if(a.l<=a.r)rep.push_back(a);if(b.l<=b.r)rep.push_back(b);
    v.erase(v.begin()+i);v.insert(v.begin()+i,rep.begin(),rep.end());}
  }}
 vector<It>r;for(auto&x:v){if(!x.ins&&!r.empty()&&!r.back().ins&&r.back().r+1==x.l)r.back().r=x.r;else r.push_back(x);}
 return r;}
int main(){auto a=rd();auto b=rd();puts(a==b?"0":"1");}
