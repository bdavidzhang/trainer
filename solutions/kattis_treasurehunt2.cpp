#include <bits/stdc++.h>
using namespace std;
// 16 candidate top-left corners; memoized search for a decision tree of depth <= 5.
map<pair<int,int>,int> memo; // (set,q) -> best cell or -1 (fail), -2 = done
int hitMask[25];
int solve(int s,int q){
    if(__builtin_popcount(s)<=1) return -2;
    if(q==0) return -1;
    if(__builtin_popcount(s)>(1<<q)) return -1;
    auto key=make_pair(s,q);auto it=memo.find(key);if(it!=memo.end())return it->second;
    int res=-1;
    for(int c=0;c<25&&res==-1;c++){
        int a=s&hitMask[c],b=s&~hitMask[c];
        if(!a||!b)continue;
        if(solve(a,q-1)!=-1&&solve(b,q-1)!=-1)res=c;
    }
    return memo[key]=res;
}
int main(){
    for(int c=0;c<25;c++){int r=c/5,cc=c%5;hitMask[c]=0;
        for(int i=0;i<4;i++)for(int j=0;j<4;j++) if(r>=i&&r<=i+1&&cc>=j&&cc<=j+1)hitMask[c]|=1<<(i*4+j);}
    int s=(1<<16)-1,q=5;
    while(__builtin_popcount(s)>1){
        int c=solve(s,q);
        if(c<0)return 1;
        printf("? %d %d\n",c/5+1,c%5+1);fflush(stdout);
        int x;if(scanf("%d",&x)!=1||x<0)return 0;
        if(x)s&=hitMask[c];else s&=~hitMask[c];
        q--;
    }
    int b=__builtin_ctz(s);
    printf("! %d %d\n",b/4+1,b%4+1);fflush(stdout);
}
