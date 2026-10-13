#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;cin>>n;vector<double>b(n);vector<string>nm(n);map<string,int>id;
    double S=0;
    for(int i=0;i<n;i++){cin>>b[i]>>nm[i];id[nm[i]]=i;S+=b[i];}
    vector<array<double,3>> pos(n,{0,0,0});
    vector<array<double,4>> cnt(n,{0,0,0,0}); // not in top3, a = # top3 teams worse (smaller index)
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(j!=i)for(int l=0;l<n;l++)if(l!=i&&l!=j){
        double p=b[i]/S*b[j]/(S-b[i])*b[l]/(S-b[i]-b[j]);
        pos[i][0]+=p;pos[j][1]+=p;pos[l][2]+=p;
        int x[3]={i,j,l};sort(x,x+3);
        // teams t<x0: a=0; x0<t<x1: a=1; x1<t<x2: 2; t>x2: 3
        for(int t=0;t<n;t++){
            if(t==x[0]||t==x[1]||t==x[2])continue;
            int a=(t>x[0])+(t>x[1])+(t>x[2]);
            cnt[t][a]+=p;
        }
    }
    int q;cin>>q;
    while(q--){
        string s;int k;cin>>s>>k;int t=id[s];
        double r=0;
        for(int i=0;i<min(k,3);i++)r+=pos[t][i];
        if(k>3)for(int a=0;a<4;a++){ if(3+(t-a)+1<=k) r+=cnt[t][a]; }
        printf("%.10f\n",r);
    }
}
