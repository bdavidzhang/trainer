#include <bits/stdc++.h>
using namespace std;
int main(){
    int q; scanf("%d",&q);
    while(q--){
        double p,r,y; scanf("%lf %lf %lf",&p,&r,&y);
        double sg=y<0?-1:1; double h=fabs(y)/2, P=fabs(p)/2, Rr=fabs(r)/2;
        // e=a+p/2,w=a-p/2,n=b+r/2,s=b-r/2, a+b=y/2; minimise max(|a|+P,|b|+Rr)
        double a=(h+Rr-P)/2; a=max(0.0,min(h,a)); double b=h-a;
        a*=sg;b*=sg;
        printf("%.9f %.9f %.9f %.9f\n",b+r/2,a+p/2,b-r/2,a-p/2);
    }
}
