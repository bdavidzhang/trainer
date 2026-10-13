#include <bits/stdc++.h>
using namespace std;
int main(){
    int p;scanf("%d",&p);vector<int> s(p);for(auto&x:s)scanf("%d",&x);
    int th=(p+39)/40+1;
    static int c3[1000],ab[100],bc[100],ac[100];
    int bi=INT_MAX,bn=0,bm=0;
    for(int n=1;n<p;n++)for(int m=1;n+m<p;m++){
        int W=p-n-m;if(W<th)break;
        memset(c3,0,sizeof c3);memset(ab,0,sizeof ab);memset(bc,0,sizeof bc);memset(ac,0,sizeof ac);
        for(int i=0;i<W;i++){int a=s[i],b=s[i+n],c=s[i+n+m];c3[a*100+b*10+c]++;ab[a*10+b]++;bc[b*10+c]++;ac[a*10+c]++;}
        int lim=min(W,bi);
        for(int i=0;i<lim;i++){int a=s[i],b=s[i+n],c=s[i+n+m];int k=c3[a*100+b*10+c];
            if(k>=th&&ab[a*10+b]==k&&bc[b*10+c]==k&&ac[a*10+c]==k){bi=i;bn=n;bm=m;break;}}
    }
    if(bi==INT_MAX)puts("random sequence");
    else printf("triple correlation %d(%d)%d(%d)%d found\n",s[bi],bn,s[bi+bn],bm,s[bi+bn+bm]);
}
