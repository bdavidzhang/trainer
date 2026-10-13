#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// f = b00 b01 b10 b11, x = left parent, y = right parent
int bitAt(const string&f,ll r,ll i){
 if(i==1||i==r)return 1;
 if(f[3]=='1')return 1;            // row 2 is "11" -> everything stays 1
 string g=f.substr(0,3);
 if(g=="000")return 0;
 if(g=="011")return ((i-1)&(r-1))==(i-1); // xor: Pascal mod 2
 if(g=="110"||g=="010")return i&1;         // NOT x, (!x)&y
 if(g=="101"||g=="001")return ((r-i)&1)==0;// NOT y, x&(!y)
 if(g=="100")return (r&1)&&i>=3&&i<=r-2;   // NOR
 return (r&1)==0;                          // NAND 111
}
ll rowCnt(const string&f,ll r){
 if(r<=2)return r;
 if(f[3]=='1')return r;
 string g=f.substr(0,3);
 if(g=="000")return 2;
 if(g=="011")return 1LL<<__builtin_popcountll(r-1);
 if(g=="110"||g=="010"||g=="101"||g=="001")return r/2+1;
 if(g=="100")return (r&1)?2+max(0LL,r-4):2;
 return (r&1)?2:r;
}
int main(){int n;cin>>n;
 map<string,vector<ll>> pre; // lazily built prefix sums of row counts per function
 const int M=1000000;
 while(n--){string f;char t;ll r;cin>>f>>t>>r;
 if(t=='B'){ll i;cin>>i;printf("%d\n",bitAt(f,r,i));}
 else{string key=f[3]=='1'?string("1"):f;auto it=pre.find(key);
  if(it==pre.end()){vector<ll> v(M+1,0);int ty;string g=f.substr(0,3);
   if(f[3]=='1')ty=0;else if(g=="000")ty=1;else if(g=="011")ty=2;else if(g=="100")ty=4;else if(g=="111")ty=5;else ty=3;
   for(ll k=1;k<=M;k++){ll c;
    if(k<=2)c=k;else switch(ty){case 0:c=k;break;case 1:c=2;break;case 2:c=1LL<<__builtin_popcountll(k-1);break;
     case 3:c=k/2+1;break;case 4:c=(k&1)?2+max(0LL,k-4):2;break;default:c=(k&1)?2:k;}
    v[k]=v[k-1]+c;}
   it=pre.emplace(key,move(v)).first;}
  printf("%lld\n",it->second[r]);}}
}
