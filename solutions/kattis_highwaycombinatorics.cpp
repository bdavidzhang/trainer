#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull MOD=1000000007ULL;
ull fib[205];
// A free 2 x k block has fib[k+1] tilings; blocks are separated by one vertical car.
// Deterministically expand a seed into block widths using at most 100 columns.
static ull sm(ull &x){ ull z=(x+=0x9E3779B97F4A7C15ULL); z=(z^(z>>30))*0xBF58476D1CE4E5B9ULL; z=(z^(z>>27))*0x94D049BB133111EBULL; return z^(z>>31); }
// Part sizes must be diverse (small and large blocks): products of only a few distinct
// Fibonacci numbers cover far fewer than 1e9+7 residues.
static vector<int> gen(ull seed){
    ull st=seed*0x2545F4914F6CDD1DULL+12345;
    vector<int> v; int budget=100;
    while(budget>=3){
        ull r=sm(st);
        int part=(r&1)? 3+(int)((r>>8)%8) : 3+(int)((r>>8)%38);   // part = width+1
        if(part>budget){ if(v.empty()||((r>>4)&1)) part=budget; else break; }
        v.push_back(part-1); budget-=part;
        if(v.size()>=2 && (r>>40)%16==0) break;
    }
    return v;
}
static ull prod(const vector<int>&v){ ull p=1; for(int k:v) p=p*fib[k+1]%MOD; return p; }
static ull pw(ull b,ull e){ ull r=1; b%=MOD; while(e){ if(e&1) r=r*b%MOD; b=b*b%MOD; e>>=1; } return r; }
int main(){
    ull n; cin>>n;
    if(n==0){ puts("##.\n.##"); return 0; }   // an isolated free cell: zero tilings
    fib[0]=0; fib[1]=1; for(int i=2;i<205;i++) fib[i]=(fib[i-1]+fib[i-2])%MOD;
    const int M=1<<21;
    vector<pair<unsigned,unsigned>> tab; tab.reserve(M);
    for(unsigned s=1;s<=(unsigned)M;s++) tab.push_back({(unsigned)prod(gen(s)),s});
    sort(tab.begin(),tab.end());
    for(ull s=(ull)1<<40;;s++){
        vector<int> R=gen(s);
        ull need=n*pw(prod(R),MOD-2)%MOD;
        auto it=lower_bound(tab.begin(),tab.end(),make_pair((unsigned)need,0u));
        if(it!=tab.end() && it->first==need){
            vector<int> L=gen(it->second);
            string row;
            for(int k:L){ row+=string(k,'.'); row+='#'; }
            for(int k:R){ row+=string(k,'.'); row+='#'; }
            cout<<row<<"\n"<<row<<"\n";
            return 0;
        }
    }
}
