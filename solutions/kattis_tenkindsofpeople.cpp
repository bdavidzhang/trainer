#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int dv(char ch){if(isdigit(ch))return ch-'0';if(islower(ch))return ch-'a'+10;return ch-'A'+36;}
ll val(const vector<int>&d,ll b){ll r=0;for(int x:d)r=r*b+x;return r;}
int main(){int n;cin>>n;while(n--){string A,B;cin>>A>>B;vector<int> da,db;int ma=1,mb=1;
 for(char ch:A){da.push_back(dv(ch));ma=max(ma,da.back());}
 for(char ch:B){db.push_back(dv(ch));mb=max(mb,db.back());}
 bool ok=false;
 for(int a=ma+1;a<=7500&&!ok;a++){ll v=val(da,a);int lo=mb+1,hi=7500;
  while(lo<hi){int mid=(lo+hi)/2;if(val(db,mid)>=v)hi=mid;else lo=mid+1;}
  if(lo<=7500&&val(db,lo)==v){printf("%lld %d %d\n",v,a,lo);ok=true;}}
 if(!ok)puts("CANNOT MAKE EQUAL");}}
