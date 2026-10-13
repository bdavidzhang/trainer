#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;cin>>n;
    vector<double> x(n),y(n);
    for(int i=0;i<n;i++)cin>>x[i]>>y[i];
    double best=1e18;
    vector<vector<double>> D(n,vector<double>(n));
    vector<double> dp((size_t)(1<<n)*n);
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){
        double th=atan2(y[j]-y[i],x[j]-x[i]);
        double c=cos(th),s=sin(th);
        for(int a=0;a<n;a++)for(int b=0;b<n;b++){
            double dx=x[a]-x[b],dy=y[a]-y[b];
            D[a][b]=fabs(dx*c+dy*s)+fabs(-dx*s+dy*c);
        }
        fill(dp.begin(),dp.end(),1e18);
        for(int a=0;a<n;a++)dp[(size_t)(1<<a)*n+a]=0;
        for(int m=1;m<(1<<n);m++)for(int l=0;l<n;l++){
            double v=dp[(size_t)m*n+l];
            if(v>1e17)continue;
            for(int t=0;t<n;t++)if(!(m>>t&1)){
                double&r=dp[(size_t)(m|1<<t)*n+t];
                if(v+D[l][t]<r)r=v+D[l][t];
            }
        }
        for(int l=0;l<n;l++)best=min(best,dp[(size_t)((1<<n)-1)*n+l]);
    }
    printf("%.9f\n",best);
}
