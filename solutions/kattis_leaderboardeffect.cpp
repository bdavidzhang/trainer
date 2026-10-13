#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,t; scanf("%d %d",&n,&t);
    vector<int> r(n),c(n); vector<double> p(n);
    for(int i=0;i<n;i++) scanf("%d %d %lf",&r[i],&c[i],&p[i]);
    int M=1<<n;
    vector<vector<double>> P(t+1);
    for(int i=0;i<=t;i++) P[i].assign(M,0.0);
    vector<vector<double>> solveAt(t+1, vector<double>(n,0.0));
    vector<double> s(n,0.0);
    P[0][0]=1.0;
    for(int tau=0;tau<=t;tau++){
        for(int i=0;i<n;i++) s[i]+=solveAt[tau][i];
        if(tau==t) break;
        double tot=0; for(int i=0;i<n;i++) tot+=s[i];
        vector<double>& cur=P[tau];
        for(int m=0;m<M;m++){
            double q=cur[m]; if(q==0) continue;
            if(m==M-1) continue;
            double w=0; int cntu=0;
            for(int i=0;i<n;i++) if(!(m>>i&1)){ w+=s[i]; cntu++; }
            for(int i=0;i<n;i++) if(!(m>>i&1)){
                double pr = (w>0)? s[i]/w : 1.0/cntu;
                if(pr==0) continue;
                double x=q*pr;
                int t1=tau+r[i];
                if(t1>t) continue;
                int nm=m|(1<<i);
                P[t1][nm]+=x*(1-p[i]);
                int t2=t1+c[i];
                if(t2<=t){ P[t2][nm]+=x*p[i]; solveAt[t2][i]+=x*p[i]; }
            }
        }
        vector<double>().swap(P[tau]);
    }
    for(int i=0;i<n;i++) printf("%.12f\n",s[i]);
}
