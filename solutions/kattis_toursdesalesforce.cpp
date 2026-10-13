#include <bits/stdc++.h>
using namespace std;
static double dp[1<<15][15];
double tsp(const vector<pair<double,double>>&p){
    int n=p.size();int m=n-1;
    static double d[16][16];
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)d[i][j]=hypot(p[i].first-p[j].first,p[i].second-p[j].second);
    int F=1<<m;
    for(int s=1;s<F;s++)for(int i=0;i<m;i++)dp[s][i]=1e18;
    for(int i=0;i<m;i++)dp[1<<i][i]=d[m][i];
    double best=1e18;
    for(int s=1;s<F;s++){
        for(int i=0;i<m;i++){
            if(!(s>>i&1))continue;
            double v=dp[s][i];if(v>=1e17)continue;
            if(s==F-1){best=min(best,v+d[i][m]);continue;}
            int rest=(F-1)&~s;
            while(rest){int j=__builtin_ctz(rest);rest&=rest-1;
                double nv=v+d[i][j];double&t=dp[s|1<<j][j];if(nv<t)t=nv;}
        }
    }
    return best;
}
int main(){
    int D;scanf("%d",&D);
    vector<vector<pair<double,double>>> P(D);
    double before=0;
    for(auto&v:P){int n;scanf("%d",&n);v.resize(n);for(auto&q:v)scanf("%lf %lf",&q.first,&q.second);before+=tsp(v);}
    int h=D/2;
    vector<vector<double>> a(h+1,vector<double>(h+1,0));
    for(int i=0;i<h;i++)for(int j=0;j<h;j++){
        auto v=P[i];v.insert(v.end(),P[h+j].begin(),P[h+j].end());
        a[i+1][j+1]=tsp(v);
    }
    int n=h;
    vector<double> u(n+1),v(n+1);vector<int> p(n+1),way(n+1);
    for(int i=1;i<=n;i++){
        p[0]=i;int j0=0;vector<double> minv(n+1,1e18);vector<char> used(n+1,0);
        do{used[j0]=1;int i0=p[j0],j1=0;double delta=1e18;
            for(int j=1;j<=n;j++)if(!used[j]){double cur=a[i0][j]-u[i0]-v[j];
                if(cur<minv[j]){minv[j]=cur;way[j]=j0;}
                if(minv[j]<delta){delta=minv[j];j1=j;}}
            for(int j=0;j<=n;j++)if(used[j]){u[p[j]]+=delta;v[j]-=delta;}else minv[j]-=delta;
            j0=j1;
        }while(p[j0]!=0);
        do{int j1=way[j0];p[j0]=p[j1];j0=j1;}while(j0);
    }
    double after=0;for(int j=1;j<=n;j++)after+=a[p[j]][j];
    printf("%.6f %.6f\n",before,after);
}
