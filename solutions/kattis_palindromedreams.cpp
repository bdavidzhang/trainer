#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
// number of palindromes in [1,x], computed arithmetically
ull cntPal(ull x){
    if(x==0) return 0;
    string s=to_string(x); int L=s.size();
    ull res=0;
    for(int l=1;l<L;l++){ull c=9;for(int i=1;i<(l+1)/2;i++)c*=10;res+=c;}
    int hl=(L+1)/2; string hs=s.substr(0,hl);
    ull h=stoull(hs), lo=1; for(int i=1;i<hl;i++) lo*=10;
    res+=h-lo;
    string pal=hs; for(int i=L/2-1;i>=0;i--) pal+=hs[i];
    if(pal<=s) res++;
    return res;
}
int main(){
    int n; scanf("%d",&n);
    while(n--){ull a,b;scanf("%llu %llu",&a,&b); if(a>b)swap(a,b); printf("%llu\n",cntPal(b)-cntPal(a-1));}
}
