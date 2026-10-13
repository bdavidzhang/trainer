#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
int main(){
    int N,K;scanf("%d %d",&N,&K);
    int cnt[4]={0,0,0,0};
    for(int i=0;i<=K;i++)scanf("%d",&cnt[i]);
    int a=cnt[0],b=cnt[2],c=cnt[3];
    int D=b+2*c-a;
    if(N==1){puts("1.0");return 0;}
    if(D<=-2){puts("0.0");return 0;}
    if(D==-1){printf("%.12f\n",1.0/N);return 0;}
    vector<ld> lf(N+2,0);
    for(int i=1;i<=N+1;i++)lf[i]=lf[i-1]+logl((ld)i);
    ld logTot=lf[a+b+c]-lf[a]-lf[b]-lf[c];
    ld bad=0;
    for(int k=0;k<=c;k++)for(int j=0;j<=b;j++){
        int i=j+2*k+1;if(i>a)break;
        int n=i+j+k;
        ld v=lf[n]-lf[i]-lf[j]-lf[k]-logl((ld)n)+lf[a+b+c-n]-lf[a-i]-lf[b-j]-lf[c-k]-logTot;
        bad+=expl(v);
    }
    ld ans=1-bad;if(ans<0)ans=0;if(ans>1)ans=1;
    printf("%.12Lf\n",ans);
}
