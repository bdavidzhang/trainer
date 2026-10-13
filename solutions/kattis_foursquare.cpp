#include <bits/stdc++.h>
using namespace std;
int w[4],h[4];
bool tile(int mask,int W,int H){
    if(W<=0||H<=0)return false;
    if(__builtin_popcount(mask)==1){int i=__builtin_ctz(mask);return (w[i]==W&&h[i]==H)||(w[i]==H&&h[i]==W);}
    for(int s=(mask-1)&mask;s>0;s=(s-1)&mask){
        int a=0;for(int i=0;i<4;i++)if(s>>i&1)a+=w[i]*h[i];
        if(a%H==0){int x=a/H;if(x<W&&tile(s,x,H)&&tile(mask^s,W-x,H))return true;}
        if(a%W==0){int y=a/W;if(y<H&&tile(s,W,y)&&tile(mask^s,W,H-y))return true;}
    }
    return false;
}
int main(){int A=0;for(int i=0;i<4;i++){cin>>w[i]>>h[i];A+=w[i]*h[i];}
    int s=(int)llround(sqrt((double)A));
    if(s*s!=A){puts("0");return 0;}
    puts(tile(15,s,s)?"1":"0");}
