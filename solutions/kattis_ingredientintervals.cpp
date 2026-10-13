#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; cin>>n; string line; getline(cin,line);
    vector<string> name(n); vector<double> val(n,-1);
    double R=100;
    for(int i=0;i<n;i++){
        getline(cin,line); istringstream ss(line);
        ss>>name[i]; double p; if(ss>>p){val[i]=p;R-=p;}
    }
    struct G{int s,k;double L,U;};
    vector<G> g;
    for(int i=0;i<n;){
        if(val[i]>=0){i++;continue;}
        int j=i; while(j<n&&val[j]<0) j++;
        G x; x.s=i;x.k=j-i; x.U=i>0?val[i-1]:100.0; x.L=j<n?val[j]:0.0;
        g.push_back(x); i=j;
    }
    double sumMin=0,sumMax=0;
    for(auto&x:g){sumMin+=x.k*x.L;sumMax+=x.k*x.U;}
    for(auto&x:g){
        double Smax=min(x.k*x.U,R-(sumMin-x.k*x.L));
        double Smin=max(x.k*x.L,R-(sumMax-x.k*x.U));
        for(int j=1;j<=x.k;j++){
            double hi=min(x.U,(Smax-(x.k-j)*x.L)/j);
            double lo=max(x.L,(Smin-(j-1)*x.U)/(x.k-j+1));
            if(lo<0) lo=0; if(hi<lo) hi=lo;
            printf("%s %.9f %.9f\n",name[x.s+j-1].c_str(),lo,hi);
        }
    }
}
