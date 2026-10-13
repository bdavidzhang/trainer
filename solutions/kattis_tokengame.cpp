#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N=300, WD=5;
struct BS{ ull w[WD]; };
static BS A[N][N],Bq[N][N],C[N][N];
// F[x1][y1][x2][0/1]: P-values of y2 (1-based, 0 = none). [1] only used when x1==x2 (region y2>y1)
static unsigned short F[N][N][N][2];
static inline int firstZeroFrom(const ull* w,int from){ // first zero bit index >= from, <N, else -1
    int wi=from>>6;
    if(wi>=WD)return -1;
    ull cur=~w[wi] & (~0ULL<<(from&63));
    while(true){
        if(cur){int b=wi*64+__builtin_ctzll(cur); return b<N?b:-1;}
        if(++wi>=WD)return -1;
        cur=~w[wi];
    }
}
static inline void setb(BS&b,int i){b.w[i>>6]|=1ULL<<(i&63);}
static inline void clrb(BS&b,int i){b.w[i>>6]&=~(1ULL<<(i&63));}
int main(){
    for(int x1=0;x1<N;x1++)for(int y1=0;y1<N;y1++)for(int x2=0;x2<N;x2++){
        // blocking resets
        if(x1==x2){ clrb(A[y1][x2],y1); clrb(Bq[x1][x2],y1); clrb(C[x1][y1],y1); }
        ull w[WD];
        for(int i=0;i<WD;i++) w[i]=A[y1][x2].w[i]|Bq[x1][x2].w[i]|C[x1][y1].w[i];
        int p0=-1,p1=-1;
        if(x1!=x2){
            p0=firstZeroFrom(w,0);
        } else {
            p0=firstZeroFrom(w,0); if(p0>=y1)p0=-1;
            p1=firstZeroFrom(w,y1+1);
        }
        F[x1][y1][x2][0]=p0+1; F[x1][y1][x2][1]=p1+1;
        for(int p:{p0,p1}) if(p>=0){ setb(A[y1][x2],p); setb(Bq[x1][x2],p); setb(C[x1][y1],p); }
    }
    int q; scanf("%d",&q);
    // count moves of the "4th coord" v given fixed token (a,b) and shared coord c: tokens (a,b),(c,v)
    auto cnt=[&](int a,int b,int c,int v)->int{
        int r=0;
        for(int t=0;t<2;t++){
            int p=F[a][b][c][t]; if(!p)continue; p--;
            if(p>=v)continue;
            if(a==c && v>b && p<b)continue;
            r++;
        }
        return r;
    };
    while(q--){
        int x1,y1,x2,y2; scanf("%d %d %d %d",&x1,&y1,&x2,&y2); x1--;y1--;x2--;y2--;
        int r=cnt(x1,y1,x2,y2)+cnt(x2,y2,x1,y1)+cnt(y1,x1,y2,x2)+cnt(y2,x2,y1,x1);
        printf("%d\n",r);
    }
}
