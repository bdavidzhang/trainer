#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
#ifndef ALPHA
#define ALPHA 26
#endif
const u64 CAP=2000000000000000000ULL;
static inline u64 mul(u64 a,u64 b){ if(!a||!b) return 0; unsigned __int128 p=(unsigned __int128)a*b; return p>CAP?CAP:(u64)p; }
static inline u64 add(u64 a,u64 b){ u64 s=a+b; return s>CAP?CAP:s; }
u64 C[400][400];
static inline u64 binom(int n,int r){ if(r<0||n<0||r>n) return 0; return C[n][r]; }
// insert r>=1 equal letters into strings of length L described by dp[b*2+f]; accumulate into out (length L+r)
void insertLetter(const vector<u64>&dp,int L,int r,bool special,vector<u64>&out){
    int NL=L+r; if(out.empty()) out.assign(2*(NL+1),0);
    for(int b=0;b<=L;b++) for(int f=0;f<2;f++){
        u64 v=dp[b*2+f]; if(!v) continue;
        for(int j=1;j<=r;j++){
            u64 w1=mul(v,C[r-1][j-1]); 
            int xm=min(j,b);
            for(int x=0;x<=xm;x++){
                u64 w=mul(w1,C[b][x]);
                int nb=b-x+r-j;
                if(special){
                    u64 a=binom(L-b,j-x); if(a){auto&o=out[nb*2+f]; o=add(o,mul(w,a));}
                    a=binom(L-b,j-x-1); if(a){auto&o=out[nb*2+1]; o=add(o,mul(w,a));}
                }else if(f==0){
                    u64 a=binom(L+1-b,j-x); if(a){auto&o=out[nb*2]; o=add(o,mul(w,a));}
                }else{
                    u64 a=binom(L-b,j-x); if(a){auto&o=out[nb*2+1]; o=add(o,mul(w,a));}
                    a=binom(L-b,j-x-1); if(a){auto&o=out[nb*2]; o=add(o,mul(w,a));}
                }
            }
        }
    }
}
// number of completions (capped) given per-letter counts so far and last letter
u64 countComp(int k,const int*c,int last){
    int A=0; for(int i=0;i<ALPHA;i++){ if(c[i]>k) return 0; if(c[i]>0) A++; }
    if(A>k) return 0;
    int U=k-A; if(U>ALPHA-A) return 0;
    for(int i=1;i<=k;i++){int q=0; for(int l=0;l<ALPHA;l++) if(c[l]>=i) q++; if(q>k-i+1) return 0;}
    // groups
    vector<int> gc,gs; vector<char> gsp;
    {
        map<int,int> mp;
        for(int l=0;l<ALPHA;l++) if(c[l]>0&&l!=last) mp[c[l]]++;
        for(auto&pr:mp){gc.push_back(pr.first);gs.push_back(pr.second);gsp.push_back(0);}
        if(last>=0){gc.push_back(c[last]);gs.push_back(1);gsp.push_back(1);}
    }
    int G=gc.size();
    map<vector<int>,vector<u64>> cur,nxt;
    vector<int> key0(G+1,0);
    cur[key0]=vector<u64>{1,0};
    for(int j=1;j<=k;j++){
        nxt.clear();
        for(auto&pr:cur){
            const vector<int>&key=pr.first; const vector<u64>&dp=pr.second;
            int L=(j-1)*j/2; for(int g=0;g<G;g++) L-=key[g]*gc[g];
            auto go=[&](int g,int r,bool sp){
                vector<int> nk=key; nk[g]++;
                auto&out=nxt[nk];
                if(r==0){
                    if(out.empty()) out=dp; else for(size_t i=0;i<dp.size();i++) out[i]=add(out[i],dp[i]);
                }else insertLetter(dp,L,r,sp,out);
            };
            if(key[G]<U) go(G,j,false);
            for(int g=0;g<G;g++) if(gc[g]<=j&&key[g]<gs[g]) go(g,j-gc[g],gsp[g]);
        }
        cur.swap(nxt);
    }
    u64 res=0;
    for(auto&pr:cur) res=add(res,pr.second[0]);
    for(int g=0;g<G;g++) for(int i=2;i<=gs[g];i++) res=mul(res,i);
    for(int i=0;i<U;i++) res=mul(res,ALPHA-A-i);
    return res;
}
int main(){
    for(int i=0;i<400;i++){C[i][0]=1; for(int j=1;j<=i;j++) C[i][j]=add(C[i-1][j-1], j<=i-1?C[i-1][j]:0);}
    int k; u64 n; if(scanf("%d %llu",&k,&n)!=2) return 0;
    int T=k*(k+1)/2;
    int c[ALPHA]; memset(c,0,sizeof(c)); int last=-1;
    if(countComp(k,c,-1)<n){puts("-1");return 0;}
    string res;
    int start=0;
#ifndef NOJUMP
    {
        // F = lexicographically first string: pairs (k,k-1),(k-2,k-3),... alternating, e.g. ababa cdc e.
        // Requires 2*ceil(k/2) <= ... letters in order; completions along prefixes of F are non-increasing,
        // so binary search the longest prefix of F that still has >= n completions and start from there.
        string F; int letter=0;
        for(int v=k;v>=1;v-=2){
            int a=letter++, b=letter++;
            for(int i=0;i<v+(v-1);i++) F+=char('a'+(i%2?b:a));
        }
        if((int)F.size()==T && letter<=ALPHA+1){
            auto cntPref=[&](int p){
                int cc[ALPHA]; memset(cc,0,sizeof(cc));
                for(int i=0;i<p;i++) cc[F[i]-'a']++;
                return countComp(k,cc,p?F[p-1]-'a':-1);
            };
            int lo=0,hi=T; // cntPref(lo)>=n
            while(lo<hi){int mid=(lo+hi+1)/2; if(cntPref(mid)>=n) lo=mid; else hi=mid-1;}
            start=lo; res=F.substr(0,lo);
            for(int i=0;i<lo;i++) c[F[i]-'a']++;
            if(lo) last=F[lo-1]-'a';
        }
    }
#endif
    for(int pos=start;pos<T;pos++){
        bool found=false;
        for(int ch=0;ch<ALPHA;ch++){
            if(ch==last||c[ch]>=k) continue;
            c[ch]++;
            u64 w=countComp(k,c,ch);
            if(w>=n){res+=char('a'+ch);last=ch;found=true;break;}
            n-=w; c[ch]--;
        }
        if(!found){puts("-1");return 0;}
    }
    puts(res.c_str());
}
