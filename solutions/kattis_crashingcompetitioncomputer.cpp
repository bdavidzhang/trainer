#include <bits/stdc++.h>
using namespace std;
int main(){
    int c; long double t,r,p;
    double td,rd,pd;
    scanf("%d %lf %lf %lf",&c,&td,&rd,&pd); t=td;r=rd;p=pd;
    long double q=1-p;
    vector<long double> A(c+1,0),dp(c+1,0);
    for(int k=1;k<=c;k++) A[k]=(A[k-1]+1+p*r)/q;
    for(int i=1;i<=c;i++){
        long double b=INFINITY;
        for(int j=0;j<i;j++){ long double v=dp[j]+A[i-j]+t; if(v<b) b=v; }
        dp[i]=b;
    }
    printf("%.9Lf\n",dp[c]);
}
