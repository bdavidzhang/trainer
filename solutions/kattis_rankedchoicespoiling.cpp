#include <bits/stdc++.h>
using namespace std;
// returns index of eliminated among given (count, rank) entries: min count, tie -> largest rank
static inline int loser3(int cA,int cY,int rY,int cZ){ // ranks: A=0, Y=rY, Z=3 ; returns 0=A,1=Y,2=Z
    int best=2,bc=cZ; // Z has largest rank, wins ties
    if(cY<bc){best=1;bc=cY;}
    if(cA<bc){best=0;bc=cA;}
    return best;
}
int main(){
    int n,k; scanf("%d %d",&n,&k);
    int cnt[3][3]; memset(cnt,0,sizeof cnt);
    for(int i=0;i<n;i++){ char s[3][4]; for(int j=0;j<k;j++)scanf("%3s",s[j]); cnt[s[0][0]-'A'][s[1][0]-'A']++; }
    int A0=cnt[0][1]+cnt[0][2];
    for(int X=1;X<=2;X++){
        int Y=3-X;
        int XA=cnt[X][0],XY=cnt[X][Y],Y0=cnt[Y][0]+cnt[Y][X];
        int X0=XA+XY;
        bool pairAY = 2*(A0+XA)>=n;
        for(int t=0;t<=XA+A0;t++){
            int a=min(t,XA),e=t-a;
            for(int b=0;b<=XY;b++){
                int tX=X0-a-b, tA=A0-e;
                if(tX>tA) continue;
                int A2=tA+XA-a;
                for(int c=0;c<=Y0;c++){
                    int tY=Y0-c,tZ=a+b+c+e;
                    // round 1: who is eliminated among A(0),X,Y,Z(3)
                    // need X eliminated
                    if(tX>tA||tX>tY||tX>tZ) continue;
                    if(tX==tZ) continue;           // Z goes instead
                    if(tX==tY && Y>X) continue;    // Y goes instead
                    int Y2=tY+XY-b;
                    int l=loser3(A2,Y2,Y,tZ);
                    bool ok=false;
                    if(l==1) ok = (n-tZ)>=tZ;
                    else if(l==2) ok = pairAY;
                    if(ok){ puts("1"); return 0; }
                }
            }
        }
    }
    // original election (Z irrelevant)
    {
        int B0=cnt[1][0]+cnt[1][2],C0=cnt[2][0]+cnt[2][1];
        bool ok;
        if(k==2) ok = A0>=B0;
        else{
            // eliminate min, tie -> lex last
            int el; 
            if(C0<=B0&&C0<=A0) el=2; else if(B0<=A0) el=1; else el=0;
            if(el==0) ok=false;
            else if(el==2) ok = 2*(A0+cnt[2][0])>=n;
            else ok = 2*(A0+cnt[1][0])>=n;
        }
        puts(ok?"1":"0");
    }
}
