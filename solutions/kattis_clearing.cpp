#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,p; scanf("%d %d",&n,&p);
    vector<double> a(n);
    for(auto&x:a){scanf("%lf",&x); x*=M_PI/180;}
    const double NEG=-1e18;
    double best=0;
    vector<vector<double>> s(n,vector<double>(n));
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)s[i][j]=sin(a[j]-a[i]);
    vector<double> cur(n),nx(n);
    for(int st=0;st<n;st++){
        fill(cur.begin(),cur.end(),NEG);
        cur[st]=0;
        for(int k=2;k<=p;k++){
            fill(nx.begin(),nx.end(),NEG);
            for(int i=st;i<n;i++){
                if(cur[i]==NEG)continue;
                double c=cur[i];
                for(int j=i+1;j<n;j++){
                    double v=c+s[i][j];
                    if(v>nx[j])nx[j]=v;
                }
            }
            swap(cur,nx);
            if(k>=3)for(int j=st+1;j<n;j++)if(cur[j]!=NEG)best=max(best,cur[j]+s[j][st]);
        }
    }
    printf("%.6f\n",best*0.5*1e6);
}
