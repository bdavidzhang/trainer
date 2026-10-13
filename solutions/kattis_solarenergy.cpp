#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
struct Ev{ ld x, dA, dB; };
int main(){
    int n; scanf("%d",&n);
    const ld PI=acosl(-1.0L);
    vector<Ev> ev; ev.reserve(9*(size_t)n);
    for(int i=0;i<n;i++){
        double Td,sd,ad; scanf("%lf %lf %lf",&Td,&sd,&ad);
        ld T=Td,s=sd,a=ad;
        bool clipped = !(s>0 && T/s<PI);
        ld w = clipped?PI:T/s;
        for(int k=-1;k<=1;k++){
            ld c=a+2*k*PI, L, R;
            if(clipped){ L=a+(2*k-1)*PI; R=a+(2*k+1)*PI; }
            else { L=c-w; R=c+w; }
            ev.push_back({L, T-s*c, s});
            ev.push_back({c, 2*s*c, -2*s});
            ev.push_back({R, -(T+s*c), s});
        }
    }
    sort(ev.begin(),ev.end(),[](const Ev&p,const Ev&q){return p.x<q.x;});
    ld A=0,B=0,best=0;
    size_t i=0;
    while(i<ev.size()){
        size_t j=i;
        while(j<ev.size() && ev[j].x==ev[i].x){ A+=ev[j].dA; B+=ev[j].dB; j++; }
        ld x=ev[i].x;
        if(x>=-1e-9L && x<=2*PI+1e-9L) best=max(best,A+B*x);
        i=j;
    }
    printf("%.9Lf\n",best);
}
