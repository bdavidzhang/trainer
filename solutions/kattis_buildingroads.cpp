#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n; scanf("%d",&n);
    vector<ll> x(n),y(n);
    for(int i=0;i<n;i++) scanf("%lld %lld",&x[i],&y[i]);
    vector<vector<ll>> d2(n,vector<ll>(n));
    vector<vector<double>> d(n,vector<double>(n));
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){d2[i][j]=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);d[i][j]=sqrt((double)d2[i][j]);}
    double best=1e18; // radius
    vector<int> ord(n);
    for(int a=0;a<n;a++){
        // vertex centre
        double mx=0; for(int v=0;v<n;v++) mx=max(mx,d[a][v]);
        best=min(best,mx);
        for(int b=a+1;b<n;b++){
            for(int i=0;i<n;i++) ord[i]=i;
            sort(ord.begin(),ord.end(),[&](int u,int v){
                if(d2[a][u]!=d2[a][v]) return d2[a][u]>d2[a][v];
                return d2[b][u]>d2[b][v];
            });
            double L=d[a][b];
            int p=ord[0];
            for(int i=1;i<n;i++){
                int v=ord[i];
                if(d2[b][v]>d2[b][p]){
                    best=min(best,(d[a][v]+d[b][p]+L)/2);
                    p=v;
                }
            }
        }
    }
    printf("%.10f\n",2*best);
}
