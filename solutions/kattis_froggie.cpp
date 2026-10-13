#include <bits/stdc++.h>
using namespace std;
int main(){
    int L,W; cin>>L>>W;
    vector<long long> O(L),I(L),S(L);
    for(int i=0;i<L;i++) cin>>O[i]>>I[i]>>S[i];
    int P; string mv; cin>>P>>mv;
    int r=L,c=P;
    for(int t=1;t<=(int)mv.size();t++){
        char ch=mv[t-1];
        if(ch=='U') r--; else if(ch=='D') r++; else if(ch=='L') c--; else c++;
        if(r<0){ puts("safe"); return 0; }
        if(r>=L){ r=L; continue; }
        long long d = (r%2==0)? c : W-1-c;
        long long m = (((O[r]+S[r]*t-d)%I[r])+I[r])%I[r];
        if(m < max(S[r],1LL)){ puts("squish"); return 0; }
    }
    puts("squish");
}
