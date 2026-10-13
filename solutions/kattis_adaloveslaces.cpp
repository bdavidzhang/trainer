#include <bits/stdc++.h>
using namespace std;
int N; double d,s,t; vector<double> lens; double cr[10];
void go(int row,int vis,double len,int cnt){
    if(row==N-1){ lens.push_back(s+2*len+2*cnt*t); return; }
    for(int r=0;r<N;r++) if(!(vis>>r&1)){
        int dr=abs(r-row);
        go(r,vis|1<<r,len+cr[dr],cnt+1);
        if(dr==1) go(r,vis|1<<r,len+d,cnt+1);
    }
}
int main(){
    double fmin_,fmax_;
    cin>>N>>d>>s>>t>>fmin_>>fmax_;
    for(int i=0;i<10;i++)cr[i]=sqrt(s*s+i*d*i*d);
    go(0,1,0,1);
    sort(lens.begin(),lens.end());
    double L;
    while(cin>>L){
        double lo=L-2*fmax_, hi=L-2*fmin_;
        long long c=upper_bound(lens.begin(),lens.end(),hi)-lower_bound(lens.begin(),lens.end(),lo);
        printf("%lld\n",c);
    }
}
