#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int main(){int n,C;scanf("%d %d",&n,&C);vector<ull>a(n);for(auto&x:a)scanf("%llu",&x);
 const int B=10001;bitset<B> cur;cur[0]=1;bool ok=false;
 for(int p=0;p<=60&&!ok;p++){vector<int>vals;for(ull x:a){ull q=(p==0)?x:((x>>p)+((x&((1ULL<<p)-1))?1:0));if(q<=(ull)C)vals.push_back((int)q);}
  sort(vals.begin(),vals.end());vals.erase(unique(vals.begin(),vals.end()),vals.end());
  bitset<B> nx;for(int v:vals)nx|=cur<<v;
  cur=nx;if(cur[C])ok=true;}
 // after index 60 every pillow contributes exactly 1
 if(!ok){for(int s=0;s<=C;s++)if(cur[s]){ok=true;break;}}
 puts(ok?"YES":"NO");}
