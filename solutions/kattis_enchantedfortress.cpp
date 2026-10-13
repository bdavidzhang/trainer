#include <bits/stdc++.h>
using namespace std;
int n,L,H;
int d[30][30];
static int Q[1<<15];
int main(){
    char sb[64];scanf("%s",sb);string s=sb;n=s.size();
    for(int i=0;i<n;i++)for(int j=i;j<n;j++){scanf("%d",&d[i][j]);d[j][i]=d[i][j];}
    L=min(n,15);H=n-L;
    int LA=L/2,LB=L-LA; // low bits split: A = bits [0,LA), B = bits [LA,L)
    // Q[m]: pure pair sum among low bits (no diagonal)
    Q[0]=0;
    for(int m=1;m<(1<<L);m++){
        int b=__builtin_ctz(m);int r=m&(m-1);
        int v=Q[r];
        for(int j=b+1;j<L;j++)if(r>>j&1)v+=d[b][j];
        Q[m]=v;
    }
    // high masks: bits index L+k
    vector<int> HV(1<<H,0); // value of high subset including diagonals
    for(int m=1;m<(1<<H);m++){
        int b=__builtin_ctz(m);int r=m&(m-1);
        int v=HV[r]+d[L+b][L+b];
        for(int j=b+1;j<H;j++)if(r>>j&1)v+=d[L+b][L+j];
        HV[m]=v;
    }
    vector<int> linA(1<<LA),linB(1<<LB);
    int c[15];
    long long bestV=LLONG_MIN;int bestH=0;
    auto compute=[&](int hm){
        for(int i=0;i<L;i++){int v=d[i][i];for(int k=0;k<H;k++)if(hm>>k&1)v+=d[i][L+k];c[i]=v;}
        linA[0]=0;for(int m=1;m<(1<<LA);m++){int b=__builtin_ctz(m);linA[m]=linA[m&(m-1)]+c[b];}
        linB[0]=0;for(int m=1;m<(1<<LB);m++){int b=__builtin_ctz(m);linB[m]=linB[m&(m-1)]+c[LA+b];}
    };
    for(int hm=0;hm<(1<<H);hm++){
        compute(hm);
        int mx=INT_MIN;
        int sa=1<<LA;
        for(int hb=0;hb<(1<<LB);hb++){
            const int*q=Q+((size_t)hb<<LA);const int*la=linA.data();
            int loc=INT_MIN;
            for(int a=0;a<sa;a++){int v=q[a]+la[a];loc=v>loc?v:loc;}
            loc+=linB[hb];
            if(loc>mx)mx=loc;
        }
        long long tot=(long long)mx+HV[hm];
        if(tot>bestV){bestV=tot;bestH=hm;}
    }
    compute(bestH);
    int bestL=0;long long bl=LLONG_MIN;
    for(int m=0;m<(1<<L);m++){
        long long v=(long long)Q[m]+linA[m&((1<<LA)-1)]+linB[m>>LA];
        if(v>bl){bl=v;bestL=m;}
    }
    string out;
    for(int i=0;i<L;i++)if(bestL>>i&1)out+=s[i];
    for(int k=0;k<H;k++)if(bestH>>k&1)out+=s[L+k];
    printf("%d\n%s\n",(int)out.size(),out.c_str());
}
